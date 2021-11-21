/*
 * GameRepo.h
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#ifndef REPOSITORIES_GAMEREPO_H_
#define REPOSITORIES_GAMEREPO_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

#include "../properties_file.h"
#include "../entities/GameEnt.h"
#include "../utils/LinkedList.h"

GameEnt* gr_createGame(char* gmIdStr,char* gmName);
int gr_getGameIdByName(LinkedList* gmLList,char* gameName);
int gr_getGameNameById(LinkedList* gmLList,int gameId,char* gameName);

#endif /* REPOSITORIES_GAMEREPO_H_ */
