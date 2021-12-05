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

func TestSelectComponentState_Enter_Exit(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewSelectComponentState(env.Menu)
	act := fakes.NewFakeActor(env.Scope, env.User, state)
	p := api.Project{2, "P2"}
	act.Storage().Set("project", p)

	err := state.OnEnter(act)
	assert.NoError(t, err)
	assert.Equal(t, 0, len(state.components))

	err = state.OnExit(act)
	assert.NoError(t, err)
	assert.Equal(t, 0, len(state.components))
}

func TestSelectComponentState_SelectComponent(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewSelectComponentState(env.Menu)
	act := fakes.NewFakeActor(env.Scope, env.User, state)

	p := api.Project{2, "P2"}
	act.Storage().Set("project", p)
	err := state.OnEnter(act)
	assert.NoError(t, err)
	assert.Equal(t, 0, len(state.components))

	cb := &tb.Callback{Message: &tb.Message{ID: 1, Text: ""}}
	ret, err := act.OnCallback(cb)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetProcessedOk, ret)

	assert.Equal(t, true, strings.Contains(env.Bot.EditedTText, "Выберите компонент"))

	cb.Data = "1;0;3"
	ret, err = act.OnCallback(cb)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetRepeatProcessing, ret)
	assert.Equal(t, "SelectConfirmState", act.State().Name())
	c, ok := act.Storage().Get("component")
	assert.Equal(t, true, ok)

	component := c.(api.Component)
	assert.Equal(t, int64(1), component.Id)
}
