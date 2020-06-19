CC = g++
CFLAGS = -g -I.
DEPS = Socket.h ClientMessage.h GameClient.h GameServer.h GameObject.h Vector2. Game.h Player.h Texture.h Track.h
OBJ = Socket.o ClientMessage.o GameClient.o GameServer.o GameObject.o Vector2.o Game.o Player.o Texture.o Track.o
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