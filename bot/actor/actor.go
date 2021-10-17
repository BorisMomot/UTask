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
	Log() *logrus.Entry
	Scope() *scope.Scope
	Storage() Storage
}

type DefaultActor struct {
	state   State
	name    string
	scope   *scope.Scope
	user    *tb.User
	storage Storage
}

func NewDefaultActor(scope *scope.Scope, user *tb.User, state State) *DefaultActor {
	return &DefaultActor{
		scope:   scope,
		state:   state,
		user:    user,
		storage: NewMemStorage(),
	}
}

func (ba *DefaultActor) Scope() *scope.Scope {
	return ba.scope
}

func (ba *DefaultActor) Log() *logrus.Entry {
	return ba.scope.Log.WithFields(
		logrus.Fields{
			"actor": ba.Name(),
		})
}

func (ba *DefaultActor) Storage() Storage {
	return ba.storage
}

func (ba *DefaultActor) Name() string {
	return ba.user.Username
}

func (ba *DefaultActor) StateName() string {
	return ba.state.Name()
}

func (ba *DefaultActor) OnStart(msg *tb.Message) (RetCode, error) {
	return ba.state.OnStart(ba, msg)
}
func (ba *DefaultActor) OnMessage(msg *tb.Message) (RetCode, error) {
	return ba.state.OnMessage(ba, msg)
}

func (ba *DefaultActor) OnCallback(cb *tb.Callback) (RetCode, error) {
	return ba.state.OnCallback(ba, cb)
}

func (ba *DefaultActor) ToState(newState State) {

	if ba.state == nil {
		ba.state = newState
		err := ba.state.OnEnter(ba)
		if err != nil {
			ba.Log().WithFields(logrus.Fields{
				"func":  "ToState::OnEnter",
				"state": newState.Name(),
			}).Errorf("change state error: %s", err)
		}
		return
	}

	if ba.state.Name() == newState.Name() {
		return
	}

	err := ba.state.OnExit(ba)
	if err != nil {
		ba.Log().WithFields(logrus.Fields{
			"func":  "ToState::OnExit",
			"state": ba.state.Name(),
		}).Errorf("change state error: %s", err)

		return
	}

	ba.state = newState

	err = ba.state.OnEnter(ba)
	if err != nil {
		ba.Log().WithFields(logrus.Fields{
			"func":  "ToState::OnEnter",
			"state": newState.Name(),
		}).Errorf("change state error: %s", err)

		return
	}
}
