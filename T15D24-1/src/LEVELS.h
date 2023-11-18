#ifndef LEVELS_TABLE_H_
#define LEVELS_TABLE_H_

typedef struct {
    int memory_level;
    int cell_number;
    int protection_flag;
} MemoryLevel;

int insertLevel(const char *filename, MemoryLevel *newLevel);
MemoryLevel *selectAllLevels(const char *filename, int *numLevels);
MemoryLevel *selectLevelByMemoryLevel(const char *filename, int memoryLevel);
int updateLevelByMemoryLevel(const char *filename, MemoryLevel *newLevel, int memoryLevel);
int deleteLevelByMemoryLevel(const char *filename, int memoryLevel);
MemoryLevel *selectLevelStructByMemoryLevel(const char *filename, int memoryLevel);
int levelExists(const char *filename, int memoryLevel);

#endif