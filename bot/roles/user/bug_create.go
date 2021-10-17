package user

import (
	"fmt"
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

func (s *CreateBugState) OnStart(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	return toBegin(s, act, msg.Sender, txt_CANCALLED)
}

func (s *CreateBugState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnCallback",
			"state": s.Name(),
		})

	ptmp, ok := act.Storage().Get("project")
	if !ok {
		log.Warn("Unknown project")
		return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
	}
	project := ptmp.(*api.Project)

	ctmp, ok := act.Storage().Get("component")
	if !ok {
		log.Infof("Unknown component")
		return toBegin(s, act, cb.Sender, txt_INTERNAL_ERROR)
	}
	component := ctmp.(*api.Component)

	log.Infof("create bug for '%s'/'%s' ", project.Name, component.Name)
	txt := fmt.Sprintf("<b>Проект:</b> %s\n<b>Компонент:</b> %s\n\nВведите описание проблемы..", project.Name, component.Name)
	_, err := act.Scope().Bot.Edit(cb.Message, txt, tb.ModeHTML)
	if err != nil {
		log.Infof("Send message error: %s", err)
		return actor.RetProcessedOk, err
	}

	return actor.RetProcessedOk, nil
}
