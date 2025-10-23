#pragma once

#ifndef COMMON_DATATYPES

#include "includes.h"

#define LONGUEUR_NOM_PROF 128
#define LONGUEUR_NOM_GROUPE 32
#define LONGUEUR_NOM_RESSOURCE 64

typedef uint16_t idProf_t;
typedef uint16_t idRessource_t;
typedef uint16_t idGroupe_t;

#pragma pack(1)

typedef struct Devoir {
	char intitule[384];

	idProf_t idProf;
	idRessource_t idRessource;
	idGroupe_t idGroupe;

	time_t timestampAjout;
	time_t timestampRendu;
} Devoir;

typedef struct Prof {
	idProf_t idProf;
	char nomProf[LONGUEUR_NOM_PROF + 1];
} Prof;

typedef struct Groupe {
	idGroupe_t idGroupe;
	char nomGroupe[LONGUEUR_NOM_GROUPE + 1];
} Groupe;

typedef struct Ressource {
	idRessource_t idRessource;
	char nomRessource[LONGUEUR_NOM_RESSOURCE + 1];
} Ressource;

typedef struct RefGroupe {
	idGroupe_t alias, valeur;
} RefGroupe;

#pragma pack()

#define PROF_SIZE sizeof(Prof)
#define DEVOIR_SIZE sizeof(Devoir)
#define GROUPE_SIZE sizeof(Groupe)
#define REFGROUPE_SIZE sizeof(RefGroupe)

#define COMMON_DATATYPES
#endif
