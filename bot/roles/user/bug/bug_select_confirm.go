package bug

import (
	"fmt"
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/helpers"
	"github.com/BorisMomot/UTask/bot/menu"
	"github.com/BorisMomot/UTask/bot/roles/user/common"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
	"strings"
)

type SelectConfirmState struct {
	actor.DefaultState
	mainMenu  menu.Menu
	project   *api.Project
	component *api.Component
}

func (s *SelectConfirmState) Name() string {
	return "SelectConfirmState"
}

func NewSelectConfirmState(mainMenu menu.Menu) *SelectConfirmState {
	return &SelectConfirmState{
		mainMenu: mainMenu,
	}
}

func (s *SelectConfirmState) OnStart(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	return s.mainMenu.Activate(act, common.TXT_CANCELLED)
}

func (s *SelectConfirmState) OnEnter(act actor.Actor) error {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnEnter",
			"state": s.Name(),
		})

	ptmp, ok := act.Storage().Get("project")
	if !ok {
		log.Warn("Unknown project")
		return common.ErrInternal
	}
	s.project = ptmp.(*api.Project)

	ctmp, ok := act.Storage().Get("component")
	if !ok {
		log.Infof("Unknown component")
		return common.ErrInternal
	}
	s.component = ctmp.(*api.Component)
	return nil
}

func (s *SelectConfirmState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnCallback",
			"state": s.Name(),
		})

	query := strings.TrimSpace(cb.Data)
	cb.Data = ""
	log.Tracef("call: project=%s component=%s query=%s", s.project.Name, s.component.Name, query)

	if query == "BACK" {
		act.ToState(NewSelectComponentState(s.mainMenu))
		return actor.RetRepeatProcessing, nil
	} else if query == "CANCEL" {
		return s.mainMenu.Activate(act, common.TXT_CANCELLED)
	} else if query == "OK" {
		act.ToState(NewCreateBugState(s.mainMenu))
		return actor.RetRepeatProcessing, nil
	}

	log.Infof("create bug for '%s'/'%s' ", s.project.Name, s.component.Name)
	txt := fmt.Sprintf("<b>Проект:</b> %s\n<b>Компонент:</b> %s", s.project.Name, s.component.Name)
	dlg, err := act.Scope().Bot.Edit(cb.Message, txt, helpers.NewOkCancelBackButtons(), tb.ModeHTML)
	if err != nil {
		log.Warnln("Send message error: %s", err)
	} else {
		act.Storage().Set("dialog", dlg)
	}

	return actor.RetProcessedOk, err
}
