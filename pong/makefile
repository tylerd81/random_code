#Makefile for pong2k3 version 0.00001
#big problem that everyone depends on pong.h, oh well for now
FLAGS=-pg

pong: vid.o draw.o main.o ball.o vsync.o paddle.o isrs.o
	gcc $(FLAGS) -o pong.exe vid.o draw.o main.o ball.o vsync.o paddle.o isrs.o

debug: vid.o draw.o main.o ball.o vsync.o paddle.o isrs.o
	gcc $(FLAGS) -o  pd.exe vid.o draw.o main.o ball.o vsync.o paddle.o isrs.o

clean:
	del *.o pd.exe pong.exe

vid.o: vid.c pong.h
	gcc $(FLAGS) -c vid.c

draw.o: draw.c pong.h
	gcc $(FLAGS) -c draw.c

main.o: main.c pong.h
	gcc $(FLAGS) -c main.c

ball.o: ball.c pong.h
	gcc $(FLAGS) -c ball.c


vsync.o: vsync.c
	gcc $(FLAGS) -c vsync.c

paddle.o: paddle.c pong.h
	gcc $(FLAGS) -c paddle.c

isrs.o:	isrs.c timer.h keys.h
	gcc $(FLAGS) -c isrs.c