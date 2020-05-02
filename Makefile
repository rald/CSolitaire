CC=gcc
CFLAGS=
LDFLAGS=-lm -lpthread -lX11 -lXrandr -lGL -lGLU -lgl2d -lglfw
OBJS=game.o
EXE=game


$(EXE): $(OBJS)
	gcc $(OBJS) -o $(EXE) $(LDFLAGS)

game.o: game.c uvcoord_sprites.h

clean:
	rm $(OBJS) $(EXE)
