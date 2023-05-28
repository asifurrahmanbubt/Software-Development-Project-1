#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Month {
    int year;
    int month;
    int num_days;
    int start_day;
    char* tasks[31];
};

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

struct Month init_month(int year, int month) {
    struct Month m;
    m.year = year;
    m.month = month;

    if (month == 2) {
        m.num_days = is_leap_year(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        m.num_days = 30;
    } else {
        m.num_days = 31;
    }

    int y = year - (14 - month) / 12;
    int m1 = month + 12 * ((14 - month) / 12) - 2;
    m.start_day = (1 + y + y / 4 - y / 100 + y / 400 + (31 * m1) / 12) % 7;

    for (int i = 0; i < m.num_days; i++) {
        m.tasks[i] = NULL;
    }

    return m;
}

void print_month(struct Month m) {

    printf("\n\n   %d/%d\n", m.month, m.year);
    printf("Su Mo Tu We Th Fr Sa\n");

    for (int i = 0; i < m.start_day; i++) {
        printf("   ");
    }
    for (int i = 1; i <= m.num_days; i++) {
        printf("%2d ", i);
        if ((i + m.start_day) % 7 == 0) {
            printf("\n");
        }
    }
}

void add_task(struct Month* m, int day, const char* task) {

    if (day < 1 || day > m->num_days) {
        printf("Invalid day! Task not added.\n");
        return;
    }

    char* new_task = (char*)malloc(strlen(task) + 1);
    strcpy(new_task, task);

    if (m->tasks[day - 1] != NULL) {
        free(m->tasks[day - 1]);
    }

    m->tasks[day - 1] = new_task;
}

void modify_task(struct Month* m, int day) {
    if (day < 1 || day > m->num_days) {
        printf("Invalid day!\n");
        return;
    }

    int index = day - 1;
    if (m->tasks[index] != NULL) {
        printf("Current task for Day %d: %s\n", day, m->tasks[index]);
        printf("Enter new task description: ");
        char task[100];
        scanf(" %[^\n]", task);
        free(m->tasks[index]);
        m->tasks[index] = (char*)malloc(strlen(task) + 1);
        strcpy(m->tasks[index], task);
        printf("Task modified successfully!\n");
    } else {
        printf("No tasks found for Day %d\n", day);
    }
}

void delete_task(struct Month* m, int day) {
    if (day < 1 || day > m->num_days) {
        printf("Invalid day!\n");
        return;
    }

    int index = day - 1;
    if (m->tasks[index] != NULL) {
        printf("Deleting task for Day %d: %s\n", day, m->tasks[index]);
        free(m->tasks[index]);
        m->tasks[index] = NULL;
        printf("Task deleted successfully!\n");
    } else {
        printf("No tasks found for Day %d\n", day);
    }
}

void view_tasks(struct Month* m) {
    int day;
    printf("\nEnter day to view tasks (1-%d, 0 to exit): ", m->num_days);
    scanf("%d", &day);

    if (day == 0) {
        return;
    }

    if (day < 1 || day > m->num_days) {
        printf("Invalid day!\n");
        return;
    }

    int index = day - 1;
    if (m->tasks[index] != NULL) {
        printf("Tasks for Day %d: %s\n", day, m->tasks[index]);
        printf("Select an option:\n");
        printf("1. Modify task\n");
        printf("2. Delete task\n");
        printf("0. Exit\n");
        printf("Enter option: ");
        int option;
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                modify_task(m, day);
                break;
            case 2:
                delete_task(m, day);
                break;
            default:
                printf("Invalid option!\n");
        }
    } else {
        printf("No tasks found for Day %d\n", day);
        printf("Select an option:\n");
        printf("1. Add task on this day\n");
        printf("0. Exit\n");
        printf("Enter option: ");
        int option;
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                printf("Enter task description: ");
                char task[100];
                scanf(" %[^\n]", task);
                add_task(m, day, task);
                printf("Task added successfully!\n");
                break;
            default:
                printf("Invalid option!\n");
        }
    }

    printf("Do you want to view more tasks? (y/n): ");
    char choice;
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        view_tasks(m);
    }
}

int main() {
    int year, month;

    while (1) {

        printf("Enter year: ");
        scanf("%d", &year);
        printf("Enter month (1-12): ");
        scanf("%d", &month);

        struct Month m = init_month(year, month);
        print_month(m);

        printf("\nEnter tasks (press enter to finish):\n");
        char task[100];
        int day;
        while (1) {
            printf("Enter day to add a task (0 to finish): ");
            scanf("%d", &day);

            if (day == 0) {
                break;
            }

            printf("Enter task description: ");
            scanf(" %[^\n]", task);

            add_task(&m, day, task);
        }

        print_month(m);

        view_tasks(&m);

        char choice;
        printf("Do you want to repeat the process? (y/n): ");
        scanf(" %c", &choice);

        if (choice != 'y' && choice != 'Y') {
            break;
        }

        for (int i = 0; i < m.num_days; i++) {
            if (m.tasks[i] != NULL) {
                free(m.tasks[i]);
            }
        }
    }

    return 0;
}

