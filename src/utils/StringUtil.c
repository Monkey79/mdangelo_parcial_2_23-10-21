/*
 * StringUtil.c
 * Created on: 2 nov. 2021
 * Author: Mariano DAngelo
 */

#include "StringUtil.h"


int su_showMatrixStrings(char* mssgs[],int len){
	int success = TRUE;
	if(mssgs==NULL){
		success = FALSE;
	}else{
		for(int i=0; i<len; i++){
			printf("%s\n", *(mssgs+i));
		}
	}
	return success;
}

void su_getStringValue(char* mssg,char* vlStr){
	printf("%s",mssg);
	__fpurge(stdin);
	scanf("%s",vlStr);
}

void su_getStringValueConditional(char* mssg, char* vlStr, char* cond1, char* cond2){
	do {
		printf("%s",mssg);
		__fpurge(stdin);
		scanf("%s",vlStr);
	} while (strcmp(vlStr, cond1)!=0 && strcmp(vlStr, cond2)!=0);
}

int su_cleanString(char* strValue, int length){
	int success = TRUE;
	int strSize;

	if(strValue != NULL){
		strSize = str_getStringSize(strValue, length);
		*(strValue+(strSize))=0;
	}else{
		success = FALSE;
	}

	return success;
}

int str_getStringSize(char* strValue, int length){
	int i;
	if(strValue != NULL){
		for(i=0;*(strValue+i)!=0 && i<length;i++);
	}else{
		i = -1;
	}
	return i;
}

char str_getYesNoQstion(char* strMssg){
	char qst;
	do {
		printf("%s\n", strMssg);
		__fpurge(stdin);
		scanf("%c",&qst);
		qst = toupper(qst);
	} while (qst!='S' && qst!='N');

	return qst;
}

