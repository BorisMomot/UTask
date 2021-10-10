FROM golang:1.17 as builder

RUN mkdir -p /go/src/utask/bot
COPY . /go/src/utask/bot/

WORKDIR /go/src/utask/bot

ARG COMMIT=''
ARG BUILD_TIME=''

# RUN go test -mod vendor

RUN CGO_ENABLED=0 GOOS=linux go build -mod vendor -ldflags="-X main.COMMIT=${COMMIT} -X main.BUILD_TIME=${BUILD_TIME}" -a -installsuffix cgo -o utask-bot

############ RUN ####################
FROM alpine:3.9

RUN apk update \
        && apk upgrade \
        && apk add --no-cache \
        ca-certificates \
        && update-ca-certificates 2>/dev/null || true

RUN mkdir -p /opt/utask/
COPY botconfig.yaml /opt/utask/

COPY --from=builder /go/src/utask/bot/utask-bot /usr/local/bin/
COPY bot-entrypoint.sh /usr/local/bin/

WORKDIR /tmp

ENTRYPOINT [ "/usr/local/bin/bot-entrypoint.sh" ]
