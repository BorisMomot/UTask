package main

import (
	"fmt"
	"github.com/BorisMomot/UTask/bot/actor"
	api "github.com/BorisMomot/UTask/bot/api"
	"github.com/BorisMomot/UTask/bot/scope"
	"github.com/BorisMomot/UTask/bot/session"
	nested "github.com/antonfisher/nested-logrus-formatter"
	"github.com/sirupsen/logrus"
	"os"
	"time"

	"github.com/spf13/viper"
	tb "gopkg.in/tucnak/telebot.v2"
)

var VERSION = "0.0.1"
var COMMIT = ""
var BUILD_TIME = ""

func CreateDefaultLogger(loglevel string) *logrus.Logger {
	logger := logrus.New()
	logger.Out = os.Stdout
	logger.SetFormatter(&nested.Formatter{
		HideKeys: false,
		// DisableColors: true,
	})

	// logger.SetReportCaller(true)
	// default level
	// logger.SetLevel(logrus.PanicLevel)
	// logger.SetLevel(logrus.FatalLevel)
	// logger.SetLevel(logrus.ErrorLevel)
	logger.SetLevel(logrus.WarnLevel)

	if loglevel == "info" {
		logger.SetLevel(logrus.InfoLevel)
	}
	if loglevel == "trace" {
		logger.SetLevel(logrus.TraceLevel)
	}

	return logger
}

func main() {
	viper.SetEnvPrefix("utask")
	viper.SetConfigName("botconfig")
	viper.SetConfigType("yaml")
	viper.AddConfigPath(".")
	viper.AutomaticEnv()

	err := viper.ReadInConfig()
	if err != nil {
		fmt.Println("fatal error config file: default \n", err)
		os.Exit(1)
	}

	log := CreateDefaultLogger(viper.GetString("loglevel"))

	token := viper.GetString("token")
	if token == "" {
		log.Fatalf("Unknown token for bot")
	}

	log.Infof("UTaskBot: VERSION: %s BUILD: %s COMMIT: %s", VERSION, BUILD_TIME, COMMIT)

	bot, err := tb.NewBot(tb.Settings{
		Token:  token,
		Poller: &tb.LongPoller{Timeout: 10 * time.Second},
	})

	if err != nil {
		log.Fatal(err)
		return
	}

	addr := viper.GetString("server")
	if addr == "" {
		log.Fatalf("Unknown address for server")
	}

	var srvApi api.Api
	if viper.GetBool("fakeapi") {
		srvApi = api.NewFakeApi()
	} else {
		srvApi = api.NewHttpApi(addr)
	}

	scope := scope.NewScope(bot, srvApi, log)
	sess := session.NewSessionManager(scope)
	fsm := actor.NewFSM(scope)

	bot.Handle(tb.OnText, func(msg *tb.Message) {

		l := log.WithFields(logrus.Fields{
			"func":   "OnText",
			"userID": msg.Sender.ID,
		})

		actor, err := sess.Restore(msg.Sender)
		if err != nil {
			l.Errorf("Restore session error: %s", err)
			return
		}
		err = fsm.OnMessage(actor, msg)
		if err != nil {
			l.WithFields(logrus.Fields{"actor": actor.Name()}).Errorln(err)
		}
	})

	bot.Handle(tb.OnCallback, func(cb *tb.Callback) {

		l := log.WithFields(logrus.Fields{
			"func":   "OnCallback",
			"userID": cb.Sender.ID,
		})

		actor, err := sess.Restore(cb.Sender)
		if err != nil {
			l.Errorf("Restore session error: %s", err)
			return
		}
		err = fsm.OnCallback(actor, cb)
		if err != nil {
			l.WithFields(logrus.Fields{"actor": actor.Name()}).Errorln(err)
		}
	})

	bot.Start()
}
