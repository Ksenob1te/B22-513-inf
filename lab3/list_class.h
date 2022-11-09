//
// Created by Ksenob1te on 07.11.2022.
//

#ifndef STUDY_LIST_CLASS_H
#define STUDY_LIST_CLASS_H

#include "stdio.h"
#include "stdlib.h"

#define li long long int

void splitString(const char *snumber, li *ip, li *rp);

char* create_new_number(li ip, li rp);

struct List {
    char **array;
    int length;

    void (*free_array) (struct List *this);
    void (*fill)(struct List *this);
    void (*print)(const struct List *this);
    void (*remove_index)(struct List *this, int index);
    void (*add_index)(struct List *this, int index, char *element);
    struct List (*process)(struct List *this);
};


extern const struct ListClass {
    struct List (*new)(int length);
} List;

void free_array(struct List *this);

void fill_list(struct List *this);

void print_list(const struct List *this);

void remove_index(struct List *this, int index);

void add_index(struct List *this, int index, char *element);

struct List process_mass(struct List* this);

static struct List newList(int length);

#endif //STUDY_LIST_CLASS_H
