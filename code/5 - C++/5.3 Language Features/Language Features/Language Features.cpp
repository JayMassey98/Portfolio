// imports functions required for coded examples

#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <tuple>
#include <bitset>
#include <stack>
#include <queue>
#include <thread>

void lists()
{
    std::cout << "List Example:\n";

    std::list <std::string> customers = { "Alex", "Brian", "Chad" };

    customers.push_back("Dorothy");
    customers.push_back("Ethan");

    std::cout << "\nNumber of Customers: " << customers.size() << std::endl;

    //    for (auto const& i : customers)   // reference used instead of a value to avoid copying items in list
    //    {
    //            std::cout << i << "\n";   // prints all items in "customers" on seperate lines, but with no comma
    //    }                                 // better code in some uses, but produces a less desirable output here

    for (std::list <std::string> ::const_iterator i = customers.begin(); i != std::prev(customers.end()); i++)
    {
        std::cout << *i << ", ";
    }

    std::cout << customers.back() << std::endl;  // prints final item in list "customers" with no comma after
}

void maps()
{
    std::cout << "\nMap Example:\n\n";

    std::map<std::string, std::string> config = { { "title", "Jay's Portfolio" } };
    config.insert({ "example", "Map" });

    for (auto const& i : config) { std::cout << i.first << " => " << i.second << "\n"; }
}

void vectors()
{
    std::cout << "\nVector Example:\n\n";

    std::vector<std::string> vector_example;

    vector_example.push_back("Vector");
    vector_example.push_back("Jay's Portfolio");

    std::sort(vector_example.begin(), vector_example.end());    // will place "Jay's Portfolio" to the front

    for (auto const& i : vector_example) { std::cout << i << "\n"; }
}

void unordered_maps()
{
    std::cout << "\nUnordered Map Example:\n\n";

    std::unordered_map<std::string, std::string> u_map_example;

    u_map_example["title", "Jay's Portfolio"] = 1;
    u_map_example["example", "Unordered Map"] = 2;

    for (auto const& x : u_map_example) { std::cout << x.first << std::endl; }

}

void tuples()
{

    std::cout << "\nTuple Example:\n\n";

    std::tuple<int, std::string, bool> tuple_example_1 = std::make_tuple(1, "Jay's Portfolio", true);
    std::tuple<int, std::string, bool, bool> tuple_example_2 = std::make_tuple(2, "Tuples", false, false);

    std::cout << std::get<1>(tuple_example_1) << std::endl;
    std::cout << std::get<1>(tuple_example_2) << std::endl;
}

void bits()
{
    std::cout << "\nBits Example:\n\n";

    std::bitset<8> bits_example_1;                                                  // length of bits set to 8
    int bits_as_int_1 = static_cast <int>(bits_example_1.to_ulong());               // converts bits to int type
    std::cout << bits_as_int_1 << " in binary: \t" << bits_example_1 << std::endl;  // 0 is equal to 00000000

    std::bitset<8> bits_example_2(std::string("1010"));                             // length of bits set to 8
    int bits_as_int_2 = static_cast <int>(bits_example_2.to_ulong());               // converts bits to int type
    std::cout << bits_as_int_2 << " in binary: \t" << bits_example_2 << std::endl;  // 10 is equal to 00001010

    std::bitset<8> bits_example_3(20);                                              // length of bits set to 8
    int bits_as_int_3 = static_cast <int>(bits_example_3.to_ulong());               // converts bits to int type
    std::cout << bits_as_int_3 << " in binary: \t" << bits_example_3 << std::endl;  // 20 is equal to 00010100

    int number_of_1 = bits_example_3.count();                                       // total number of set bits
    int number_of_0 = bits_example_3.size() - number_of_1;                          // the number of unset bits

    std::cout << "\n" << bits_example_3 << ": " << number_of_1 << " 1's and "
        << number_of_0 << " 0's\n\n";

    std::cout << "All bits set: \t" << bits_example_1.set() << std::endl;
    std::cout << "Set bit 4 to 0: " << bits_example_1.set(4, 0) << std::endl;
    std::cout << "Set bit 4: \t" << bits_example_1.set(4) << std::endl;
    std::cout << "Reset bit 2: \t" << bits_example_1.reset(2) << std::endl;
    std::cout << "Reset all bits: " << bits_example_1.reset() << std::endl;
    std::cout << "Flip bit 2: \t" << bits_example_1.flip(2) << std::endl;
    std::cout << "Flip all bits: \t" << bits_example_1.flip() << std::endl;
}

void stacks()
{
    std::cout << "\nStacks Example:\n\n";

    std::stack<int> stack_example;

    stack_example.push(3);
    stack_example.push(4);
    stack_example.push(2);
    stack_example.push(5);
    stack_example.push(1);

    while (!stack_example.empty())
    {
        std::cout << stack_example.top() << " ";
        stack_example.pop();
    }
}

void show_queue(std::queue<int> queue)
{
    std::queue<int> q = queue;

    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }

    std::cout << std::endl;
}

void queues()
{
    std::cout << "\n\nStacks Example:\n\n";

    std::queue<int> queue_example;

    queue_example.push(3);
    queue_example.push(4);
    queue_example.push(2);
    queue_example.push(5);
    queue_example.push(1);

    show_queue(queue_example);

    std::cout << "\nQueue Size:  \t" << queue_example.size();
    std::cout << "\nQueue Front: \t" << queue_example.front();
    std::cout << "\nQueue Back:  \t" << queue_example.back();
    std::cout << "\nQueue Popped:\t";

    queue_example.pop();
    show_queue(queue_example);
}

void thread_point(int x)
{
    for (int i = 0; i < x; i++) { std::cout << "Thread " << i << " using function pointer as callable\n"; }
    std::cout << std::endl;
}

class thread_obj {
public:

    void operator()(int x)
    {
        for (int i = 0; i < x; i++) { std::cout << "Thread " << i << " using function object as callable\n"; }
        std::cout << std::endl;
    }
};

void multithreads()
{
    std::cout << "\nMultithreads Example:\n";
    std::cout << "\nThreads 0, 1 and 2 operating independently\n\n";

    auto thread_lamb = [](int x)                    // define a lambda expression
    {
        for (int i = 0; i < x; i++) { std::cout << "Thread " << i << " using lambda expression as callable\n"; }
        std::cout << std::endl;
    };

    std::thread thread_example_1(thread_point, 3);  // thread launched by using function pointer as callable
    std::thread thread_example_2(thread_obj(), 3);  // thread launched by using function object as callable
    std::thread thread_example_3(thread_lamb, 3);   // thread launched by using lambda expression as callable

    thread_example_1.join();                        // wait for thread t1 to finish
    thread_example_2.join();                        // wait for thread t2 to finish
    thread_example_3.join();                        // wait for thread t3 to finish

    std::cout << "All operating threads executed successfully\n";
}

int main()
{
    lists();
    maps();
    vectors();
    unordered_maps();
    tuples();
    bits();
    stacks();
    queues();
    multithreads();

    return 0;
}