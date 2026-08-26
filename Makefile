.PHONY: build rebuild clean
buildtest:
	mkdir -p build/test
	gcc -Wall -Wextra -O2 src/message.c src/notify.c src/main.c -o build/test/application  -lsystemd

buildfinal:
	mkdir -p build/release
	gcc -Wall -Wextra -O2 src/message.c src/notify.c src/main.c -o build/release/application  -lsystemd

rebuild: clean buildtest

clean:
	rm -f build/release/* build/test/*
