#include <stdio.h>
#include <stdlib.h>
#include "list_class.h"


void send_command_menu() {
    printf("____________________________________\n");
    printf("__________Here's your menu__________\n");
    printf("Select one option from below\n");
    printf("[1] Add to array multiple values\n");
    printf("[2] Add new element by index\n");
    printf("[3] Delete element by index\n");
    printf("[4] Process data from array\n");
    printf("[5] Show current array status\n");
    printf("[6] Show afterprocess array status\n");
    printf("[0] Exit\n");
    printf("____________________________________\n");
}
void menu() {
    struct List mainList = List.new(0), ansList = List.new(0);
    send_command_menu();
    while (1) {
        printf("Type command (number [0-6]) or [-1] for command menu:\n");
        int command = 0;
        int x = scanf("%d", &command);
        if (x == EOF) {
            scanf("%*[^\n]*c");
            return;
        }
        if (x == 0) {
            printf("Incorrect input, try again\n");
            printf("Or [-1] for command menu\n");
            scanf("%*[^\n]*c");
            continue;
        }
        switch (command) {
            case 1:
                mainList.fill(&mainList);
                break;
            case 2:
                printf("Type index and then number:\n");
                int index = 0;
                char* number = malloc(35 * sizeof(char));
                x = scanf("%d%34s", &index, number);
                if (x == EOF) {
                    scanf("%*[^\n]*c");
                    break;
                }
                if (x <= 1) {
                    printf("Incorrect input, try again\n");
                    printf("Or [-1] for command menu\n");
                    scanf("%*[^\n]*c");
                    break;
                }
                mainList.add_index(&mainList, index, number);
                break;
            case 3:
                printf("Type index:\n");
                index = 0;
                x = scanf("%d", &index);
                if (x == EOF) {
                    scanf("%*[^\n]*c");
                    break;
                }
                if (x <= 0) {
                    printf("Incorrect input, try again\n");
                    printf("Or [-1] for command menu\n");
                    scanf("%*[^\n]*c");
                    break;
                }
                mainList.remove_index(&mainList, index);
                break;
            case 4:
                ansList = mainList.process(&mainList);
                printf("Result array: ");
                ansList.print(&ansList);
                break;
            case 5:
                printf("Your main array is: ");
                mainList.print(&mainList);
                break;
            case 6:
                printf("Your result array is: ");
                ansList.print(&ansList);
                break;
            case 0:
                return;
            case -1:
                send_command_menu();
                break;
            default:
                break;
        }

    }
}


int main() {
    menu();
    return 0;
}
