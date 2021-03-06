package user

import (
	"encoding/json"
	"fmt"
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/helpers"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
	"strconv"
	"strings"
)

type SelectComponentState struct {
	actor.DefaultState
}

func (s *SelectComponentState) Name() string {
	return "SelectComponentState"
}

func NewSelectComponentState() actor.State {
	return &SelectComponentState{}
}

func (s *SelectComponentState) OnStart(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	return toBegin(s, act, msg.Sender, txt_CANCALLED)
}

func (s *SelectComponentState) OnEnter(act actor.Actor) error {
	act.Storage().Delete("components")
	return nil
}

func (s *SelectComponentState) OnExit(act actor.Actor) error {
	act.Storage().Delete("components")
	return nil
}

func (s *SelectComponentState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnCallback",
			"state": s.Name(),
		})

	ptmp, ok := act.Storage().Get("project")
	if !ok {
		log.Infof("Unknown project")
		return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
	}
	project := ptmp.(*api.Project)

	query := strings.TrimSpace(cb.Data)
	cb.Data = ""
	beg := 0
	pageSize := defaultPageSize

	tmp := strings.Split(query, ";")
	if len(tmp) > 2 {
		query = tmp[0]
		beg, _ = strconv.Atoi(tmp[1])
		pageSize, _ = strconv.Atoi(tmp[2])
	}

	log.Tracef("call: project=%s btn=%s beginPage=%d pageSize=%d", project.Name, query, beg, pageSize)

	if query == "UNUSED" {
		return actor.RetProcessedOk, nil
	} else if query == "BACK" {
		act.ToState(NewSelectProjectState())
		return actor.RetRepeatProcessing, nil
	} else if query == "NEXT" {

	} else if query == "PREV" {
		beg = beg - pageSize
	} else if len(query) > 0 {
		log.Infof("select project ID=%s", query)
		components, ok := act.Storage().Get("components")
		if !ok {
			log.Warn("not found components list")
			return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
		}

		id, err := strconv.Atoi(query)
		if err != nil {
			log.Warn("Convert component ID error: ", err)
			return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
		}

		component, ok := api.FindComponentById(components.([]api.Component), int64(id))
		if !ok {
			log.Warn("not found component ", query)
			return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
		}

		act.Storage().Set("component", component)
		act.ToState(NewSelectConfirmState())
		return actor.RetRepeatProcessing, nil
	}

	data, err := act.Scope().Api.Get(fmt.Sprintf("/projects/components/list?project=%d", project.Id))
	if err != nil {
		act.ToState(NewDefaultState())
		return actor.RetProcessedOk, err
	}

	var clist api.ComponentListResponse
	err = json.Unmarshal(data, &clist)
	if err != nil {
		return actor.RetProcessedOk, err
	}

	err = act.Storage().Set("components", clist.Components)
	if err != nil {
		log.Warn("save components list error: ", err)
		return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
	}

	blst := make([]helpers.BtnItem, 0, len(clist.Components))
	for _, p := range clist.Components {
		blst = append(blst, helpers.BtnItem{p.Name, fmt.Sprintf("%d", p.Id)})
	}
	txt := fmt.Sprintf("<b>????????????:</b> %s\n???????????????? ??????????????????..", project.Name)
	dlg, err := act.Scope().Bot.Edit(cb.Message, txt, helpers.NewButtonList(blst, beg, pageSize), tb.ModeHTML)
	if dlg != nil {
		act.Storage().Set("dialog", dlg)
	}

	return actor.RetProcessedOk, err
}
