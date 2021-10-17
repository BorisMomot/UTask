package user

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
)

type CreateBugState struct {
	actor.DefaultState
}

func (s *CreateBugState) Name() string {
	return "CreateBugState"
}

func NewCreateBugState() actor.State {
	return &CreateBugState{}
}

func (s *CreateBugState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func": "OnCallback",
			"state": s.Name(),
		})

	tmp, ok := act.Storage().Get("project")
	if !ok {
		log.Warn("Unknown project")
		act.ToState(NewSelectProjectState())
		return actor.RetProcessedOk, nil
	}
	project := tmp.(*api.Project)

	log.Infof("create bug for '%s'", project.Name)
	return actor.RetProcessedOk, nil
}
