#include <ctype.h>      // allows tolower()
#include <stdbool.h>    // allows bool variable
#include <stdio.h>      // allows printf() + scanf()
#include <stdlib.h>     // allows rand()
#include <string.h>     // allows string functions
#include <time.h>       // allows time()

bool main_loop = true;

int random(int min, int max)
{
    srand((unsigned)time(0));
    int random_number;
    random_number = (rand() % max) + min;
    return random_number;
}

void cat(char* name)
{
    int meow_length = random(1, 5);

    printf("\n%s says: Me", name);
    for (int i = 0; i < meow_length; i++) { printf("o"); }
    printf("w!\n%s has meowed 1 time.", name);
};

void dog(char* name)
{
    int bark_number = random(1, 5);

    printf("\n%s says: ", name);
    for (int i = 0; i < bark_number; i++) { printf("Bark! "); }

    if (bark_number != 1) {
        printf("\n%s has barked %i times.", name, bark_number); }
    else { printf("\n%s has barked 1 time.", name); }
};

void animal(char* type, char* name, int age)
{
    printf("\n%s is a %i year old %s.", name, age, type);

    // would change to a switch statement if 5 or more types were present, as
    // c switches to a slightly more efficient lookup table behind the scenes

    if (!strcmp(type, "cat")) { cat(name); }
    else if (!strcmp(type, "dog")) { dog(name); }
}

int main()
{
    while (main_loop == true)
    {
        char type[70];
        char name[70];  // standard set by the UK Government Data
        int age;

        printf("Select an animal to initialise: ");
        scanf("%s", type);

        for (int i = 0; i < strlen(type); i++) {
        type[i] = tolower((unsigned char) type[i]); }

        if (!strcmp(type, "end")) { main_loop = false; break; }

        printf("\nChoose a name for your %s: ", type);
        scanf("%s", name);
        printf("Input the age for your %s: ", type);
        scanf("%i", &age);

        animal(type, name, age);
        printf("\n\n");
    }

    return 0;
}
