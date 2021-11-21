/*
 * AracadeRepo.h
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#ifndef REPOSITORIES_ARACADEREPO_H_
#define REPOSITORIES_ARACADEREPO_H_

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include "../entities/ArcadeEnt.h"
#include "../dto/ArcadeDto.h"

ArcadeEnt* ar_createNewArcade(ArcadeDto arcDto);

#endif /* REPOSITORIES_ARACADEREPO_H_ */
