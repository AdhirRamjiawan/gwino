package main

import (
	"fmt"
	"./gwino"
)

func main() {

	menuItems := gwino.CreateMenuList()
	menu1 := gwino.CreateMenuListItem("&File")
	menu2 := gwino.CreateMenuListItem("&File2")
	menu3 := gwino.CreateMenuListItem("&File3")

	menuItems = append(menuItems, menu1)
	menuItems = append(menuItems, menu2)
	menuItems = append(menuItems, menu3)

	wndProps := gwino.WndProps{"test window", 800, 640, menuItems}

	mainFunc := func() {
		fmt.Println("testing gwino...")
		gwino.Window(wndProps)	
	}

	mouseDownHandler := func() {
		gwino.MsgBox("window 3, looksy!! --- I'm PACKAGED!!!!", "LOOKSY!!!")
	}

	gwino.Run(mainFunc, mouseDownHandler)
}