package bug

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/fakes"
	"github.com/stretchr/testify/assert"
	tb "gopkg.in/tucnak/telebot.v2"
	"testing"
)

func TestSelectConfirmState_Enter_Exit(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewSelectConfirmState(env.Menu)
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
	assert.Equal(t, p, state.project)
	assert.Equal(t, c, state.component)
}

func TestSelectConfirmState_OK(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewSelectConfirmState(env.Menu)
	p := api.Project{Id: 1, Name: "P1"}
	c := api.Component{Id: 1, Name: "C1"}
	act := fakes.NewFakeActor(env.Scope, env.User, state)
	act.Storage().Set("project", p)
	act.Storage().Set("component", c)

	err := state.OnEnter(act)
	assert.NoError(t, err)
	assert.Equal(t, p, state.project)
	assert.Equal(t, c, state.component)

	cb := &tb.Callback{Message: &tb.Message{ID: 1, Text: "OK"}, Data: "OK"}
	ret, err := act.OnCallback(cb)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetRepeatProcessing, ret)
	assert.Equal(t, "CreateBugState", act.State().Name())
	ptmp, ok := act.Storage().Get("project")
	assert.Equal(t, true, ok)
	project := ptmp.(api.Project)
	assert.Equal(t, int64(1), project.Id)
}

func TestSelectConfirmState_BACK(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewSelectConfirmState(env.Menu)
	p := api.Project{Id: 1, Name: "P1"}
	c := api.Component{Id: 1, Name: "C1"}
	act := fakes.NewFakeActor(env.Scope, env.User, state)
	act.Storage().Set("project", p)
	act.Storage().Set("component", c)

	err := state.OnEnter(act)
	assert.NoError(t, err)
	assert.Equal(t, p, state.project)
	assert.Equal(t, c, state.component)

	cb := &tb.Callback{Message: &tb.Message{ID: 1, Text: "BACK"}, Data: "BACK"}
	ret, err := act.OnCallback(cb)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetRepeatProcessing, ret)
	assert.Equal(t, "SelectComponentState", act.State().Name())
}

func TestSelectConfirmState_CANCEL(t *testing.T) {
	env := fakes.NewTestEnviroument()
	state := NewSelectConfirmState(env.Menu)
	p := api.Project{Id: 1, Name: "P1"}
	c := api.Component{Id: 1, Name: "C1"}
	act := fakes.NewFakeActor(env.Scope, env.User, state)
	act.Storage().Set("project", p)
	act.Storage().Set("component", c)

	err := state.OnEnter(act)
	assert.NoError(t, err)
	assert.Equal(t, p, state.project)
	assert.Equal(t, c, state.component)

	env.Menu.Activated = true
	cb := &tb.Callback{Message: &tb.Message{ID: 1, Text: "Cancel"}, Data: "CANCEL"}
	ret, err := act.OnCallback(cb)
	assert.NoError(t, err)
	assert.Equal(t, actor.RetProcessedOk, ret)
	assert.Equal(t, true, env.Menu.Activated)
}
