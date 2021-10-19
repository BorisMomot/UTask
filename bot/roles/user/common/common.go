package common

import "fmt"

var (
	ErrInternal = fmt.Errorf("internal error")
)
const (
	DEFAULT_PAGE_SIZE  = 6
	TXT_INTERNAL_ERROR = "Внутренняя ошибка. Пожалуйста попробуйте ещё раз или сообщите о проблеме администратору"
	TXT_CANCELLED      = "..действие отменено.."
	TXT_USER_MAIN_MENU = "❊❊❊ Menu ❊❊❊"
	TXT_SHRUG          = "¯\\_(ツ)_/¯"
)
