package gwino

// #cgo CFLAGS: -g -Wall
// #include "win32.h"
import "C"
import (
	"unsafe"
)

var mainCallBack func()

// DO NOT REMOVE BELOW EXPORT COMMENT!! USED TO INTERFACE WITH C CODE!!!

//export libWin32MainCallback
func libWin32MainCallback() {
	mainCallBack()
}

func MsgBox(msg, title string) {
	cstr1 := C.CString(msg)
	cstr2 := C.CString(title)
	defer C.free(unsafe.Pointer(cstr1))
	defer C.free(unsafe.Pointer(cstr2))

	C.GwinoMsgBox(cstr1, cstr2)
}

func Window(title string, width, height int) {
	cstr1 := C.CString(title)
	cint1 := C.int(width)
	cint2 := C.int(height)

	defer C.free(unsafe.Pointer(cstr1))
	
	C.GwinoWindow(cstr1, cint1, cint2)
}

func Run(f func()) {
	mainCallBack = f
	C.GwinoRunMain()
}