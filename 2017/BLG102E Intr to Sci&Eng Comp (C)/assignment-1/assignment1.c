#include <stdio.h>  // printf, scanf
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

int main()
{

    // Get year, month and day from user.
    int year = 0, month = 0, day = 0;
    printf("Enter date [year month day]: ");
    scanf("%d %d %d", &year, &month, &day);
    
    // Input validation.
    if ((month > 12 || month < 1) || (year < 0) || (day < 1)){
        printf("Invalid date.\n");
        return EXIT_FAILURE;
    }
    switch (month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day > 31){
                printf ("Invalid date.\n");
                return EXIT_FAILURE;
            }
            break;
        case 2:
            if (day > 28){
                printf ("Invalid date.\n");
                return EXIT_FAILURE;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (day > 30){
                printf ("Invalid date.\n");
                return EXIT_FAILURE;
            }
    }
    
    // Get end year from user. 
    int end_year = 0;
    printf("Enter end year: ");
    scanf("%d", &end_year);
    
    // Input validation.
    if (end_year <= year){
        printf("End year must be greater than first one.\n"
               "Unfortunately, there is no while loop here:( You need to re-run the program.\n"
               "Be careful next time!\n");
        return EXIT_FAILURE;
    }
    
    // Initialize the variables q, m, j and k.
    int q = day;
    int m = month;
    int j = year / 100;
    int k = year % 100;
    
    // Adjust m, j and k if necessary. (From the definition of Zeller's formula.)
    if (month == 1 || month == 2){
        m += 12;
        j = (year - 1) / 100;
        k = (year - 1) % 100;
    }
    
    // Calculate the weekday and print it.
    int week_day = (q + (13 * (m + 1) / 5) + k + k / 4 + j / 4 +5 * j) % 7;
    printf("It's a ");
    switch (week_day){
        case 0:
            printf("Saturday");
            break;
        case 1:
            printf("Sunday");
            break;
        case 2:
            printf("Monday");
            break;
        case 3:
            printf("Tuesday");
            break;
        case 4:
            printf("Wednesday");
            break;
        case 5:
            printf("Thursday");
            break;
        case 6:
            printf("Friday");
            break;
    }
    printf(".\n");
    
    /* Count and print how many times the given day-and-month 
     * falls on the same weekday starting with the 
     * next year and ending on a given year.
     */
    int count = 0;
    for(int i = year + 1; i <= end_year; i++){
        int j = i / 100;
        int k = i % 100;
        if (month == 1 || month == 2){
            // No need to do m += 12 here because we have already did it 
            // and don't want to change it everytime.
            j = (i - 1) / 100;
            k = (i - 1) % 100;
        }
        if ((q + (13 * (m + 1) / 5) + k + k / 4 + j / 4 +5 * j) % 7 == week_day){
            count++;
        }
    }
    printf("Same day-and-month on same weekday between %d and %d: %d\n", year+1, end_year, count);

    return EXIT_SUCCESS;
}
