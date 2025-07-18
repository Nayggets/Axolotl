SRC_DIR = ../source
INC_DIR = ../include/


all: build
	make simple_test

build: 
	g++ $(SRC_DIR)/*.cpp -I$(INC_DIR)  -o emulator 


simple_test:	build
	./emulator ../test/resultExemple	