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

func TestSelectProjectState_Enter_Exit(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewSelectProjectState(env.Menu)
	act := fakes.NewFakeActor(env.Scope, env.User, state)

	err := state.OnEnter(act)
	assert.NoError(t, err)
	assert.Equal(t, 0, len(state.projects))

	err = state.OnExit(act)
	assert.NoError(t, err)
	assert.Equal(t, 0, len(state.projects))
}

func TestSelectProjectState_SelectProject(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewSelectProjectState(env.Menu)
	act := fakes.NewFakeActor(env.Scope, env.User, state)

	err := state.OnEnter(act)
	assert.NoError(t, err)
	assert.Equal(t, 0, len(state.projects))

	cb := &tb.Callback{Message: &tb.Message{ID: 1, Text: ""}}
	ret, err := act.OnCallback(cb)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetProcessedOk, ret)

	assert.Equal(t, true, strings.Contains(env.Bot.EditedTText, "Выберите проект"))

	cb.Data = "1;0;3"
	ret, err = act.OnCallback(cb)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetRepeatProcessing, ret)
	assert.Equal(t, "SelectComponentState", act.State().Name())
	p, ok := act.Storage().Get("project")
	assert.Equal(t, true, ok)

	project := p.(api.Project)
	assert.Equal(t, int64(1), project.Id)
}
