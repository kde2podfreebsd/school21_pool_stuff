#ifndef MODULES_TABLE_H_
#define MODULES_TABLE_H_

typedef struct {
    int module_id;
    char module_name[30];
    int memory_level;
    int cell_number;
    int deletion_flag;
} Module;

int insertModule(const char *filename, Module *newModule);
Module *selectModules(const char *filename, int *numModules);
Module *selectModuleByID(const char *filename, int id);
int updateModuleByID(const char *filename, Module *newModule, int id);
int deleteModuleByID(const char *filename, int id);
int moduleExists(const char *filename, int moduleID);
Module *selectModulesWithOpenFlag(const char *filename, int *numModules);
Module *selectModulesWithFirstMemLevel(const char *filename, int *numModules);

#endif