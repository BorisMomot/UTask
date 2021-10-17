package menu

import (
	"github.com/BorisMomot/UTask/bot/actor"
)

type Menu interface {
	Activate(act actor.Actor, txt string) (actor.RetCode, error)
}
