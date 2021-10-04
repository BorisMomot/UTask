package api

type Project struct {
	Id   int64  `json:"id"`
	Name string `json:"name"`
}

type ProjectListResponse struct {
	Projects []Project `json:"projects"`
}
