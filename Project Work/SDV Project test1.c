#include <stdio.h>

int main() {
    int year, month, num_days, start_day;

    // Prompt user for input
    printf("Enter year: ");
    scanf("%d", &year);

    // Loop through each month
    for (month = 1; month <= 12; month++) {
        // Determine number of days in the month
        if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                num_days = 29;
            } else {
                num_days = 28;
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            num_days = 30;
        } else {
            num_days = 31;
        }

        // Determine the day of the week the month starts on
        int y = year - (14 - month) / 12;
        int m = month + 12 * ((14 - month) / 12) - 2;
        start_day = (1 + y + y/4 - y/100 + y/400 + (31 * m)/12) % 7;

        // Print the month header
        printf("\n\n   %d/%d\n", month, year);
        printf("Su Mo Tu We Th Fr Sa\n");

        // Print the calendar
        for (int i = 0; i < start_day; i++) {
            printf("   ");
        }
        for (int i = 1; i <= num_days; i++) {
            printf("%2d ", i);
            if ((i + start_day) % 7 == 0) {
                printf("\n");
            }
        }
    }

    return 0;
}

