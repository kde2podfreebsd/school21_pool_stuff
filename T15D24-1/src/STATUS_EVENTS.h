#ifndef STATUS_EVENTS_TABLE_H_
#define STATUS_EVENTS_TABLE_H_

typedef struct {
    int event_id;
    int module_id;
    int new_status;
    char date[11];
    char time[9];
} StatusEvent;

int insertStatusEvent(const char *filename, StatusEvent *newEvent);
StatusEvent *selectStatusEvents(const char *filename, int *numEvents);
StatusEvent *selectStatusEventByID(const char *filename, int id);
int updateStatusEventByID(const char *filename, StatusEvent *newEvent, int id);
int deleteStatusEventByID(const char *filename, int id);
void binSearch(const char *filename, int id);

#endif