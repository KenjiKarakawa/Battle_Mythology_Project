#pragma once

#include "ofMain.h"
#include <string>

#define MAXSPEED 3

struct PlayerType {
	ofImage Sprite;
	int X, Y, Vida;
	int Direcao = 1;
	char Acao[9] = "idle";
	int Frame, FPS;
	float VelX, VelY, Speed = 0.09f;
	bool Vivo;
};

struct KeyInput {
	bool Up = false;
	bool Down = false;
	bool Left = false;
	bool Right = false;
};



class ofApp : public ofBaseApp{

	KeyInput keys;
	PlayerType player;
	
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		

		void SeeDirection(PlayerType *ply, KeyInput *tecla) {
		// Funcao para verificar se para qual direcao o player esta indo:
			/*				  	
						   2   3   4	 
							\  |  /
						1 --- key --- 5
						    /  |  \
						   8   7   6
			*/


			int aux = ply->Direcao;	//salva a direcao anterior, para continuar na mesma posicao se nao tiver apertado nada.
			ply->Direcao = 0;		//zera a direcao para iniciar uma nova contagem

			if (tecla->Left) {
				ply->Direcao = 1;
			}
			if (tecla->Up) {
				ply->Direcao = 3;
			}
			if (tecla->Right) {
				ply->Direcao = 5;
			}
			if (tecla->Down) {
				ply->Direcao = 7;
			}
			if (tecla->Left && tecla->Up) {
				ply->Direcao = 2;
			}
			if (tecla->Right && tecla->Up) {
				ply->Direcao = 4;
			}
			if (tecla->Right && tecla->Down) {
				ply->Direcao = 6;
			}
			if (tecla->Left && tecla->Down) {
				ply->Direcao = 8;
			}
			if ((ply->Direcao == 0) || (ply->Direcao > 11)) {	//Se nenhuma tecla tiver sido precionada ou a soma das teclas 
				ply->Direcao = aux;								//for maior que 11, ply->Direcao recebe a direcao anterior.
			}
		}

		void SeeAction(PlayerType *ply, KeyInput *tecla) {
		//Funcao para gerenciar as acoes do player:
		//andando, ataque1, ataque2, ataque3, levadano, dash

			//se alguma das setas do teclado tiver precionada, sera atribuido "andando"
			//na variavel ply->Acao.
			if (tecla->Down || tecla->Up || tecla->Left || tecla->Right) {
				strcpy_s(ply->Acao, "andando");
			}
			if (!tecla->Down && !tecla->Up && !tecla->Left && !tecla->Right) {
				strcpy_s(ply->Acao, "idle");
			}

			//colocar acoes novas aki:

		}

		void Animation(PlayerType *ply, KeyInput *tecla) {
		//Funcao que controla o load dos sprites do player, conforme a Acao e Direcao, alem de mudar os frames.
			
			if (ply->FPS >= 10) {	//ply tem uma var que conta os fps, aki se ela for menor igual a 10
				ply->FPS = 0;		//ela eh zerada e a variavel frame soma 1.
				ply->Frame++;
			}
			if (ply->Frame > 3) {	//aki ocorre o mesmo que com o fps, mas com os frames, quando Frame passar de 3
				ply->Frame = 0;		//o Frame eh zerado.
			}

			//Aki eh onde sera juntado a variavel Acao, Direcao e Frame, para poder carregar os frames de acordo com o 
			//o jogador esta fazendo.
			char anim[50];	//tudo sera juntado nessa variavel
			snprintf(anim, sizeof(anim), "players/%s/%d/%d.png", ply->Acao,ply->Direcao, 0); //juntando tudo
			std::cout << anim;
			ply->Sprite.loadImage(anim);
		}
		

		void SpeedPlayer(PlayerType *ply, KeyInput *tecla) {
			if (ply->VelX < MAXSPEED && tecla->Right) {
				ply->VelX+= ply->Speed;
			}
			if (ply->Speed > -MAXSPEED && tecla->Left) {
				ply->VelX -= ply->Speed;
			}
			if (ply->Speed > -MAXSPEED && tecla->Up) {
				ply->VelY -= ply->Speed;
			}
			if (ply->Speed < MAXSPEED && tecla->Down) {
				ply->VelY += ply->Speed;
			}
		}

		void MovPlayer(PlayerType *ply, KeyInput *tecla) {
			if (tecla->Left || tecla->Right){
				ply->X += ply->VelX;
			}
			if (tecla->Up || tecla->Down) {
				ply->Y += ply->VelY;
			}
		}
};