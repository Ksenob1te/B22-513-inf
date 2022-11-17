//
// Created by Ksenob1te on 09.11.2022.
//

#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "list_class.h"

#define li long long int

const struct ListClass List = {.new=&newList};

void splitString(const char *snumber, li *ip, li *rp) {
    int i = 0;
    int checker = 0;
    while (snumber[i] != '\0') {
        if (snumber[i] == '.' || snumber[i] == ',') {
            checker = 1;
            i++;
            continue;
        }
        else if (!isdigit(snumber[i])) return;
        if (!checker) {
            *ip *= 10;
            *ip += snumber[i] - '0';
        } else {
            *rp *= 10;
            *rp += snumber[i] - '0';
        }
        i++;
    }
}

char* create_new_number(li ip, li rp) {
    char* nnum = malloc(35 * sizeof(char));
    int global_counter = 0;
    int counter = 0;
    li ip_copy = ip;
    while (ip_copy) {
        counter++;
        ip_copy /= 10;
    }
    global_counter += counter;
    while (ip) {
        nnum[--counter] = (ip % 10) + '0';
        ip /= 10;
    }
    nnum[global_counter] = '.';
    global_counter += 1;
    li rp_copy = rp;
    while (rp_copy) {
        counter++;
        rp_copy /= 10;
    }
    nnum[global_counter + counter] = '\0';
    while (rp) {
        nnum[(--counter) + global_counter] = (rp % 10) + '0';
        rp /= 10;
    }
//    nnum[global_counter] = '\0';
    return nnum;
}

void fill_list(struct List *this) {
    int add_counter = 0;
    printf("Enter the num of inputs:");
    int x = scanf("%d", &add_counter);
    if (x <= 0) {
        printf("Incorrect input, try again\n");
        scanf("%*[^\n]*c");
        return;
    }
    this->free_array(this);
    this->array = malloc(0);
    this->memory_worker(this, add_counter);
    for (int i = 0; i < add_counter; ++i) {
        printf("%d:", i + 1);
        x = scanf("%34s", this->array[i]);
        if (x == EOF) {
            printf("Aborting operation..\n");
            scanf("%*[^\n]");
            this->length = i;
            return;
        }
        if (x == 0) {
            printf("Incorrect input, try again\n");
            scanf("%*[^\n]");
            i--;
            continue;
        }
    }
    this->length = add_counter;
}

void print_list(const struct List *this) {
    for (int i = 0; i < this->length; ++i) {
        printf("%s ", this->array[i]);
    }
    printf("\n");
}

void remove_index(struct List *this, int index) {
    if (this->length <= index) return;
    free(this->array[index]);
    for (int i = index; i < this->length - 1; ++i)
        this->array[i] = this->array[i + 1];
    this->length -= 1;
    this->array[this->length] = NULL;
    this->memory_worker(this, this->length);
}

void add_index(struct List *this, int index, char *element) {
    if (index > this->length || index < 0)
        index = this->length;
    this->length += 1;
    this->memory_worker(this, this->length);
    for (int i = this->length; i > index; --i)
        this->array[i] = this->array[i - 1];
    this->array[index] = element;
}

struct List process_mass(struct List* this) {
    int ans_list_size = 0;
    for (int i = 0; i < this->length; ++i) {
        li ip = 0, rp = 0;
        splitString(this->array[i], &ip, &rp);
        if (rp > ip) ans_list_size += 1;
    }
    int new_counter = 0, ans_counter = 0;

    struct List ans_array = List.new(ans_list_size, MEMORY_UNIT);
//    char ** new_array = (char **) malloc((this->length - ans_list_size) * sizeof(char *));
    for (int i = 0; i < this->length; ++i) {
        li ip = 0, rp = 0;
        splitString(this->array[i], &ip, &rp);
        if (rp > ip) {
            free(this->array[i]);
            this->array[i] = NULL;
            ans_array.array[ans_counter++] = create_new_number(rp, ip);
        } else
            this->array[new_counter++] = this->array[i];
    }
    for (int i = this->length - ans_list_size; i < this->length; ++i)
        this->array[i] = NULL;
    this->length -= ans_list_size;
//    printf("%d %d\n", this->max_size, this->length);
    this->memory_worker(this, this->length);
    return ans_array;
}

void free_array(struct List *this) {
//    printf("Free'd: ");
    for (int i = 0; i < this->max_size; ++i) {
        if (this->array[i] != NULL) free(this->array[i]);
//        printf("%p ", this->array[i]);
    }
    free(this->array);
    this->length = 0;
    this->max_size = 0;
    this->array = NULL;
}

void memory_worker(struct List *this, int units_requested) {
    if ((this->max_size - units_requested) <= this->memory_unit && (this->max_size >= units_requested)) return;
    int new_size = 0;
    if (((int) units_requested / this->memory_unit) * this->memory_unit == units_requested)
        new_size = units_requested;
    else
        new_size = ((int) units_requested / this->memory_unit + 1) * this->memory_unit;
    if (this->max_size < units_requested) {
        this->array = (char**) realloc(this->array, new_size * sizeof(char*));
        for (int i = this->max_size; i < new_size; ++i)
            this->array[i] = malloc(35 * sizeof(char));
    } else {
        char **new_array;
        new_array = (char **) malloc(new_size * sizeof(char *));
        for (int i = 0; i < this->length; ++i)
            new_array[i] = this->array[i];
        for (int i = new_size; i < this->max_size; ++i)
            free(this->array[i]);
        free(this->array);
        this->array = new_array;
    }
    this->max_size = new_size;
}

static struct List newList(int length, int memory_unit) {
    return (struct List) {
            .array=malloc(length * sizeof(char*)),
            .length=length,
            .max_size=length,
            .memory_unit=memory_unit,

            .remove_index=remove_index,
            .add_index=add_index,
            .print=print_list,
            .fill=fill_list,
            .process=process_mass,
            .free_array=free_array,
            .memory_worker=memory_worker
    };
}
