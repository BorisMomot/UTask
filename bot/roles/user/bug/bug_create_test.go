package bug

import (
	"github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/fakes"
	"github.com/stretchr/testify/assert"
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
