/*
 * ArcadeDto.h
 *
 *  Created on: 20 nov. 2021
 *      Author: Mariano DAngelo
 */

#ifndef DTO_ARCADEDTO_H_
#define DTO_ARCADEDTO_H_

#include "../properties_file.h"

typedef struct{
	char arcIdStr[STR_6];

	char arcCtzshpStr[STR_100];
	char arcSndTypeStr[STR_6];
	char arcPlyAmntStr[STR_6];
	char arcCoinsCapStr[STR_6];

	char arcSaloonName[STR_200];
	char arcGameName[STR_200];

	int arcId;
	int arcGameId;
	int arcPlyAmn;
}ArcadeDto;


#endif /* DTO_ARCADEDTO_H_ */
