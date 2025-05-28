#include "../structures/objeto.h"
#include "colision.h"
#include <stdio.h>
#include <stdlib.h>

#define LINHAS 20
#define COLUNAS 20
#define TILE_SIZE 32

int numeroDeObjeto(int matriz[LINHAS][COLUNAS], int parametro) {
  int i, j, count = 0;
  for (i = 0; i < LINHAS; i++) {
    for (j = 0; j < COLUNAS; j++) {
      if (matriz[i][j] == parametro) {
        count++; // conta objetos com o valor igual ao parâmetro
      }
    }
  }
  return count;
}

HITBOX *cria_mapa(char mapa[], OBJETO obj1, int *qnt_objeto) {
  FILE *arquivo;
  int matriz[LINHAS][COLUNAS];
  HITBOX *obj_mapa;
  int i, j, obj_num = 0;

  arquivo = fopen(mapa, "r");
  if (!arquivo) {
    perror("Erro ao abrir o arquivo");
    return NULL;
  }

  for (i = 0; i < LINHAS; i++) {
    for (j = 0; j < COLUNAS; j++) {
      if (fscanf(arquivo, "%d", &matriz[i][j]) != 1) {
        fclose(arquivo);
        return NULL;
      }
    }
  }
  fclose(arquivo);

  *qnt_objeto = numeroDeObjeto(matriz, 1); // por exemplo, 1 representa "caixas"
  obj_mapa = malloc(*qnt_objeto * sizeof(HITBOX)); // prepara vetor de struct
                                                   //
  if (!obj_mapa)
    return NULL;

  for (i = 0; i < LINHAS; i++) {
    for (j = 0; j < COLUNAS; j++) {
      if (matriz[i][j] == 1) {
        // obj_mapa[obj_num].x = j;
        // obj_mapa[obj_num].y = i;
        obj_mapa[obj_num] =
            create_hitbox(TILE_SIZE * i, TILE_SIZE * j, TILE_SIZE, TILE_SIZE);

        // Desenha na tela
        al_draw_bitmap_region(obj1.sprite, 0, 0, obj1.sprite_w, obj1.sprite_h,
                              j * TILE_SIZE, i * TILE_SIZE, 0);

        obj_num++;
      }
    }
  }

  return obj_mapa;
}
