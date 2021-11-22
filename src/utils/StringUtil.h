/*
 * StringUtil.h
 * Created on: 2 nov. 2021
 * Author: Mariano DAngelo
 */

#ifndef UTILS_STRINGUTIL_H_
#define UTILS_STRINGUTIL_H_

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../properties_file.h"

int su_showMatrixStrings(char* mssgs[],int len);
void su_getStringValue(char* mssg,char* vlStr);
void su_getStringValueConditional(char* mssg, char* vlStr, char* cond1, char* cond2);
int su_cleanString(char* strValue, int length);
int str_getStringSize(char* strValue, int length);
char str_getYesNoQstion(char* strMssg);
void su_getAlphabeticStringValue(char* mssg,char* vlStr);

#endif /* UTILS_STRINGUTIL_H_ */
