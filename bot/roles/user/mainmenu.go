package user

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/roles/user/bug"
	"github.com/BorisMomot/UTask/bot/roles/user/common"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
	"strings"
)

const (
	menu_CREATE = "ch_btn_create"
	menu_LIST   = "ch_btn_list"
)

type MainMenuState struct {
	actor.DefaultState
}

func (s *MainMenuState) Name() string {
	return "MainMenuState"
}

func NewMainMenuState() *MainMenuState {
	return &MainMenuState{}
}

func (s *MainMenuState) Activate(act actor.Actor, txt string) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "ToMainMenu",
			"state": act.State().Name(),
		})

	act.ToState(s)

	if tmp, ok := act.Storage().Get("dialog"); ok {
		dlg := tmp.(*tb.Message)
		_, err := act.Scope().Bot.Edit(dlg, txt, tb.ModeHTML)
		if err != nil {
			log.Warnf("reset dialog error: %s", err)
		}
		act.Storage().Delete("dialog")
	} else {
		if txt != "" {
			_, err := act.Scope().Bot.Send(act.User(), txt)
			if err != nil {
				log.Warnf("send text error: %s", err)
			}
		}
	}
	return actor.RetRepeatProcessing, nil
}

func (s *MainMenuState) mainMenu() *tb.ReplyMarkup {
	menu := &tb.ReplyMarkup{}

	btnCreate := menu.Data("☎️ Сообщить о проблеме", menu_CREATE)
	btnList := menu.Data("🗓 Список задач", menu_LIST)
	menu.Inline(
		menu.Row(btnCreate),
		menu.Row(btnList),
	)
	return menu
}

func (s *MainMenuState) showMainMenu(act actor.Actor) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "showMainMenu",
			"state": s.Name(),
		})

	var err error
	if tmp, ok := act.Storage().Get("dialog"); ok {
		dlg := tmp.(*tb.Message)
		_, err = act.Scope().Bot.Edit(dlg, common.TXT_USER_MAIN_MENU, s.mainMenu(), tb.ModeHTML)
	} else {
		var dlg *tb.Message
		dlg, err = act.Scope().Bot.Send(act.User(), common.TXT_USER_MAIN_MENU, s.mainMenu())
		if dlg != nil {
			act.Storage().Set("dialog", dlg)
		}
	}

	if err != nil {
		log.Warnf("update dialog error: %s", err)
	}

	return actor.RetProcessedOk, err
}

func (s *MainMenuState) OnStart(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	_, err := act.Scope().Bot.Send(msg.Sender, common.TXT_USER_MAIN_MENU, s.mainMenu())
	return actor.RetProcessedOk, err
}

func (s *MainMenuState) OnMessage(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	// FIXME: not realized yet
	_, err := act.Scope().Bot.Send(msg.Sender, "[OK]: "+msg.Text)
	return actor.RetProcessedOk, err
}

func (s *MainMenuState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnCallback",
			"state": s.Name(),
		})

	menuItem := strings.TrimSpace(cb.Data)

	log.Traceln("call menu item:", menuItem)

	if menuItem == menu_CREATE {
		cb.Data = ""
		act.ToState(bug.NewSelectProjectState(s))
		return actor.RetRepeatProcessing, nil
	}

	//if menuItem == menu_LIST {
	//	act.ToState(NewUserListState())
	//	return actor.RetRepeatProcessing, nil
	//}

	return s.showMainMenu(act)
}