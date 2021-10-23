package common

import "fmt"

var (
	ErrInternal     = fmt.Errorf("internal error")
	ErrBigMediaSize = fmt.Errorf("big media size")
)

const (
	DEFAULT_PAGE_SIZE    = 6
	TXT_INTERNAL_ERROR   = "Внутренняя ошибка. Пожалуйста попробуйте ещё раз или сообщите о проблеме администратору"
	TXT_CANCELLED        = "..действие отменено.."
	TXT_USER_MAIN_MENU   = "❊❊❊ Menu ❊❊❊"
	TXT_SHRUG            = "¯\\_(ツ)_/¯"
	TXT_TITLE_CREATE_BUG = "☎️️"
	TXT_BIG_FILE_SIZE    = "Слишком большой размер файла. Файл должен быть меньше %d Mb"
	TXT_TOO_MANY_FILES   = "Разрешено добавлять не более %d файлов"
)
