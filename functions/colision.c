#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>

HITBOX create_hitbox(float x, float y, float w, float h) {
  HITBOX hb;
  hb.L = x;
  hb.R = x + w * 0.6;
  hb.U = y;
  hb.D = y + h * 0.6;
  return hb;
}

HITBOX create_hitbox_scaled(int x, int y, int w, int h, float escala) {
  HITBOX hb;

  float scaled_w = w * escala;
  float scaled_h = h * escala;

  float cx = x + w / 2.0f;
  float cy = y + h / 2.0f;

  hb.L = cx - scaled_w / 2.0f;
  hb.R = cx + scaled_w / 2.0f;
  hb.U = cy - scaled_h / 2.0f;
  hb.D = cy + scaled_h / 2.0f;

  return hb;
}
// Calcula a hitbox dos pés com deslocamento X
HITBOX get_hitbox_pes_x(const OBJETO *p) {
  return create_hitbox(p->posx + p->vec_velocidade.dx,
                       p->posy + (p->sprite_h - PÉS_ALTURA), p->sprite_w,
                       PÉS_ALTURA);
}

// Calcula a hitbox dos pés com deslocamento Y
HITBOX get_hitbox_pes_y(const OBJETO *p) {
  return create_hitbox(
      p->posx, p->posy + p->vec_velocidade.dy + (p->sprite_h - PÉS_ALTURA),
      p->sprite_w, PÉS_ALTURA);
}

bool testa_colisao(HITBOX a, HITBOX b) {
  return a.L < b.R && a.R > b.L && a.U < b.D && a.D > b.U;
}

/*
 * 1)pega a hitbox dos pes do personagem-
 * 2)supoe que o incremento foi adicionado
 * 3)olha todos os elementos do vetor hitbox e ve se houve a sobreposiçao
 * da hitbox_pes_personagem com hitbox_obj
 */

void colision(HITBOX *objetosHITBOX, int num_objetos, OBJETO *personagem) {
  HITBOX hitbox_pes_x = get_hitbox_pes_x(personagem);
  HITBOX hitbox_pes_y = get_hitbox_pes_y(personagem);

  for (int i = 0; i < num_objetos; i++) {

    HITBOX hitbox_obj = objetosHITBOX[i];

    bool colidiu_x = testa_colisao(hitbox_pes_x, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_pes_y, hitbox_obj);

    if (colidiu_x) {
      personagem->vec_velocidade.dx = 0;
    }
    if (colidiu_y) {
      personagem->vec_velocidade.dy = 0;
    }
  }
}

void colision_With_Reset(HITBOX *objetos, int num_objetos, OBJETO *personagem) {
  HITBOX hitbox_pes_x = get_hitbox_pes_x(personagem);
  HITBOX hitbox_pes_y = get_hitbox_pes_y(personagem);

  for (int i = 0; i < num_objetos; i++) {

    HITBOX hitbox_obj = objetos[i];

    bool colidiu_x = testa_colisao(hitbox_pes_x, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_pes_y, hitbox_obj);
    if ((colidiu_x || colidiu_y)) { // gameOver
      personagem->colisao = false;

      break;
    }
  }
}

void colision_Consumable(HITBOX *objetos, int num_objetos, OBJETO *personagem,
                         OBJETO *objeto, int *qnt) {
  HITBOX hitbox_pes_x = get_hitbox_pes_x(personagem);
  HITBOX hitbox_pes_y = get_hitbox_pes_y(personagem);

  for (int i = 0; i < num_objetos; i++) {
    HITBOX hitbox_obj = objetos[i];

    bool colidiu_x = testa_colisao(hitbox_pes_x, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_pes_y, hitbox_obj);
    if ((colidiu_x || colidiu_y)) { // gameOver
      printf("coletado\n");

      (*qnt)--;
      printf(" Restamm %d\n", *qnt);
      // "remove" o objeto
      objetos[i] = (HITBOX){0, 0, 0, 0};

      return;
    }
  }
  return;
}
void limita_mapa(float *posx, float *posy, int maxdisplay_w, int maxdisplay_h,
                 int sprite_w, int sprite_h) {
  const int margin = 12;

  // Horizontal
  if (*posx < -sprite_w + margin)
    *posx = maxdisplay_w - margin;
  else if (*posx > maxdisplay_w - margin)
    *posx = -sprite_w + margin;

  // Vertical
  if (*posy < -sprite_h + margin)
    *posy = maxdisplay_h - margin;
  else if (*posy > maxdisplay_h - margin)
    *posy = -sprite_h + margin;
}

void colision_enemy_scenery(HITBOX *objetosHITBOX, int num_objetos,
                            OBJETO *enemy, int maxdisplay_w, int maxdisplay_h) {

  HITBOX hitbox_prox_x =
      create_hitbox_scaled(enemy->posx + enemy->vec_velocidade.dx, enemy->posy,
                           enemy->sprite_w, enemy->sprite_h, 1.0);

  HITBOX hitbox_prox_y =
      create_hitbox_scaled(enemy->posx, enemy->posy + enemy->vec_velocidade.dy,
                           enemy->sprite_w, enemy->sprite_h, 1.0);

  for (int i = 0; i < num_objetos; i++) {
    HITBOX obj = objetosHITBOX[i];

    if (testa_colisao(hitbox_prox_x, obj)) {
      enemy->vec_velocidade.dx *= -1;
      enemy->posx +=
          enemy->vec_velocidade.dx * enemy->vec_velocidade.velocidade;
      if (enemy->vec_velocidade.dx == 1) {
        enemy->sprite_dir = 2;

      } else if (enemy->vec_velocidade.dx == -1) {
        enemy->sprite_dir = 1;
      }
    }

    if (testa_colisao(hitbox_prox_y, obj)) {
      enemy->vec_velocidade.dy *= -1;
      enemy->posy +=
          enemy->vec_velocidade.dy * enemy->vec_velocidade.velocidade;
      if (enemy->vec_velocidade.dy == 1) {
        enemy->sprite_dir = 0;

      } else if (enemy->vec_velocidade.dy == -1) {
        enemy->sprite_dir = 3;
      }
    }
  }

  // Limita posição à tela
  limita_mapa(&(enemy->posx), &(enemy->posy), maxdisplay_w, maxdisplay_h,
              enemy->sprite_w, enemy->sprite_h);
}

void colision_With_Enemy(OBJETO *enemy, OBJETO *personagem) {
  HITBOX hitbox_enemy = create_hitbox_scaled(
      enemy->posx, enemy->posy, enemy->sprite_w, enemy->sprite_h, 1.0);
  HITBOX hitbox_personagem =
      create_hitbox_scaled(personagem->posx, personagem->posy,
                           personagem->sprite_w, personagem->sprite_h, 1.0);

  bool test = testa_colisao(hitbox_personagem, hitbox_enemy);
  if (test) { // gameOver
    personagem->colisao = false;
  }
}
