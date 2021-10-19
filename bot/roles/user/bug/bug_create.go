package bug

import (
	"fmt"
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/menu"
	"github.com/BorisMomot/UTask/bot/roles/user/common"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
	"strings"
)

type CreateBugState struct {
	actor.DefaultState
	mainMenu      menu.Menu
	project       *api.Project
	component     *api.Component
	text          string
	dlg           *tb.Message
	docs          []*tb.Document
	photos        []*tb.Photo
	audios        []*tb.Audio
	voices        []*tb.Voice
	videos        []*tb.Video
	isEditMessage bool
}

func (s *CreateBugState) Name() string {
	return "CreateBugState"
}

func NewCreateBugState(mainMenu menu.Menu) *CreateBugState {
	return &CreateBugState{
		mainMenu: mainMenu,
	}
}

func (s *CreateBugState) OnStart(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	return s.mainMenu.Activate(act, common.TXT_CANCELLED)
}

func (s *CreateBugState) OnExit(act actor.Actor) error {
	s.text = ""
	s.dlg = nil
	s.docs = nil
	s.photos = nil
	s.audios = nil
	s.voices = nil
	s.videos = nil
	s.isEditMessage = false
	return nil
}

func (s *CreateBugState) OnEnter(act actor.Actor) error {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnEnter",
			"state": s.Name(),
		})

	// new
	s.docs = make([]*tb.Document, 0)
	s.photos = make([]*tb.Photo, 0)
	s.audios = make([]*tb.Audio, 0)
	s.voices = make([]*tb.Voice, 0)
	s.videos = make([]*tb.Video, 0)

	ptmp, ok := act.Storage().Get("project")
	if !ok {
		log.Warn("Unknown project")
		return common.ErrInternal
	}
	s.project = ptmp.(*api.Project)

	ctmp, ok := act.Storage().Get("component")
	if !ok {
		log.Infof("Unknown component")
		return common.ErrInternal
	}
	s.component = ctmp.(*api.Component)

	dtmp, ok := act.Storage().Get("dialog")
	if ok {
		s.dlg = dtmp.(*tb.Message)
	}

	return nil
}

func (s *CreateBugState) OnCallback(act actor.Actor, cb *tb.Callback) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnCallback",
			"state": s.Name(),
		})

	query := strings.TrimSpace(cb.Data)
	cb.Data = ""
	log.Traceln("call", query)

	if query == "EDIT" {
		//return s.showDialog(act)
		s.isEditMessage = true
	} else if query == "BACK" {
		return s.showDialog(act)
	} else if query == "OK" {
		return s.showDialog(act)
	} else if query == "CANCEL" {
		return s.mainMenu.Activate(act, common.TXT_CANCELLED)
	}

	log.Infof("create bug for '%s'/'%s' ", s.project.Name, s.component.Name)
	txt := fmt.Sprintf("<b>Проект:</b> %s\n<b>Компонент:</b> %s\n\nВведите описание проблемы..", s.project.Name, s.component.Name)
	dlg, err := act.Scope().Bot.Edit(cb.Message, txt, s.NewBackButton(), tb.ModeHTML)
	if err != nil {
		log.Infof("Send message error: %s", err)
		return actor.RetProcessedOk, err
	}
	act.Storage().Set("dialog", dlg)
	return actor.RetProcessedOk, nil
}

func (s *CreateBugState) NewConfirmKeyboard() *tb.ReplyMarkup {
	keyb := &tb.ReplyMarkup{}
	var rows []tb.Row

	btnEdit := keyb.Data("Редактировать описание", "EDIT")
	btnOk := keyb.Data("OK", "OK")
	btnCancel := keyb.Data("Cancel", "CANCEL")

	rows = append(rows, tb.Row{btnEdit})
	rows = append(rows, tb.Row{btnOk, btnCancel})
	keyb.Inline(rows...)
	return keyb
}

func (s *CreateBugState) NewBackButton() *tb.ReplyMarkup {
	keyb := &tb.ReplyMarkup{}
	var rows []tb.Row

	btnBack := keyb.Data("BACK", "BACK")

	rows = append(rows, tb.Row{btnBack})
	keyb.Inline(rows...)
	return keyb
}

func (s *CreateBugState) showDialog(act actor.Actor) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "showDialog",
			"state": s.Name(),
		})

	var err error
	if s.dlg != nil {
		// reset old dialog
		_, err = act.Scope().Bot.Edit(s.dlg, "...")
		if err != nil {
			log.Warnf("reset dialog error: %s", err)
		}
	}

	txt := fmt.Sprintf("<b>Проект:</b> %s\n<b>Компонент:</b> %s\n<b>Описание:</b>\n%s\n", s.project.Name, s.component.Name, s.text)
	if len(s.docs) > 0 {
		txt += fmt.Sprintf("<b>Docs:</b> %d\n", len(s.docs))
	}
	if len(s.photos) > 0 {
		txt += fmt.Sprintf("<b>Фото:</b> %d\n", len(s.photos))
	}
	if len(s.videos) > 0 {
		txt += fmt.Sprintf("<b>Видео файлов:</b> %d\n", len(s.videos))
	}
	if len(s.audios) > 0 {
		txt += fmt.Sprintf("<b>Аудио файлов:</b> %d\n", len(s.audios))
	}
	if len(s.voices) > 0 {
		txt += fmt.Sprintf("<b>Голосовых сообщений:</b> %d\n", len(s.voices))
	}

	s.dlg, err = act.Scope().Bot.Send(act.User(), txt, s.NewConfirmKeyboard(), tb.ModeHTML)
	if err != nil {
		log.Infof("Send message error: %s", err)
		return actor.RetProcessedOk, err
	}
	act.Storage().Set("dialog", s.dlg)
	return actor.RetProcessedOk, nil
}

func (s *CreateBugState) OnMessage(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnMessage",
			"state": s.Name(),
		})

	log.Trace("on message")

	if !s.isEditMessage && len(s.text) > 0 {
		// send answer
		_, err := act.Scope().Bot.Send(msg.Sender, "Вы уже ввели описание.\nДля редактирования нажмите соответствующую кнопку", tb.ModeHTML)
		if err != nil {
			log.Infof("Send message error: %s", err)
			return actor.RetProcessedOk, err
		}
		return s.showDialog(act)
	}

	s.isEditMessage = false
	s.text = msg.Text
	return s.showDialog(act)
}

func (s *CreateBugState) OnUpload(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnMessage",
			"state": s.Name(),
		})

	log.Trace("on upload")
	if msg.Photo != nil {
		log.Trace("on photo: ", msg.Photo.Caption)
		s.photos = append(s.photos, msg.Photo)
	}
	if msg.Audio != nil {
		log.Trace("on audio: ", msg.Audio.Caption)
		s.audios = append(s.audios, msg.Audio)
	}
	if msg.Video != nil {
		log.Trace("on video: ", msg.Video.Caption)
		s.videos = append(s.videos, msg.Video)
	}
	if msg.Voice != nil {
		log.Trace("on voice: ", msg.Voice.Caption)
		s.voices = append(s.voices, msg.Voice)
	}
	if msg.Document != nil {
		log.Trace("on document: ", msg.Document.Caption)
		s.docs = append(s.docs, msg.Document)
	}
	return s.showDialog(act)
}
