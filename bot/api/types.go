package api

type Project struct {
	Id   int64  `json:"id"`
	Name string `json:"name"`
}

type ProjectListResponse struct {
	Projects []Project `json:"projects"`
}

func FindProjectById(projects []Project, id int64) (*Project, bool) {
	for _, p := range projects {
		if p.Id == id {
			return &p, true
		}
	}

	return nil, false
}
