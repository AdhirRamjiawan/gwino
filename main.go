package main

import (
	"fmt"
	"./gwino"
)

func main() {
	mainFunc := func() {
		fmt.Println("testing gwino...")
		gwino.Window("test window", 800, 640)	
	}

	mouseDownHandler := func() {
		gwino.MsgBox("window 3, looksy!! --- I'm PACKAGED!!!!", "LOOKSY!!!")
	}
	
	gwino.Run(mainFunc, mouseDownHandler)
}