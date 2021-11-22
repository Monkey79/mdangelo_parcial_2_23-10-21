/*
 * ArcadeSrvc.c
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#include "ArcadeSrvc.h"

//----Private-----
void _writeArcadesFile(LinkedList* arcLList,char* fileName);
int _isGameNameLessThan(void* pElm1, void* pElm2);
int _hasTheArcadeMoreThanNPlayer(void* pElm);
int _upgradeCoinsCapacity(void* pElm);

int as_chargeArcadeFromFile(LinkedList** arcadesLList,LinkedList** gamesLList){
	int success = TRUE;

	FILE* arcFile = NULL;
	ArcadeDto arcDto;
	ArcadeEnt* arcEnt=NULL;
	int cnt;


	if(*arcadesLList != NULL){
		arcFile = fu_openFileByMode(ARCADE_FILE, "r"); //abro archivo
		if(arcFile != NULL){
			cnt = fscanf(arcFile, ARCADE_REGEX, arcDto.arcIdStr, arcDto.arcCtzshpStr, arcDto.arcSndTypeStr,arcDto.arcPlyAmntStr,arcDto.arcCoinsCapStr,arcDto.arcSaloonName,arcDto.arcGameName); //avoid header
			do {
				//leo registro
				cnt = fscanf(arcFile, ARCADE_REGEX, arcDto.arcIdStr, arcDto.arcCtzshpStr, arcDto.arcSndTypeStr,arcDto.arcPlyAmntStr,arcDto.arcCoinsCapStr,arcDto.arcSaloonName,arcDto.arcGameName);
				if(cnt==7){
					//arcDto.arcGameId = gr_getGameIdByName(*gamesLList,arcDto.arcGameName); //busco id de juego por su nombre
					arcEnt = ar_createNewArcade(arcDto); //creo arcade a partir de su dto
					if(arcEnt!=NULL){
						ll_add(*arcadesLList,arcEnt);
					}
				}
			} while (!feof(arcFile));
		}
		as_createGameFile(arcadesLList, gamesLList); //[punto-6] luego de tener el llist de arcades inmediatamente despues creo el llist de juegos sin repetir
	}
	fclose(arcFile);
	return success;
}

int as_createGameFile(LinkedList** arcadesLList,LinkedList** gamesLList){
	int success = TRUE;
	int arLn;
	GameEnt* gmEnt;
	ArcadeEnt* arEnt;
	char gmIdStr[STR_200];
	int newId=0;

	if(*arcadesLList != NULL && *gamesLList != NULL){
		arLn = ll_len(*arcadesLList);
		for(int i=0; i<arLn; i++){
			arEnt = ll_get(*arcadesLList, i);
			sprintf(gmIdStr, "%d",(i+1));
			gmEnt = gs_createNewGameEnt(gmIdStr,arEnt->arcGameName);
			if(!gs_gameAlreadyExist(*gamesLList, gmEnt->gameName)){ //si NO existe en la lista lo adjunto
				gmEnt->gameId = ++newId;
				ll_add(*gamesLList, gmEnt);
			}
		}
		gs_writeGames(*gamesLList); //genero archito txt "games.csv"
	}
	return success;
}

int as_createNewArcade(LinkedList** arcadesLList,LinkedList** gamesLList){
	int success = TRUE;
	ArcadeDto arcDto;
	ArcadeEnt* arcEnt = ll_get(*arcadesLList, (*arcadesLList)->size-1); //ultimo elemento de la lista
	int rst;

	if(arcEnt != NULL){
		sprintf(arcDto.arcIdStr, "%d",arcEnt->arcId+1);
		su_getAlphabeticStringValue("-ingrese nacionalidad del arcade-\n", arcDto.arcCtzshpStr);
		su_cleanString(arcDto.arcCtzshpStr, STR_100);
		su_getStringValueConditional("-ingrese tipo de sonido [MONO-STEREO]-\n",arcDto.arcSndTypeStr,"MONO","STEREO");
		su_cleanString(arcDto.arcSndTypeStr, STR_6);
		su_getStringValue("-ingrese cantidad de jugadores-\n",arcDto.arcPlyAmntStr);
		su_cleanString(arcDto.arcPlyAmntStr, STR_6);
		su_getStringValue("-ingrese capacidad max de fichas-\n",arcDto.arcCoinsCapStr);
		su_cleanString(arcDto.arcCoinsCapStr, STR_6);
		su_getAlphabeticStringValue("-ingrese nombre del salon que pertenece-\n",arcDto.arcSaloonName);
		su_cleanString(arcDto.arcSaloonName, STR_200);

		gs_printAllGames(*gamesLList);
		su_getAlphabeticStringValue("--de los siguientes juegos ingrese un nombre de juego valido--\n",arcDto.arcGameName);
		su_cleanString(arcDto.arcGameName, STR_200);

		//cuando se crea un arcade nuevo y el juego que ingresa el usuario NO existe lo creo y actualizo el archivo "games.csv"
		gs_ifNotExistCreate(gamesLList,arcDto.arcGameName);
		arcDto.arcGameId = gs_getGameIdByName(*gamesLList, arcDto.arcGameName);

		arcEnt = ar_createNewArcade(arcDto);
		rst = ll_add(*arcadesLList, arcEnt);

		if(!rst){
			_writeArcadesFile(*arcadesLList,ARCADE_FILE);
		}else
			printf("--error creacion de nuevo arcade--\n");
	}
	return success;
}

int as_updateArcade(LinkedList** arcadesLList,LinkedList** gamesLList){
	int success = TRUE;
	int arcId;
	char qst;

	ArcadeEnt* arcEntUpd = NULL;
	int match = FALSE;

	int arcPlyAm;
	char arcGame[STR_200];


	do {
		as_printAllArcades(*arcadesLList);
		arcId = iu_getPositiveIntegerValue("-de los siguientes arcades seleccione un id valido para modificar--\n");

		for(int i=0;i<(*arcadesLList)->size && !match;i++){
			arcEntUpd = ll_get(*arcadesLList, i);
			match = (arcEntUpd->arcId == arcId)?TRUE:FALSE;
		}
	} while (!match);

	arcPlyAm = iu_getPositiveIntegerValue("-ingrese cantidad de jugadores-\n");

	gs_printAllGames(*gamesLList);
	su_getAlphabeticStringValue("--de los siguientes juegos ingrese un nombre de juego valido--\n",arcGame);
	su_cleanString(arcGame, STR_200);
	gs_ifNotExistCreate(gamesLList,arcGame);

	qst = str_getYesNoQstion("-desea actualizar el arcade? [S|N]-\n");

	if(qst=='S'){
		arcEntUpd->arcPlyAmount = arcPlyAm;
		arcEntUpd->arcGameId = gs_getGameIdByName(*gamesLList, arcGame);
		strcpy(arcEntUpd->arcGameName, arcGame);
		_writeArcadesFile(*arcadesLList, ARCADE_FILE);
		printf("--actualizacion correcta--\n");
	}else{
		printf("-actualizacion cancelada-\n");
		success = FALSE;
	}

	return success;
}

int as_deleteArcade(LinkedList** arcadesLList,LinkedList** gamesLList){
	int success = TRUE;
	int match = FALSE;
	int arcId;
	int arcIdx;

	ArcadeEnt* arcEntDel = NULL;
	char qst;

	do {
		as_printAllArcades(*arcadesLList);
		arcId = iu_getPositiveIntegerValue("-de los siguientes arcades seleccione un id valido para modificar--\n");

		for(int i=0;i<(*arcadesLList)->size && !match;i++){
			arcEntDel = ll_get(*arcadesLList, i);
			match = (arcEntDel->arcId == arcId)?TRUE:FALSE;
		}
	} while (!match);

	qst = str_getYesNoQstion("-desea eliminar el arcade? [S|N]-\n");

	if(qst=='S'){
		arcIdx = ll_indexOf(*arcadesLList, arcEntDel);
		if(arcIdx>=0){
			success = ll_remove(*arcadesLList, arcIdx);
		}
		if(success==0){
			printf("--eliminacion exitosa--\n");
			_writeArcadesFile(*arcadesLList, ARCADE_FILE);
		}
	}else{
		printf("-eliminacion cancelada-\n");
		success = FALSE;
	}

	return success;
}

void as_printAllArcades(LinkedList* arcLList){
	ArcadeEnt* arcEnt;
	int arcLen;
	char sndType[STR_6];
	if(arcLList!=NULL){
		arcLen = arcLList->size;
		for(int i=0; i<arcLen;i++){
			arcEnt = ll_get(arcLList, i); //obtengo elemento
			strcpy(sndType,(arcEnt->arcSoundType==1)?"MONO":(arcEnt->arcSoundType==2)?"STEREO":"UNDEFINED");//convierto a mono o stereo (segun corresponda)
			printf("-arcade.id=%d | arcade.nacionalidad=%s | arcade.tipo_sonido=%s | arcade.jugadores=%d | arcade.fichas=%d | arcade.salon=%s | arcade.juego=%s\n"
					,arcEnt->arcId, arcEnt->arcCitizenship,sndType,arcEnt->arcPlyAmount, arcEnt->arcCoinsCap, arcEnt->arcSaloonName,
					arcEnt->arcGameName);
		}
	}
}

void as_printAllArcadesSortByGame(LinkedList** arcLList,LinkedList** gameLList){
	if(arcLList!=NULL && *gameLList!=NULL){
		ll_sort(*arcLList, _isGameNameLessThan, 0); //[1] Indica orden ascendente - [0] Indica orden descendente
	}
	as_printAllArcades(*arcLList);
}

void as_createMultiPlayerFile(LinkedList** arcadesLList){
	LinkedList* cloneArcLList = ll_clone(*arcadesLList);
	if(*arcadesLList!=NULL){
		ll_filter(cloneArcLList, _hasTheArcadeMoreThanNPlayer); //filtro lista previamente clonada
		as_printAllArcades(cloneArcLList);
		_writeArcadesFile(cloneArcLList, ARCADE_MP_FILE);
	}else{
		printf("-no puedo generar nada desde una lista vacia o nula-\n");
	}
}

//NOTE: Asumo como que se modifica la capc de fichas de todos los elementos de la lista
//los mismos deben actualizarse, tambien, en el archivo arcades.csv
void as_upgradeCoinsCapacity(LinkedList** arcadesLList){
	char qst;
	qst = str_getYesNoQstion("--¿Esta seguro de aplicar el cambio (impactara en toda la lista y en el archivo)? [S|N]--\n");
	if(qst=='S'){
		ll_map(*arcadesLList, _upgradeCoinsCapacity);
		as_printAllArcades(*arcadesLList);
		_writeArcadesFile(*arcadesLList, ARCADE_FILE); //actualizo el archivo arcades.csv
	}else{
		printf("--Actualizacion fichas CANCELADA--\n");
	}
}

//------Private------------
void _writeArcadesFile(LinkedList* arcLList,char* fileName){
	FILE* arcFile = NULL;
	arcFile = fu_openFileByMode(fileName, "w"); //abro archivo

	ArcadeEnt* arcEnt=NULL;
	ArcadeDto arcDto; //uso un Dto para para almacenar valores casteados a string
	int gmLen;


	if(arcFile!=NULL){
		fprintf(arcFile,"%s,%s,%s,%s,%s,%s,%s\n","id","nacionalidad","tipo_sonido","cant_jug","fichas_max","salon","game");
		gmLen = ll_len(arcLList);
		for(int i=0;i<gmLen;i++){
			arcEnt = ll_get(arcLList, i);

			sprintf(arcDto.arcIdStr, "%d",arcEnt->arcId);
			strcpy(arcDto.arcSndTypeStr, (arcEnt->arcSoundType)==1?"MONO":(arcEnt->arcSoundType)==2?"STEREO":"UNDEFINED");
			sprintf(arcDto.arcPlyAmntStr, "%d",arcEnt->arcPlyAmount);
			sprintf(arcDto.arcCoinsCapStr, "%d",arcEnt->arcCoinsCap);

			if(i==gmLen-1){
				fprintf(arcFile,"%s,%s,%s,%s,%s,%s,%s",arcDto.arcIdStr,
											arcEnt->arcCitizenship,arcDto.arcSndTypeStr,
											arcDto.arcPlyAmntStr,arcDto.arcCoinsCapStr,
											arcEnt->arcSaloonName,arcEnt->arcGameName);
			}else{
				fprintf(arcFile,"%s,%s,%s,%s,%s,%s,%s\n",arcDto.arcIdStr,
											arcEnt->arcCitizenship,arcDto.arcSndTypeStr,
											arcDto.arcPlyAmntStr,arcDto.arcCoinsCapStr,
											arcEnt->arcSaloonName,arcEnt->arcGameName);
			}
		}
		fclose(arcFile);
	}
}
//[1]=Indica orden ascendente - [0]=Indica orden descendente
int _isGameNameLessThan(void* pElm1, void* pElm2){
	int rst;
	ArcadeEnt* arc1 = (ArcadeEnt *) pElm1;
	ArcadeEnt* arc2 = (ArcadeEnt *) pElm2;
	rst = (strcmp(arc1->arcGameName, arc2->arcGameName)<0)?-1:(strcmp(arc1->arcGameName, arc2->arcGameName)==0)?-1:1;
	return rst;
}

int _hasTheArcadeMoreThanNPlayer(void* pElm){
	ArcadeEnt* arcEnt = (ArcadeEnt*) pElm;
	return (arcEnt->arcPlyAmount > PLAYER_TOP);
}

int _upgradeCoinsCapacity(void* pElm){
	int scss = TRUE;
	ArcadeEnt* arc1 = (ArcadeEnt *) pElm;
	arc1->arcCoinsCap *= 2;
	return scss;
}

