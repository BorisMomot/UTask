# utask-bot

Бот предоставляет интерфейс для удалённого управления задачами, просмотра информации по проектам
и текущим багам.  Доступа к документации по проектам и т.п.


### Конфигурирование
Конфигурирование производится при помощи переменных окружения и конфигурационного файла.

**ВАЖНО**: Переменные окружения имеют приоритет.

* `UTASK_BOT_TOKEN` - телеграм-токен бота
* `UTASK_BOT_API_URL` - url для обращений к API сервера. Пример: https://apiserver/api
* `UTASK_BOT_API_TIMEOUT` - таймаут (в секундах), на чтение данных с API сервера. По умолчанию 5 сек
* `UTASK_BOT_LOG_LEVEL` - [INFO | WARNING | ERROR | TRACE] - Уровень логов

Конфигурационный файл представляет собой yaml. См. `botconfig.yaml`
Если в текущем каталоге присутствует файл `.env` он тоже используется
переопределяя переменные из основного файла (при этом значения переменных окружения
должны в нём определяться без префикса `UTASK_BOT`)

### Список доступных комманд
#### Общие
* `/start` - начать работу или перейти в главное меню (из любой стадии где-бы не находились)
* `/help` - краткий help по доступным командам

**WARNING:** Все используемые данным ботом команды задаются без '/', кроме команд `/start`, `/help`

### Детали реализации

Бот построен на принципе конечных автоматов (Finite State Machine).
Основан на использовании библиотеки https://github.com/tucnak/telebot/
Работает по polling-модели (опрашивает телеграм сервер на предмет новых событий от пользователей)

**ВАЖНО**: По умолчанию бот хранит всё состояние в памяти и теряет его при перезагрузке.

Для каждого подключившегося пользователя создаётся отдельный объект (actor), привязанный к user_id(telegram).
Во время обработки событий, в начале восстанавливается контекст соответствующего пользователя (актора),
и происходит обработка. Актор переходит между состояниями обеспечивая необходимую логику
и реализуя обработку событий в зависимости от своего текущего состояния.
Какие-то команды или нажатия игнорируются, какие-то обрабатываются.
Базовый интерфейс для акторов - Actor (см. `actor/actor.go`), его реализуют соответствующие роли
и каждая реализует свою логику

Каждый пользователь имеет свою роль в системе
* Пользователь (User)
* Администратор (Admin)
* Разработчик (developer)
* ...

И для каждой роли реализован свой граф переходов по состояниям (см. `roles/xxx`)
