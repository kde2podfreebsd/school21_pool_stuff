#ifndef SHARED_H_
#define SHARED_H_

#include "LEVELS.h"
#include "MODULES.h"

int sharedInsertModule(const char* name, int level, int cell, int flag);
void sharedSelectModules();
void sharedSelectModuleByID(int id);
Module* sharedSelectModulesStructByID(int id);
int sharedUpdateModuleByID(int id, const char* name, int level, int cell, int flag);
int sharedDeleteModuleByID(int id);

void sharedSelectModulesWithOpenFlag();
void sharedSelectModulesWithFirstMemLevel();

int sharedInsertStatusEvent(int module_id, int new_status, const char* date, const char* time);
void sharedSelectStatusEvents();
void sharedSelectStatusEventByID(int id);
int sharedUpdateStatusEventByID(int id, int module_id, int new_status, const char* date, const char* time);
int sharedDeleteStatusEventByID(int id);

int sharedInsertLevel(int level, int cell, int protectionFlag);
void sharedSelectAllLevels();
void sharedSelectLevelByMemoryLevel(int memoryLevel);
int sharedUpdateLevelByMemoryLevel(int level_id, int memoryLevel, int cell, int protectionFlag);
int sharedDeleteLevelByMemoryLevel(int memoryLevel);
MemoryLevel* sharedSelectLevelStructByMemoryLevel(int memoryLevel);

void binSearchStatusEventByID(int id);

#endif