package scope

import (
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
)

type Scope struct {
	Log *logrus.Logger
	Bot *tb.Bot
	Api api.Api
}

func NewScope(bot *tb.Bot, api api.Api, log *logrus.Logger) *Scope {
	return &Scope{
		Log: log,
		Bot: bot,
		Api: api,
	}
}
