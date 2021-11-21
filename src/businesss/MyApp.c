/*
 * MyApp.c
 * Created on: 20 nov. 2021
 * Author: Mariano DAngelo
 */
#include "MyApp.h"

void _checkUsrSelection(LinkedList** arcadesLList,LinkedList** gamesLList, int usrSlct);

void ma_startApplication(void) {
	char* menuItems[] = {"1-Leer arcades desde archivo csv (modo texto)-",
			"2-Incorporar arcade-",
			"3-Modificar arcade-",
			"4-Eliminar arcade-",
			"5-Imprimir arcades-",
			"6-Generar archivo juego-",
			"7-Generar archivo multi-jugador-",
			"8-Actualizar cantidad de fichas-",
			"0--SALIR--",};

	LinkedList* arcadesLList = ll_newLinkedList();
	LinkedList* gamesLList = ll_newLinkedList();
	int usrSlct;

	if(arcadesLList != NULL){
		do {
			su_showMatrixStrings(menuItems,9);
			__fpurge(stdin);
			scanf("%d",&usrSlct);
			_checkUsrSelection(&arcadesLList, &gamesLList, usrSlct);
		} while (usrSlct!= EXIT);
	}else{
		printf(MAIN_ERROR);
		exit(0);
	}
}

void _checkUsrSelection(LinkedList** arcadesLList,LinkedList** gamesLList, int usrSlct){
	switch (usrSlct) {
		case 1:
			printf("-leer arcade-\n");
			//gs_chargeGamesFromFile(gamesLList);
			as_chargeArcadeFromFile(arcadesLList,gamesLList);
			break;
		case 2:
			printf("-crear arcade-\n");
			as_createNewArcade(arcadesLList, gamesLList);
			break;
		case 3:
			printf("-modificar arcade-\n");
			as_updateArcade(arcadesLList, gamesLList);
			break;
		case 4:
			printf("-eliminar arcade-\n");
			as_deleteArcade(arcadesLList, gamesLList);
			break;
		case 5:
			printf("-imprimir arcade-\n");
			//gs_printAllGames(*gamesLList);
			as_printAllArcades(*arcadesLList, *gamesLList);

			as_printAllArcadesSortByGame(arcadesLList,gamesLList);
			break;
		case 6:
			printf("-generar juegos-\n");
			break;
		case 7:
			printf("-generar multi-jugador-\n");
			break;
		case 8:
			printf("-actualizar fichas-\n");
			break;
		default:
			printf("-SIN DEFINIR-\n");
			break;
	}
}
