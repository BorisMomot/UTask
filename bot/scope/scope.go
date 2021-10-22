package scope

import (
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
)

type Bot interface {
	Reply(msg *tb.Message, what interface{}, options ...interface{}) (*tb.Message, error)
	Edit(msg tb.Editable, what interface{}, options ...interface{}) (*tb.Message, error)
	Send(to tb.Recipient, what interface{}, options ...interface{}) (*tb.Message, error)
	Respond(c *tb.Callback, resp ...*tb.CallbackResponse) error
	Notify(to tb.Recipient, action tb.ChatAction) error
}

type Scope struct {
	Log *logrus.Logger
	Bot Bot
	Api api.Api
}

func NewScope(bot Bot, api api.Api, log *logrus.Logger) *Scope {
	return &Scope{
		Log: log,
		Bot: bot,
		Api: api,
	}
}
