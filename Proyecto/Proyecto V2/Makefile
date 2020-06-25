CC = g++
CFLAGS = -g -I.
DEPS = Socket.h ClientMessage.h GameClient.h GameServer.h GameObject.h Vector2D. Game.h Player.h Texture.h Map.h Bullet.h
OBJ = Socket.o ClientMessage.o GameClient.o GameServer.o GameObject.o Vector2D.o Game.o Player.o Texture.o Map.o Bullet.o
LIBS = -lpthread -lSDL2 -lSDL2_image

%.o: %.cc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

all: gameServer gameClient

gameServer: $(OBJ) Server.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

gameClient: $(OBJ) Client.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o gameServer gameClient