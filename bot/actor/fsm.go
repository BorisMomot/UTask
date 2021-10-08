package actor

import (
	"github.com/BorisMomot/UTask/bot/scope"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
	"strings"
)

type FSM struct {
	scope *scope.Scope
}

func NewFSM(scope *scope.Scope) *FSM {
	return &FSM{
		scope: scope,
	}
}

func (f *FSM) OnMessage(act Actor, msg *tb.Message) error {

	log := f.scope.Log.WithFields(logrus.Fields{
		"actor":  act.Name(),
		"userID": msg.Sender.ID,
		"func":   "OnMessage",
	})

	log.Tracef(msg.Text)

	var fn func(*tb.Message) (RetCode, error)

	if strings.HasPrefix(msg.Text, "/start") {
		fn = act.OnStart
	} else {
		fn = act.OnMessage
	}

	for {
		ret, err := fn(msg)
		if err != nil {
			return err
		}
		if ret != RetRepeatProcessing {
			break
		}
	}

	return nil
}

func (f *FSM) OnCallback(act Actor, cb *tb.Callback) error {

	log := f.scope.Log.WithFields(logrus.Fields{
		"actor":  act.Name(),
		"userID": cb.Sender.ID,
		"func":   "OnCallback",
	})

	log.Traceln(strings.TrimSpace(cb.Data))

	act.Scope().Bot.Respond(cb, &tb.CallbackResponse{
		CallbackID: cb.ID,
	})

	for {
		ret, err := act.OnCallback(cb)
		if err != nil {
			return err
		}
		if ret != RetRepeatProcessing {
			break
		}
	}

	return nil
}
