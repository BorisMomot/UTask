package actor

type Storage interface {
	Get(key string) (interface{}, bool)
	Set(key string, val interface{}) error
	Delete(key string)
}

type MemStorage struct {
	storage map[string]interface{}
}

func NewMemStorage() Storage {
	return &MemStorage{
		storage: make(map[string]interface{}),
	}
}

func (s *MemStorage) Set(key string, val interface{}) error {
	s.storage[key] = val
	return nil
}

func (s *MemStorage) Get(key string) (interface{}, bool) {
	if v, ok := s.storage[key]; ok {
		return v, true
	}

	return nil, false
}

func (s *MemStorage) Delete(key string) {
	delete(s.storage, key)
}