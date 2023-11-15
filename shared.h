#ifndef SHARED_H_
#define SHARED_H_

#include "MODULES.h"

int     sharedInsertModule(const char* name, int level, int cell, int flag);
void    sharedSelectModules();
void    sharedSelectModuleByID(int id);
Module* sharedSelectModulesStructByID(int id);
int     sharedUpdateModuleByID(int id, const char* name, int level, int cell, int flag);
int     sharedDeleteModuleByID(int id);

int     sharedInsertStatusEvent(int module_id, int new_status, const char* date, const char* time);
void    sharedSelectStatusEvents();
void    sharedSelectStatusEventByID(int id);
int     sharedUpdateStatusEventByID(int id, int module_id, int new_status, const char* date, const char* time);
int     sharedDeleteStatusEventByID(int id);

#endif