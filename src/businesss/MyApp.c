/*
 * MyApp.c
 * Created on: 20 nov. 2021
 * Author: Mariano DAngelo
 */
#include "MyApp.h"

void _checkUsrSelection(LinkedList** arcadesLList,LinkedList** gamesLList, int usrSlct);

void ma_startApplication(void) {
	//"1-Leer arcades desde archivo csv (modo texto)-",
	char* menuItems[] = {
				"1-Incorporar arcade-",
				"2-Modificar arcade-",
				"3-Eliminar arcade-",
				"4-Imprimir arcades (ord nombre de juego)-",
				"5-Generar archivo juego (y mostrarlo)-",
				"6-Generar archivo multi-jugador-",
				"7-Actualizar cantidad de fichas-",
				"8-Imprimir arcades y juegos (sin ordenar)-",
				"0--SALIR--"};

	LinkedList* arcadesLList = ll_newLinkedList();
	LinkedList* gamesLList = ll_newLinkedList();
	int usrSlct;

	_checkUsrSelection(&arcadesLList, &gamesLList,10);

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
		case 10:
			printf("-leer arcade-\n");
			//gs_chargeGamesFromFile(gamesLList);//deprecated
			as_chargeArcadeFromFile(arcadesLList,gamesLList);
			break;
		case 1:
			printf("-crear arcade-\n");
			as_createNewArcade(arcadesLList, gamesLList);
			break;
		case 2:
			printf("-modificar arcade-\n");
			as_updateArcade(arcadesLList, gamesLList);
			break;
		case 3:
			printf("-eliminar arcade-\n");
			as_deleteArcade(arcadesLList, gamesLList);
			break;
		case 4:
			printf("-imprimir arcade-\n");
			as_printAllArcadesSortByGame(arcadesLList,gamesLList);
			break;
		case 5:
			printf("-generar juegos-\n");
			gs_printAllGames(*gamesLList);
			break;
		case 6:
			printf("-generar multi-jugador-\n");
			as_createMultiPlayerFile(arcadesLList);
			break;
		case 7:
			printf("-actualizar fichas-\n");
			as_upgradeCoinsCapacity(arcadesLList);
			break;
		case 8:
			printf("-imprimir todo (sin ordenar)-\n");
			as_printAllArcades(*arcadesLList);
			gs_printAllGames(*gamesLList);
			break;
		default:
			printf("-SIN DEFINIR-\n");
			break;
	}
}
