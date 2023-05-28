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

void view_tasks(struct Month m) {
  int day;
  printf("\nEnter day to view tasks (1-%d, 0 to exit): ", m.num_days);
  scanf("%d", &day);

  if (day == 0) {
    return;
  }

  if (day < 1 || day > m.num_days) {
    printf("Invalid day!\n");
    return;
  }

  for (int i = 0; i < m.num_days; i++) {
    if (day == i + 1) {
      if (m.tasks[i] != NULL) {
        printf("Tasks for Day %d: %s\n", day, m.tasks[i]);
      } else {
        printf("No tasks found for Day %d\n", day);
      }
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

    view_tasks(m);

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
