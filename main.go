package main

import (
	"fmt"
	"./gwino"
)

func main() {
	gwino.Run(func() {
		fmt.Println("testing gwino...")
		gwino.MsgBox("Adhir, looksy!! --- I'm PACKAGED!!!!", "LOOKSY!!!")
		gwino.MsgBox("Adhir, looksy!! --- I'm PACKAGED!!!!", "LOOKSY!!!")
		gwino.MsgBox("Adhir, looksy!! --- I'm PACKAGED!!!!", "LOOKSY!!!")
		gwino.Window("test window", 800, 640)
	})
}