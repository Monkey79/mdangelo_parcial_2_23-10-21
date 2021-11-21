/*
 * AracadeRepo.c
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#include "AracadeRepo.h"

ArcadeEnt* ar_createNewArcade(ArcadeDto arcDto){
	ArcadeEnt* arcEnt = (ArcadeEnt*) malloc(sizeof(ArcadeEnt));

	if(arcEnt!=NULL){
		arcEnt->arcId = atoi(arcDto.arcIdStr);
		strcpy(arcEnt->arcCitizenship, arcDto.arcCtzshpStr);

		if(!(strcmp(arcDto.arcSndTypeStr,"MONO"))){
			arcEnt->arcSoundType = 1;
		}else if(!(strcmp(arcDto.arcSndTypeStr,"STEREO"))){
			arcEnt->arcSoundType = 2;
		}
		arcEnt->arcGameId = arcDto.arcGameId;
		strcpy(arcEnt->arcGameName, arcDto.arcGameName);
		arcEnt->arcPlyAmount = atoi(arcDto.arcPlyAmntStr);
		arcEnt->arcCoinsCap = atoi(arcDto.arcCoinsCapStr);
		strcpy(arcEnt->arcSaloonName, arcDto.arcSaloonName);
	}else{
		printf(ERROR_NO_MEMORY);
	}
	return arcEnt;
}


