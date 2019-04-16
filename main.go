package main

import (
	"fmt"
	"./gwino"
)

func main() {
	gwino.Run(func() {
		fmt.Println("testing gwino...")
		gwino.MsgBox("Adhir, looksy!! --- I'm PACKAGED!!!!", "LOOKSY!!!")
	})
}