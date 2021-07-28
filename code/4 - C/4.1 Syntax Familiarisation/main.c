#include <stdbool.h>    // allows bool variable
#include <stdio.h>      // allows printf() + scanf()
#include <stdlib.h>     // allows malloc()
#include <string.h>     // allows strcpy() + strlen()

// could import strdup(), but not a standard C library

char* strdup(const char* string)
{
    char* new_string = malloc(strlen(string) + 1);
    strcpy(new_string, string);
    return new_string;
}

int main()
{
    float input;
    int student_count;
    char student[70];   // standard set by the UK Government Data Standards
    bool input_valid = false;

    while (input_valid == false)
    {
        printf("How many students are in your class: ");
        scanf("%f", &input);
        while ((getchar()) != '\n');        // flushes input (clears buffer)
        student_count = (int) input;

        if (student_count > 0 && input == (int) input) { input_valid = true; }
        else { printf("Integer expected. Please try again.\n\n"); }
    }

    input_valid = false;

    char* student_names[student_count];
    int student_marks[student_count];
    char* student_grades[student_count];

    for (int i = 0; i < student_count; i++)
    {
        while (input_valid == false)
        {
            printf("\nName of Student %i: ", (i + 1));
            scanf("%s", student);
            student_names[i] = strdup(student);  // strdup() refreshes student
            input_valid = true;
        }

        input_valid = false;

        while (input_valid == false)
        {
            printf("%s's Mark: ", student_names[i]);
            scanf("%f", &input);
            while ((getchar()) != '\n');    // flushes input (clears buffer)
            student_marks[i] = (int) input;

            if (student_marks[i] >= 0 && student_marks[i] <= 100 && input ==
            (int) input && student_marks[i] == (int) input)
                { input_valid = true; }
            else { printf("Integer between 0 and 100 expected. "
                          "Please try again.\n\n"); }
        }

        input_valid = false;

        if (student_marks[i] >= 70) { student_grades[i] = "1st"; }
        else if (student_marks[i] >= 60) { student_grades[i] = "2:1"; }
        else if (student_marks[i] >= 50) { student_grades[i] = "2:2"; }
        else if (student_marks[i] >= 40) { student_grades[i] = "3rd"; }
        else { student_grades[i] = "Fail"; }

        printf("%s's Grade: %s\n", student_names[i], student_grades[i]);
    }

    printf("\nGrade Results:\n\n");

    for (int i = 0; i < student_count; i++) { printf("Name: %s \tMark: %i"
    "\tGrade: %s\n", student_names[i], student_marks[i], student_grades[i]); }

    return 0;
}
