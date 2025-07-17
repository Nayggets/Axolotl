INCLUDE=../include/
SOURCE=../source/
APP_NAME=Axolotl_asm

build:
	g++ -I ${INCLUDE} ${SOURCE}*.cpp ../source/main/main.cpp -o ${APP_NAME};


lexer_test:
	g++ -I ${INCLUDE} ${SOURCE}*.cpp -g ../test/mainLexer.cpp -o LexerTest
	./LexerTest ../test/codeExemple/simple.axolotl

parser_test:
	g++ -I ${INCLUDE} ${SOURCE}*.cpp -g ../test/mainParser.cpp -o ParserTest
	./ParserTest ../test/codeExemple/simple.axolotl

visitor_test:
	g++ -I ${INCLUDE} ${SOURCE}*.cpp -g ../test/mainVisitor.cpp -o VisitorTest
	./VisitorTest ../test/codeExemple/simple.axolotl ../test/resultExemple


