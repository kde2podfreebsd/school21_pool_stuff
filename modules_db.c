#include "shared.h"
#include "MODULES.h"
#include "InitDatabase.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ClearScreen(void);
void showModulesDBOperations();
void showFirstMenu();
void ModulesInput(char* name, int* level, int* cell, int* deletion_flag);
void currentDate(char* currentdate);
void currentTime(char* currenttime);
void showStatusEvenetsDBOperations();

int main() {
    int flag = 1;
    int bd_menu;
    int operation_num;
    char name[50];
    int level;
    int cell;
    int deletion_flag;
    int module_id;
    int moudleID;
    char dateBuffer[11];
    char timeBuffer[9];
    
    CreateDatabaseModels();

    while (flag) {
        showFirstMenu();
        printf("Введите номер базы данных ----> ");
        scanf("%d", &bd_menu);
        getchar();

        switch (bd_menu) {

            case 1:

                ClearScreen();
                showModulesDBOperations();
                printf("Введите номер операции ----> ");
                scanf("%d", &operation_num);
                getchar();

                if (operation_num == 1) {

                    ClearScreen();
                    ModulesInput(name, &level, &cell, &deletion_flag);
                    moudleID = sharedInsertModule(name, level, cell, deletion_flag);
                    currentDate(dateBuffer);
                    currentTime(timeBuffer);
                    sharedInsertStatusEvent(moudleID, deletion_flag, dateBuffer, timeBuffer);
                } else if (operation_num == 2) {

                    ClearScreen();
                    sharedSelectModules();

                } else if (operation_num == 3) {

                    ClearScreen();
                    printf("Введите id модуля ----> ");
                    
                    if(scanf("%d", &module_id) != 1){
                        printf("Ошибка ввода названия модуля.\n");
                        exit(EXIT_FAILURE);
                    }

                    getchar();
                    sharedSelectModuleByID(module_id);

                } else if(operation_num == 4){

                    ClearScreen();
                    printf("Введите id модуля ----> ");
                    
                    if(scanf("%d", &module_id) != 1){
                        printf("Ошибка ввода названия модуля.\n");
                        exit(EXIT_FAILURE);
                    }

                    Module* selectdModuleStruct = sharedSelectModulesStructByID(module_id);

                    getchar();
                    ModulesInput(name, &level, &cell, &deletion_flag);
                    sharedUpdateModuleByID(module_id, name, level, cell, deletion_flag);
                    if(selectdModuleStruct->deletion_flag != deletion_flag){
                        currentDate(dateBuffer);
                        currentTime(timeBuffer);
                        sharedInsertStatusEvent(module_id, deletion_flag, dateBuffer, timeBuffer);
                    }

                    free(selectdModuleStruct);

                } else if(operation_num == 5){

                    ClearScreen();
                    printf("Введите id модуля ----> ");

                    if(scanf("%d", &module_id) != 1){
                        printf("Ошибка ввода названия модуля.\n");
                        exit(EXIT_FAILURE);
                    }

                    getchar();
                    sharedDeleteModuleByID(module_id);

                }

                break;

            case 3:
                ClearScreen();
                showStatusEvenetsDBOperations();
                printf("Введите номер операции ----> ");
                scanf("%d", &operation_num);
                getchar();

                if (operation_num == 1) {
                    ClearScreen();
                    sharedSelectStatusEvents();
                } else if(operation_num == 2){
                    ClearScreen();
                    printf("Введите id события ----> ");
                    
                    if(scanf("%d", &module_id) != 1){
                        printf("Ошибка ввода id события.\n");
                        exit(EXIT_FAILURE);
                    }

                    getchar();
                    sharedSelectStatusEventByID(module_id);
                }

                break;
            
            case 4:
                flag = 0;
                break;
        }
    }

    return 0;
}

void currentDate(char* currentdate) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(currentdate, 11, "%d.%m.%Y", timeinfo);
}

void currentTime(char* currenttime) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(currenttime, 9, "%H:%M:%S", timeinfo);
}

void ClearScreen(void) { printf("\033[2J\033[1;1H"); }

void showFirstMenu() {
    printf("Выберите базу данных\n");
    printf("1 - MODULES.db\n");
    printf("2 - LEVELS.db\n");
    printf("3 - STATUS_EVENTS.db\n");
    printf("4 - Выйти из UI\n");
}

void showModulesDBOperations() {
    printf("MODULES.db\n\nВыберите операцию\n");
    printf("1 - INSERT\n");
    printf("2 - SELECT ALL\n");
    printf("3 - SELECT BY ID\n");
    printf("4 - UPDATE BY ID\n");
    printf("5 - DELETE BY ID\n");
}

void ModulesInput(char* name, int* level, int* cell, int* deletion_flag) {
    printf("Введите название модуля: ");
    if (scanf("%49s", name) != 1) {
        printf("Ошибка ввода названия модуля.\n");
        exit(EXIT_FAILURE);
    }
    printf("Введите уровень памяти модуля: ");
    if (scanf("%d", level) != 1) {
        printf("Ошибка ввода уровня памяти.\n");
        exit(EXIT_FAILURE);
    }
    printf("Введите номер ячейки в памяти: ");
    if (scanf("%d", cell) != 1) {
        printf("Ошибка ввода номера ячейки.\n");
        exit(EXIT_FAILURE);
    }
    printf("Введите флаг удаления: ");
    if (scanf("%d", deletion_flag) != 1) {
        printf("Ошибка ввода флага удаления.\n");
        exit(EXIT_FAILURE);
    }
}

void showStatusEvenetsDBOperations(){
    printf("STATUS_EVENTS.db\n\nВыберите операцию\n");
    printf("1 - SELECT ALL\n");
    printf("2 - SELECT BY ID\n");
}
