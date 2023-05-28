#include <stdio.h>

// Function to determine if a year is a leap year
int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// Function to determine the number of days in a month
int get_num_days(int month, int year) {
    int num_days;

    switch(month) {
        case 2:
            num_days = is_leap_year(year) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            num_days = 30;
            break;
        default:
            num_days = 31;
    }

    return num_days;
}

// Function to print the calendar for a given month and year
void print_calendar(int month, int year) {
    int num_days, day_of_week, i;

    // Determine the number of days in the month and the day of the week the month starts on
    num_days = get_num_days(month, year);
    day_of_week = ((1 - month + 12) % 12 * 31 + 2) / 10 % 7;

    // Print the header for the calendar
    printf("     %d/%d\n", month, year);
    printf(" Su Mo Tu We Th Fr Sa\n");

    // Print the calendar days
    for (i = 1; i <= num_days + day_of_week; i++) {
        if (i <= day_of_week) {
            printf("   ");
        } else {
            printf("%3d", i - day_of_week);
        }
        if (i % 7 == 0) {
            printf("\n");
        }
    }

    printf("\n");
}

int main() {
    int month, year;

    // Prompt the user for the month and year
    printf("Enter the month (1-12): ");
    scanf("%d", &month);
    printf("Enter the year: ");
    scanf("%d", &year);

    // Print the calendar for the given month and year
    print_calendar(month, year);

    return 0;
}

