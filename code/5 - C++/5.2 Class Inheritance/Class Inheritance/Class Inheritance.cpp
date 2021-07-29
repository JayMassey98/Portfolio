#include <iostream> // imports base functions

int random(int min, int max)
{
    srand((unsigned)time(0));
    int randomNumber;
    randomNumber = (rand() % max) + min;
    return randomNumber;
}

class Animal
{
private: std::string animalType; int animalAge;

protected: std::string animalName; int animalNoise = 0;

public:

    Animal(std::string type, std::string name, int age, int noise = 0) :
        animalType{ type }, animalName{ name }, animalAge{ age }, animalNoise{ noise }
    {
        std::cout << "\n" << animalName << " is a " << animalAge <<
            " year old " << animalType << "." << std::endl;
    }
};

class Cat : public Animal
{
private: int meowLength = 0;

public:

    Cat(std::string type, std::string name, int age, int meows = 0) :
        Animal{ type, name, age, meows }
    {
        meowLength = random(1, 5);
        animalNoise += 1;

        std::cout << animalName << " says: Me";
        for (int i = 0; i < meowLength; i++) { std::cout << "o"; }
        std::cout << "w!\n" << animalName << " meowed 1 time.\n";
    }
};

class Dog : public Animal
{
private: std::string plural;

public:

    Dog(std::string type, std::string name, int age, int barks = 0) :
        Animal{ type, name, age, barks }
    {
        animalNoise = random(1, 3);
        if (animalNoise != 1) { plural = "s"; }
        else { plural = ""; }

        std::cout << animalName << " says: ";
        for (int i = 0; i < animalNoise; i++) { std::cout << "Bark! "; }
        std::cout << "\n" << animalName << " barked " << animalNoise << " time" << plural << ".\n";
    }
};

int main()
{
    while (true)
    {
        std::string animalType;
        std::string nameInput;
        int ageInput;

        std::cout << "Select an animal to initialise: ";
        std::cin >> animalType;

        for (char& c : animalType) { c = std::tolower(c); } // all letters switched to lower case

        if (animalType == "end") { break; }

        std::cout << "\nChoose a name for your " << animalType << ": ";
        std::cin >> nameInput;
        std::cout << "Input the age for your " << animalType << ": ";
        std::cin >> ageInput;

        // would change the following code to a switch statement if 5 or more animal types were
        // present, as c++ switches to a slightly more efficient lookup table behind the scenes

        if (animalType == "cat") { Cat cat(animalType, nameInput, ageInput); }
        else if (animalType == "dog") { Dog dog(animalType, nameInput, ageInput); }
        else { Animal animal(animalType, nameInput, ageInput); }

        std::cout << std::endl;
    }

    return 0;
}