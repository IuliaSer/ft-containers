#include "Stack.hpp"
#include <stack>
#include <iostream>
#define RED "\x1b[31m"
#define END "\x1b[0m"
#define BLUE "\x1b[36m"
# define GREEN "\e[92m"

int main()
{
    //ft::list<int> myl;
    std::stack<int> s;
    ft::stack<int> mys;
    std::cout << RED << "CHECKING FUNCTION push:\n" << END;
    for (int i=0; i<10; i++) s.push(i);
    for (int i=0; i<10; i++) mys.push(i);
    std::cout << mys.top() << std::endl;
    std::cout << s.top() << std::endl;

    std::cout << RED << "CHECKING FUNCTION pop and top:\n" << END;
    for (int i=0; i<5; i++) s.pop();
    for (int i=0; i<5; i++) mys.pop();
    std::cout << mys.top() << std::endl;
    std::cout << s.top() << std::endl;

    std::cout << RED << "CHECKING FUNCTION empty:\n" << END;
    std::cout << mys.empty() << std::endl;
    std::cout << s.empty() << std::endl;

    std::cout << RED << "CHECKING FUNCTION size:\n" << END;
    std::cout << mys.size() << std::endl;
    std::cout << s.size() << std::endl;
}