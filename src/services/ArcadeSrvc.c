/*
 * ArcadeSrvc.c
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#include "ArcadeSrvc.h"

void _writeArcadesFile(LinkedList* arcLList,LinkedList* gmLList);

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
					arcDto.arcGameId = gr_getGameIdByName(*gamesLList,arcDto.arcGameName); //busco id de juego por su nombre
					arcEnt = ar_createNewArcade(arcDto); //creo arcade a partir de su dto
					if(arcEnt!=NULL){
						ll_add(*arcadesLList,arcEnt);
					}
				}
			} while (!feof(arcFile));
		}
	}
	fclose(arcFile);
	return success;
}

int as_createNewArcade(LinkedList** arcadesLList,LinkedList** gamesLList){
	int success = TRUE;
	ArcadeDto arcDto;
	ArcadeEnt* arcEnt = ll_get(*arcadesLList, (*arcadesLList)->size-1); //ultimo elemento de la lista
	int rst;

	if(arcEnt != NULL){
		sprintf(arcDto.arcIdStr, "%d",arcEnt->arcId+1);
		su_getStringValue("-ingrese nacionalidad del arcade-\n", arcDto.arcCtzshpStr);
		su_cleanString(arcDto.arcCtzshpStr, STR_100);
		su_getStringValueConditional("-ingrese tipo de sonido [MONO-STEREO]-\n",arcDto.arcSndTypeStr,"MONO","STEREO");
		su_cleanString(arcDto.arcSndTypeStr, STR_6);
		su_getStringValue("-ingrese cantidad de jugadores-\n",arcDto.arcPlyAmntStr);
		su_cleanString(arcDto.arcPlyAmntStr, STR_6);
		su_getStringValue("-ingrese capacidad max de fichas-\n",arcDto.arcCoinsCapStr);
		su_cleanString(arcDto.arcCoinsCapStr, STR_6);
		su_getStringValue("-ingrese nombre del salon que pertenece-\n",arcDto.arcSaloonName);
		su_cleanString(arcDto.arcSaloonName, STR_200);

		gs_printAllGames(*gamesLList);
		su_getStringValue("--de los siguientes juegos ingrese un juego valido--\n",arcDto.arcGameName);
		su_cleanString(arcDto.arcGameName, STR_200);

		gs_ifNotExistCreate(gamesLList,arcDto.arcGameName);
		arcDto.arcGameId = gs_getGameIdByName(*gamesLList, arcDto.arcGameName);

		arcEnt = ar_createNewArcade(arcDto);
		rst = ll_add(*arcadesLList, arcEnt);

		if(!rst){
			_writeArcadesFile(*arcadesLList,*gamesLList);
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
		as_printAllArcades(*arcadesLList, *gamesLList);
		arcId = iu_getPositiveIntegerValue("-de los siguientes arcades seleccione un id valido para modificar--\n");

		for(int i=0;i<(*arcadesLList)->size && !match;i++){
			arcEntUpd = ll_get(*arcadesLList, i);
			match = (arcEntUpd->arcId == arcId)?TRUE:FALSE;
		}
	} while (!match);

	arcPlyAm = iu_getPositiveIntegerValue("-ingrese cantidad de jugadores-\n");

	gs_printAllGames(*gamesLList);
	su_getStringValue("--de los siguientes juegos ingrese un juego valido--\n",arcGame);
	su_cleanString(arcGame, STR_200);
	gs_ifNotExistCreate(gamesLList,arcGame);

	qst = str_getYesNoQstion("-desea actualizar el arcade? [S|N]-\n");

	if(qst=='S'){
		arcEntUpd->arcPlyAmount = arcPlyAm;
		arcEntUpd->arcGameId = gs_getGameIdByName(*gamesLList, arcGame);
		_writeArcadesFile(*arcadesLList,*gamesLList);
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
		as_printAllArcades(*arcadesLList, *gamesLList);
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
			_writeArcadesFile(*arcadesLList, *gamesLList);
		}
	}else{
		printf("-eliminacion cancelada-\n");
		success = FALSE;
	}

	return success;
}

void as_printAllArcades(LinkedList* arcLList,LinkedList* gameLList){
	ArcadeEnt* arcEnt;
	int arcLen;
	char sndType[STR_6];
	char arcGameName[STR_200];
	if(arcLList!=NULL){
		arcLen = arcLList->size;
		for(int i=0; i<arcLen;i++){
			arcEnt = ll_get(arcLList, i); //obtengo elemento
			strcpy(sndType,(arcEnt->arcSoundType==1)?"MONO":(arcEnt->arcSoundType==2)?"STEREO":"UNDEFINED");//convierto a mono o stereo (segun corresponda)
			gr_getGameNameById(gameLList,arcEnt->arcGameId,arcGameName); //obtengo nombre del juego segun su id
			printf("-arcade.id=%d | arcade.nacionalidad=%s | arcade.tipo_sonido=%s | arcade.jugadores=%d | arcade.fichas=%d | arcade.salon=%s | arcade.juego=%s\n"
					,arcEnt->arcId, arcEnt->arcCitizenship,sndType,arcEnt->arcPlyAmount, arcEnt->arcCoinsCap, arcEnt->arcSaloonName,
					arcGameName);
		}
	}
}


//------Private------------
void _writeArcadesFile(LinkedList* arcLList,LinkedList* gmLList){
	FILE* arcFile = NULL;
	arcFile = fu_openFileByMode(ARCADE_FILE, "w"); //abro archivo

	ArcadeEnt* arcEnt=NULL;
	ArcadeDto arcDto;
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
			gs_getGameNameById(gmLList,arcEnt->arcGameId,arcDto.arcGameName);

			if(i==gmLen-1){
				fprintf(arcFile,"%s,%s,%s,%s,%s,%s,%s",arcDto.arcIdStr,
											arcEnt->arcCitizenship,arcDto.arcSndTypeStr,
											arcDto.arcPlyAmntStr,arcDto.arcCoinsCapStr,
											arcEnt->arcSaloonName,arcDto.arcGameName);
			}else{
				fprintf(arcFile,"%s,%s,%s,%s,%s,%s,%s\n",arcDto.arcIdStr,
											arcEnt->arcCitizenship,arcDto.arcSndTypeStr,
											arcDto.arcPlyAmntStr,arcDto.arcCoinsCapStr,
											arcEnt->arcSaloonName,arcDto.arcGameName);
			}
		}
		fclose(arcFile);
	}
}

