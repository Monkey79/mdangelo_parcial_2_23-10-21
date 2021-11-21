/*
 * GameEnt.h
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#ifndef ENTITIES_GAMEENT_H_
#define ENTITIES_GAMEENT_H_

#include "../properties_file.h"

typedef struct {
	int gameId;
	char gameName[STR_200];
}GameEnt;

#endif /* ENTITIES_GAMEENT_H_ */
