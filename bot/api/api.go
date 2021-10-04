package api

import (
	"fmt"
	"github.com/valyala/fasthttp"
	"time"
)

type Api interface {
	Get(query string) ([]byte, error)
}

type HttpApi struct {
	addr   string
	client *fasthttp.Client
}

func NewHttpApi(addr string) Api {
	return &HttpApi{
		addr: addr,
		client: &fasthttp.Client{
			ReadBufferSize:  8000,
			WriteBufferSize: 8000,
			ReadTimeout:     3 * time.Second,
		},
	}
}

func (api *HttpApi) Get(query string) ([]byte, error) {
	// FIXME: not realized yet
	return nil, fmt.Errorf("API: Not realized yet")
}
