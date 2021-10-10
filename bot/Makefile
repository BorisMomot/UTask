COMMIT?=$(shell git rev-parse HEAD)
BUILD_TIME?=$(shell date -u '+%Y-%m-%d_%H:%M:%S')

all: *.go
	go build -mod vendor -ldflags="-X main.COMMIT=$(COMMIT) -X main.BUILD_TIME=$(BUILD_TIME)" -o utask-bot

docker: *.go *.yaml
	docker build --build-arg "COMMIT=$(COMMIT)" --build-arg "BUILD_TIME=$(BUILD_TIME)" -t utask-bot -f ./Dockerfile .
