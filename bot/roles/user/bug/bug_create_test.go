package bug

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/fakes"
	"github.com/stretchr/testify/assert"
	tb "gopkg.in/tucnak/telebot.v2"
	"strings"
	"testing"
)

func TestCreateBugState_Enter_Exit(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewCreateBugState(env.Menu)
	p := api.Project{Id: 1, Name: "P1"}
	c := api.Component{Id: 1, Name: "C1"}
	act := fakes.NewFakeActor(env.Scope, env.User, state)
	act.Storage().Set("project", p)
	act.Storage().Set("component", c)

	err := state.OnEnter(act)
	assert.NoError(t, err)
	assert.Equal(t, p, state.project)
	assert.Equal(t, c, state.component)

	err = state.OnExit(act)
	assert.NoError(t, err)
	assert.Equal(t, api.Project{}, state.project)
	assert.Equal(t, api.Component{}, state.component)
}

func TestCreateBugState_Description(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewCreateBugState(env.Menu)
	p := api.Project{Id: 1, Name: "P1"}
	c := api.Component{Id: 1, Name: "C1"}
	act := fakes.NewFakeActor(env.Scope, env.User, state)
	act.Storage().Set("project", p)
	act.Storage().Set("component", c)

	msg := &tb.Message{ID: 1, Text: "description text"}
	ret, err := act.OnMessage(msg)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetProcessedOk, ret)
	assert.Equal(t, msg, state.txtMessage)
	assert.Equal(t, true, strings.Contains(state.txtMessage.Text, "description text"))

	// edit
	cb := &tb.Callback{Message: &tb.Message{ID: 1, Text: ""}, Data: "EDIT"}
	ret, err = act.OnCallback(cb)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetProcessedOk, ret)
	assert.Equal(t, true, strings.Contains(env.Bot.EditedTText, "Введите описание проблемы"))

	emsg := &tb.Message{ID: 2, Text: "new description text"}
	ret, err = act.OnEdited(emsg)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetProcessedOk, ret)
	assert.Equal(t, true, strings.Contains(state.txtMessage.Text, "new description text"))
}
