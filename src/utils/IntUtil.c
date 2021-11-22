/*
 * IntUtil.c
 * Created on: 2 nov. 2021
 * Author: Mariano DAngelo
 */

#include <stdio.h>
#include <stdio_ext.h>
#include "IntUtil.h"

int iu_isIncluded(int opt,int from, int until){
	return (opt>=from && opt<=until);
}

int iu_getPositiveIntegerValue(char* mmsg){
	int value;
	do {
		printf("%s",mmsg);
		__fpurge(stdin);
		scanf("%d",&value);
	} while (value<0);
	return value;
}

