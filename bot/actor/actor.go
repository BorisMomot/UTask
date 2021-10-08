package actor

import (
	"github.com/BorisMomot/UTask/bot/scope"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
)

type RetCode uint32

const (
	RetProcessedOk      = 0
	RetRepeatProcessing = 1
)

type Actor interface {
	Name() string
	StateName() string
	OnStart(msg *tb.Message) (RetCode, error)
	OnMessage(msg *tb.Message) (RetCode, error)
	OnCallback(cb *tb.Callback) (RetCode, error)
	ToState(newState State)
	Log() *logrus.Logger
	Scope() *scope.Scope
}

type BaseActor struct {
	state State
	name  string
	scope *scope.Scope
	user  *tb.User
}

func NewBaseActor(scope *scope.Scope, user *tb.User, state State) *BaseActor {
	return &BaseActor{
		scope: scope,
		state: state,
		user:  user,
	}
}

func (ba *BaseActor) Scope() *scope.Scope {
	return ba.scope
}

func (ba *BaseActor) Log() *logrus.Logger {
	return ba.scope.Log
}

func (ba *BaseActor) Name() string {
	return ba.user.Username
}

func (ba *BaseActor) StateName() string {
	return ba.state.Name()
}

func (ba *BaseActor) OnStart(msg *tb.Message) (RetCode, error) {
	return ba.state.OnStart(ba, msg)
}
func (ba *BaseActor) OnMessage(msg *tb.Message) (RetCode, error) {
	return ba.state.OnMessage(ba, msg)
}

func (ba *BaseActor) OnCallback(cb *tb.Callback) (RetCode, error) {
	return ba.state.OnCallback(ba, cb)
}

func (ba *BaseActor) ToState(newState State) {

	if ba.state == nil {
		ba.state = newState
		err := ba.state.OnEnter(ba)
		if err != nil {
			ba.Scope().Log.WithFields(logrus.Fields{
				"func":  "ToState::OnEnter",
				"state": newState.Name(),
				"actor": ba.Name(),
			}).Errorf("change state error: %s", err)
		}
		return
	}

	if ba.state.Name() == newState.Name() {
		return
	}

	err := ba.state.OnExit(ba)
	if err != nil {
		ba.Scope().Log.WithFields(logrus.Fields{
			"func":  "ToState::OnExit",
			"state": ba.state.Name(),
			"actor": ba.Name(),
		}).Errorf("change state error: %s", err)

		return
	}

	ba.state = newState

	err = ba.state.OnEnter(ba)
	if err != nil {
		ba.Scope().Log.WithFields(logrus.Fields{
			"func":  "ToState::OnEnter",
			"state": newState.Name(),
			"actor": ba.Name(),
		}).Errorf("change state error: %s", err)

		return
	}
}
