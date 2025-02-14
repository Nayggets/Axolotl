INCLUDE=../include/
SOURCE=../source/
APP_NAME=Axolotl_asm

build:
	g++ -I ${INCLUDE} ${SOURCE}*.cpp ./main/main.cpp -o ${APP_NAME};


lexer_test:
	g++ -I ${INCLUDE} ${SOURCE}*.cpp -g ../test/mainLexer.cpp -o LexerTest
	./LexerTest ../test/codeExemple/mul.axolotl

test:
	./${APP_NAME} ../