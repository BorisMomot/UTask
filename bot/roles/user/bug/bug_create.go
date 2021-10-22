package bug

import (
	"fmt"
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/menu"
	"github.com/BorisMomot/UTask/bot/roles/user/common"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
	"strconv"
	"strings"
)

type Media struct {
	msg     *tb.Message
	btn     *tb.Message
	skipped bool
}

func mediaCount(mlist *[]Media) int {
	num := 0
	for _, m := range *mlist {
		if !m.skipped {
			num++
		}
	}

	return num
}

type CreateBugState struct {
	actor.DefaultState
	mainMenu      menu.Menu
	project       api.Project
	component     api.Component
	txtMessage    *tb.Message
	dlg           *tb.Message
	docs          []Media
	photos        []Media
	audios        []Media
	voices        []Media
	videos        []Media
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
	txt := "..обработка завершена.."
	s.completeAllMediaProcessing(act, &s.docs, txt)
	s.completeAllMediaProcessing(act, &s.photos, txt)
	s.completeAllMediaProcessing(act, &s.videos, txt)
	s.completeAllMediaProcessing(act, &s.voices, txt)
	s.completeAllMediaProcessing(act, &s.audios, txt)
	s.txtMessage = nil
	s.dlg = nil
	s.docs = nil
	s.photos = nil
	s.audios = nil
	s.voices = nil
	s.videos = nil
	s.isEditMessage = false
	s.project = api.Project{}
	s.component = api.Component{}
	return nil
}

func (s *CreateBugState) OnEnter(act actor.Actor) error {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnEnter",
			"state": s.Name(),
		})

	// new
	s.docs = make([]Media, 0)
	s.photos = make([]Media, 0)
	s.audios = make([]Media, 0)
	s.voices = make([]Media, 0)
	s.videos = make([]Media, 0)

	ptmp, ok := act.Storage().Get("project")
	if !ok {
		log.Warn("Unknown project")
		return common.ErrInternal
	}
	s.project = ptmp.(api.Project)

	ctmp, ok := act.Storage().Get("component")
	if !ok {
		log.Infof("Unknown component")
		return common.ErrInternal
	}
	s.component = ctmp.(api.Component)

	s.dlg = nil
	dtmp, ok := act.Storage().Get("dialog")
	if ok {
		s.dlg = dtmp.(*tb.Message)
	}

	return nil
}

func (s *CreateBugState) skipMedia(act actor.Actor, mlist *[]Media, id int) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "skipMedia",
			"state": s.Name(),
		})

	for i, m := range *mlist {
		if m.msg.ID == id {
			log.Traceln("skip message ID", id)
			m.skipped = true
			if m.btn != nil {
				m.btn, _ = act.Scope().Bot.Edit(m.btn, "Исключено из описания\n<i>Вы можете добавить заново, нажав кнопку 'Добавить'</i>", s.NewAddButton(m.msg), tb.ModeHTML)
			}
			(*mlist)[i] = m // update
			continue
		}
	}
}

func (s *CreateBugState) updateMedia(act actor.Actor, mlist *[]Media, id int) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "updateMedia",
			"state": s.Name(),
		})

	for i, m := range *mlist {
		if m.msg.ID == id {
			log.Traceln("re-adding message ID", id)
			m.skipped = false
			if m.btn == nil {
				m.btn, _ = act.Scope().Bot.Reply(m.msg, s.mediaToText(m.msg), s.NewSkipButton(m.msg), tb.ModeHTML)
			} else {
				m.btn, _ = act.Scope().Bot.Edit(m.btn, s.mediaToText(m.msg), s.NewSkipButton(m.msg), tb.ModeHTML)
			}
			(*mlist)[i] = m // update
			continue
		}
	}
}

func (s *CreateBugState) completeAllMediaProcessing(act actor.Actor, mlist *[]Media, txt string) {
	for _, m := range *mlist {
		if m.btn != nil {
			m.btn, _ = act.Scope().Bot.Edit(m.btn, txt, tb.ModeHTML)
		}
	}
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

	if strings.HasPrefix(query, "SKIP") {
		tmp := strings.Split(query, ";")
		if len(tmp) > 1 {
			msgID, err := strconv.Atoi(tmp[1])
			if err != nil {
				log.Warn("skip button error: ", err)
				return s.showDialog(act)
			}
			log.Traceln("skip message ID", msgID)
			s.skipMedia(act, &s.audios, msgID)
			s.skipMedia(act, &s.videos, msgID)
			s.skipMedia(act, &s.photos, msgID)
			s.skipMedia(act, &s.docs, msgID)
			s.skipMedia(act, &s.voices, msgID)
		}
		return s.showDialog(act)
	}
	if strings.HasPrefix(query, "ADD") {
		tmp := strings.Split(query, ";")
		if len(tmp) > 1 {
			msgID, err := strconv.Atoi(tmp[1])
			if err != nil {
				log.Warn("add button error: ", err)
				return s.showDialog(act)
			}
			log.Traceln("update message ID", msgID)
			s.updateMedia(act, &s.audios, msgID)
			s.updateMedia(act, &s.videos, msgID)
			s.updateMedia(act, &s.photos, msgID)
			s.updateMedia(act, &s.docs, msgID)
			s.updateMedia(act, &s.voices, msgID)
		}
		return s.showDialog(act)
	}

	if strings.HasPrefix(query, "DEL_") {
		switch query {
		case "DEL_DOCS":
			s.docs = nil
		case "DEL_PHOTOS":
			s.photos = nil
		case "DEL_VIDEOS":
			s.videos = nil
		case "DEL_VOICES":
			s.voices = nil
		case "DEL_AUDIOS":
			s.audios = nil
		}
		return s.showDialog(act)
	}

	if query == "EDIT" {
		s.isEditMessage = true
	} else if query == "BACK" {
		return s.showDialog(act)
	} else if query == "OK" {
		return s.showDialog(act)
	} else if query == "CANCEL" {
		return s.mainMenu.Activate(act, common.TXT_CANCELLED)
	}

	log.Infof("create bug for '%s'/'%s' ", s.project.Name, s.component.Name)
	txt := fmt.Sprintf("%s\n\n<b>Проект:</b> %s\n<b>Компонент:</b> %s\n\nВведите описание проблемы..", common.TXT_TITLE_CREATE_BUG, s.project.Name, s.component.Name)
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
	if len(s.docs) > 0 {
		rows = append(rows, tb.Row{keyb.Data("Исключить документы", "DEL_DOCS")})
	}
	if len(s.photos) > 0 {
		rows = append(rows, tb.Row{keyb.Data("Исключить фотографии", "DEL_PHOTOS")})
	}
	if len(s.videos) > 0 {
		rows = append(rows, tb.Row{keyb.Data("Исключить видео", "DEL_VIDEOS")})
	}
	if len(s.audios) > 0 {
		rows = append(rows, tb.Row{keyb.Data("Исключить аудио", "DEL_AUDIOS")})
	}
	if len(s.voices) > 0 {
		rows = append(rows, tb.Row{keyb.Data("Исключить голосовые сообщения", "DEL_VOICES")})
	}

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

func (s *CreateBugState) NewSkipButton(msg *tb.Message) *tb.ReplyMarkup {
	keyb := &tb.ReplyMarkup{}
	var rows []tb.Row

	btnSkip := keyb.Data("Исключить", fmt.Sprintf("SKIP;%d", msg.ID))
	rows = append(rows, tb.Row{btnSkip})
	keyb.Inline(rows...)
	return keyb
}

func (s *CreateBugState) NewAddButton(msg *tb.Message) *tb.ReplyMarkup {
	keyb := &tb.ReplyMarkup{}
	var rows []tb.Row

	btnAdd := keyb.Data("Добавить", fmt.Sprintf("ADD;%d", msg.ID))
	rows = append(rows, tb.Row{btnAdd})
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
		_, err = act.Scope().Bot.Edit(s.dlg, "♨ updated..")
		if err != nil {
			log.Warnf("reset dialog error: %s", err)
		}
	}

	desc := ""
	if s.txtMessage != nil {
		desc = s.txtMessage.Text
	}
	txt := fmt.Sprintf("%s\n\n<b>Проект:</b> %s\n<b>Компонент:</b> %s\n<b>Описание:</b>\n%s\n", common.TXT_TITLE_CREATE_BUG, s.project.Name, s.component.Name, desc)
	if mediaCount(&s.docs) > 0 {
		txt += fmt.Sprintf("<b>Docs:</b> %d\n", len(s.docs))
	}
	if mediaCount(&s.photos) > 0 {
		txt += fmt.Sprintf("<b>Фото:</b> %d\n", len(s.photos))
	}
	if mediaCount(&s.videos) > 0 {
		txt += fmt.Sprintf("<b>Видео файлов:</b> %d\n", len(s.videos))
	}
	if mediaCount(&s.audios) > 0 {
		txt += fmt.Sprintf("<b>Аудио файлов:</b> %d\n", len(s.audios))
	}
	if mediaCount(&s.voices) > 0 {
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

	if !s.isEditMessage && s.txtMessage != nil {
		// send answer
		_, err := act.Scope().Bot.Send(msg.Sender, "Вы уже ввели описание.\nДля редактирования нажмите соответствующую кнопку или отредактируйте старое сообщение", tb.ModeHTML)
		if err != nil {
			log.Infof("Send message error: %s", err)
			return actor.RetProcessedOk, err
		}
		return s.showDialog(act)
	}

	s.isEditMessage = false
	s.txtMessage = msg
	return s.showDialog(act)
}

func (s *CreateBugState) OnUpload(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnUpload",
			"state": s.Name(),
		})

	log.Trace("on upload")
	media := Media{msg, nil, false}
	if msg.Photo != nil {
		log.Trace("on photo: ", msg.Photo.Caption)
		s.photos = append(s.photos, media)
		s.updateMedia(act, &s.photos, msg.ID)
		act.Scope().Bot.Send(msg.Sender, "♨ updated..")
	}
	if msg.Audio != nil {
		log.Trace("on audio: ", msg.Audio.Caption)
		s.audios = append(s.audios, media)
		s.updateMedia(act, &s.audios, msg.ID)
		act.Scope().Bot.Send(msg.Sender, "♨ updated..")
	}
	if msg.Video != nil {
		log.Trace("on video: ", msg)
		s.videos = append(s.videos, media)
		s.updateMedia(act, &s.videos, msg.ID)
		act.Scope().Bot.Send(msg.Sender, "♨ updated..")
	}
	if msg.Voice != nil {
		log.Trace("on voice: ", msg.Voice.Caption)
		s.voices = append(s.voices, media)
		s.updateMedia(act, &s.voices, msg.ID)
		act.Scope().Bot.Send(msg.Sender, "♨ updated..")
	}
	if msg.Document != nil {
		log.Trace("on document: ", msg.Document.Caption)
		s.docs = append(s.docs, media)
		s.updateMedia(act, &s.docs, msg.ID)
		act.Scope().Bot.Send(msg.Sender, "♨ updated..")
	}
	return s.showDialog(act)
}

func (s *CreateBugState) mediaToText(msg *tb.Message) string {

	txtHelp := "<i>Вы можете исключить его нажав кнопку 'Исключить'</i>"
	if msg.Photo != nil {
		return "Фото добавлено к описанию.\n" + txtHelp
	}

	if msg.Audio != nil {
		return "Аудиофайл добавлен к описанию.\n" + txtHelp
	}

	if msg.Video != nil {
		return "Видео добавлено к описанию.\n" + txtHelp
	}

	if msg.Voice != nil {
		return "Голосовое сообщение добавлено к описанию.\n" + txtHelp
	}

	if msg.Document != nil {
		return "Документ добавлен к описанию.\n" + txtHelp
	}

	return ""
}

func (s *CreateBugState) OnEdited(act actor.Actor, msg *tb.Message) (actor.RetCode, error) {
	log := act.Log().WithFields(
		logrus.Fields{
			"func":  "OnEdited",
			"state": s.Name(),
		})

	log.Traceln("on edited message")
	s.txtMessage = msg
	return s.showDialog(act)
}
