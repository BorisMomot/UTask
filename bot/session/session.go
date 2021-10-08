package session

import (
	"github.com/BorisMomot/UTask/bot/actor"
	"github.com/BorisMomot/UTask/bot/roles/user"
	"github.com/BorisMomot/UTask/bot/scope"
	tb "gopkg.in/tucnak/telebot.v2"
	"sync"
)

type SessionManager struct {
	scope    *scope.Scope
	sessions map[int]actor.Actor
	mut      sync.RWMutex
}

func NewSessionManager(scope *scope.Scope) *SessionManager {
	return &SessionManager{
		scope:    scope,
		sessions: make(map[int]actor.Actor, 0),
	}
}

func (s *SessionManager) Restore(user *tb.User) (actor.Actor, error) {
	s.mut.RLock()
	if a, ok := s.sessions[user.ID]; ok {
		s.mut.RUnlock()
		return a, nil
	}
	s.mut.RUnlock()

	act := roles.NewUser(s.scope, user)

	s.mut.Lock()
	defer s.mut.Unlock()
	s.sessions[user.ID] = act
	return act, nil
}
