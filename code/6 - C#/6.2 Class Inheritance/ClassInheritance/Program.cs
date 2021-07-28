using System;

namespace ClassInheritance
{
    class MainClass
    {
        class Animal
        {
            public string animal;
            public string name;
            public int age;

            public void PrintBaseDetails()
            {
                Console.WriteLine("Animal: " + animal);
                Console.WriteLine("Name: " + name);
                Console.WriteLine("Age: " + age);
            }
        }

        class Dog : Animal
        {
            public int barks;
            public int barkNumber;

            public void PrintDogDetails()
            {
                Console.WriteLine("Barks: " + barks);
            }

            public void Bark()
            {
                System.Random random = new System.Random();
                barkNumber = random.Next(1, 3);

                Console.WriteLine();

                for (int i = 0; i < barkNumber; i++)
                {
                    Console.WriteLine("Bark!");
                    barks += 1;
                }

                Console.WriteLine();
            }
        }

        class Cat : Animal
        {
            public int meows;
            public int meowLength;

            public void PrintCatDetails()
            {
                Console.WriteLine("Meows: " + meows);
            }

            public void Meow()
            {
                System.Random random = new System.Random();
                meowLength = random.Next(1, 5);

                Console.Write("\nMe");

                for (int i = 0; i < meowLength; i++)
                {
                    Console.Write("o");
                }

                Console.WriteLine("w!\n");
                meows += 1;
            }
        }

        public static void Main(string[] args)
        {
            Dog spotty = new Dog
            {
                animal = "Dog",
                name = "Spotty",
                age = 7,
                barks = 0
            };

            Cat kitty = new Cat
            {
                animal = "Cat",
                name = "Kitty",
                age = 13,
                meows = 0
            };

            spotty.PrintBaseDetails();
            spotty.PrintDogDetails();

            spotty.Bark();

            spotty.PrintBaseDetails();
            spotty.PrintDogDetails();

            Console.WriteLine("\n-----------\n");

            kitty.PrintBaseDetails();
            kitty.PrintCatDetails();

            kitty.Meow();

            kitty.PrintBaseDetails();
            kitty.PrintCatDetails();
        }
    }
}