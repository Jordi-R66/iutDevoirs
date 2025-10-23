#pragma once

#ifndef COMMON_DATATYPES

#include "includes.h"

#pragma pack(1)
typedef struct Devoir {
	char intitule[256];
	char description[256];

	uint16_t prof;
	uint16_t codeRessource;
	uint16_t codeGroupe;

	time_t timestampAjout;
	time_t timestampRendu;
} Devoir;
#pragma pack()
#define DEVOIR_SIZE sizeof(Devoir)

#define COMMON_DATATYPES
#endif
