package roles

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

type UserCreateState struct {
	actor.DefaultState
}

func (s *UserCreateState) Name() string {
	return "UserCreateState"
}

func NewUserCreateState() actor.State {
	return &UserCreateState{}
}

func (s *UserCreateState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
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
		beg, _ = strconv.Atoi(tmp[0])
		pageSize, _ = strconv.Atoi(tmp[1])
		query = tmp[2]
	}

	if query == "UNUSED" {
		return actor.RetProcessedOk, nil
	} else if query == "BACK" {
		act.ToState(NewUserDefaultState())
		return actor.RetRepeatProcessing, nil
	} else if query == "NEXT" {

	} else if query == "PREV" {
		beg = beg - pageSize
	}

	data, err := act.Scope().Api.Get("/projects/list")
	if err != nil {
		return actor.RetRepeatProcessing, err
	}

	var plist api.ProjectListResponse
	err = json.Unmarshal(data, &plist)
	if err != nil {
		return actor.RetRepeatProcessing, err
	}

	blst := make([]helpers.BtnItem, 0, len(plist.Projects))
	for _, p := range plist.Projects {
		blst = append(blst, helpers.BtnItem{p.Name, fmt.Sprintf("%d", p.Id)})
	}
	_, err = act.Scope().Bot.Edit(cb.Message, "[CREATE]", helpers.NewButtonList(blst, beg, pageSize))
	return actor.RetProcessedOk, err
}
