using System;

namespace GradeTracker
{
    class Program
    {
        static void Main(string[] args)
        {
            int studentCount;

            Console.Write("How many students are in your class: ");

            while (!int.TryParse(Console.ReadLine(), out studentCount))
            {
                Console.WriteLine("Integer expected. Please try again.\n");
                Console.Write("How many students are in your class: ");
            }

            var studentNames = new string[studentCount];
            var studentMarks = new int[studentCount];
            var studentGrades = new string[studentCount];

            for (int i = 0; i < studentCount; i++)
            {
                Console.Write("\nName of Student " + (i + 1) + ": ");
                studentNames[i] = Console.ReadLine();

                Console.Write(studentNames[i] + "'s Mark: ");

                while (!int.TryParse(Console.ReadLine(), out studentMarks[i])
                    || studentMarks[i] > 100 || studentMarks[i] < 0)
                {
                    Console.WriteLine("Integer between 100 and 0 expected. Please try again.\n");
                    Console.Write(studentNames[i] + "'s Mark: ");
                }

                studentGrades[i] = studentMarks[i] switch
                {
                    int n when n >= 70 => "1st",
                    int n when n >= 60 => "2:1",
                    int n when n >= 50 => "2:2",
                    int n when n >= 40 => "3rd",
                    _ => "Fail",
                };

                Console.WriteLine(studentNames[i] + "'s Grade: " + studentGrades[i]);
            }

            Console.WriteLine("\nGrade Results:\n");

            for (int i = 0; i < studentCount; i++)
            {
                Console.WriteLine("Name: {0}\t Mark: {1}\t Grade: {2}",
                    studentNames[i], studentMarks[i], studentGrades[i]);
            }
        }
    }
}

