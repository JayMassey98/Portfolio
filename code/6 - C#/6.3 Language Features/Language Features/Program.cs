using System;
using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading;

namespace Language_Features
{
    class Program
    {
        // Concurrency

        static readonly ConcurrentDictionary<int, int> items = new ConcurrentDictionary<int, int>();

        static void Main(string[] args)
        {
            Thread thread1 = new Thread(new ThreadStart(AddItem));
            Thread thread2 = new Thread(new ThreadStart(AddItem));
            Thread thread3 = new Thread(new ThreadStart(AddItem));

            thread1.Start();
            thread2.Start();
            thread3.Start();

            // Lists

            Console.WriteLine("List Example:\n");

            List<String> customers = new List<string>
            {
                "Alex",
                "Brian",
                "Chad"
            };

            customers.Add("Dorothy");
            customers.Add("Ethan");

            Console.WriteLine("\nNumber of Customers: " + customers.Count);

            for (int i = 0; i < customers.Count - 1; i++)
            {
                Console.Write(customers[i] + ", ");
            }

            Console.Write(customers[^1]); // Prints final item in list "customers".

            // Dictionaries

            Console.WriteLine("\n\nDictionary Example:\n");

            Dictionary<String, String> config = new Dictionary<string, string>
            {
                { "title", "Jay's Portfolio" }
            };

            config.Add("example", "Dictionary");

            Console.WriteLine(config["title"]);
            Console.WriteLine(config["example"]);

            // ArrayLists

            Console.WriteLine("\nArrayList Example:\n");

            ArrayList list = new ArrayList
            {
                "Jay's Portfolio"
            };
            list.Add("ArrayList");
            String s1a = (String)list[0];
            String s1b = (String)list[1];

            Console.WriteLine(s1a + "\n" + s1b);

            // Hashtables

            Console.WriteLine("\nHashtable Example:\n");

            Hashtable table = new Hashtable
            {
                { "title", "Jay's Portfolio" }
            };

            table.Add("example", "Hashtable");

            var s2a = (String)table["title"];
            Console.WriteLine(s2a);

            var s2b = (String)table["example"];
            Console.WriteLine(s2b);

            // Tuples

            Console.WriteLine("\nTuple Example:\n");

            var tuple1 = Tuple.Create(1, "Jay's Portfolio", true);
            Tuple<int, String, bool> tuple2 = new Tuple<int, string, bool>(1, "Tuples", true);

            Console.WriteLine(tuple1.Item2);
            Console.WriteLine(tuple2.Item2);

            // BitArrays

            Console.WriteLine("\nBitArray Example:\n");

            bool[] preload = new bool[3] { true, false, true };

            BitArray booleanValues = new BitArray(preload);

            foreach (var item in booleanValues)
            {
                Console.WriteLine(item);
            }

            booleanValues[0] = false;
            booleanValues[1] = true;
            booleanValues.Set(2, false);

            Console.WriteLine();

            foreach (var item in booleanValues)
            {
                Console.WriteLine(item);
            }

            // Stacks

            Console.WriteLine("\nStack Example:\n");

            Stack<String> stackExample = new Stack<string>();

            stackExample.Push("Position #1");
            stackExample.Push("Position #2");
            stackExample.Push("Position #3");

            foreach (var pancake in stackExample)
            {
                Console.WriteLine(pancake);
            }

            Console.WriteLine();
            Console.WriteLine(stackExample.Pop());
            Console.WriteLine(stackExample.Peek());
            Console.WriteLine(stackExample.Peek());

            // Queues

            Console.WriteLine("\nQueue Example:\n");

            Queue<int> queueExample = new Queue<int>();

            queueExample.Enqueue(1);
            queueExample.Enqueue(2);
            queueExample.Enqueue(3);

            foreach (var enqueued in queueExample)
            {
                Console.WriteLine("Position #" + enqueued);
            }

            Console.WriteLine();
            Console.WriteLine("Position #" + queueExample.Dequeue());
            Console.WriteLine("Position #" + queueExample.Peek());
            Console.WriteLine("Position #" + queueExample.Peek());

            // HashSet

            Console.WriteLine("\nHashSet Example:\n");

            var hashExample1 = new HashSet<String>
            {
                "Jay's Portfolio"
            };

            hashExample1.Add("Jay's Portfolio");

            String[] s3 = new String[] { "Jay's Portfolio" };

            Console.WriteLine(hashExample1.Count + " Hash Count");
            Console.WriteLine("HashSet Match: " + hashExample1.Overlaps(s3));

            var hashExample2 = new HashSet<String>
            {
                "HashSet Example"
            };

            hashExample2.Add("HashSet Example");

            Console.WriteLine("\n" + hashExample2.Count + " Hash Count");
            Console.WriteLine("HashSet Match: " + hashExample2.Overlaps(s3));

        }

        // Concurrency

        static void AddItem()
        {
            var result = items.TryAdd(1, 2);
            Console.WriteLine("Concurrent Example: " + result);
        }
    }
}
