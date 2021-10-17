package user

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/scope"
	tb "gopkg.in/tucnak/telebot.v2"
)

type User struct {
	*actor.DefaultActor
}

func NewUser(scope *scope.Scope, user *tb.User) actor.Actor {
	return &User{actor.NewDefaultActor(scope, user, NewDefaultState())}
}

func (u *User) Name() string {
	return "(user)" + u.DefaultActor.Name()
}
