package bug

import (
	"encoding/json"
	"fmt"
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/helpers"
	"github.com/BorisMomot/UTask/bot/menu"
	"github.com/BorisMomot/UTask/bot/roles/user/common"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
	"strconv"
	"strings"
)

type SelectComponentState struct {
	actor.DefaultState
	mainMenu   menu.Menu
	project    *api.Project
	components []api.Component
}

func (s *SelectComponentState) Name() string {
	return "SelectComponentState"
}

func NewSelectComponentState(mainMenu menu.Menu) *SelectComponentState {
	return &SelectComponentState{
		mainMenu: mainMenu,
	}
}

func (s *SelectComponentState) OnStart(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	return s.mainMenu.Activate(act, common.TXT_CANCELLED)
}

func (s *SelectComponentState) OnEnter(act actor.Actor) error {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnEnter",
			"state": s.Name(),
		})

	act.Storage().Delete("components")
	s.components = make([]api.Component, 0)

	ptmp, ok := act.Storage().Get("project")
	if !ok {
		log.Infof("Unknown project")
		return common.ErrInternal
	}

	s.project = ptmp.(*api.Project)
	return nil
}

func (s *SelectComponentState) OnExit(act actor.Actor) error {
	act.Storage().Delete("components")
	s.components = nil
	return nil
}

func (s *SelectComponentState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnCallback",
			"state": s.Name(),
		})

	query := strings.TrimSpace(cb.Data)
	cb.Data = ""
	beg := 0
	pageSize := common.DEFAULT_PAGE_SIZE

	tmp := strings.Split(query, ";")
	if len(tmp) > 2 {
		query = tmp[0]
		beg, _ = strconv.Atoi(tmp[1])
		pageSize, _ = strconv.Atoi(tmp[2])
	}

	log.Tracef("call: project=%s btn=%s beginPage=%d pageSize=%d", s.project.Name, query, beg, pageSize)

	if query == "UNUSED" {
		return actor.RetProcessedOk, nil
	} else if query == "BACK" {
		act.ToState(NewSelectProjectState(s.mainMenu))
		return actor.RetRepeatProcessing, nil
	} else if query == "NEXT" {

	} else if query == "PREV" {
		beg = beg - pageSize
	} else if len(query) > 0 {
		log.Infof("select project ID=%s", query)
		id, err := strconv.Atoi(query)
		if err != nil {
			log.Warn("Convert component ID error: ", err)
			return s.mainMenu.Activate(act, common.TXT_INTERNAL_ERROR)
		}

		component, ok := api.FindComponentById(s.components, int64(id))
		if !ok {
			log.Warn("not found component ", query)
			return s.mainMenu.Activate(act, common.TXT_INTERNAL_ERROR)
		}

		act.Storage().Set("component", component)
		act.ToState(NewSelectConfirmState(s.mainMenu))
		return actor.RetRepeatProcessing, nil
	}

	act.Scope().Bot.Notify(cb.Message.Chat, tb.Typing)
	data, err := act.Scope().Api.Get(fmt.Sprintf("/projects/components/list?project=%d", s.project.Id))
	if err != nil {
		log.Warn("call api error: ", err)
		return s.mainMenu.Activate(act, common.TXT_INTERNAL_ERROR)
	}

	var clist api.ComponentListResponse
	err = json.Unmarshal(data, &clist)
	if err != nil {
		return actor.RetProcessedOk, err
	}

	s.components = clist.Components
	blst := make([]helpers.BtnItem, 0, len(s.components))
	for _, p := range clist.Components {
		blst = append(blst, helpers.BtnItem{p.Name, fmt.Sprintf("%d", p.Id)})
	}
	txt := fmt.Sprintf("<b>Проект:</b> %s\nВыберите компонент..", s.project.Name)
	dlg, err := act.Scope().Bot.Edit(cb.Message, txt, helpers.NewButtonList(blst, beg, pageSize), tb.ModeHTML)
	if err != nil {
		log.Warnln("send message error: ", err)
	} else {
		act.Storage().Set("dialog", dlg)
	}

	return actor.RetProcessedOk, err
}
