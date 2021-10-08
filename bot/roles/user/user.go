package roles

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/scope"
	tb "gopkg.in/tucnak/telebot.v2"
)

type User struct {
	*actor.BaseActor
}

func NewUser(scope *scope.Scope, user *tb.User) actor.Actor {
	return &User{actor.NewBaseActor(scope, user, NewUserDefaultState())}
}
func (u *User) Name() string {
	return "(user)" + u.BaseActor.Name()
}
