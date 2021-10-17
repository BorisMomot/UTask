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

type SelectProjectState struct {
	actor.DefaultState
}

func (s *SelectProjectState) Name() string {
	return "SelectProjectState"
}

func NewSelectProjectState() actor.State {
	return &SelectProjectState{}
}

func (s *SelectProjectState) OnStart(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	return toBegin(s, act, msg.Sender, txt_CANCALLED)
}

func (s *SelectProjectState) OnEnter(act actor.Actor) error {
	act.Storage().Delete("projects")
	return nil
}

func (s *SelectProjectState) OnExit(act actor.Actor) error {
	act.Storage().Delete("projects")
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
	pageSize := defaultPageSize

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
		return toBegin(s, act, cb.Message.Sender, txt_CANCALLED)
	} else if query == "NEXT" {

	} else if query == "PREV" {
		beg = beg - pageSize
	} else if len(query) > 0 {
		log.Infof("select project ID=%s", query)
		projects, ok := act.Storage().Get("projects")
		if !ok {
			log.Warn("not found projects list")
			return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
		}

		id, err := strconv.Atoi(query)
		if err != nil {
			log.Warn("Convert project ID error: ", err)
			return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
		}

		prj, ok := api.FindProjectById(projects.([]api.Project), int64(id))
		if !ok {
			log.Warn("not found project ", query)
			return toBegin(s, act, cb.Sender, "")
		}

		cb.Data = ""
		act.Storage().Set("project", prj)
		act.ToState(NewSelectComponentState())
		return actor.RetRepeatProcessing, nil
	}

	data, err := act.Scope().Api.Get("/projects/list")
	if err != nil {
		act.ToState(NewDefaultState())
		return actor.RetProcessedOk, err
	}

	var plist api.ProjectListResponse
	err = json.Unmarshal(data, &plist)
	if err != nil {
		return actor.RetProcessedOk, err
	}

	err = act.Storage().Set("projects", plist.Projects)
	if err != nil {
		log.Warn("save projects list error: ", err)
		return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
	}

	blst := make([]helpers.BtnItem, 0, len(plist.Projects))
	for _, p := range plist.Projects {
		blst = append(blst, helpers.BtnItem{p.Name, fmt.Sprintf("%d", p.Id)})
	}
	dlg, err := act.Scope().Bot.Edit(cb.Message, "Выберите проект..", helpers.NewButtonList(blst, beg, pageSize))
	if dlg != nil {
		act.Storage().Set("dialog", dlg)
	}
	return actor.RetProcessedOk, err
}
