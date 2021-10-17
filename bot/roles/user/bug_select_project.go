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

const (
	defaultPageSize = 2
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
	act.Storage().Delete("projects")
	return actor.RetProcessedOk, nil
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

	log.Tracef("call: %s", query)
	tmp := strings.Split(query, ";")
	if len(tmp) > 2 {
		query = tmp[0]
		beg, _ = strconv.Atoi(tmp[1])
		pageSize, _ = strconv.Atoi(tmp[2])
	}

	if query == "UNUSED" {
		return actor.RetProcessedOk, nil
	} else if query == "BACK" {
		act.ToState(NewDefaultState())
		return actor.RetRepeatProcessing, nil
	} else if query == "NEXT" {

	} else if query == "PREV" {
		beg = beg - pageSize
	} else if len(query) > 0 {
		log.Infof("select %s", query)
		projects, ok := act.Storage().Get("projects")
		if !ok {
			log.Warn("not found projects list")
			act.ToState(NewDefaultState())
			return actor.RetProcessedOk, nil
		}

		id, err := strconv.Atoi(query)
		if err != nil {
			log.Warn("Convert project ID error: ", err)
			act.ToState(NewDefaultState())
			return actor.RetProcessedOk, err
		}

		prj, ok := api.FindProjectById(projects.([]api.Project), int64(id))
		if !ok {
			log.Warn("not found project ", query)
			act.ToState(NewDefaultState())
			return actor.RetProcessedOk, nil
		}

		act.Storage().Delete("projects")
		act.Storage().Set("project", prj)
		act.ToState(NewCreateBugState())
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
		act.ToState(NewDefaultState())
		return actor.RetProcessedOk, err
	}

	blst := make([]helpers.BtnItem, 0, len(plist.Projects))
	for _, p := range plist.Projects {
		blst = append(blst, helpers.BtnItem{p.Name, fmt.Sprintf("%d", p.Id)})
	}
	_, err = act.Scope().Bot.Edit(cb.Message, "Выберите проект", helpers.NewButtonList(blst, beg, pageSize))
	return actor.RetProcessedOk, err
}
