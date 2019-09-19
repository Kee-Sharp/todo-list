#include "todo.h"
#include "useful_strings.h"

int main(int argc, const char *argv[]) 
{
    if (argc == 2) {
        FILE *in_file = fopen(argv[1], "r");
        if (in_file == NULL) {
            printf("ERROR: File, %s, does not exist!\n", argv[1]);
            return 1;
        }
        int a = 1;
        while (a == 1) {
            a = read_todo_list_item(in_file);
        } 
    } else if (argc > 2) {
        printf("%s", ERROR_USAGE);
        return 1;
    }
    main_menu();
    return 0;
}
void main_menu(void) {
    printf("%s", MAIN_MENU_HEADER);
    printf("%s", QUERY);
    printf("%s", OPTIONS_LIST);
    printf("%s", GRAB_INPUT);
    char buffer[128];
    int end = 0;
    int choice;
    while (end == 0) {
        fgets_no_newline(buffer, 128, stdin);
        choice = atoi(buffer);
        if (choice >= 1 && choice <= 6) {
            end = 1;
        } else  {
            printf("%s", INVALID_CHOICE);
            main_menu();
            end = 1;
        }
    }
    if (choice == 1) {
        print_all();
    } else if (choice == 2) {
        add_item();
    } else if (choice == 3) {
        mark_completed();
    } else if (choice == 4) {
        remove_completed();
    } else if (choice == 5) {
        save_as();
    } 
}
void print_all(void) {
    printf("%s", TODO_LIST_HEADER);
    /* Todo_list_length += 2;
    strcpy(Todo_list[0].title, "Buy milk");
    strcpy(Todo_list[0].description, "Drive to the store and get some milk for your cereal");
    Todo_list[0].is_done = 0;
    Todo_list[0].due_day = 6;
    Todo_list[0].due_month = 2;
    Todo_list[0].due_year = 119;
    strcpy(Todo_list[1].title, "Graduate!");
    strcpy(Todo_list[1].description, "I made it!");
    Todo_list[1].is_done = 1;
    Todo_list[1].due_day = 10;
    Todo_list[1].due_month = 4;
    Todo_list[1].due_year = 2019; */
    int i;
    for (i = 0; i < Todo_list_length; i++) {
        char *title = Todo_list[i].title;
        printf("%s\n\n", title);
        int complete = Todo_list[i].is_done;
        if (complete == 1) {
            printf("%s", COMPLETED);
        } else {
            int day = Todo_list[i].due_day;
            int month = Todo_list[i].due_month;
            int year = Todo_list[i].due_year;
            printf("Due: %02d/%02d/%04d\n", month, day, year);
        }
        char *description = Todo_list[i].description;
        printf("Description: %s\n", description);
        printf("%s", LINE_BREAK);
    }
    main_menu();
}
void add_item(void) {
    printf("%s", ADD_TO_LIST_HEADER);
    if (Todo_list_length == 100) {
        printf("%s", LIST_MAX);
        main_menu();
    } else {
    printf("%s", ADD_TO_LIST);
    read_todo_list_item(stdin);
    main_menu();
    }
}
void mark_completed(void) {
    printf("%s", MARK_ITEM_COMPLETED_HEADER);
    printf("%s", MARK_ITEM_USER_INPUT);
    printf("%s", GRAB_INPUT);
    char index[10];
    fgets_no_newline(index, 10, stdin);
    int i = atoi(index);
    Todo_list[i].is_done = 1;
    main_menu();
}
void remove_completed(void) {
    printf("%s", REMOVE_ITEM_HEADER);
    int count = 0;
    for (int i = 0; i < Todo_list_length; i++) {
        int done = Todo_list[i].is_done;
        if (done == 0) {
            strcpy(Todo_list[count].title, Todo_list[i].title);
            strcpy(Todo_list[count].description, Todo_list[i].description);
            Todo_list[count].is_done = Todo_list[i].is_done;
            Todo_list[count].due_day = Todo_list[i].due_day;
            Todo_list[count].due_month = Todo_list[i].due_month;
            Todo_list[count].due_year = Todo_list[i].due_year;
            count++;
        }
    }
    int removed = Todo_list_length - count;
    printf("Success! %d items removed!\n", removed);
    Todo_list_length = count;
    main_menu();
}
void save_as(void) {
    printf("%s", SAVE_FILE_HEADER);
    printf("%s", INPUT_FILE_NAME);
    printf("%s", GRAB_INPUT);
    char name[128];
    fgets_no_newline(name, 128, stdin);
    FILE *out_file = fopen(name, "w");
    int i;
    for (i = 0; i < Todo_list_length; i++) {
        fprintf(out_file, "%s\n", Todo_list[i].title);
        fprintf(out_file, "%s\n", Todo_list[i].description);
        fprintf(out_file, "%d\n", Todo_list[i].is_done);
        fprintf(out_file, "%d\n", Todo_list[i].due_day);
        fprintf(out_file, "%d\n", Todo_list[i].due_month);
        fprintf(out_file, "%d\n", Todo_list[i].due_year);
    }
    fclose(out_file);
    main_menu();
}
