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
	//[48,97] i>=48 && i<=97 sale
	do {
		printf("%s",mssg);
		__fpurge(stdin);
		scanf("%s",vlStr);
	} while ((*vlStr<48 || *vlStr>97));
}

void su_getAlphabeticStringValue(char* mssg,char* vlStr){
	//[65,90] || [97,122] == (i>=65 && i<=90) || (i>=97 && i<=122)
	do {
		printf("%s",mssg);
		__fpurge(stdin);
		scanf("%s",vlStr);
	} while ((*vlStr<65 || *vlStr>90) && (*vlStr<97 || *vlStr>122));
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

