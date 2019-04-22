package gwino

// #cgo CFLAGS: -g -Wall
// #include "win32.h"
import "C"
import (
	"unsafe"
)

var mainCallBack func()
var mouseDownEventHandler func()

// =========================================================================
//
//              GOLANG METHODS CALLED IN C
//
// =========================================================================


// DO NOT REMOVE BELOW EXPORT COMMENT!! USED TO INTERFACE WITH C CODE!!!

//export libWin32MainCallback
func libWin32MainCallback() {
	mainCallBack()
}

//export MouseDownEventHandler
func MouseDownEventHandler() {
	mouseDownEventHandler()
}


// =========================================================================
//
//              GOLANG METHODS EXPOSED AS GWINO API
//
// =========================================================================

type WndMenuItem struct {
	Text		string
	//Children	[]WndMenuItem
}

type WndProps struct {
	Title			string
	Width			int
	Height			int
	WndMenuItems	[]WndMenuItem
}


func MsgBox(msg, title string) {
	cstr1 := C.CString(msg)
	cstr2 := C.CString(title)
	defer C.free(unsafe.Pointer(cstr1))
	defer C.free(unsafe.Pointer(cstr2))

	C.GwinoMsgBox(cstr1, cstr2)
}

func CreateMenuList() []WndMenuItem {
	menuItems := make([]WndMenuItem, 0)
	return menuItems
}

func CreateMenuListItem(text string) WndMenuItem {
	return WndMenuItem{text}
}

func Window(props WndProps) {
	cstr1 := C.CString(props.Title)
	cint1 := C.int(props.Width)
	cint2 := C.int(props.Height)
	
	C.GwinoInitMenuItems();

	for _, item := range props.WndMenuItems {
		cstr2 := C.CString(item.Text)
		defer C.free(unsafe.Pointer(cstr2))
		C.GwinoAppendMenuItem(cstr2)
	}

	defer C.free(unsafe.Pointer(cstr1))

	C.GwinoWindow(cstr1, cint1, cint2)
}

func Run(f func(), f2 func()) {
	mainCallBack = f
	mouseDownEventHandler = f2
	C.GwinoRunMain()
}