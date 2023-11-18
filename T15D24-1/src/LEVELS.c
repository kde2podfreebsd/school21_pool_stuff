#include "LEVELS.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int levelExists(const char *filename, int memoryLevel) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    MemoryLevel tempLevel;

    while (fread(&tempLevel, sizeof(MemoryLevel), 1, file) == 1) {
        if (tempLevel.memory_level == memoryLevel) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int insertLevel(const char *filename, MemoryLevel *newLevel) {
    if (levelExists(filename, newLevel->memory_level)) {
        printf("Уровень уже существует в базе данных.\n");
        return -1;
    }

    FILE *file = fopen(filename, "ab");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    fwrite(newLevel, sizeof(MemoryLevel), 1, file);
    fclose(file);

    return newLevel->memory_level;
}

MemoryLevel *selectAllLevels(const char *filename, int *numLevels) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    int initialSize = 10;
    int capacity = initialSize;
    int size = 0;

    MemoryLevel *levels = malloc(initialSize * sizeof(MemoryLevel));
    if (levels == NULL) {
        perror("Ошибка выделения памяти");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    MemoryLevel tempLevel;

    while (fread(&tempLevel, sizeof(MemoryLevel), 1, file) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            MemoryLevel *temp = realloc(levels, capacity * sizeof(MemoryLevel));
            if (temp == NULL) {
                perror("Ошибка перевыделения памяти");
                free(levels);
                fclose(file);
                exit(EXIT_FAILURE);
            }
            levels = temp;
        }

        levels[size++] = tempLevel;
    }

    fclose(file);

    *numLevels = size;
    return levels;
}

MemoryLevel *selectLevelByMemoryLevel(const char *filename, int memoryLevel) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    MemoryLevel tempLevel;
    MemoryLevel *resultLevel = NULL;

    while (fread(&tempLevel, sizeof(MemoryLevel), 1, file) == 1) {
        if (tempLevel.memory_level == memoryLevel) {
            resultLevel = malloc(sizeof(MemoryLevel));
            if (resultLevel == NULL) {
                perror("Ошибка выделения памяти");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            *resultLevel = tempLevel;
            break;
        }
    }

    fclose(file);
    return resultLevel;
}

int updateLevelByMemoryLevel(const char *filename, MemoryLevel *newLevel, int memoryLevel) {
    if (!levelExists(filename, memoryLevel)) {
        printf("Уровень не существует в базе данных.\n");
        return -1;
    }

    FILE *file = fopen(filename, "r+b");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    MemoryLevel tempLevel;

    while (fread(&tempLevel, sizeof(MemoryLevel), 1, file) == 1) {
        if (tempLevel.memory_level == memoryLevel) {
            fseek(file, -sizeof(MemoryLevel), SEEK_CUR);
            fwrite(newLevel, sizeof(MemoryLevel), 1, file);
            break;
        }
    }

    fclose(file);
    return newLevel->memory_level;
}

int deleteLevelByMemoryLevel(const char *filename, int memoryLevel) {
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
    MemoryLevel tempLevel;

    while (fread(&tempLevel, sizeof(MemoryLevel), 1, file) == 1) {
        if (tempLevel.memory_level != memoryLevel) {
            fwrite(&tempLevel, sizeof(MemoryLevel), 1, tempFile);
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

MemoryLevel *selectLevelStructByMemoryLevel(const char *filename, int memoryLevel) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    MemoryLevel tempLevel;
    MemoryLevel *resultLevel = NULL;

    while (fread(&tempLevel, sizeof(MemoryLevel), 1, file) == 1) {
        if (tempLevel.memory_level == memoryLevel) {
            resultLevel = malloc(sizeof(MemoryLevel));
            if (resultLevel == NULL) {
                perror("Ошибка выделения памяти");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            *resultLevel = tempLevel;
            break;
        }
    }

    fclose(file);
    return resultLevel;
}
