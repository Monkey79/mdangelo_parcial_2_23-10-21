/*
 * properties_file.h
 * Created on: 20 nov. 2021
 * Author: Mariano DAngelo
 */

#ifndef PROPERTIES_FILE_H_
#define PROPERTIES_FILE_H_

#define STR_100 101
#define STR_200 201
#define STR_63 64
#define STR_6 7

#define TRUE 1
#define FALSE 0
#define EXIT 0

#define PLAYER_TOP 1

//----Messages------
#define MAIN_ERROR "Error principal no se puede seguir con el programa\n"
#define ERROR_NO_MEMORY "Error no hay memoria\n"

//---Files---
#define ARCADE_FILE "src/assets/arcades.csv"
#define GAME_FILE "src/assets/games.csv"
#define ARCADE_MP_FILE "src/assets/multijugador.csv"

//---Regex----
#define ARCADE_REGEX "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n"
#define GAME_REGEX "%[^,],%[^\n]\n"

#endif /* PROPERTIES_FILE_H_ */
