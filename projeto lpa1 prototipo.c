#include <stdio.h>
#include <stdlib.h>
#define String 5
#define Horario 24

int main() {
	// ------- Cria??o de Vari?veis -------------------------
	int i, j, k, m, n;
	int alternativa1, alternativa2, menu1 = 0, contadorRegistro = 0, menu2 = 0, diasMeta = 0;
	char senhaGeral[String], loginGeral[String], agenda[Horario][diasMeta];
	char senhaUsuario, loginUsuario, metaUsuario, respostaMenu2;
	
	//-------------INICIO DO PROGRAMA------------------
	
	// PRIMEIRO MENU 
	do {
		printf("\n>>>>>>>>>>>>>>>>>> BEM VINDO AO PROGRAMA <<<<<<<<<<<<<<<<<<<<\n");
		printf("> (1) - Registrar                                           <\n");
		printf("> (2) - Logar                                               <\n");
		printf("> (0) - Sair                                                <\n");
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		
		printf("\nDigite a alternativa: ");
		fflush(stdin);
		scanf("%i", &alternativa1);
		
		// Verifica??o em loop
			
		while(alternativa1 < 0 || alternativa1 > 2) {
			printf("\nVoc? digitou uma op??o inv?lida. Digite uma das op??es acima: ");
			fflush(stdin);
			scanf("%i", &alternativa1);
		}
		
		// Escolha das alternativas
		
		switch (alternativa1) {
			
			case 1:
				
				printf("\nDigite seu login: ");
				fflush(stdin);
				scanf("%c", &loginGeral[contadorRegistro]);
				
				printf("\nDigite sua senha: ");
				fflush(stdin);
				scanf("%c", &senhaGeral[contadorRegistro]);
				
				contadorRegistro++;
				
				break;
	
			case 2:
				
				printf("\nDigite seu login: ");
				fflush(stdin);
				scanf("%c", &loginUsuario);
				
				printf("\nDigite sua senha: ");
				fflush(stdin);
				scanf("%c", &senhaUsuario);
				
				// Verifica??o Login e Senha
				
				for(i = 0; i < String; i++) {
					
					if(loginGeral[i] == loginUsuario && senhaGeral[i] == senhaUsuario) {
						
						menu2 = 1;
						
					} 
					
				}
				
				if(menu2 == 1) {
					
					printf("\nLogin e senha corretos!");
					
				} else {
					
					printf("\nLogin e/ou senha incorretos!");
					
				}
				
				// ---------------- SEGUNDO MENU -------------------
				
				while(menu2 == 1) {
					
					printf("\n>>>>>>>>>>>>>>>>>>>>>> SEGUNDO MENU <<<<<<<<<<<<<<<<<<<<<<<<<\n");
					printf("> (1) - Perguntas                                           <\n");
					printf("> (2) - Preencher Agenda                                    <\n");
					printf("> (0) - Voltar                                              <\n");
					printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
					
					printf("\nDigite a alternativa: ");
					fflush(stdin);
					scanf("%i", &alternativa2);
					
					switch(alternativa2) {
						
						case 1:
							
							printf("\nOpa, tudo certo? Vamos precisar fazer algumas perguntinhas antes de abrir a op??o agenda! Pronto? (S) - Para Sim / (N) - Para N?o\n");
							fflush(stdin);
							scanf("%c", &respostaMenu2);
							
							if(respostaMenu2 == 'S'){
								
								printf("\n1? pergunta: Qual a sua meta?\n");
								fflush(stdin);
								scanf("%c", &metaUsuario);
								printf("\n2? pergunta: Quantos dias voce tem at? a sua meta?\n");
								fflush(stdin);
								scanf("%c", &diasMeta);
							
							} else {
								
								printf("\nQue pena! Adorar?amos te conhecer um pouco melhor!");
								
							}
							
							break;
						
						case 2:
							
							for(j = 0; j < 24; j++) {
								
								for(k = 0 ; k < 7; k++) {
									
									agenda[j][k] = 'a';
									
								}
								
							}
							
							for(m = 0; m < 24; m++) {
								
								for(n = 0 ; n < 7; n++) {
									
									printf("%0.2c", agenda[m][n]);
									printf(" ");
									
								}
								
							}
							
							break;
						
						case 0:
			
							menu2 = 0;
							
							break;
							
					} 
					
					
				}
				
				break;
				
			case 0:
				
				printf("\nPrograma Finalizado!");
				menu1 = 1;
				
				break;
				
		}
		
	} while (menu1 != 1);
	
	system("PAUSE");
	return 0;
}
