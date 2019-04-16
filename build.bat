echo building project...
cd .\gwino
go clean
go tool cgo gwino.go
go build
cd ..
go clean
go build
