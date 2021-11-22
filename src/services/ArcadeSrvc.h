/*
 * ArcadeSrvc.h
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#ifndef SERVICES_ARCADESRVC_H_
#define SERVICES_ARCADESRVC_H_

#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

#include "../properties_file.h"

#include "../utils/LinkedList.h"
#include "../utils/FileUtil.h"
#include "../utils/StringUtil.h"
#include "../utils/IntUtil.h"

#include "../services/GameSrvc.h"

#include "../repositories/AracadeRepo.h"
#include "../repositories/GameRepo.h"

#include "../entities/GameEnt.h"
#include "../entities/ArcadeEnt.h"
#include "../dto/ArcadeDto.h"



int as_chargeArcadeFromFile(LinkedList** arcadesLList,LinkedList** gamesLList);
int as_createGameFile(LinkedList** arcadesLList,LinkedList** gamesLList);

int as_createNewArcade(LinkedList** arcadesLList,LinkedList** gamesLList);
int as_updateArcade(LinkedList** arcadesLList,LinkedList** gamesLList);
int as_deleteArcade(LinkedList** arcadesLList,LinkedList** gamesLList);

void as_printAllArcades(LinkedList* arcLList);
void as_printAllArcadesSortByGame(LinkedList** arcLList,LinkedList** gameLList);

void as_createMultiPlayerFile(LinkedList** arcadesLList);
void as_upgradeCoinsCapacity(LinkedList** arcadesLList);
#endif /* SERVICES_ARCADESRVC_H_ */
