CC = gcc
CFLAGS = $(shell pkg-config --cflags libnotify)
LIBS = $(shell pkg-config --libs libnotify)

noti: noti.c battery.c
	$(CC) noti.c battery.c -o noti $(CFLAGS) $(LIBS)

clean:
	rm -f noti
