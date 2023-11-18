#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LEVELS.h"
#include "MODULES.h"
#include "STATUS_EVENTS.h"

const char* module_table_db = "module_table.db";
const char* status_events_table_db = "status_event_table.db";
const char* levels_table_db = "levels_table.db";

int sharedInsertModule(const char* name, int level, int cell, int flag) {
    Module* new_module = malloc(sizeof(Module));
    if (new_module == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    new_module->module_id = 0;
    strcpy(new_module->module_name, name);
    new_module->memory_level = level;
    new_module->cell_number = cell;
    new_module->deletion_flag = flag;

    MemoryLevel* existingLevel = selectLevelByMemoryLevel(levels_table_db, level);

    if (existingLevel == NULL || cell < 0 || cell > existingLevel->cell_number) {
        printf("Ошибка: Некорректный уровень памяти или номер ячейки.\n");
        free(new_module);
        return -1;
    }

    int id = insertModule(module_table_db, new_module);
    free(new_module);

    return id;
}

void sharedSelectModules() {
    int numModules = 0;

    Module* modulesArray = selectModules(module_table_db, &numModules);

    if (modulesArray == NULL) {
        printf("Ошибка при чтении структур из файла.\n");
        return;
    }

    for (int i = 0; i < numModules; ++i) {
        printf(
            "ID модуля: %d | Название модуля: %s | Уровень памяти: %d | Номер ячейки: %d | Флаг удаления: "
            "%d\n",
            modulesArray[i].module_id, modulesArray[i].module_name, modulesArray[i].memory_level,
            modulesArray[i].cell_number, modulesArray[i].deletion_flag);
        printf("----------------------------------\n\n");
    }

    free(modulesArray);
}

void sharedSelectModulesWithOpenFlag() {
    int numModules = 0;

    Module* modulesArray = selectModulesWithOpenFlag(module_table_db, &numModules);

    if (modulesArray == NULL) {
        printf("Ошибка при чтении структур из файла.\n");
        return;
    }

    for (int i = 0; i < numModules; ++i) {
        printf(
            "ID модуля: %d | Название модуля: %s | Уровень памяти: %d | Номер ячейки: %d | Флаг удаления: "
            "%d\n",
            modulesArray[i].module_id, modulesArray[i].module_name, modulesArray[i].memory_level,
            modulesArray[i].cell_number, modulesArray[i].deletion_flag);
        printf("----------------------------------\n\n");
    }

    free(modulesArray);
}

void sharedSelectModulesWithFirstMemLevel() {
    int numModules = 0;

    Module* modulesArray = selectModulesWithFirstMemLevel(module_table_db, &numModules);

    if (modulesArray == NULL) {
        printf("Ошибка при чтении структур из файла.\n");
        return;
    }

    for (int i = 0; i < numModules; ++i) {
        printf(
            "ID модуля: %d | Название модуля: %s | Уровень памяти: %d | Номер ячейки: %d | Флаг удаления: "
            "%d\n",
            modulesArray[i].module_id, modulesArray[i].module_name, modulesArray[i].memory_level,
            modulesArray[i].cell_number, modulesArray[i].deletion_flag);
        printf("----------------------------------\n\n");
    }

    free(modulesArray);
}

void sharedSelectModuleByID(int id) {
    Module* selectedModule = selectModuleByID(module_table_db, id);
    if (selectedModule == NULL) {
        printf("Модуль с таким ID не существует в базе данных.\n");
        return;
    }
    printf(
        "ID модуля: %d | Название модуля: %s | Уровень памяти: %d | Номер ячейки: %d | Флаг удаления: %d\n\n",
        selectedModule->module_id, selectedModule->module_name, selectedModule->memory_level,
        selectedModule->cell_number, selectedModule->deletion_flag);
    free(selectedModule);
}

Module* sharedSelectModulesStructByID(int id) {
    Module* selectedModule = selectModuleByID(module_table_db, id);
    if (selectedModule == NULL) {
        printf("Модуль с таким ID не существует в базе данных.\n");
        return NULL;
    }
    return selectedModule;
}

int sharedUpdateModuleByID(int id, const char* name, int level, int cell, int flag) {
    Module* new_module = malloc(sizeof(Module));

    if (new_module == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    new_module->module_id = 0;
    strcpy(new_module->module_name, name);
    new_module->memory_level = level;
    new_module->cell_number = cell;
    new_module->deletion_flag = flag;

    MemoryLevel* existingLevel = selectLevelByMemoryLevel(levels_table_db, level);
    if (existingLevel == NULL || cell < 0 || cell > existingLevel->cell_number) {
        printf("Ошибка: Некорректный уровень памяти или номер ячейки.\n");
        free(new_module);
        return -1;
    }

    int ids = updateModuleByID(module_table_db, new_module, id);

    if (ids == -1) {
        printf("Модуль с таким ID не существует в базе данных.\n");
        return -1;
    }

    free(new_module);

    return ids;
}

int sharedDeleteModuleByID(int id) {
    int res = deleteModuleByID(module_table_db, id);
    if (res == 0) {
        return 1;
    } else if (res == -1) {
        printf("Модуль с таким ID не существует в базе данных.\n");
    }
    return 0;
}

int sharedInsertStatusEvent(int module_id, int new_status, const char* date, const char* time) {
    StatusEvent* new_event = malloc(sizeof(StatusEvent));

    if (new_event == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    new_event->event_id = 0;
    new_event->module_id = module_id;
    new_event->new_status = new_status;
    strcpy(new_event->date, date);
    strcpy(new_event->time, time);

    if (insertStatusEvent(status_events_table_db, new_event)) {
        return 1;
    }

    return 0;
}

void sharedSelectStatusEvents() {
    int numEvents = 0;

    StatusEvent* eventsArray = selectStatusEvents(status_events_table_db, &numEvents);

    if (eventsArray == NULL) {
        printf("Ошибка при чтении событий из файла.\n");
        return;
    }

    for (int i = 0; i < numEvents; ++i) {
        printf("ID события: %d | ID модуля: %d | Новый статус: %d | Дата: %s | Время: %s\n",
               eventsArray[i].event_id, eventsArray[i].module_id, eventsArray[i].new_status,
               eventsArray[i].date, eventsArray[i].time);
        printf("----------------------------------\n\n");
    }

    free(eventsArray);
}

void sharedSelectStatusEventByID(int id) {
    StatusEvent* selectedEvent = selectStatusEventByID(status_events_table_db, id);
    if (selectedEvent == NULL) {
        printf("Событие с указанным ID не найдено в базе данных.\n");
        return;
    }
    printf("ID события: %d | ID модуля: %d | Новый статус: %d | Дата: %s | Время: %s\n",
           selectedEvent->event_id, selectedEvent->module_id, selectedEvent->new_status, selectedEvent->date,
           selectedEvent->time);
    free(selectedEvent);
}

int sharedInsertLevel(int level, int cell, int protectionFlag) {
    MemoryLevel* newLevel = malloc(sizeof(MemoryLevel));

    if (newLevel == NULL) {
        perror("Memory allocation failed");
        return -1;
    }

    newLevel->memory_level = level;
    newLevel->cell_number = cell;
    newLevel->protection_flag = protectionFlag;

    int id = insertLevel(levels_table_db, newLevel);

    free(newLevel);

    return id;
}

void sharedSelectAllLevels() {
    int numLevels = 0;

    MemoryLevel* levelsArray = selectAllLevels(levels_table_db, &numLevels);

    if (levelsArray == NULL) {
        printf("Ошибка при чтении уровней из файла.\n");
        return;
    }

    for (int i = 0; i < numLevels; ++i) {
        printf("Уровень памяти: %d | Номер ячейки: %d | Флаг защиты: %d\n", levelsArray[i].memory_level,
               levelsArray[i].cell_number, levelsArray[i].protection_flag);
        printf("----------------------------------\n\n");
    }

    free(levelsArray);
}

void sharedSelectLevelByMemoryLevel(int memoryLevel) {
    MemoryLevel* selectedLevel = selectLevelByMemoryLevel(levels_table_db, memoryLevel);
    if (selectedLevel != NULL) {
        printf("Уровень памяти: %d | Номер ячейки: %d | Флаг защиты: %d\n", selectedLevel->memory_level,
               selectedLevel->cell_number, selectedLevel->protection_flag);
        free(selectedLevel);
    } else {
        printf("Уровень с памятью %d не найден.\n", memoryLevel);
    }
}

int sharedUpdateLevelByMemoryLevel(int level_id, int memoryLevel, int cell, int protectionFlag) {
    MemoryLevel* newLevel = malloc(sizeof(MemoryLevel));

    if (newLevel == NULL) {
        perror("Memory allocation failed");
        return -1;
    }

    newLevel->memory_level = memoryLevel;
    newLevel->cell_number = cell;
    newLevel->protection_flag = protectionFlag;

    int updatedId = updateLevelByMemoryLevel(levels_table_db, newLevel, level_id);

    free(newLevel);

    return updatedId;
}

int sharedDeleteLevelByMemoryLevel(int memoryLevel) {
    if (!deleteLevelByMemoryLevel(levels_table_db, memoryLevel)) {
        printf("Нет такого урованя памяти\n");
        return 1;
    }
    printf("Удалено\n");
    return 0;
}

MemoryLevel* sharedSelectLevelStructByMemoryLevel(int memoryLevel) {
    MemoryLevel* selectedLevel = selectLevelStructByMemoryLevel(levels_table_db, memoryLevel);
    return selectedLevel;
}

void binSearchStatusEventByID(int id) { binSearch(status_events_table_db, id); }