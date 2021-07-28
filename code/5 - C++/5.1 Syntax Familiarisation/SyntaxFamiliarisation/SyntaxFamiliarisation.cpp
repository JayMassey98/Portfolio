#include <iostream> // imports cout function
#include <sstream> // imports getline function
#include <vector> // imports vector function
#include <math.h> // imports round function

using namespace std;

template <class T> // template added for the following tryparse function

bool try_parse(string input, T& var) // checks input type without crashing if invalid
{
    static const string ws(" \t\f\v\n\r");  // non-user inputs, characters used in formatting

    size_t pos = input.find_last_not_of(ws);

    if (pos != string::npos)
        input.erase(pos + 1);
    else input.clear();

    stringstream buffer(input);

    return buffer >> var && buffer.eof();
}

int main()
{
    int n;
    string input;
    bool inputValid = false;
    bool nameKnown = false;

    vector<int> studentCount;
    vector<string> studentNames;
    vector<int> studentMarks;
    vector<string> studentGrades;

    while (inputValid == false)
    {
        cout << "How many students are in your class: ";
        getline(cin, input);

        if (try_parse(input, n)) { inputValid = true; }
        else { cout << "Integer expected. Please try again.\n" << endl; }
    }

    inputValid = false;

    int students = stoi(input); // converts the now validated number input into an integer

    studentCount.resize(students);
    studentNames.resize(students);
    studentMarks.resize(students);
    studentGrades.resize(students);

    for (std::size_t i = 0; i < studentCount.size(); i++) // std::size_t prevents signed/unsigned mismatch
    {
        studentCount[i] = i + 1;

        while (inputValid == false)
        {
            while (nameKnown == false)
            {
                cout << "\nName of Student " << studentCount[i] << ": ";
                cin >> studentNames[i];
                nameKnown = true;

                cin.ignore(); // Needed to reset for getline() function.
            }

            cout << studentNames[i] << "'s Mark: ";
            getline(cin, input);

            if (try_parse(input, n) && stoi(input) <= 100 && stoi(input) >= 0)
            {
                studentMarks[i] = stoi(input);
                inputValid = true;
            }
            else
            {
                cout << "Integer between 0 and 100 expected. Please try again.\n" << endl;
            }
        }

        nameKnown = false;
        inputValid = false;

        if (studentMarks[i] >= 70)      { studentGrades[i] = "1st"; }
        else if (studentMarks[i] >= 60) { studentGrades[i] = "2:1"; }
        else if (studentMarks[i] >= 50) { studentGrades[i] = "2:2"; }
        else if (studentMarks[i] >= 40) { studentGrades[i] = "3rd"; }
        else                            { studentGrades[i] = "Fail"; }

        cout << studentNames[i] << "'s Grade: " << studentGrades[i] << "\n";
    }

    cout << "\nGrade Results:\n\n";

    for (std::size_t i = 0; i < studentCount.size(); i++) // std::size_t prevents unsigned mismatch
    {
        cout << "Name: " << studentNames[i] << "\tMark: " <<
            studentMarks[i] << "\tGrade: " << studentGrades[i] << "\n";
    }

    return 0;
}