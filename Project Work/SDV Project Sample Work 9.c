#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a month in the calendar
struct Month {
    int year;
    int month;
    int num_days;
    int start_day;
    char* tasks[31];
};

// Function to determine if a year is a leap year
int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// Function to initialize a Month struct
struct Month init_month(int year, int month) {
    struct Month m;
    m.year = year;
    m.month = month;

    // Determine number of days in the month
    if (month == 2) {
        m.num_days = is_leap_year(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        m.num_days = 30;
    } else {
        m.num_days = 31;
    }

    // Determine the day of the week the month starts on
    int y = year - (14 - month) / 12;
    int m1 = month + 12 * ((14 - month) / 12) - 2;
    m.start_day = (1 + y + y / 4 - y / 100 + y / 400 + (31 * m1) / 12) % 7;

    // Initialize task array to NULL
    for (int i = 0; i < m.num_days; i++) {
        m.tasks[i] = NULL;
    }

    return m;
}

// Function to print a Month struct
void print_month(struct Month m) {
    // Print the month header
    printf("\n\n   %d/%d\n", m.month, m.year);
    printf("Su Mo Tu We Th Fr Sa\n");

    // Print the calendar
    for (int i = 0; i < m.start_day; i++) {
        printf("   ");
    }
    for (int i = 1; i <= m.num_days; i++) {
        printf("%2d ", i);
        if ((i + m.start_day) % 7 == 0) {
            printf("\n");
        }
    }

    // Print the tasks
    for (int i = 0; i < m.num_days; i++) {
        if (m.tasks[i] != NULL) {
            printf("(%s)", m.tasks[i]);
        }
    }
}

// Function to add a task to a specific date
void add_task(struct Month* m, int day, const char* task) {
    // Check if the day is within the valid range
    if (day < 1 || day > m->num_days) {
        printf("Invalid day! Task not added.\n");
        return;
    }

    // Allocate memory for the task and copy it
    char* new_task = (char*)malloc(strlen(task) + 1);
    strcpy(new_task, task);

    // Check if there is an existing task for the day
    if (m->tasks[day - 1] != NULL) {
        // Free the memory for the existing task
        free(m->tasks[day - 1]);
    }

    // Add the new task
    m->tasks[day - 1] = new_task;
}

int main() {
    int year, month;

    // Prompt user for input
    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month (1-12): ");
    scanf("%d", &month);

    // Initialize and print the specified month
    struct Month m = init_month(year, month);
    print_month(m);

    // Prompt user for tasks
    printf("\nEnter tasks (press enter to finish):\n");
    char task[100];
    int day;
    while (1) {
        printf("Enter day to add a task (0 to finish): ");
        scanf("%d", &day);

        // Exit loop if day is 0
        if (day == 0) {
            break;
        }

        printf("Enter task description: ");
        scanf(" %[^\n]", task);

        add_task(&m, day, task);
    }

    // Print the calendar with tasks
    print_month(m);

    // Free memory allocated for tasks
    for (int i = 0; i < m.num_days; i++) {
        if (m.tasks[i] != NULL) {
            free(m.tasks[i]);
        }
    }

    return 0;
}

