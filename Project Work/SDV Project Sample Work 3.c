#include <stdio.h>

int main() {
    int year, month, daysInMonth, startingDay, i, j;
    int dayOfWeek = 0; // 0 represents Sunday, 1 represents Monday, etc.

    // Get user input for year and month
    printf("Enter the year: ");
    scanf("%d", &year);
    printf("Enter the month (1-12): ");
    scanf("%d", &month);

    // Calculate the number of days in the month
    if (month == 2) {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            daysInMonth = 29;
        } else {
            daysInMonth = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else {
        daysInMonth = 31;
    }

    // Calculate the starting day of the month (Sunday = 0, Monday = 1, etc.)
    startingDay = dayOfWeek + 1;

    // Print the calendar header
    printf("\n-----------------------------\n");
    printf("   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    printf("-----------------------------\n");

    // Print the calendar days
    for (i = 1; i <= daysInMonth; i++) {
        // Print the spaces before the first day of the month
        if (i == 1) {
            for (j = 0; j < startingDay; j++) {
                printf("     ");
            }
        }

        // Print the day
        printf("%5d", i);

        // Move to the next line if it's Saturday
        if (++dayOfWeek > 6) {
            printf("\n");
            dayOfWeek = 0;
        }
    }

    // Print the calendar footer
    printf("\n-----------------------------\n");

    return 0;
}

