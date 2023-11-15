#include "MODULES.h"
#include "STATUS_EVENTS.h"
#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* module_table_db = "module_table.db";
const char* status_events_table_db = "status_event_table.db";

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

    int id = insertModule(module_table_db, new_module);

    free(new_module);

    return id;
}

void sharedSelectModules(){
    int numModules = 0;

    Module* modulesArray = selectModules(module_table_db, &numModules);

    if (modulesArray == NULL) {
        printf("Ошибка при чтении структур из файла.\n");
        return;
    }

    for (int i = 0; i < numModules; ++i) {
        printf("ID модуля: %d | Название модуля: %s | Уровень памяти: %d | Номер ячейки: %d | Флаг удаления: %d\n", modulesArray[i].module_id, modulesArray[i].module_name, modulesArray[i].memory_level, modulesArray[i].cell_number, modulesArray[i].deletion_flag);
        printf("----------------------------------\n\n");
    }

    free(modulesArray);
}

void sharedSelectModuleByID(int id){
    Module* selectedModule = selectModuleByID(module_table_db, id);
    printf("ID модуля: %d | Название модуля: %s | Уровень памяти: %d | Номер ячейки: %d | Флаг удаления: %d\n\n", selectedModule->module_id, selectedModule->module_name, selectedModule->memory_level, selectedModule->cell_number, selectedModule->deletion_flag);
    free(selectedModule);
}

Module* sharedSelectModulesStructByID(int id){
    Module* selectedModule = selectModuleByID(module_table_db, id);
    return selectedModule;
}

int sharedUpdateModuleByID(int id, const char* name, int level, int cell, int flag){
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

    int ids = updateModuleByID(module_table_db, new_module, id);

    free(new_module);

    return ids;
}

int sharedDeleteModuleByID(int id){
    if(!deleteModuleByID(module_table_db, id)){
        return 1;
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

    if(insertStatusEvent(status_events_table_db, new_event)){
        return 1;
        free(new_event);
    }

    free(new_event);

    return 0;
}

void sharedSelectStatusEvents(){
    int numEvents = 0;

    StatusEvent* eventsArray = selectStatusEvents(status_events_table_db, &numEvents);

    if (eventsArray == NULL) {
        printf("Ошибка при чтении событий из файла.\n");
        return;
    }

    for (int i = 0; i < numEvents; ++i) {
        printf("ID события: %d | ID модуля: %d | Новый статус: %d | Дата: %s | Время: %s\n", eventsArray[i].event_id, eventsArray[i].module_id, eventsArray[i].new_status, eventsArray[i].date, eventsArray[i].time);
        printf("----------------------------------\n\n");
    }

    free(eventsArray);
}

void sharedSelectStatusEventByID(int id){
    StatusEvent* selectedEvent = selectStatusEventByID(status_events_table_db, id);
    printf("ID события: %d | ID модуля: %d | Новый статус: %d | Дата: %s | Время: %s\n", selectedEvent->event_id, selectedEvent->module_id, selectedEvent->new_status, selectedEvent->date, selectedEvent->time);
    free(selectedEvent);
}

int sharedUpdateStatusEventByID(int id, int module_id, int new_status, const char* date, const char* time){
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

    if(!updateStatusEventByID(status_events_table_db, new_event, id)){
        return 1;
        free(new_event);
    }

    free(new_event);

    return 0;
}

int sharedDeleteStatusEventByID(int id){
    if(!deleteStatusEventByID(status_events_table_db, id)){
        return 1;
    }
    return 0;
}
