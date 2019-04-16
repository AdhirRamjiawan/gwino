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

	C.GowinMsgBox(cstr1, cstr2)
}

func Run(f func()) {
	mainCallBack = f
	C.GowinRunMain()
}