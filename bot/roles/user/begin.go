package user

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
	"strings"
)

const (
	menu_CREATE = "ch_btn_create"
	menu_LIST   = "ch_btn_list"
)

type DefaultState struct {
	actor.DefaultState
}

func (s *DefaultState) Name() string {
	return "DefaultState"
}

func NewDefaultState() actor.State {
	return &DefaultState{}
}

func (s *DefaultState) MainMenu() *tb.ReplyMarkup {
	menu := &tb.ReplyMarkup{}

	btnCreate := menu.Data("☎️ Сообщить о проблеме", menu_CREATE)
	btnList := menu.Data("🗓 Список задач", menu_LIST)
	menu.Inline(
		menu.Row(btnCreate),
		menu.Row(btnList),
	)
	return menu
}

func (s *DefaultState) showMainMenu(act actor.Actor, usr *tb.User) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "showMainMenu",
			"state": s.Name(),
		})

	var err error
	if tmp, ok := act.Storage().Get("dialog"); ok {
		dlg := tmp.(*tb.Message)
		_, err = act.Scope().Bot.Edit(dlg, txt_USER_MAIN_MENU, s.MainMenu(), tb.ModeHTML)
	} else {
		var dlg *tb.Message
		dlg, err = act.Scope().Bot.Send(usr, txt_USER_MAIN_MENU, s.MainMenu())
		if dlg != nil {
			act.Storage().Set("dialog", dlg)
		}
	}

	if err != nil {
		log.Warnf("update dialog error: %s", err)
	}

	return actor.RetProcessedOk, err
}

func (s *DefaultState) OnStart(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	_, err := act.Scope().Bot.Send(msg.Sender, txt_USER_MAIN_MENU, s.MainMenu())
	return actor.RetProcessedOk, err
}

func (s *DefaultState) OnMessage(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	// FIXME: not realized yet
	_, err := act.Scope().Bot.Send(msg.Sender, "[OK]: "+msg.Text)
	return actor.RetProcessedOk, err
}

func (s *DefaultState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnCallback",
			"state": s.Name(),
		})

	menuItem := strings.TrimSpace(cb.Data)

	log.Traceln("call menu item:", menuItem)

	if menuItem == menu_CREATE {
		cb.Data = ""
		act.ToState(NewSelectProjectState())
		return actor.RetRepeatProcessing, nil
	}

	//if menuItem == menu_LIST {
	//	act.ToState(NewUserListState())
	//	return actor.RetRepeatProcessing, nil
	//}

	return s.showMainMenu(act, cb.Sender)
}
