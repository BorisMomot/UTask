package bug

import (
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/fakes"
	"github.com/stretchr/testify/assert"
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

func TestSelectConfirmState_SelectProject(t *testing.T) {
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

	//cb := &tb.Callback{Message: &tb.Message{ID: 1, Text: ""}}
	//ret, err := act.OnCallback(cb)
	//assert.NoError(t, err)
	//assert.Equal(t, actor.RetProcessedOk, ret)
	//
	//assert.Equal(t, true, strings.Contains(env.Bot.EditedTText, "Выберите проект"))
	//
	//cb.Data = "1;0;3"
	//ret, err = act.OnCallback(cb)
	//assert.NoError(t, err)
	//assert.Equal(t, actor.RetRepeatProcessing, ret)
	//assert.Equal(t, "SelectComponentState", act.State().Name())
	//p, ok := act.Storage().Get("project")
	//assert.Equal(t, true, ok)
	//
	//project := p.(api.Project)
	//assert.Equal(t, int64(1), project.Id)
}
