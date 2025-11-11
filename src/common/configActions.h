#pragma once

#ifndef CONFIG_ACTIONS

#include "config.h"
#include "networktypes.h"

bool fileExists(char* filename);
Config createConfig(uint8_t ip[4], uint16_t port);
Config readConfig(char* filename);
void writeConfig(char* filename, Config config);

Config parseConfig(char* ipString, char* portString);

socketParams_t configToParams(Config config);

#define CONFIG_ACTIONS
#endif