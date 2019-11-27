#include <allegro.h>

BITMAP *fundo, *buffer, *alien;
//funções:
void controles();
void sair();
int colisao(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh);

//variaveis globais
int sai = 0;
int atirar = 0;

struct objeto{
    int x;
    int y;
    int wx;
    int wy;
    int w;
    int h;
} monster[5][10];

struct objeto
    nave        = {364,499,364,499,72,45},
    tiro        = {-10,-10,380,530, 4, 8},
    destrui     = { 57,177, 57,177,56,55},
    disco       = {469,190,469,190,68,24},
    tiromon[2]  = {-10,-10,380,530, 4, 8, -10,-10,380,530, 4, 8}

;

int main() {

  allegro_init();
  install_keyboard();

//Ajusta video para 16 bits de cores
  set_color_depth(16);

//Autodetecta a placa  de video e usa resolucao de 800x600 em modo janela
  set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,800,600);

//variaveis:

  int i, j;
  int t = 0;
  int end = 0;
  int width = 800;
  int height = 600;
  int lft = 0;
  int dwn;
  int passo = 0;
  int time = 60;
  int face = 0;
  int dscx = 1500;
  int pontos = 0;
  int vida = 0;
  int vidas = 3;
  int play = 0;
  int atingido = 0;
  int numonstro = 0;

    tiromon[0].y = height/2;
    tiromon[1].y = height/2;
    tiromon[0].x = -10;
    tiromon[1].x = -10;
//

  buffer = create_bitmap(SCREEN_W,SCREEN_H);

  SAMPLE *hit   = load_sample("sons/invaderkilled.wav");
  SAMPLE *disc  = load_sample("sons/ufo_lowpitch.wav");
  SAMPLE *fase  = load_sample("sons/spaceinvaders1.wav");
  SAMPLE *tiros = load_sample("sons/shoot.wav");
  SAMPLE *morto = load_sample("sons/explosion.wav");


//carrega o fundo

    for(i = 0; i < 5; i++ ){
        for(j = 0; j < 10; j++){

            monster[j][i].x =   49 + j * 66;
            monster[j][i].y =  256 + i * 43;
            monster[j][i].wx =  49;
            monster[j][i].wy = 256 + i * 43;
            monster[j][i].w =   38;
            monster[j][i].h =   22;
        }
    }


  fundo = load_bitmap("fundo.bmp",NULL);

  alien = load_bitmap("alien.bmp",NULL);

  while(!(sai || key[KEY_ESC])){

    controles();

        t++;
        passo = 0;

        //tempo dos eventos

    //if(t > time){
      //  t = 0;
        //passo = 1;
        //face = !face;
    //}

        draw_sprite(buffer, fundo, 0, 0);

        play_sample(fase, 255, 128, 1000, 1);

//disco:
        if(disco.x == 800) play_sample(disc, 255, 128, 1000, 1);
        if(disco.x < -disco.w) {stop_sample(disc); dscx = 2000;}
        dscx --;
        disco.x = dscx;
        if(disco.x < disco.w) dscx = 1500;
        masked_blit(alien, buffer, disco.wx, disco.wy, disco.x, disco.y, disco.w, disco.h);

    //atigindo o disco

    //colisao(Ax, Ay, Bx, By, Aw, Ah, Bw, Bh);

        if(colisao(tiro.x, tiro.y, disco.x, disco.y, tiro.w, tiro.h, disco.w, disco.h)){
            masked_blit(alien, buffer, destrui.wx, destrui.wy, disco.x, disco.y, destrui.w+10, destrui.h+10);
            stop_sample(disc);
            play_sample(morto, 255, 128, 1000, 1);
            pontos += 150;
            dscx = 1500;
            atirar = 0;
            numonstro ++;
        }

    //tiro dos monstro////
        int sort = rand()%10;
        if(tiromon[0].y < height) tiromon[0].y +=3;
        if(tiromon[1].y < height) tiromon[1].y +=3;

        for(i = 0; i < 5; i++ ){
            if(tiromon[1].y >= height && monster[sort][4 - i].y < height){
                tiromon[1].x = monster[sort][4 - i].x + monster[sort][4 - i].w/2;
                tiromon[1].y = monster[sort][4 - i].y + monster[sort][4 - 1].h/2;
            }
        for(j = 0; j < 10; j++){

            if(monster[j][i].y < height){
                if(monster[j][i].x <  10 && !lft){ dwn = 1; monster[j][i].x += passo*15;}
                if(monster[j][i].x > 770 &&  lft){ dwn = 1; monster[j][i].x -= passo*15;}
                lft ? (monster[j][i].x += passo*15) : (monster[j][i].x -= passo*15);
            }
            if(monster[j][i].x == nave.x && tiromon[0].y >= height && monster[j][i].y < height){
                tiromon[0].x = monster[9 - j][4 - i].x + monster[9 - j][4 - i].w/2;
                tiromon[0].y = monster[9 - j][4 - i].y + monster[9 - j][4 - i].h/2;
            }
            masked_blit(alien, buffer, monster[j][i].wx + face*66, monster[j][i].wy, monster[j][i].x, monster[j][i].y, monster[j][i].w, monster[j][i].h );

            //colisao///

            if(colisao(tiro.x, tiro.y, monster[j][i].x, monster[j][i].y, tiro.w, tiro.h, monster[j][i].w, monster[j][i].h)){

                masked_blit(alien, buffer, destrui.wx, destrui.wy, monster[j][i].x, monster[j][i].y, destrui.w, destrui.h);
                play_sample(hit, 255, 128, 1000, 1);
                monster[j][i].y = height;
                pontos += 25;
                atirar = 0;

                numonstro++;
            }
        }
    }



        if(colisao(nave.x, nave.y, tiromon[0].x, tiromon[0].y, nave.w, nave.h, tiromon[0].w, tiromon[0].h) ||
        colisao(nave.x, nave.y, tiromon[1].x, tiromon[1].y, nave.w, nave.h, tiromon[1].w, tiromon[1].h)){
        atingido = 1;

        play = 0;
        }
    //prints//
        if(atingido){
            masked_blit(alien, buffer, destrui.wx, destrui.wy, nave.x, nave.y, destrui.w, destrui.h);
            play_sample(morto, 255, 128, 1000, 1);
        }else{
            masked_blit(alien, buffer, nave.wx, nave.wy, nave.x, nave.y, nave.w, nave.h);
            masked_blit(alien, buffer, tiro.wx, tiro.wy, tiro.x, tiro.y, tiro.w, tiro.h);
            masked_blit(alien, buffer, tiromon[0].wx, tiromon[0].wy, tiromon[0].x, tiromon[0].y, tiromon[0].w, tiromon[0].h);
            masked_blit(alien, buffer, tiromon[1].wx, tiromon[1].wy, tiromon[1].x, tiromon[1].y, tiromon[1].w, tiromon[1].h);
        }

        textprintf_centre_ex(buffer, font, width/2, 6, 0xffffff, -1, "SCORE: %i", pontos );
        textprintf_centre_ex(buffer, font, width/1.2, height/1.05, 0xffffff, -1, "LIFES: %i", vidas);

        draw_sprite(screen, buffer, 0, 0);

            if(atingido){
                vidas --;
                rest(200);
                stop_sample(fase);
                atingido = 0;
            }
        rest(5);
    }


  allegro_exit();
  return 0;
}

 END_OF_MAIN()

 int colisao(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh){

    if(Ax + Aw > Bx && Ax < Bx + Bw && Ay + Ah > By && Ay < By + Bh){

        return 1;
    }
    else { return 0;}
 }

 void controles(){

    if(key[KEY_RIGHT] && nave.x > 1) nave.x += 4;
    if(key[KEY_LEFT] && nave.x < 800) nave.x -= 4;
    if(key[KEY_SPACE] && tiro.y > nave.y && !atirar) atirar = 1;
    if(atirar) tiro.y -= 8;
    if(tiro.y < 160)  atirar = 0;
    if(!atirar) {
        tiro.x = nave.x + nave.w/2;
        tiro.y = nave.y + nave.h/2;}
 }

 void sair(){sai = 1;}
