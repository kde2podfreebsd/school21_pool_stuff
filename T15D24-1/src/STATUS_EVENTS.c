#include "STATUS_EVENTS.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int statusEventExists(const char *filename, int eventID) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    StatusEvent tempEvent;

    while (fread(&tempEvent, sizeof(StatusEvent), 1, file) == 1) {
        if (tempEvent.event_id == eventID) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int insertStatusEvent(const char *filename, StatusEvent *newEvent) {
    FILE *file_to_read = fopen(filename, "rb");

    if (file_to_read == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    StatusEvent tempEvent;

    int max_id = 0;

    while (fread(&tempEvent, sizeof(StatusEvent), 1, file_to_read) == 1) {
        if (max_id < tempEvent.event_id) {
            max_id = tempEvent.event_id;
        }
    }

    fclose(file_to_read);

    FILE *file_to_write = fopen(filename, "ab");

    newEvent->event_id = ++max_id;

    if (file_to_write == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    fwrite(newEvent, sizeof(StatusEvent), 1, file_to_write);

    fclose(file_to_write);
    return 0;
}

StatusEvent *selectStatusEvents(const char *filename, int *numEvents) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    int initialSize = 10;
    int capacity = initialSize;
    int size = 0;

    StatusEvent *events = malloc(initialSize * sizeof(StatusEvent));
    if (events == NULL) {
        perror("Ошибка выделения памяти");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    StatusEvent tempEvent;

    while (fread(&tempEvent, sizeof(StatusEvent), 1, file) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            StatusEvent *temp = realloc(events, capacity * sizeof(StatusEvent));
            if (temp == NULL) {
                perror("Ошибка перевыделения памяти");
                free(events);
                fclose(file);
                exit(EXIT_FAILURE);
            }
            events = temp;
        }

        events[size++] = tempEvent;
    }

    fclose(file);

    *numEvents = size;
    return events;
}

StatusEvent *selectStatusEventByID(const char *filename, int id) {
    if (!statusEventExists(filename, id)) {
        return NULL;
    }

    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    StatusEvent tempEvent;
    StatusEvent *resultEvent = NULL;

    while (fread(&tempEvent, sizeof(StatusEvent), 1, file) == 1) {
        if (tempEvent.event_id == id) {
            resultEvent = malloc(sizeof(StatusEvent));
            if (resultEvent == NULL) {
                perror("Ошибка выделения памяти");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            *resultEvent = tempEvent;
            break;
        }
    }

    fclose(file);
    return resultEvent;
}

void binSearch(const char *filename, int id) {
    FILE *db = fopen(filename, "rb+");
    fseek(db, 0, SEEK_END);
    int size = ftell(db) / sizeof(StatusEvent);

    StatusEvent record;
    record.event_id = record.module_id = record.new_status = -1;

    int down = 0, up = size - 1;
    int step = 1;
    while (down <= up) {
        int mid = (down + up) / 2;
        int offset = mid * sizeof(StatusEvent);
        fseek(db, offset, SEEK_SET);
        fread(&record, sizeof(StatusEvent), 1, db);
        if (record.event_id > id)
            up = mid - 1;
        else if (record.event_id < id)
            down = mid + 1;
        else
            break;

        printf("step number: %d\n", step);
        step++;
    }

    if (record.event_id == -1)
        printf("Record not found\n");
    else
        printf("Event_id: %d Module: %d New status: %d Date:%s Time: %s\n", record.event_id, record.module_id,
               record.new_status, record.date, record.time);
    fclose(db);
}