/*
 * FileUtil.c
 * Created on: 27 oct. 2021
 * Author: Mariano DAngelo
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "FileUtil.h"

#define ERROR_FILE_OPEN "-Error abriendo el archivo-\n"

FILE* fu_openFileByMode(char* fileName, char* fileMode){
	FILE* flAux = NULL;
	flAux = fopen(fileName, fileMode);

	if(flAux == NULL){
		printf(ERROR_FILE_OPEN);
		printf("%s\n", fileName);
		exit(0);
	}

	return flAux;
}
