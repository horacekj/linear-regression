OUTPUT=linReg
SOURCE=main.c gauss.c
DEP=main.h gauss.h

$(OUTPUT): $(SOURCES) $(DEP)
	gcc $(SOURCE) -std=c99 -o $(OUTPUT) -Wall -pedantic

clean:
	rm $(OUTPUT)

