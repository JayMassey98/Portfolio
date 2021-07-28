#include <ctype.h>      // allows tolower()
#include <stdbool.h>    // allows bool variable
#include <stdio.h>      // allows printf() + scanf()
#include <stdlib.h>     // allows malloc function
#include <string.h>     // allows string functions

int total_animals = 0;
int total_groups = 0;
int animal_limit = 10;

int animal_ids[10] = {};
char animal_types[10][71] = {};
char animal_names[10][71] = {};
int animal_ages[10] = {};

int total_deleted = 0;
int deleted_ids[10] = {};

char animal_groups[10][71] = {};

// ----------------------------------------------------

char* strdup(const char* string)
{
    char* new_string = malloc(strlen(string) + 1);
    strcpy(new_string, string);
    return new_string;
}

// ----------------------------------------------------

int add_animal(int id, char* type, char* name, int age)
{
    int n = 0;
    bool in_groups = false;

    if (id != 0) { animal_ids[total_animals] = id; }
    else
    {
        for (int i = 0; i < total_animals; i++)
        {
            if (total_deleted == 0) { animal_ids[total_animals] = total_animals + 1; }
            else
            {
                if (deleted_ids[i] != 0)
                {
                    FILE* deleted;     // deleted = deleted.csv file pointer
                    remove("deleted.csv");

                    animal_ids[total_animals] = deleted_ids[i];

                    if ((deleted = fopen("deleted.csv", "a+")) == NULL)
                        { puts("Error: File could not be opened."); }
                    else
                    {
                        for (int n = 0; n < total_deleted; n++)
                        {
                            deleted_ids[n] = deleted_ids[n + 1];
                            if ((n + 1) < total_deleted) { fprintf(deleted, "%i\n", deleted_ids[n]); }
                        }
                    }

                    fclose(deleted);
                    total_deleted -= 1;
                    break;
                }
            }
        }
    }

    if (animal_ids[total_animals] == 0) { animal_ids[total_animals] = 1; }

    while (type[n] != '\0') { animal_types[total_animals][n] = type[n]; n++; }

    for (int i = 0; i < total_groups; i++)
    {
        if (strcmp(animal_types[total_animals], animal_groups[i]) == 0) { in_groups = true; break; }
    }

    if (in_groups == false)
    {
        n = 0;
        while (type[n] != '\0') { animal_groups[total_groups][n] = type[n]; n++; }
        total_groups += 1;
    }

    n = 0;

    while (name[n] != '\0') { animal_names[total_animals][n] = name[n]; n++; }

    animal_ages[total_animals] = age;
    total_animals += 1;

    return animal_ids[total_animals - 1];
}

void debug_screen()
{
    printf("\nDebug Screen:\n\n");

    printf("total_animals = %i\n", total_animals);
    printf("total_deleted = %i\n", total_deleted);
    printf("total_groups = %i\n\n", total_groups);

    if (total_deleted != 0)
    {
        printf("deleted_ids = ");
        for (int i = 0; i < total_deleted - 1; i++) { printf("%i, ", deleted_ids[i]); }
        printf("%i\n", deleted_ids[total_deleted - 1]);
    }

    if (total_groups != 0)
    {
        printf("animal_groups = ");
        for (int i = 0; i < total_groups - 1; i++) { printf("%s, ", animal_groups[i]); }
        printf("%s\n", animal_groups[total_groups - 1]);
    }

    printf("\n");
}

void display_animals()
{
    if (total_animals == 0) { printf("\nNo animals currently in the system.\n"); }
    else {
        if (total_groups != 1) { printf("\nThere are %i animal types in the system:\n", total_groups); }
        else { printf("\nThere is 1 animal type in the system:\n"); }

        for (int i = 0; i < total_groups; i++)
        {
            printf("\nCollection of %s's:\n\n", animal_groups[i]);

            for (int n = 0; n < total_animals; n++)
            {
                if (strcmp(animal_groups[i], animal_types[n]) == 0)
                {
                    printf("%i\t%s\t%s\t%i\n", animal_ids[n], animal_types[n], animal_names[n], animal_ages[n]);
                }
            }
        }
    }

    printf("\n");
}

void help_options()
{
    printf("\nThe available commands:\n\n"
           "/add\t\tAdd a new animal into the system.\n"
           "/display\tDisplays all animals in the system.\n"
           "/end\t\tTerminates the program immediately.\n"
           "/help\t\tDisplays all available commands.\n"
           "/remove\t\tRemove an animal from the system.\n\n");
}

void input_animal()
{
    char type_input[71];
    char name_input[71];    // standard set by UK Government (+1 for null character)
    int age_input;

    FILE* data;             // data = data.csv file pointer

    printf("\nSelect an animal to initialise: ");
    scanf("%s", type_input);
    printf("Choose a name for your %s: ", type_input);
    scanf("%s", name_input);
    printf("Input the age for your %s: ", type_input);
    scanf("%i", &age_input);

    int animal_id = add_animal(0, type_input, name_input, age_input);

    printf("\n%s, the %i year old %s, is initialised.\n\n", name_input, age_input, type_input);

    // free(type_input); - will be used once malloc function is added
    // free(name_input); - will be used once malloc function is added

    if ((data = fopen("data.csv", "a+")) == NULL)
        { puts("Error: Data file could not be opened."); }
    else
    {
        fprintf(data, "%i,%s,%s,%i\n", animal_id, type_input, name_input, age_input);
    }

    fclose(data);
}

int check_data()    // add to load_data when finished, better to all be in one function
{
    // if too many animals detected:    "Too many animals detected (x).
    //                                  Please configure the data.csv file if you are having issues loading
    //                                  in each animal automatically, or add them manually into the system."

    //                                  Press any key to terminate the program."

    return 0;
}

void load_data()
{
    int id;
    int id_position = 0;
    char type[71];
    char name[71];  // standard set by UK Government (+1 for null character)
    int age;

    FILE* data;     // data = data.csv file pointer
    FILE* deleted;  // deleted = deleted.csv file pointer

    if ((data = fopen("data.csv", "r")) == NULL)
        { puts("Error: Data file could not be opened."); }
    else
    {
        while (fscanf(data, "%i,%70[^,],%70[^,],%i\n", &id, type, name, &age) == 4)
            { add_animal(id, type, name, age); }
    }

    fclose(data);

    if ((deleted = fopen("deleted.csv", "r")) == NULL)
        { puts("Error: Deleted file could not be opened."); }
    else
    {
        while (fscanf(deleted, "%i\n", &id) == 1)
            { deleted_ids[id_position] = id; total_deleted += 1; id_position += 1; }
    }

    fclose(data);

    // return 1;
}

void remove_animal()
{
    // char animal_type[71];
    // char animal_name[71];
    // int animal_age;

    int id_input;
    bool animal_removed = false;
    FILE* temp_data;    // temp_data = temp_data.csv file pointer
    FILE* deleted;      // deleted = deleted.csv file pointer

    printf("\nSelect the id of an animal to remove: ");
    scanf("%i", &id_input);

    if (((temp_data = fopen("temp_data.csv", "a+")) == NULL) || (deleted = fopen("deleted.csv", "a+")) == NULL)
        { puts("Error: Files could not be opened. Please try again."); }
    else
    {
        for (int i = 0; i < total_animals; i++)
        {
            if (id_input != animal_ids[i])
            {
                fprintf(temp_data, "%i,%s,%s,%i\n", animal_ids[i], animal_types[i], animal_names[i], animal_ages[i]);
            }
            else
            {
                deleted_ids[total_deleted] = id_input;
                fprintf(deleted, "%i\n", animal_ids[i]);
                animal_removed = true;
            }
        }

        fclose(temp_data);
        fclose(deleted);

        if (animal_removed == true)
        {
            printf("\n%s, the %i year old %s, has been removed.\n\n", animal_names[id_input - 1], animal_ages[id_input - 1], animal_types[id_input - 1]);

            total_animals = 0;
            total_groups = 0;
            total_deleted = 0;

            memset(animal_ids, 0, sizeof(animal_ids));
            memset(animal_types, 0, sizeof(animal_types));
            memset(animal_types, 0, sizeof(animal_types));
            memset(animal_ages, 0, sizeof(animal_ages));
            memset(animal_groups, 0, sizeof(animal_groups));
            memset(deleted_ids, 0, sizeof(deleted_ids));

            remove("data.csv");
            rename("temp_data.csv", "data.csv");

            load_data();
        }
        else
        {
            printf("No animal with that corresponding ID found.\n\n");
            remove("temp_data.csv");
        }
    }

/*    for (auto& tuple : animals)
    {
        // std::get<0>(tuple) = animal_id;      // std::get<1>(tuple) = animal_type
        // std::get<2>(tuple) = animal_name;    // std::get<3>(tuple) = animal_age

        if (id_input == std::get<0>(tuple))
        {
            std::cout << "\n" << std::get<2>(tuple) << ", the " << std::get<3>(tuple)
                << " year old " << std::get<1>(tuple) << ", has been removed.\n\n";
            deleted_ids.push(std::get<0>(tuple));
            animals.remove(tuple);

            std::ifstream data_log;
            data_log.open("data.csv");

            std::ofstream temp_log;
            temp_log.open("temp.csv");

            // rewrite data to new temp.csv, so rather than sorting and finding the id that needs removing,
            // the id won't be included in the new file with a simple if statement check done 11 lines down.

            if (!data_log.is_open()) { std::cout << "Error: data_log.csv is open." << "\n"; }

            while (data_log.peek() != EOF)
            {
                getline(data_log, animal_id, ',');
                getline(data_log, animal_type, ',');
                getline(data_log, animal_name, ',');
                getline(data_log, animal_age, '\n');

                if (id_input != stoi(animal_id)) { temp_log << animal_id << "," << animal_type << ","
                    << animal_name << "," << animal_age << "\n"; }
            }

            data_log.close();
            temp_log.close();

            remove("data.csv");
            if (rename("temp.csv", "data.csv") != 0) { std::cout << "Error: temp.csv is open." << "\n"; }

            std::ofstream deleted_ids_log;
            deleted_ids_log.open("deleted_ids.csv", std::ios_base::app);  // append instead of overwrite
            deleted_ids_log << id_input << "\n";
            deleted_ids_log.close();

            animal_removed = true;
            break;
        }
    }
    if (animal_removed == false) { "No animal with that corresponding ID found.\n\n"; } */
}

// end of all other functions except for the main function below

int main()
{
    char command_input[9];

    // if (check_data() == 0) { exit(0); };    // terminates the program early
    load_data();

    printf("Welcome to the animal sanctuary database.\n");

//    while (true)
//    {
//        printf("How many animals can you fit in your sanctuary: ");
//        scanf("%f", &input);
//        while ((getchar()) != '\n');        // flushes input (clears buffer)
//        animal_limit = (int) input;
//
//        if (animal_limit > 0 && input == (int) input) { break; }
//        else { printf("Integer expected. Please try again.\n\n"); }
//    }

    // printf("%zu", sizeof(animals));
    // printf(" animals have been loaded into the system.\n\n"

    if (animal_limit != 1) { printf("Space for up to %i animals has"
        " been allocated.\n\n", animal_limit); }
    else { printf("Space for up to 1 animal has been allocated.\n\n"); }

    // animals = malloc(sizeof *animals * (((animal_limit * 70)) + 1));
    // animal_groups = malloc(sizeof *animal_groups * (((animal_limit * 70)) + 1));

    printf("Type \"/help\" for a list of available commands.\n\n");

    while (true)
    {
        printf("Choose a command to run: ");
        scanf("%s", command_input);

        for (int i = 0; i < strlen(command_input); i++) {
        command_input[i] = tolower((unsigned char) command_input[i]); }

        // would change to a switch statement if 5 or more types were present, as
        // c switches to a slightly more efficient lookup table behind the scenes

        if      (!strcmp(command_input, "/add")     )
                { input_animal();       continue;   }

        else if (!strcmp(command_input, "/debug")   )
                { debug_screen();       continue;   }

        else if (!strcmp(command_input, "/display") )
                { display_animals();    continue;   }

        else if (!strcmp(command_input, "/end")     )
                { break; }

        else if (!strcmp(command_input, "/help")    )
                { help_options();       continue;   }

        else if (!strcmp(command_input, "/remove")  )
                { remove_animal();      continue;   }

        else    { printf("Command not recognised.\n\n"); }
    }

    return 0;
}
