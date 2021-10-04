package helpers

import (
	"fmt"
	tb "gopkg.in/tucnak/telebot.v2"
)

type BtnItem struct {
	Name string
	Id   string
}

func NewButtonList(items []BtnItem, begin_num int, pageSize int) *tb.ReplyMarkup {

	keyb := &tb.ReplyMarkup{}
	if begin_num < 0 {
		begin_num = 0
	}

	beg := begin_num
	end := begin_num + pageSize
	cnt := len(items)
	var lst []BtnItem

	if cnt >= end {
		lst = items[beg:end]
	} else if end > cnt && cnt >= beg {
		lst = items[beg:]
		end = cnt
	} else if cnt < beg {
		beg = 0
	}

	var rows []tb.Row
	for _, b := range lst {
		btn := keyb.Data(b.Name, b.Id)
		rows = append(rows, tb.Row{btn})
	}

	var specButtons tb.Row

	if beg == 0 {
		specButtons = append(specButtons, keyb.Data(" ", "UNUSED"))
	} else {
		specButtons = append(specButtons, keyb.Data("<<<", fmt.Sprintf("PREV;%d;%d", beg, pageSize)))
	}
	specButtons = append(specButtons, keyb.Data("BACK", "BACK"))

	if cnt > end {
		specButtons = append(specButtons, keyb.Data(">>>", fmt.Sprintf("NEXT;%d;%d", end, pageSize)))
	} else {
		specButtons = append(specButtons, keyb.Data(" ", "UNUSED"))
	}

	rows = append(rows, specButtons)
	keyb.Inline(rows...)
	return keyb
}
