game:game.o oled.o
	gcc -o game game.o oled.o -lwiringPi -lpthread

game.o:game.c
	gcc -c game.c

oled.o:oled.c
	gcc -c oled.c
	
clean: 
	rm *.o