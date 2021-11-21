/*
 * GameSrvc.c
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#include "GameSrvc.h"

void _writeGamesFile(LinkedList* gmLList);

GameEnt* gs_createNewGameEnt(char* gmId, char* gmName){
	return gr_createGame(gmId, gmName);
}

int gs_chargeGamesFromFile(LinkedList** gamesLList){
	int success = TRUE;
	FILE* gmFile = NULL;
	GameEnt* gmEnt = NULL;

	char gmId[STR_6];
	char gmName[STR_200];

	int cnt;

	if(gamesLList!=NULL){
		gmFile = fu_openFileByMode(GAME_FILE, "r"); //abro archivo
		if(gmFile!=NULL){
			cnt = fscanf(gmFile,GAME_REGEX,gmId,gmName); //avoid header
			do {
				cnt = fscanf(gmFile,GAME_REGEX,gmId,gmName); //avoid header
				if(cnt == 2){
					gmEnt = gr_createGame(gmId, gmName);
					if(gmEnt!=NULL){
						ll_add(*gamesLList, gmEnt);
					}
				}
			} while (!feof(gmFile));
		}
	}else
		success = FALSE;

	fclose(gmFile);
	return success;
}

int gs_writeGames(LinkedList* gmLList){
	int success = TRUE;

	if(gmLList!=NULL){
		_writeGamesFile(gmLList);
	}else
		success = FALSE;

	return success;
}

void gs_ifNotExistCreate(LinkedList** gmLList, char* gameStr){
	int match = FALSE;
	GameEnt* gmEnt = NULL;
	char gmIdStr[STR_100];
	int rsl;

	if(gmLList!=NULL){
		for(int i=0; i<(*gmLList)->size && !match; i++){
			gmEnt = ll_get(*gmLList, i);
			match = (strcmp(gmEnt->gameName, gameStr)==0)?TRUE:FALSE;
		}
		if(!match){
			printf("-el juego no existe lo creo-\n");

			sprintf(gmIdStr, "%d",gmEnt->gameId+1);
			gmEnt = gr_createGame(gmIdStr,gameStr);
			rsl = ll_add(*gmLList, gmEnt);

			if(!rsl){
				printf("-el juego en la lista se creo bien ahora a escribir archivo-\n");
				_writeGamesFile(*gmLList);
			}
		}
	}

}

void gs_printAllGames(LinkedList* gameLList){
	GameEnt* gmEnt = NULL;
	for(int i=0;i<gameLList->size;i++){
		gmEnt = ll_get(gameLList, i);
		printf("-juego.id=%d | juego.nombre=%s\n",gmEnt->gameId,gmEnt->gameName);
	}
}

int gs_getGameNameById(LinkedList* gmLList,int gameId,char* gameName){
	return gr_getGameNameById(gmLList, gameId, gameName);
}

int gs_getGameIdByName(LinkedList* gmLList,char* gameName){
	return gr_getGameIdByName(gmLList, gameName);
}

int gs_gameAlreadyExist(LinkedList* gmLList,char* gameName){
	GameEnt* gmEnt=NULL;
	int match = FALSE;
	for (int i = 0; i < gmLList->size && !match; i++) {
		gmEnt = ll_get(gmLList, i);
		match = (strcmp(gmEnt->gameName, gameName)==0)?TRUE:FALSE;
	}
	return match;
}


//------Private------------
void _writeGamesFile(LinkedList* gmLList){
	FILE* gmFile = NULL;
	GameEnt* gmEnt = NULL;
	int len;
	char gmIdStr[STR_100];

	printf("-el juego en la lista se creo bien ahora a escribir archivo-\n");
	gmFile = fu_openFileByMode(GAME_FILE, "w"); //abro archivo
	if(gmFile!=NULL){
		len = ll_len(gmLList);
		fprintf(gmFile,"%s,%s\n","id","game");
		for(int i=0;i<len;i++){
			gmEnt = ll_get(gmLList, i);
			sprintf(gmIdStr,"%d",gmEnt->gameId);
			if(i==(len-1))
				fprintf(gmFile,"%s,%s",gmIdStr,gmEnt->gameName);
			else
				fprintf(gmFile,"%s,%s\n",gmIdStr,gmEnt->gameName);
		}
	}
	fclose(gmFile);
}


