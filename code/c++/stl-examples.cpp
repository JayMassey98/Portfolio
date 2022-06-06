// ---------------------------------------------------------------------------
// This project is a self-taught exercise. For more examples of various coding
// projects, please see my GitHub portfolio at https://github.com/JayMassey98.
// ---------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <queue>


// global items

std::string command;
std::list <std::tuple <int, std::string, std::string, int> > animals;
std::map <std::string, int> animal_groups;
std::queue <int> deleted_ids;


// base functions

int add_animal(int animal_id, std::string animal_type,
    std::string animal_name, int animal_age)
{
    int total_animals = 0;

    for (auto const& x : animal_groups)
    {
        if (x.first == animal_type) { break; }
        else { total_animals += 1; }
    }

    std::map<std::string, int>::iterator it = animal_groups.find(animal_type);

    if (it != animal_groups.end()) { it->second++; }
    else { animal_groups.insert({ animal_type, 1 }); }

    if (animal_id == NULL)  // the id may already be sourced from data.csv
    {
        if (deleted_ids.empty())
        {
            animal_id = static_cast<int>(animals.size()) + 1;
        }
        else
        {
            animal_id = deleted_ids.front(); deleted_ids.pop();
        }
    }

    std::tuple<int, std::string, std::string, int> animal_details =
        std::make_tuple(animal_id, animal_type, animal_name, animal_age);

    animals.push_back(animal_details);

    return (animal_id);
}


void debug_screen()
{
    std::cout << "\nDebug Screen:\n\n";
    std::cout << "animals.size() = "        << animals.size()       << "\n";
    std::cout << "animal_groups.size() = "  << animal_groups.size() << "\n";
    std::cout << "deleted_ids.size() = "    << deleted_ids.size()   << "\n\n";

    if (animal_groups.size() > 0)
    {
        for (auto const& x : animal_groups)
        {
            std::cout << x.first << "s = " << x.second << "\n";
        }

        std::cout << "\n";
    }

    if (deleted_ids.size() > 0)
    {
        std::cout << "Deleted ID's: ";
        std::queue <int> temp_queue = deleted_ids;

        for (unsigned int i = 0; i < deleted_ids.size() - 1; i++)
        {
            std::cout << temp_queue.front() << ", ";
            temp_queue.pop();
        }

        std::cout << temp_queue.front() << "\n\n";
    }
}


void display_animals()
{
    if (animals.empty())
    {
        std::cout << "\nNo animals currently in the system.\n\n";
    }
    else
    {
        if (animal_groups.size() != 1)
        {
            std::cout << "\nThere are " <<  animal_groups.size() <<
                " animal types in the system:\n\n";
        }
        else
        {
            std::cout << "\nThere is 1 animal type in the system:\n\n";
        }

        for (auto const& x : animal_groups)
        {
            std::cout << "Collection of " << x.first << "s:\n\n";

            for (auto& tuple : animals)
            {
                if (std::get<1>(tuple) == x.first)
                {
                    std::cout << std::get<2>(tuple) << "\tAge " <<
                        std::get<3>(tuple) << "\t ID #" <<
                        std::get<0>(tuple) << "\n";
                }
            }

            std::cout << "\n";
        }
    }
}


void help_options()
{
    std::cout << "\nThe available commands:\n\n"
        "/add\t\tAdd a new animal into the system.\n"
        "/debug\t\tShows several key variable values.\n"
        "/display\tDisplays all animals in the system.\n"
        "/end\t\tTerminates the program immediately.\n"
        "/help\t\tDisplays all available commands.\n"
        "/remove\t\tRemove an animal from the system.\n\n";
}


void input_animal()
{
    std::string deleted_id;
    std::string type_input;
    std::string name_input;
    int age_input;

    std::cout << "\nSelect an animal to initialise: ";
    std::cin >> type_input;

    // flush the newline from the previous cin for the next getline
    std::cin.ignore(1, '\n');

    for (char& c : type_input)
    {
        c = std::tolower(c);    // all characters switched to lower case
    }

    std::cout << "Choose a name for your " << type_input << ": ";
    std::getline(std::cin, name_input); // getline used due to possible spaces
    std::cout << "Input the age for your " << type_input << ": ";
    std::cin >> age_input;

    int animal_id = add_animal(NULL, type_input, name_input, age_input);

    std::cout << "\n" << name_input << ", the " << age_input <<
        " year old " << type_input << ", is initialised.\n\n";

    // append the new data to data_log.csv, so it's
    // saved after the program has been terminated

    std::ofstream data_log;

    // append from end instead of overwriting

    data_log.open("data.csv", std::ios_base::app);
    data_log << animal_id << "," << type_input << "," << name_input << "," <<
        age_input << "\n";
    data_log.close();

    std::ifstream deleted_ids_log;
    deleted_ids_log.open("deleted.csv");

    std::ofstream temp_log;
    temp_log.open("temp.csv");

    if (!deleted_ids_log.is_open())
    {
        std::cout << "Error: deleted.csv open." << "\n";
    }

    while (deleted_ids_log.peek() != EOF)
    {
        getline(deleted_ids_log, deleted_id, '\n');

        if (animal_id != stoi(deleted_id))
        {
            temp_log << animal_id << "\n";
        }
    }

    deleted_ids_log.close();
    temp_log.close();

    remove("deleted.csv");

    if (rename("temp.csv", "deleted.csv") != false)
    {
        std::cout << "Error: temp.csv open." << "\n";
    }
}


void load_data()
{
    std::string animal_id;
    std::string animal_type;
    std::string animal_name;
    std::string animal_age;

    int total_animals = 0;

    std::ifstream data_log;
    data_log.open("data.csv");

    if (!data_log.is_open())
    {
        std::cout << "Error: data_log.csv open." << "\n";
    }

    while (data_log.peek() != EOF)
    {
        getline(data_log, animal_id, ',');
        getline(data_log, animal_type, ',');
        getline(data_log, animal_name, ',');
        getline(data_log, animal_age, '\n');

        if (!animal_id.empty()) {
            add_animal(stoi(animal_id), animal_type, animal_name,
                stoi(animal_age)); total_animals += 1;
        }
    }

    data_log.close();

    std::ifstream deleted_ids_log;
    deleted_ids_log.open("deleted.csv");

    if (!deleted_ids_log.is_open())
    {
        std::cout << "Error: deleted.csv open." << "\n";
    }

    while (deleted_ids_log.peek() != EOF)
    {
        getline(deleted_ids_log, animal_id, '\n');

        if (!animal_id.empty())
        {
            deleted_ids.push(stoi(animal_id));
        }
    }

    deleted_ids_log.close();
}


void remove_animal()
{
    std::string animal_id;
    std::string animal_type;
    std::string animal_name;
    std::string animal_age;

    int id_input;
    bool animal_removed = false;

    std::cout << "\nSelect the id of an animal to remove: ";
    std::cin >> id_input;

    for (auto& tuple : animals)
    {
        // TODO: Replace the follow numbers with an enum.
        
        // for reference:
        // std::get<0>(tuple) = animal_id
        // std::get<1>(tuple) = animal_type
        // std::get<2>(tuple) = animal_name
        // std::get<3>(tuple) = animal_age

        if (id_input == std::get<0>(tuple))
        {
            std::map<std::string, int>::iterator it =
                animal_groups.find(std::get<1>(tuple));

            if (it != animal_groups.end())
            {
                it->second -= 1;
            }

            for (auto const& x : animal_groups)
            {
                if (x.second == 0) { animal_groups.erase(it); break; };
            }

            std::cout << std::get<2>(tuple) << ", the " << std::get<3>(tuple)
                << " year old " << std::get<1>(tuple) <<
                ", has been removed.\n\n";

            deleted_ids.push(std::get<0>(tuple));
            animals.remove(tuple);

            std::ifstream data_log;
            data_log.open("data.csv");

            std::ofstream temp_log;
            temp_log.open("temp.csv");

            // rewrite data to new temp.csv, so rather than sorting and finding
            // the id to remove, the id won't be included in the new file with
            // an if statement done below.

            if (!data_log.is_open())
            {
                std::cout << "Error: data_log.csv is open." << "\n";
            }

            while (data_log.peek() != EOF)
            {
                getline(data_log, animal_id, ',');
                getline(data_log, animal_type, ',');
                getline(data_log, animal_name, ',');
                getline(data_log, animal_age, '\n');

                if (id_input != stoi(animal_id))
                {
                    temp_log << animal_id << "," << animal_type <<
                        "," << animal_name << "," << animal_age << "\n";
                }
            }

            data_log.close();
            temp_log.close();

            remove("data.csv");

            if (rename("temp.csv", "data.csv") != false)
            {
                std::cout << "Error: temp.csv is open." << "\n";
            }

            std::ofstream deleted_ids_log;
            deleted_ids_log.open("deleted.csv", std::ios_base::app);
            deleted_ids_log << id_input << "\n";
            deleted_ids_log.close();

            animal_removed = true;

            break;
        }
    }

    if (animal_removed == false)
    {
        "No animal with that corresponding ID found.\n\n";
    }
}


// main function

int main()
{
    load_data();

    std::cout << "Welcome to the animal sanctuary database.\n" <<
        animals.size() << " animals have been loaded into the system.\n\n"
        "Type \"/help\" for a list of available commands.\n\n";

    while (true)
    {
        std::cout << "Choose a command to run: ";
        std::cin >> command;

        for (char& c : command)
        {
            c = std::tolower(c);    // all characters switched to lower case
        }

        if      (command == "/add")     { input_animal();       continue; }
        else if (command == "/debug")   { debug_screen();       continue; }
        else if (command == "/display") { display_animals();    continue; }
        else if (command == "/end")     {                       break;    }
        else if (command == "/help")    { help_options();       continue; }
        else if (command == "/remove")  { remove_animal();      continue; }

        else { std::cout << "Command not recognised.\n\n"; }
    }

    return 0;
}
