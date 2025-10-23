CC = gcc

# ALLEGRO = allegro64

ifdef ALLEGRO
CFLAGS = -I${ALLEGRO}/include 
LDFLAGS = -L${ALLEGRO}/lib 
endif

LDLIBS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio functions/moving.c functions/colision.c functions/cria_mapa.c 


TARGETS = bin/game_linux

all: ${TARGETS}
	./${TARGETS}

bin/game_linux: main.c | bin
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS} ${LDLIBS}

output:
	mkdir -p output

clean:
	rm -rf output
