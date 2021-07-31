using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace FileHandling
{
    class Program
    {
        private static readonly List<Tuple<int, string, string, int>> animals = new List<Tuple<int, string, string, int>>();
        private static readonly Dictionary<string, int> animalGroups = new Dictionary<string, int>();
        private static readonly Queue deletedIds = new Queue();

        static int AddAnimal(int animalId, string animalType, string animalName, int animalAge)
        {
            if (!animalGroups.ContainsKey(animalType)) { animalGroups.Add(animalType, 1); }
            else { animalGroups[animalType] += 1; }

            if (animalId == 0)  // if the id is being sourced from data.csv
            {
                if (deletedIds.Count == 0) { animalId = animals.Count + 1; }
                else { animalId = (int)deletedIds.Peek(); deletedIds.Dequeue(); }
            }

            Tuple<int, string, string, int> animalDetails
                = Tuple.Create(animalId, animalType, animalName, animalAge);
            animals.Add(animalDetails);

            return (animalId);
        }

        static void DebugScreen()
        {
            Console.WriteLine("\nDebug Screen:\n");
            Console.WriteLine("animals.size() = " + animals.Count);
            Console.WriteLine("animal_groups.size() = " + animalGroups.Count);
            Console.WriteLine("deleted_ids.size() = " + deletedIds.Count + "\n");

            if (animalGroups.Count > 0)
            {
                foreach (var item in animalGroups) { Console.WriteLine(item.Key + "s = " + item.Value); }
                Console.WriteLine();
            }

            if (deletedIds.Count > 0)
            {
                Console.Write("Deleted ID's: ");
                Queue tempQueue = (Queue)deletedIds.Clone();

                // lists all but the final deleted ID
                for (int i = 0; i < deletedIds.Count - 1; i++)
                {
                    Console.Write(tempQueue.Peek() + ", ");
                    tempQueue.Dequeue();
                }

                // adds the final deleted ID
                Console.WriteLine(tempQueue.Peek() + "\n");
            }
        }

        static void DisplayAnimals()
        {
            if (animals.Count == 0) { Console.WriteLine("\nNo animals currently in the system."); }
            else
            {
                if (animalGroups.Count != 1) { Console.WriteLine("\nThere are "
                    + animalGroups.Count + " animal types in the system:\n"); }
                else { Console.WriteLine("\nThere is 1 animal type in the system:\n"); }

                foreach (var item in animalGroups)
                {
                    Console.WriteLine("Collection of " + item.Key + "s:\n");

                    foreach (var tuple in animals)
                    {
                        int animalId = tuple.Item1;
                        string animalType = tuple.Item2;
                        string animalName = tuple.Item3;
                        int animalAge = tuple.Item4;

                        if (animalType == item.Key) { Console.WriteLine(animalName
                             + "\tAge " + animalAge + "\t ID #" + animalId);
                        }
                    }

                    Console.WriteLine();
                }
            }
        }

        static void HelpOptions()
        {
            Console.WriteLine("\nThe available commands:\n\n" +
                "/add\t\tAdd a new animal into the system.\n" +
                "/debug\t\tShows several key variable values.\n" +
                "/display\tDisplays all animals in the system.\n" +
                "/end\t\tTerminates the program immediately.\n" +
                "/help\t\tDisplays all available commands.\n" +
                "/remove\t\tRemove an animal from the system.\n");
        }

        static void InputAnimal()
        {
            // user inputs animal details
            Console.Write("\nSelect an animal to initialise: ");
            string typeInput = Console.ReadLine();
            typeInput.ToLower();

            Console.Write("Choose a name for your " + typeInput + ": ");
            string nameInput = Console.ReadLine();

            Console.Write("Input the age for your " + typeInput + ": ");
            int ageInput = int.Parse(Console.ReadLine());

            int animalId = AddAnimal(0, typeInput, nameInput, ageInput);

            Console.WriteLine("\n" + nameInput + ", the " + ageInput +
                " year old " + typeInput + ", is initialised.\n");

            // animal details ammended to data.csv
            try
            {
                using System.IO.StreamWriter file = new System.IO.StreamWriter("data.csv", true);
                file.WriteLine(animalId + "," + typeInput + "," + nameInput + "," + ageInput);
            }
            catch (Exception ex)
            {
                throw new ApplicationException("Error reading from data.csv: ", ex);
            }

            // checking deleted.csv for deleted ID's
            bool deletedAvailable = false;

            try
            {
                if (new FileInfo("deleted.csv").Length != 0)    // only needs to run if file is not empty
                {
                    string[] lines = System.IO.File.ReadAllLines("deleted.csv");
                    deletedAvailable = true;    // if file error occurs now, due to temp.csv and not deleted.csv
                    Console.WriteLine("lines.length: " + lines.Length);

                    for (int i = 0; i < lines.Length; i++)
                    {
                        if (animalId != int.Parse(lines[i]))
                        {
                            using System.IO.StreamWriter file = new System.IO.StreamWriter("temp.csv", true);
                            file.WriteLine(lines[i]);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                if (deletedAvailable == false) { throw new ApplicationException("Error reading from deleted.csv: ", ex); }
                else { throw new ApplicationException("Error writing to temp.csv: ", ex); }
            }

            File.Delete("deleted.csv");
            if (File.Exists("temp.csv")) { File.Move("temp.csv", "deleted.csv", true); }
            else { using (File.Create("deleted.csv")) {}; }     // closes file after being created
        }

        static void LoadData()
        {
            ReadDataFile(0);

            try
            {
                string[] lines = System.IO.File.ReadAllLines("deleted.csv");
                for (int i = 0; i < lines.Length; i++) { deletedIds.Enqueue(int.Parse(lines[i])); }
            }
            catch (Exception ex) { throw new ApplicationException("Error reading from deleted.csv: ", ex); }
        }

        static void ReadDataFile(int idInput)
        {
            try
            {
                string[] lines = System.IO.File.ReadAllLines("data.csv");

                for (int i = 0; i < lines.Length; i++)
                {
                    string[] fields = lines[i].Split(',');

                    int animalId = int.Parse(fields[0]);
                    string animalType = fields[1];
                    string animalName = fields[2];
                    int animalAge = int.Parse(fields[3]);

                    if(idInput == 0) { AddAnimal(animalId, animalType, animalName, animalAge); }
                    else
                    {
                        if (idInput != animalId)
                        {
                            using System.IO.StreamWriter file = new System.IO.StreamWriter("temp.csv", true);
                            file.WriteLine(animalId + "," + animalType + "," + animalName + "," + animalAge);
                        }
                    }
                }
            }
            catch (Exception ex) { throw new ApplicationException("Error writing to temp.csv: ", ex); }
        }

        static void RemoveAnimal()
        {
            bool animalRemoved = false;

            Console.Write("\nSelect the id of an animal to remove: ");
            int idInput = int.Parse(Console.ReadLine());

            foreach (var tuple in animals)
            {
                int animalId = tuple.Item1;
                string animalType = tuple.Item2;
                string animalName = tuple.Item3;
                int animalAge = tuple.Item4;

                if (idInput == animalId)
                {
                    if (animalGroups.ContainsKey(animalType)) { animalGroups[animalType] -= 1; }

                    foreach (var item in animalGroups)
                    {
                        if (item.Value == 0) { animalGroups.Remove(animalType); break; };
                    }

                    Console.WriteLine(animalName + ", the " + animalAge
                        + " year old " + animalType + ", has been removed.\n");
                    deletedIds.Enqueue(animalId);
                    animals.Remove(tuple);

                    // rewrite data to new temp.csv, using less resources than sorting for the id to remove
                    ReadDataFile(idInput);

                    // delete the file if exists, else no exception thrown
                    File.Delete("data.csv");
                    File.Move("temp.csv", "data.csv", true);

                    // adding deleted ID to deleted.csv
                    try
                    {
                        using System.IO.StreamWriter file = new System.IO.StreamWriter("deleted.csv", true);
                        file.WriteLine(idInput);
                    }
                    catch (Exception ex) { throw new ApplicationException("Error writing to deleted.csv: ", ex); }

                    animalRemoved = true;
                    break;
                }
            }

            if (animalRemoved == false) { Console.WriteLine("No animal with that corresponding ID found.\n"); }
        }

        static void Main(string[] args)
        {
            LoadData();

            Console.WriteLine("Welcome to the animal sanctuary database.\n"
                + animals.Count + " animals have been loaded into the system.\n\n"
                + "Type \"/help\" for a list of available commands.\n");

            while (true)
            {
                string commandInput;

                Console.Write("Choose a command to run: ");
                commandInput = Console.ReadLine();
                commandInput = commandInput.ToLower();

                switch (commandInput)
                {
                    case "/add":        InputAnimal();      break;
                    case "/debug":      DebugScreen();      break;
                    case "/display":    DisplayAnimals();   break;
                    case "/end":        goto ProgramEnd;
                    case "/help":       HelpOptions();      break;
                    case "/remove":     RemoveAnimal();     break;

                    default: Console.WriteLine("Command not recognised.\n"); continue;
                }
                
                /* less efficient if statement, will keep until tests done to confirm

                if      (commandInput == "/add")        { InputAnimal();    continue; }
                else if (commandInput == "/debug")      { DebugScreen();    continue; }
                else if (commandInput == "/display")    { DisplayAnimals(); continue; }
                else if (commandInput == "/end")        { break;                      }
                else if (commandInput == "/help")       { HelpOptions();    continue; }
                else if (commandInput == "/remove")     { RemoveAnimal();   continue; }

                else { Console.WriteLine("Command not recognised.\n"); } */
            }

            ProgramEnd:;    // used to break out of the switch statement above
        }
    }
}