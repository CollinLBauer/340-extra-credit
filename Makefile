all: src

clean:
	rm ./ccsh

src: src/main.c
	gcc -Wall -o ccsh src/main.c