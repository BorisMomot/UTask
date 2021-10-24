package fakes

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/scope"
	"github.com/sirupsen/logrus"
	tb "gopkg.in/tucnak/telebot.v2"
)

// ------------------------------
type FakeConfig struct {
	MaxMediaSize  int
	MaxMediaCount int
}

func NewFakeConfig() *FakeConfig {
	return &FakeConfig{
		MaxMediaSize:  1,
		MaxMediaCount: 5,
	}
}

func (c *FakeConfig) GetMaxMediaSize() int {
	return 1
}
func (c *FakeConfig) GetMaxMediaCount() int {
	return 3
}

// ------------------------------
type FakeMainMenu struct{
	Activated bool
}

func (m *FakeMainMenu) Name() string {
	return "FakeMainMenu"
}

func (m *FakeMainMenu) Activate(act actor.Actor, txt string, options ...interface{}) (actor.RetCode, error) {
	m.Activated = true
	return actor.RetProcessedOk, nil
}
func NewFakeMenu() *FakeMainMenu {
	return &FakeMainMenu{}
}

// ------------------------------
func NewFakeUser() *tb.User {
	return &tb.User{
		ID:           1,
		FirstName:    "Ivan",
		LastName:     "Ivanov",
		Username:     "iivanov",
		LanguageCode: "ru",
		IsBot:        false,
	}
}

// ------------------------------

type FakeActor struct {
	*actor.DefaultActor
}

func NewFakeActor(scope *scope.Scope, user *tb.User, state actor.State) *FakeActor {
	return &FakeActor{actor.NewDefaultActor(scope, user, state)}
}

// ------------------------------
type FakeBot struct {
	EditedTText string
	SendedText  string
	RepliedText string
	Action      tb.ChatAction
}

func NewFakeBot() *FakeBot {
	return &FakeBot{}
}

func (b *FakeBot) Reply(msg *tb.Message, what interface{}, options ...interface{}) (*tb.Message, error) {
	b.RepliedText = what.(string)
	return &tb.Message{ID: 100}, nil
}
func (b *FakeBot) Edit(msg tb.Editable, what interface{}, options ...interface{}) (*tb.Message, error) {
	b.EditedTText = what.(string)
	return &tb.Message{ID: 100}, nil
}
func (b *FakeBot) Send(to tb.Recipient, what interface{}, options ...interface{}) (*tb.Message, error) {
	b.SendedText = what.(string)
	return &tb.Message{ID: 100}, nil
}
func (b *FakeBot) Respond(c *tb.Callback, resp ...*tb.CallbackResponse) error {
	return nil
}
func (b *FakeBot) Notify(to tb.Recipient, action tb.ChatAction) error {
	b.Action = action
	return nil
}

type TestEnviroument struct {
	Bot   *FakeBot
	Menu  *FakeMainMenu
	Api   *api.FakeApi
	User  *tb.User
	Msg   *tb.Message
	Scope *scope.Scope
}

func NewTestEnviroument() *TestEnviroument {
	log := logrus.New()
	menu := NewFakeMenu()
	bot := NewFakeBot()
	api := api.NewFakeApi()
	conf := NewFakeConfig()
	scope := scope.NewScope(bot, api, conf, log)
	user := NewFakeUser()
	msg := &tb.Message{ID: 100}
	return &TestEnviroument{
		Bot:   bot,
		Menu:  menu,
		Api:   api,
		User:  user,
		Msg:   msg,
		Scope: scope,
	}
}
