#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdint.h>

#define FORMAT "YYMMDD-nnnC"
#define PERSONNUMMER_DIGIT 10U
#define YEAR_MIN 00U
#define YEAR_MAX 99U
#define MONTH_MIN 1U
#define MONTH_MAX 12U
#define DAY_MIN 1U
#define FEBRUARY 2U

int main(){

    char format[] = FORMAT;
    char string[sizeof(FORMAT)] = {0};
    printf("Enter a personnummer in the format of %s: ", format);
    uint8_t i = 0;
    unsigned int year = 0, month = 0, day = 0, birth_nr = 0, control = 0;
    
    while (i < sizeof(FORMAT) - 1)
    {
        char chr = getchar();
        if ((chr == '\n') || (chr == EOF))
        {
            break;
        }
        string[i++] = chr;
    }

    bool status = true;
    i = 0;

    while (i < sizeof(FORMAT) - 1)
    {
        if (isalpha(format[i])) 
        {
            if (!isdigit(string[i]))
            {
                status = false;
                break;
            }
        }
        else
        {
            if (format[i] != string[i]) 
            {
                status = false;
                break;
            }
        }
        i++;
    }

    // Implementing if it was a leap year. (in case a person is born in Feb/29)
    if (status)
    {
        sscanf(string, "%02u%02u%02u-%03u%u ", &year, &month, &day, &birth_nr, &control);

        if ((year < YEAR_MIN) || (year > YEAR_MAX) || (month < MONTH_MIN) || (month > MONTH_MAX) || (day < DAY_MIN))
        {
            status = false;
        }
        else
        {
            uint8_t days[MONTH_MAX] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            if (day > days[month - 1])
            {
                status = false;

                if (month == FEBRUARY)
                {
                    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) 
                    {
                        if (day == days[month - 1] + 1)
                        {
                            status = true;
                        }
                    }
                }
            }
        }
    }

    if(status)
    {
        // "YYMMDD-nnnC"  ==> "Y1Y2M1M2D1D2-n1n2n3C"
        unsigned int Y1 = 0, Y2 = 0, M1 = 0, M2 = 0, D1 = 0,  D2 = 0, n1 = 0, n2 = 0, n3 = 0, C = 0, sum= 0, result = 0;
        bool is_correct = true; 

        sscanf(string,"%01u%01u%01u%01u%01u%01u-%01u%01u%01u%01u", &Y1, &Y2, &M1, &M2, &D1, &D2, &n1, &n2, &n3, &C);
        unsigned int personnr[PERSONNUMMER_DIGIT] = {Y1,Y2,M1,M2,D1,D2,n1,n2,n3,C};

        for ( i = 0; i < (sizeof(personnr)/sizeof(personnr[i]))-1; i++)
        {
            int sum = 0;
            if (i % 2 == 0)
            {
                if (personnr[i] * 2 > 9 )
                {
                    sum = personnr[i] * 2 - 9;                   
                }
                else
                {
                    sum = personnr[i] * 2;
                }                          
            }
            else
            {
                sum = personnr[i];
            }
            result += sum;                     
        }

        if ((10-(result %10 )) %10 == C)
        {
            printf("The personnumer you entered is correct!\n");
        }
        else
        {
            int checksum = (10-(result %10 )) %10;
            printf("%d\n", checksum);
            printf("The entered personnummer is not a valid one!");
        }
        
    }

    else{
        printf("The entered format of the personnummer is%s valid!\n", status ? "" : " not");
    }

    return 0;
}