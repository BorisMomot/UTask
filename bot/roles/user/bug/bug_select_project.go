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

type SelectProjectState struct {
	actor.DefaultState
	mainMenu menu.Menu
	projects []api.Project
}

func (s *SelectProjectState) Name() string {
	return "SelectProjectState"
}

func NewSelectProjectState(mainMenu menu.Menu) *SelectProjectState {
	return &SelectProjectState{
		mainMenu: mainMenu,
	}
}

func (s *SelectProjectState) OnStart(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	return s.mainMenu.Activate(act, common.TXT_CANCELLED)
}

func (s *SelectProjectState) OnEnter(act actor.Actor) error {
	act.Storage().Delete("projects")
	s.projects = make([]api.Project, 0)
	return nil
}

func (s *SelectProjectState) OnExit(act actor.Actor) error {
	act.Storage().Delete("projects")
	s.projects = nil
	return nil
}

func (s *SelectProjectState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnCallback",
			"state": s.Name(),
		})

	query := strings.TrimSpace(cb.Data)
	beg := 0
	pageSize := common.DEFAULT_PAGE_SIZE
	cb.Data = ""

	tmp := strings.Split(query, ";")
	if len(tmp) > 2 {
		query = tmp[0]
		beg, _ = strconv.Atoi(tmp[1])
		pageSize, _ = strconv.Atoi(tmp[2])
	}

	log.Tracef("call: btn=%s beginPage=%d pageSize=%d", query, beg, pageSize)

	if query == "UNUSED" {
		return actor.RetProcessedOk, nil
	} else if query == "BACK" {
		return s.mainMenu.Activate(act, common.TXT_CANCELLED)
	} else if query == "NEXT" {

	} else if query == "PREV" {
		beg = beg - pageSize
	} else if len(query) > 0 {
		log.Infof("select project ID=%s", query)
		id, err := strconv.Atoi(query)
		if err != nil {
			log.Warn("Convert project ID error: ", err)
			return s.mainMenu.Activate(act, common.TXT_INTERNAL_ERROR)
		}

		prj, ok := api.FindProjectById(s.projects, int64(id))
		if !ok {
			log.Warn("not found project ", query)
			return s.mainMenu.Activate(act, common.TXT_INTERNAL_ERROR)
		}

		act.Storage().Set("project", prj)
		act.ToState(NewSelectComponentState(s.mainMenu))
		return actor.RetRepeatProcessing, nil
	}

	act.Scope().Bot.Notify(cb.Message.Chat, tb.Typing)
	data, err := act.Scope().Api.Get("/projects/list")
	if err != nil {
		log.Warn("call api error: ", err)
		return s.mainMenu.Activate(act, common.TXT_INTERNAL_ERROR)
	}

	var plist api.ProjectListResponse
	err = json.Unmarshal(data, &plist)
	if err != nil {
		return actor.RetProcessedOk, err
	}

	s.projects = plist.Projects
	blst := make([]helpers.BtnItem, 0, len(s.projects))
	for _, p := range plist.Projects {
		blst = append(blst, helpers.BtnItem{p.Name, fmt.Sprintf("%d", p.Id)})
	}
	dlg, err := act.Scope().Bot.Edit(cb.Message, common.TXT_TITLE_CREATE_BUG + "\n---\nВыберите проект..", helpers.NewButtonList(blst, beg, pageSize), tb.ModeHTML)
	if err != nil {
		log.Warnln("send message error: ", err)
	} else {
		act.Storage().Set("dialog", dlg)
	}

	return actor.RetProcessedOk, err
}
