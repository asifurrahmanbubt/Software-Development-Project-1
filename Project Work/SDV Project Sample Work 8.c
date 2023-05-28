#include <stdio.h>

// Structure to represent a task
struct Task {
    int day;
    char description[100];
};

// Structure to represent a month in the calendar
struct Month {
    int year;
    int month;
    int num_days;
    int start_day;
    struct Task tasks[31];  // Maximum 31 tasks in a month
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
    m.start_day = (1 + y + y/4 - y/100 + y/400 + (31 * m1)/12) % 7;

    return m;
}

// Function to add a task to a specific date in a month
void add_task(struct Month* m, int day, const char* description) {
    if (day < 1 || day > m->num_days) {
        printf("Invalid day!\n");
        return;
    }

    struct Task task;
    task.day = day;
    snprintf(task.description, sizeof(task.description), "%s", description);

    m->tasks[day - 1] = task;
    printf("Task added successfully!\n");
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

        // Print tasks for the current day, if any
        if (m.tasks[i - 1].day != 0) {
            printf("(%s)", m.tasks[i - 1].description);
        }

        if ((i + m.start_day) % 7 == 0) {
            printf("\n");
        }
    }
}

// Function to save the tasks to a file
void save_tasks(struct Month m) {
    char filename[50];
    snprintf(filename, sizeof(filename), "tasks_%d_%d.txt", m.month, m.year);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < m.num_days; i++) {
        if (m.tasks[i].day != 0) {
            fprintf(file, "%d: %s\n", m.tasks[i].day, m.tasks[i].description);
        }
    }

    fclose(file);
    printf("Tasks saved to file: %s\n", filename);
}

// Function to load tasks from a file
void load_tasks(struct Month* m) {
    char filename[50];
    snprintf(filename, sizeof(filename), "tasks_%d_%d.txt", m->month, m->year);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("No tasks found for this month.\n");
        return;
    }

    int day;
    char description[100];

    while (fscanf(file, "%d: %[^\n]\n", &day, description) != EOF) {
        if (day >= 1 && day <= m->num_days) {
            struct Task task;
            task.day = day;
            snprintf(task.description, sizeof(task.description), "%s", description);
            m->tasks[day - 1] = task;
        }
    }

    fclose(file);
    printf("Tasks loaded from file: %s\n", filename);
}

int main() {
    int year, month;

    // Prompt user for input
    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month (1-12): ");
    scanf("%d", &month);

    // Initialize the specified month
    struct Month m = init_month(year, month);

    // Load tasks from file (if available)
    load_tasks(&m);

    // Prompt user for task input
    int day;
    char description[100];
    printf("Enter day to add a task: ");
    scanf("%d", &day);
    printf("Enter task description: ");
    scanf(" %[^\n]", description);

    // Add task to the specified date
    add_task(&m, day, description);

    // Print the updated month
    print_month(m);

    // Save tasks to file
    save_tasks(m);

    return 0;
}


