package api

import (
	"encoding/json"
	"strings"
)

type FakeApi struct {
}

func NewFakeApi() Api {
	return &FakeApi{}
}

func (api *FakeApi) Get(query string) ([]byte, error) {

	if strings.HasPrefix(query, "/projects/list") {
		resp := ProjectListResponse{
			Projects: []Project{
				{Id: 1, Name: "22220.1"},
				{Id: 2, Name: "22220.2"},
				{Id: 3, Name: "22220.3"},
			},
		}

		tmp, err := json.Marshal(resp)
		if err != nil {
			return nil, err
		}

		return tmp, nil
	}

	if strings.HasPrefix(query, "/projects/components/list?project=") {
		resp := ComponentListResponse{
			Components: []Component{
				{Id: 1, Name: "Схемы"},
				{Id: 2, Name: "Документация"},
				{Id: 3, Name: "ПО"},
			},
		}

		tmp, err := json.Marshal(resp)
		if err != nil {
			return nil, err
		}

		return tmp, nil
	}

	return nil, nil
}
