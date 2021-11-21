/*
 * GameRepo.c
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */


#include "GameRepo.h"

GameEnt* gr_createGame(char* gmIdStr,char* gmName){
	GameEnt* gmEnt = (GameEnt*) malloc(sizeof(GameEnt));
	if(gmEnt != NULL){
		gmEnt->gameId = atoi(gmIdStr);
		strcpy(gmEnt->gameName, gmName);
	}else
		printf(ERROR_NO_MEMORY);

	return gmEnt;
}
int gr_getGameIdByName(LinkedList* gmLList,char* gameName){
	int match = FALSE;
	int id = -1;
	GameEnt* gmEnt;

	if(gmLList != NULL){
		for (int i = 0; i<gmLList->size && !match; i++) {
			gmEnt = ll_get(gmLList, i);
			match = (strcmp(gmEnt->gameName,gameName)==0)?TRUE:FALSE;
			if(match) id = gmEnt->gameId;
		}
	}
	return id;
}

int gr_getGameNameById(LinkedList* gmLList,int gameId,char* gameName){
	int success = TRUE;
	int match = FALSE;
	GameEnt* gmEnt;

	if(gmLList != NULL){
		for (int i = 0; i<gmLList->size && !match; i++) {
			gmEnt = ll_get(gmLList, i);
			match = gmEnt->gameId == gameId;
			if(match) strcpy(gameName,gmEnt->gameName);
		}
	}else
		success = FALSE;

	return success;
}

