package actor

import tb "gopkg.in/tucnak/telebot.v2"

type State interface {
	Name() string
	OnStart(act Actor, msg *tb.Message) (RetCode, error)
	OnMessage(act Actor, msg *tb.Message) (RetCode, error)
	OnCallback(act Actor, cb *tb.Callback) (RetCode, error)
	OnUpload(act Actor, msg *tb.Message) (RetCode, error)
	OnExit(act Actor) error
	OnEnter(act Actor) error
}

type DefaultState struct {
}

func (s *DefaultState) OnStart(act Actor, msg *tb.Message) (RetCode, error) {
	return RetProcessedOk, nil
}
func (s *DefaultState) OnMessage(act Actor, msg *tb.Message) (RetCode, error) {
	return RetProcessedOk, nil
}
func (s *DefaultState) OnExit(act Actor) error {
	return nil
}
func (s *DefaultState) OnEnter(act Actor) error {
	return nil
}
func (s *DefaultState) OnCallback(act Actor, cb *tb.Callback) (RetCode, error) {
	return RetProcessedOk, nil
}
func (s *DefaultState) OnUpload(act Actor, msg *tb.Message) (RetCode, error) {
	return RetProcessedOk, nil
}
