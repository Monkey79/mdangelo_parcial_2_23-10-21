/*
 * ArcadeEnt.h
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#ifndef ENTITIES_ARCADEENT_H_
#define ENTITIES_ARCADEENT_H_

#include "../properties_file.h"

typedef struct{
	int arcId; //ai

	char arcCitizenship[STR_100];
	int arcSoundType;
	int arcPlyAmount;
	int arcCoinsCap;
	char arcSaloonName[STR_200];

	int arcGameId;
}ArcadeEnt;

#endif /* ENTITIES_ARCADEENT_H_ */
