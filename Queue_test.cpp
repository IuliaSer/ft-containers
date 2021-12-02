#include "Queue.hpp"
#include <queue>
#include <iostream>
#define RED "\x1b[31m"
#define END "\x1b[0m"
#define BLUE "\x1b[36m"
# define GREEN "\e[92m"

int main()
{
    std::queue<int> q;
    ft::queue<int> myq;
    std::cout << RED << "CHECKING FUNCTION push and front:\n" << END;
    for (int i=0; i<10; i++) q.push(i);
    for (int i=0; i<10; i++) myq.push(i);
    std::cout << myq.front() << std::endl;
    std::cout << q.front() << std::endl;

    std::cout << RED << "CHECKING FUNCTION pop and back:\n" << END;
    for (int i=0; i<5; i++) q.pop();
    for (int i=0; i<5; i++) myq.pop();
    std::cout << myq.back() << std::endl;
    std::cout << q.back() << std::endl;

    std::cout << RED << "CHECKING FUNCTION empty:\n" << END;
    std::cout << myq.empty() << std::endl;
    std::cout << q.empty() << std::endl;

    std::cout << RED << "CHECKING FUNCTION size:\n" << END;
    std::cout << myq.size() << std::endl;
    std::cout << q.size() << std::endl;
}