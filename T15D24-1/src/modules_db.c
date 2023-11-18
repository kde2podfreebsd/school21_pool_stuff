#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "InitDatabase.h"
#include "LEVELS.h"
#include "MODULES.h"
#include "shared.h"

void ClearScreen(void);
void showModulesDBOperations();
void showLevelsDBOperations();
void showFirstMenu();
void ModulesInput(char* name, int* level, int* cell, int* deletion_flag);
void LevelsInput(int* level, int* cell, int* protectionFlag);
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
    int protectionFlag;
    int module_id;
    int moudleID;
    int level_id;
    char dateBuffer[11];
    char timeBuffer[9];
    int update_status_module;

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
                    if (deletion_flag != 0 && deletion_flag != 1) {
                        printf("DELETE FLAG %d\n", deletion_flag);
                        printf("Некорректное значение protected flag; может быть только 0 или 1\n");
                        continue;
                    }
                    moudleID = sharedInsertModule(name, level, cell, deletion_flag);
                    if (moudleID == -1) {
                        continue;
                    }
                    currentDate(dateBuffer);
                    currentTime(timeBuffer);
                    sharedInsertStatusEvent(moudleID, deletion_flag, dateBuffer, timeBuffer);
                } else if (operation_num == 2) {
                    ClearScreen();
                    sharedSelectModules();

                } else if (operation_num == 3) {
                    ClearScreen();
                    printf("Введите id модуля ----> ");

                    if (scanf("%d", &module_id) != 1) {
                        printf("Ошибка ввода названия модуля.\n");
                        exit(EXIT_FAILURE);
                    }

                    getchar();
                    sharedSelectModuleByID(module_id);

                } else if (operation_num == 4) {
                    ClearScreen();
                    printf("Введите id модуля ----> ");

                    if (scanf("%d", &module_id) != 1) {
                        printf("Ошибка ввода названия модуля.\n");
                        exit(EXIT_FAILURE);
                    }

                    Module* selectdModuleStruct = sharedSelectModulesStructByID(module_id);

                    if (selectdModuleStruct == NULL) continue;

                    getchar();
                    ModulesInput(name, &level, &cell, &deletion_flag);

                    if (deletion_flag != 0 && deletion_flag != 1) {
                        printf("DELETE FLAG %d\n", deletion_flag);
                        printf("Некорректное значение protected flag; может быть только 0 или 1\n");
                        continue;
                    }

                    update_status_module =
                        sharedUpdateModuleByID(module_id, name, level, cell, deletion_flag);
                    if (update_status_module == -1) {
                        continue;
                    }

                    if (selectdModuleStruct->deletion_flag != deletion_flag) {
                        currentDate(dateBuffer);
                        currentTime(timeBuffer);
                        sharedInsertStatusEvent(module_id, deletion_flag, dateBuffer, timeBuffer);
                    }

                    free(selectdModuleStruct);

                } else if (operation_num == 5) {
                    ClearScreen();
                    printf("Введите id модуля ----> ");

                    if (scanf("%d", &module_id) != 1) {
                        printf("Ошибка ввода названия модуля.\n");
                        exit(EXIT_FAILURE);
                    }

                    getchar();
                    sharedDeleteModuleByID(module_id);

                } else if (operation_num == 6) {
                    ClearScreen();
                    sharedSelectModulesWithOpenFlag();
                } else if (operation_num == 7) {
                    ClearScreen();
                    sharedSelectModulesWithFirstMemLevel();
                } else if (operation_num == 8) {
                    Module* selectdModuleStruct = sharedSelectModulesStructByID(1);

                    if (selectdModuleStruct == NULL) {
                        printf("Нет Main Module\n");
                        continue;
                    }

                    currentDate(dateBuffer);
                    currentTime(timeBuffer);
                    sharedInsertStatusEvent(moudleID, 0, dateBuffer, timeBuffer);

                    currentDate(dateBuffer);
                    currentTime(timeBuffer);
                    sharedInsertStatusEvent(moudleID, 1, dateBuffer, timeBuffer);

                    currentDate(dateBuffer);
                    currentTime(timeBuffer);
                    sharedInsertStatusEvent(moudleID, 20, dateBuffer, timeBuffer);

                    update_status_module =
                        sharedUpdateModuleByID(1, selectdModuleStruct->module_name, 1, 1, 1);
                    if (update_status_module == -1) {
                        continue;
                    }
                }

                break;

            case 2:
                ClearScreen();
                showLevelsDBOperations();

                printf("Введите номер операции ----> ");
                scanf("%d", &operation_num);
                getchar();

                if (operation_num == 1) {
                    ClearScreen();
                    LevelsInput(&level, &cell, &protectionFlag);
                    sharedInsertLevel(level, cell, protectionFlag);
                } else if (operation_num == 2) {
                    ClearScreen();
                    sharedSelectAllLevels();
                } else if (operation_num == 3) {
                    ClearScreen();
                    printf("Введите уровень памяти ----> ");

                    if (scanf("%d", &level_id) != 1) {
                        printf("Ошибка ввода уровня.\n");
                        exit(EXIT_FAILURE);
                    }

                    getchar();
                    sharedSelectLevelByMemoryLevel(level_id);
                } else if (operation_num == 4) {
                    ClearScreen();
                    printf("Введите уровень памяти ----> ");

                    if (scanf("%d", &level_id) != 1) {
                        printf("Ошибка ввода уровня.\n");
                        exit(EXIT_FAILURE);
                    }

                    MemoryLevel* selectdModuleStruct = sharedSelectLevelStructByMemoryLevel(level_id);

                    getchar();
                    LevelsInput(&level, &cell, &protectionFlag);

                    sharedUpdateLevelByMemoryLevel(level_id, level, cell, protectionFlag);

                    free(selectdModuleStruct);

                } else if (operation_num == 5) {
                    ClearScreen();
                    printf("Введите уровень памяти ----> ");

                    if (scanf("%d", &level_id) != 1) {
                        printf("Ошибка ввода уровня.\n");
                        exit(EXIT_FAILURE);
                    }

                    getchar();
                    sharedDeleteLevelByMemoryLevel(level_id);
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
                } else if (operation_num == 2) {
                    ClearScreen();
                    printf("Введите id события ----> ");

                    if (scanf("%d", &module_id) != 1) {
                        printf("Ошибка ввода id события.\n");
                        exit(EXIT_FAILURE);
                    }

                    getchar();
                    sharedSelectStatusEventByID(module_id);
                } else if (operation_num == 3) {
                    ClearScreen();
                    printf("Введите id status event ----> ");

                    if (scanf("%d", &module_id) != 1) {
                        printf("Ошибка ввода названия status event.\n");
                        exit(EXIT_FAILURE);
                    }

                    getchar();

                    binSearchStatusEventByID(module_id);
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
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(currentdate, 11, "%d.%m.%Y", timeinfo);
}

void currentTime(char* currenttime) {
    time_t rawtime;
    struct tm* timeinfo;
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
    printf("6 - SELECT Moudles with Open Protected Flag\n");
    printf("7 - SELECT Moudles on First Memory level\n");
    printf("8 - DISABLE MAIN MODULE\n");
    printf("9 - BINARY SEARCH MODULE BY ID\n");
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

void LevelsInput(int* level, int* cell, int* protectionFlag) {
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
    if (scanf("%d", protectionFlag) != 1) {
        printf("Ошибка ввода флага удаления.\n");
        exit(EXIT_FAILURE);
    }
}

void showLevelsDBOperations() {
    printf("LEVELS.db\n\nВыберите операцию\n");
    printf("1 - INSERT\n");
    printf("2 - SELECT ALL\n");
    printf("3 - SELECT BY Memory level\n");
    printf("4 - UPDATE BY Memory level\n");
    printf("5 - DELETE BY Memory level\n");
}

void showStatusEvenetsDBOperations() {
    printf("STATUS_EVENTS.db\n\nВыберите операцию\n");
    printf("1 - SELECT ALL\n");
    printf("2 - SELECT BY ID\n");
    printf("3 - BINARY SEARCH STATUS EVENT BY ID\n");
}

void CreateDatabaseModels() {
    char module_table[] = "module_table.db";
    FILE* module_table_file = fopen(module_table, "ab");
    if (module_table_file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    fclose(module_table_file);

    char status_event_table[] = "status_event_table.db";
    FILE* status_event_file = fopen(status_event_table, "ab");
    if (status_event_file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    fclose(status_event_file);

    char levels_table[] = "levels_table.db";
    FILE* levels_file = fopen(levels_table, "ab");
    if (levels_file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    fclose(levels_file);
}