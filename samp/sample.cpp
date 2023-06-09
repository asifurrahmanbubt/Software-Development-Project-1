#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TASK_LENGTH 100

struct Month {
    int year;
    int month;
    int num_days;
    int start_day;
    char tasks[31][MAX_TASK_LENGTH];
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
        m.tasks[i][0] = '\0';
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

    strncpy(m->tasks[day - 1], task, MAX_TASK_LENGTH - 1);
    m->tasks[day - 1][MAX_TASK_LENGTH - 1] = '\0';
}

void modify_task(struct Month* m, int day) {
    if (day < 1 || day > m->num_days) {
        printf("Invalid day!\n");
        return;
    }

    int index = day - 1;
    if (m->tasks[index][0] != '\0') {
        printf("Current task for Day %d: %s\n", day, m->tasks[index]);
        printf("Enter new task description: ");
        char task[MAX_TASK_LENGTH];
        scanf(" %[^\n]", task);
        strncpy(m->tasks[index], task, MAX_TASK_LENGTH - 1);
        m->tasks[index][MAX_TASK_LENGTH - 1] = '\0';
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
    if (m->tasks[index][0] != '\0') {
        printf("Deleting task for Day %d: %s\n", day, m->tasks[index]);
        m->tasks[index][0] = '\0';
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
    if (m->tasks[index][0] != '\0') {
        printf("Tasks for Day %d: %s\n", day, m->tasks[index]);
        printf("Select an option:\n");
        printf("1. Modify task\n");
        printf("2. Delete task\n");
        printf("3. Change task date\n");
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
            case 3:
                printf("Enter new day for the task: ");
                int new_day;
                scanf("%d", &new_day);
                if (new_day < 1 || new_day > m->num_days) {
                    printf("Invalid day!\n");
                } else {
                    char task[MAX_TASK_LENGTH];
                    strncpy(task, m->tasks[index], MAX_TASK_LENGTH - 1);
                    task[MAX_TASK_LENGTH - 1] = '\0';
                    m->tasks[index][0] = '\0';
                    add_task(m, new_day, task);
                    printf("Task date changed successfully!\n");
                }
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
                char task[MAX_TASK_LENGTH];
                scanf(" %[^\n]", task);
                add_task(m, day, task);
                printf("Task added successfully!\n");
                break;
            default:
                printf("Invalid option!\n");
        }
    }

    view_tasks(m);
}

void save_tasks(struct Month* m, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    fprintf(file, "%d,%d\n", m->year, m->month);
    for (int i = 0; i < m->num_days; i++) {
        if (m->tasks[i][0] != '\0') {
            fprintf(file, "%d,%s\n", i + 1, m->tasks[i]);
        }
    }

    fclose(file);
    printf("Tasks saved successfully!\n");
}

void load_tasks(struct Month* m, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return;
    }

    char line[100];
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d,%d", &(m->year), &(m->month));
    }

    for (int i = 0; i < m->num_days; i++) {
        m->tasks[i][0] = '\0';
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        int day;
        char task[MAX_TASK_LENGTH];
        sscanf(line, "%d,%[^\n]", &day, task);
        if (day >= 1 && day <= m->num_days) {
            strncpy(m->tasks[day - 1], task, MAX_TASK_LENGTH - 1);
            m->tasks[day - 1][MAX_TASK_LENGTH - 1] = '\0';
        }
    }

    fclose(file);
    printf("Tasks loaded successfully!\n");
}

void search_tasks(struct Month* m, const char* task_description) {
    printf("Tasks matching the description '%s':\n", task_description);
    bool found = false;

    for (int i = 0; i < m->num_days; i++) {
        if (strcmp(m->tasks[i], task_description) == 0) {
            printf("Day %d: %s\n", i + 1, m->tasks[i]);
            found = true;
        }
    }

    if (!found) {
        printf("No tasks found.\n");
        printf("Select an option:\n");
        printf("1. Add task with this description\n");
        printf("0. Exit\n");
        printf("Enter option: ");
        int option;
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                printf("Enter day to add the task: ");
                int day;
                scanf("%d", &day);
                if (day < 1 || day > m->num_days) {
                    printf("Invalid day!\n");
                } else {
                    add_task(m, day, task_description);
                    printf("Task added successfully!\n");
                }
                break;
            default:
                printf("Invalid option!\n");
        }
    } else {
        printf("Select an option:\n");
        printf("1. Change task date\n");
        printf("0. Exit\n");
        printf("Enter option: ");
        int option;
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                printf("Enter new day for the task: ");
                int new_day;
                scanf("%d", &new_day);
                if (new_day < 1 || new_day > m->num_days) {
                    printf("Invalid day!\n");
                } else {
                    for (int i = 0; i < m->num_days; i++) {
                        if (strcmp(m->tasks[i], task_description) == 0) {
                            m->tasks[i][0] = '\0';
                            add_task(m, new_day, task_description);
                            printf("Task date changed successfully!\n");
                            break;  // Break the loop after changing the task's date
                        }
                    }
                }
                break;
            default:
                printf("Invalid option!\n");
        }
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
        char task[MAX_TASK_LENGTH];
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

        printf("Do you want to search for tasks? (y/n): ");
        char choice;
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            while (1) {
                printf("Enter task description to search: ");
                char description[MAX_TASK_LENGTH];
                scanf(" %[^\n]", description);

                search_tasks(&m, description);

                printf("Do you want to search for more tasks? (y/n): ");
                scanf(" %c", &choice);

                if (choice != 'y' && choice != 'Y') {
                    break;
                }
            }
        }

        printf("Do you want to save tasks? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            printf("Enter filename to save tasks: ");
            char filename[100];
            scanf(" %[^\n]", filename);
            save_tasks(&m, filename);
        }

        printf("Do you want to load tasks? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            printf("Enter filename to load tasks: ");
            char filename[100];
            scanf(" %[^\n]", filename);
            load_tasks(&m, filename);
            print_month(m);
            view_tasks(&m);
        }

        printf("Do you want to create tasks for another month? (y/n): ");
        scanf(" %c", &choice);

        if (choice != 'y' && choice != 'Y') {
            break;
        }

        for (int i = 0; i < m.num_days; i++) {
            m.tasks[i][0] = '\0';
        }
    }

    return 0;
}
