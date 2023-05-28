#include <stdio.h>

int main() {
    int year, month, day, start_day, num_days;

    // Prompt user for year
    printf("Enter a year: ");
    scanf("%d", &year);

    // Determine if it's a leap year
    int is_leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    // Loop through each month
    for (month = 1; month <= 12; month++) {
        // Determine the number of days in this month
        if (month == 2) {
            num_days = is_leap ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            num_days = 30;
        } else {
            num_days = 31;
        }

        // Determine the day of the week the first day of the month falls on
        start_day = ((year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
        for (int i = 1; i < month; i++) {
            if (i == 2) {
                start_day += is_leap ? 29 : 28;
            } else if (i == 4 || i == 6 || i == 9 || i == 11) {
                start_day += 30;
            } else {
                start_day += 31;
            }
        }
        start_day %= 7;

        // Print the month header
        printf("\n\n%2d/%4d\n", month, year);
        printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        // Print the calendar for this month
        for (int i = 0; i < start_day; i++) {
            printf("     ");
        }
        for (day = 1; day <= num_days; day++) {
            printf("%-5d", day);
            if ((start_day + day) % 7 == 0) {
                printf("\n");
            }
        }
    }

    return 0;
}

