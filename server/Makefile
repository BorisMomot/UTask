docker: *.yaml
	docker build --build-arg "COMMIT=$(COMMIT)" --build-arg "BUILD_TIME=$(BUILD_TIME)" -t utask-server -f ./Dockerfile .
