#include <iostream>
#include "Vector.hpp"
#include <vector>
#define RED "\x1b[31m"
#define END "\x1b[0m"
#define BLUE "\x1b[36m"
# define GREEN "\e[92m"

template <typename T>
void print_vectors(std::string message, std::string message2, ft::vector<T> &myv, std::vector<T> &v)
{
    std::cout << BLUE << message << END << std::endl;
    for (size_t i = 0; i < myv.size(); i++)
        std::cout << myv[i] << " ";
    std::cout << std::endl;
    std::cout << BLUE << message2 << END << std::endl;
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
        std::cout << std::endl;
}

template <typename T>
void print_vectors(std::string message, std::string message2, ft::vector<T> &myv, ft::vector<T> &myv2)
{
    std::cout << BLUE << message << END << std::endl;
    for (size_t i = 0; i < myv.size(); i++)
        std::cout << myv[i] << " ";
        std::cout << std::endl;
    std::cout << BLUE << message2 << END << std::endl;
    for (size_t i = 0; i < myv2.size(); i++)
        std::cout << myv2[i] << " ";
        std::cout << std::endl;
}

template <typename T>
void print_vectors(std::string message, std::string message2, std::vector<T> &v, std::vector<T> &v2)
{
    std::cout << BLUE << message << END << std::endl;
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
        std::cout << std::endl;
    std::cout << BLUE << message2 << END << std::endl;
    for (size_t i = 0; i < v2.size(); i++)
        std::cout << v2[i] << " ";
        std::cout << std::endl;
}

template <typename T>
void print_variables(ft::vector<T> &myv, std::vector<T> &v)
{
    std::cout << GREEN << "My vector size: " <<  END << myv.size() << "\n";
    std::cout << GREEN << "My vector capacity: " << END <<  myv.capacity() << "\n";
    std::cout << GREEN << "Original vector size: " << END << v.size() << "\n";
    std::cout << GREEN << "Original vector capacity: " << END << v.capacity() << "\n";
}
