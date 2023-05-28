#include <stdio.h>

// Structure to represent a month in the calendar
struct Month {
    int year;
    int month;
    int num_days;
    int start_day;
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
}

int main() {
    int year;

    // Prompt user for input
    printf("Enter year: ");
    scanf("%d", &year);

    // Loop through each month and print the calendar
    for (int month = 1; month <= 12; month++) {
        struct Month m = init_month(year, month);
        print_month(m);
    }

    return 0;
}
