package user

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
)

const (
	DEFAULT_PAGE_SIZE  = 6
	TXT_INTERNAL_ERROR = "Внутренняя ошибка. Пожалуйста попробуйте ещё раз или сообщите о проблеме"
	TXT_CANCALLED      = "отменён.."
	TXT_USER_MAIN_MENU = "❊❊❊ Menu ❊❊❊"
)

func ToMainMenu(state actor.State, act actor.Actor, usr *tb.User, txt string) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "ToMainMenu",
			"state": state.Name(),
		})

	act.ToState(NewMainMenuState())

	if tmp, ok := act.Storage().Get("dialog"); ok {
		dlg := tmp.(*tb.Message)
		_, err := act.Scope().Bot.Edit(dlg, txt, tb.ModeHTML)
		if err != nil {
			log.Warnf("reset dialog error: %s", err)
		}
		act.Storage().Delete("dialog")
	} else {
		if txt != "" {
			_, err := act.Scope().Bot.Send(usr, txt)
			if err != nil {
				log.Warnf("send text error: %s", err)
			}
		}
	}
	return actor.RetRepeatProcessing, nil
}
