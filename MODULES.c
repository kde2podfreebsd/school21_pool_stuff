#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MODULES.h"

int insertModule(const char *filename, Module *newModule) {

    FILE *file_to_read = fopen(filename, "rb");

    if (file_to_read == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    Module tempModule;

    int max_id = 0;

    while (fread(&tempModule, sizeof(Module), 1, file_to_read) == 1) {
        if(max_id < tempModule.module_id){
            max_id = tempModule.module_id;
        }
    }

    fclose(file_to_read);

    FILE *file_to_write = fopen(filename, "ab");

    newModule->module_id = ++max_id;

    if (file_to_write == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    fwrite(newModule, sizeof(Module), 1, file_to_write);

    fclose(file_to_write);
    return newModule->module_id;
}

Module* selectModules(const char *filename, int *numModules) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    int initialSize = 10;
    int capacity = initialSize;
    int size = 0;

    Module* modules = malloc(initialSize * sizeof(Module));
    if (modules == NULL) {
        perror("Ошибка выделения памяти");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    Module tempModule;

    while (fread(&tempModule, sizeof(Module), 1, file) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            Module* temp = realloc(modules, capacity * sizeof(Module));
            if (temp == NULL) {
                perror("Ошибка перевыделения памяти");
                free(modules);
                fclose(file);
                exit(EXIT_FAILURE);
            }
            modules = temp;
        }

        modules[size++] = tempModule;
    }

    fclose(file);

    *numModules = size;
    return modules;
}

Module* selectModuleByID(const char *filename, int id) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    Module tempModule;
    Module* resultModule = NULL;

    while (fread(&tempModule, sizeof(Module), 1, file) == 1) {
        if (tempModule.module_id == id) {
            resultModule = malloc(sizeof(Module));
            if (resultModule == NULL) {
                perror("Ошибка выделения памяти");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            *resultModule = tempModule;
            break;
        }
    }

    fclose(file);
    return resultModule;
}

int updateModuleByID(const char *filename, Module *newModule, int id) {
    FILE *file = fopen(filename, "r+b");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    Module tempModule;

    newModule->module_id = id;

    while (fread(&tempModule, sizeof(Module), 1, file) == 1) {
        if (tempModule.module_id == id) {
            fseek(file, -sizeof(Module), SEEK_CUR);
            fwrite(newModule, sizeof(Module), 1, file);
            break;
        }
    }

    fclose(file);
    return newModule->module_id;
}

int deleteModuleByID(const char *filename, int id) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    FILE *tempFile = fopen("tempFile.db", "wb");
    if (tempFile == NULL) {
        perror("Ошибка создания временного файла");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int deleted = 0;
    Module tempModule;

    while (fread(&tempModule, sizeof(Module), 1, file) == 1) {
        if (tempModule.module_id != id) {
            fwrite(&tempModule, sizeof(Module), 1, tempFile);
        } else {
            deleted = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("tempFile.db", filename);

    return deleted;
}
