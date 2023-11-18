#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define FILEPATH_MAX_LEN 1025

typedef struct bfile_record {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} Bfile_record;

Bfile_record search_date_in_binary(FILE *fpointer, Bfile_record record_date, int *error);
void read_string_from_stdin(char *str);
Bfile_record read_record_from_file(FILE *pfile, int index);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
int is_equal_to_date(Bfile_record record_date, Bfile_record record);
Bfile_record read_date_to_bfile_record(int *error);

int main() {
    char filepath[FILEPATH_MAX_LEN] = {'\0'};
    int error = 0;

    read_string_from_stdin(filepath);
    FILE *fpointer = fopen(filepath, "rb+");
    if (fpointer == NULL) error = 1;
    if (!error) {
        Bfile_record record_date = read_date_to_bfile_record(&error);
        Bfile_record result = search_date_in_binary(fpointer, record_date, &error);
        if (result.year != 0) {
            printf("%d", result.code);
            fclose(fpointer);
        } else
            error = 1;
    }

    if (error) printf("n/a");

    return 0;
}

Bfile_record search_date_in_binary(FILE *fpointer, Bfile_record record_date, int *error) {
    Bfile_record result;
    result.year = result.month = result.day = result.hour = result.minute = result.second = result.status =
        result.code = 0;
    int records_count = get_records_count_in_file(fpointer);
    if (records_count == 0) {
        *error = 1;
    } else {
        for (int i = 0; i < records_count && result.year == 0; i++) {
            Bfile_record record = read_record_from_file(fpointer, i);
            if (is_equal_to_date(record_date, record)) result = record;
        }
    }
    return result;
}

void read_string_from_stdin(char *str) {
    int i = 0;
    char ch;
    do {
        ch = getchar();
        if (ch != '\n') str[i] = ch;
        i++;
    } while (ch != '\n' && i < FILEPATH_MAX_LEN - 1);
    str[i] = '\0';
}

Bfile_record read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(Bfile_record);
    fseek(pfile, offset, SEEK_SET);

    Bfile_record record;
    fread(&record, sizeof(Bfile_record), 1, pfile);

    rewind(pfile);
    return record;
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile) { return get_file_size_in_bytes(pfile) / sizeof(Bfile_record); }

int is_equal_to_date(Bfile_record record_date, Bfile_record record) {
    int comparation_dif = record_date.year - record.year;
    if (comparation_dif == 0) comparation_dif += record_date.month - record.month;
    if (comparation_dif == 0) comparation_dif += record_date.day - record.day;

    return comparation_dif == 0;
}

Bfile_record read_date_to_bfile_record(int *error) {
    Bfile_record record;
    record.year = record.month = record.day = record.hour = record.minute = record.second = record.status =
        record.code = 0;
    if (scanf("%d.%d.%d", &record.day, &record.month, &record.year) < 3) *error = 1;
    getchar();
    return record;
}