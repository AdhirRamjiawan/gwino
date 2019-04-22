echo building project...
cd .\gwino
go clean
rem go tool cgo gwino.go
rem go build
cd ..
go clean
go build
