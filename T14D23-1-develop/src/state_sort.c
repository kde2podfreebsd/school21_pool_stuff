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

void use_menu_options(FILE *fpointer, int option, int *error);
void read_binary_file(FILE *fpointer, int *error);
void read_string_from_stdin(char *str);
Bfile_record read_input_to_bfile_record(int *error);
void sort_and_print_binary_file(FILE *fpointer, int *error);
void add_sort_and_print_binary_file(FILE *fpointer, int *error);

Bfile_record read_record_from_file(FILE *pfile, int index);
void write_record_in_file(FILE *pfile, const Bfile_record *record_to_write, int index);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
int is_record_B_less_than_A(Bfile_record record_A, Bfile_record record_B);

int main() {
    int menu_option = -1;
    char filepath[FILEPATH_MAX_LEN] = {'\0'};
    int error = 0;

    read_string_from_stdin(filepath);
    FILE *fpointer = fopen(filepath, "rb+");
    if (fpointer == NULL) error = 1;
    if (error || !scanf("%d", &menu_option)) error = 1;
    while (getchar() != '\n')
        ;

    if (!error) {
        use_menu_options(fpointer, menu_option, &error);
        fclose(fpointer);
    }

    if (error) {
        printf("n/a");
        error = 0;
    }

    return 0;
}

void use_menu_options(FILE *fpointer, int option, int *error) {
    if (option == 0)
        read_binary_file(fpointer, error);
    else if (option == 1)
        sort_and_print_binary_file(fpointer, error);
    else if (option == 2)
        add_sort_and_print_binary_file(fpointer, error);
    else if (option != -1)
        *error = 1;
}

void read_binary_file(FILE *fpointer, int *error) {
    int records_count = get_records_count_in_file(fpointer);
    if (records_count == 0) {
        *error = 1;
    } else {
        for (int i = 0; i < records_count; i++) {
            Bfile_record record = read_record_from_file(fpointer, i);
            printf("%d %d %d %d %d %d %d %d", record.year, record.month, record.day, record.hour,
                   record.minute, record.second, record.status, record.code);
            if (i != records_count - 1) printf("\n");
        }
    }
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

void sort_and_print_binary_file(FILE *fpointer, int *error) {
    int records_count = get_records_count_in_file(fpointer);
    if (records_count == 0) {
        *error = 1;
    } else {
        for (int i = 0; i < records_count - 1; i++) {
            for (int j = i + 1; j < records_count; j++) {
                if (is_record_B_less_than_A(read_record_from_file(fpointer, i),
                                            read_record_from_file(fpointer, j)))
                    swap_records_in_file(fpointer, i, j);
            }
        }
        rewind(fpointer);
        read_binary_file(fpointer, error);
    }
}

void add_sort_and_print_binary_file(FILE *fpointer, int *error) {
    Bfile_record record_to_write = read_input_to_bfile_record(error);
    if (!*error) {
        int records_count = get_records_count_in_file(fpointer);
        if (records_count == 0) {
            *error = 1;
        } else {
            write_record_in_file(fpointer, (const Bfile_record *)&record_to_write, records_count);
            rewind(fpointer);
            sort_and_print_binary_file(fpointer, error);
        }
    }
}

Bfile_record read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(Bfile_record);
    fseek(pfile, offset, SEEK_SET);

    Bfile_record record;
    fread(&record, sizeof(Bfile_record), 1, pfile);

    rewind(pfile);
    return record;
}

void write_record_in_file(FILE *pfile, const Bfile_record *record_to_write, int index) {
    int offset = index * sizeof(Bfile_record);

    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(Bfile_record), 1, pfile);
    fflush(pfile);

    rewind(pfile);
}

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    Bfile_record record1 = read_record_from_file(pfile, record_index1);
    Bfile_record record2 = read_record_from_file(pfile, record_index2);

    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile) { return get_file_size_in_bytes(pfile) / sizeof(Bfile_record); }

int is_record_B_less_than_A(Bfile_record record_A, Bfile_record record_B) {
    int comparation_dif = record_A.year - record_B.year;
    if (comparation_dif == 0) comparation_dif += record_A.month - record_B.month;
    if (comparation_dif == 0) comparation_dif += record_A.day - record_B.day;
    if (comparation_dif == 0) comparation_dif += record_A.hour - record_B.hour;
    if (comparation_dif == 0) comparation_dif += record_A.minute - record_B.minute;
    if (comparation_dif == 0) comparation_dif += record_A.second - record_B.second;
    if (comparation_dif == 0) comparation_dif += record_A.status - record_B.status;
    if (comparation_dif == 0) comparation_dif += record_A.code - record_B.code;

    return comparation_dif > 0;
}

Bfile_record read_input_to_bfile_record(int *error) {
    Bfile_record record;
    if (scanf("%d %d %d %d %d %d %d %d", &record.year, &record.month, &record.day, &record.hour,
              &record.minute, &record.second, &record.status, &record.code) < 8)
        *error = 1;
    getchar();
    return record;
}