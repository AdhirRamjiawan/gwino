package main

import (
	"fmt"
	"./gwino"
)

func main() {
	menuItems := make([]gwino.WndMenuItem, 0)
	menuItems = append(menuItems, gwino.WndMenuItem{"&File"})

	mainFunc := func() {
		fmt.Println("testing gwino...")
		gwino.Window("test window", 800, 640, menuItems)	
	}

	mouseDownHandler := func() {
		gwino.MsgBox("window 3, looksy!! --- I'm PACKAGED!!!!", "LOOKSY!!!")
	}

	gwino.Run(mainFunc, mouseDownHandler)
}