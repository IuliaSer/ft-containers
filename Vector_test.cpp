#include "Vector.hpp"
#include <vector>
#include <iostream>
#define RED "\x1b[31m"
#define END "\x1b[0m"
#define BLUE "\x1b[36m"
# define GREEN "\e[92m"
#include <unistd.h>
#include "Display.cpp"

void constructors_check()
{
    //___________________fill_constructor_____________//
    ft::vector<int> myv(5, 100);
    std::vector<int> v(5, 100);
    print_vectors("My vector fill constructor: ", "Original vector fill constructor: ", myv, v);
    print_variables(myv, v);
    //__________________range_constructor_____________//
    ft::vector<int>::iterator it = myv.begin();
    ft::vector<int>::iterator ite = myv.end();
    std::vector<int>::iterator it2 = v.begin();
    std::vector<int>::iterator it2e = v.end();
    ft::vector<int> myv2(++it, --ite);
    std::vector<int> v2(++it2, --it2e);
    print_vectors("My vector range constructor: ", "Original vector range constructor: ", myv2, v2);
    print_variables(myv, v);
    // // //__________________copy_constructor_____________//
    ft::vector<int> myv3(myv);
    std::vector<int> v3(v);
    print_vectors("My vector copy constructor: ", "Original vector copy constructor: ", myv3, v3);
    print_variables(myv3, v3);
    //_________________equality_operator____________//
    ft::vector<int> myv4(5, 55);
    std::vector<int> v4(5, 55);
    myv4 = myv3;
    v4 = v3;
    print_vectors("My vector equality_operator: ", "Original vector equality_operator: ", myv4, v4);
    print_variables(myv4, v4);
}

void push_back_check()
{
    std::cout << RED << "CHECKING FUNCTION PUSH_BACK:\n" << END;
    std::vector<int> v;
    ft::vector<int> myv;
    
    v.push_back(100);
    myv.push_back(100);
    print_vectors("My vector before push_back: ", "Original vector before push_back: ", myv, v);
    for (int i=0; i<10; i++) v.push_back(i);
    for (int i=0; i<10; i++) myv.push_back(i);
    print_variables(myv, v);
    print_vectors("My vector after push_back: ", "Original vector after push_back: ", myv, v);
    print_variables(myv, v);
}

void pop_back_check()
{
    std::cout << RED << "CHECKING FUNCTION POP_BACK:\n" << END;
    std::vector<int> v;
    ft::vector<int> myv;
    
    for (int i=0; i<10; i++) v.push_back(i);
    for (int i=0; i<10; i++) myv.push_back(i);
    print_vectors("My vector before pop_back: ", "Original vector before pop_back: ", myv, v);
    for (int i=0; i<5; i++) v.pop_back();
    for (int i=0; i<5; i++) myv.pop_back();
    print_variables(myv, v);
    print_vectors("My vector after pop_back: ", "Original vector after pop_back: ", myv, v);
    print_variables(myv, v);
}

void clear_check()
{
    std::cout << RED << "CHECKING FUNCTION CLEAR:\n" << END;
    std::vector<int> v;
    ft::vector<int> myv;
    
    for (int i=0; i<10; i++) v.push_back(i);
    for (int i=0; i<10; i++) myv.push_back(i);
    print_vectors("My vector before clear: ", "Original vector before clear: ", myv, v);
    v.clear();
    myv.clear();
    print_variables(myv, v);
    print_vectors("My vector after clear: ", "Original vector after clear ", myv, v);
    print_variables(myv, v);
}

void insert_check()
{
    std::cout << RED << "CHECKING FUNCTION INSERT:\n" << END;
    std::cout << RED << "First version: iterator insert (iterator position, const value_type& val)\n" << END;
    std::vector<int> v;
    ft::vector<int> myv;
    
    for (int i=0; i<10; i++) v.push_back(i);
    for (int i=0; i<10; i++) myv.push_back(i);

    std::vector<int> v2;
    ft::vector<int> myv2;
    
    for (int i=0; i<10; i++) v2.push_back(i);
    for (int i=0; i<10; i++) myv2.push_back(i);
    print_vectors("My vector before insert: ", "Original vector before insert: ", myv, v);
    print_variables(myv, v);
    ft::vector<int>::iterator it = myv.begin();
    std::vector<int>::iterator it2 = v.begin();
    std::cout << BLUE << "Insert in the beginnig\n" << END;
    it = myv.insert(it, 8000);
    it2 = v.insert(it2, 8000);
    print_vectors("My vector after insert: ", "Original vector after insert: ", myv, v);
    print_variables(myv, v);
    std::cout << BLUE << "Iterator position after insert for my_vector" << END << std::endl;
    std::cout << *it << std::endl;
    std::cout << BLUE << "Iterator position after insert for original_vector" << END << std::endl;
    std::cout << *it2 << std::endl;

    // //-----------------pereolakaciya pamyati chtobi proverit insert----------------
    myv.resize(7, 100);
    v.resize(7, 100);

    std::cout << RED << "Single element insert: \n" << END;
    print_vectors("My vector before insert: ", "Original vector before insert: ", myv, v);
    print_variables(myv, v);
    ft::vector<int>::iterator it3 = myv.begin();
    std::vector<int>::iterator it4 = v.begin();
    std::cout << BLUE << "Insert in the middle\n" << END;
    it3 = myv.insert(it3 + 2, 9000);
    it4 = v.insert(it4 + 2, 9000);
    print_vectors("My vector after insert: ", "Original vector after insert: ", myv, v);
    std::cout << BLUE << "Iterator position after insert for my_vector" << END << std::endl;
    std::cout << *it3 << std::endl;
    std::cout << BLUE << "Iterator position after insert for my_vector " << END << std::endl;
    std::cout << *it4 << std::endl;
    print_variables(myv, v);

    // //___________________________Fill version____________________________/
    std::cout << RED << "Fill insert: void insert (iterator position, size_type n, const value_type& val)\n" << END;
    for (int i=0; i<5; i++) v.push_back(i);
    for (int i=0; i<5; i++) myv.push_back(i);
    print_vectors("My vector before insert: ", "Original vector before insert: ", myv, v);
    ft::vector<int>::iterator it5 = myv.begin();
    std::vector<int>::iterator it6 = v.begin();
    std::cout << BLUE << "Insert in the beginnig\n" << END;
    myv.insert(it5, 4, 8000);
    v.insert(it6, 4, 8000);
    print_vectors("My vector after insert: ", "Original vector after insert: ", myv, v);
    print_variables(myv, v);

    // //_______________________Range version_______________________________//

    std::cout << RED << "Range insert: void insert (iterator position, InputIterator first, InputIterator last)\n" << END;
    ft::vector<int>::iterator it7 = myv.begin();
    std::vector<int>::iterator it8 = v.begin();
    ft::vector<int>::iterator it9 = myv2.begin();
    ft::vector<int>::iterator it10 = myv2.end();
    std::vector<int>::iterator it12 = v2.end();
    std::cout << BLUE << "Insert in the end\n" << END;
    print_vectors("My vector before insert: ", "Original vector before insert: ", myv, v);
    myv2.insert(it10, it7, it7 + 2);
    v2.insert(it12, it8, it8 + 2);
    print_vectors("My vector after insert: ", "Original vector after insert: ", myv, v);
    print_variables(myv, v);
}

void swap_check()
{
    std::cout << RED << "CHECKING FUNCTION SWAP:\n" << END;
    ft::vector<int> myv;
    ft::vector<int> myv2;
    std::vector<int> v;
    std::vector<int> v2;
    for (int i=0; i<5; i++) myv.push_back(i);
    for (int i=0; i<5; i++) myv2.push_back(10);
    for (int i=0; i<5; i++) v.push_back(i);
    for (int i=0; i<5; i++) v2.push_back(10);
    print_vectors("My vector before swap: ", "My vector2 before swap: ", myv, myv2);
    myv.swap(myv2);
    print_vectors("My vector after swap: ", "My vector2 after swap: ", myv, myv2);
    print_vectors("Original vector before swap: ", "Original vector2 before swap: ", v, v2);
    v.swap(v2);
    print_vectors("Original vector after swap: ", "Original vector2 after swap: ", v, v2);
}

void resize_check()
{
    std::cout << RED << "CHECKING FUNCTION RESIZE:\n" << END;
    ft::vector<int> myv;
    std::vector<int> v;
    for (int i=0; i<10; i++) myv.push_back(i);
    for (int i=0; i<10; i++) v.push_back(i);
    print_vectors("My vector before resize: ", "Original vector before resize: ", myv, v);
    print_variables(myv, v);
    myv.resize(5, 100);
    v.resize(5, 100);
    print_vectors("My vector after resize: ", "Original vector after resize: ", myv, v);
    print_variables(myv, v);
    v.resize(15, 100);
    myv.resize(15, 100);
    print_vectors("My vector after insert: ", "Original vector after insert: ", myv, v);
    print_variables(myv, v);
}

void assign_check()
{
    std::cout << RED << "CHECKING FUNCTION ASSIGN:\n" << END;
    std::cout << RED << "First version: void assign (size_type n, const value_type& val):\n" << END;
    ft::vector<int> myv;
    std::vector<int> v;
    for (int i=0; i<5; i++) myv.push_back(i);
    for (int i=0; i<5; i++) v.push_back(i);
    print_vectors("My vector before assigment: ", "Original vector before assigment: ", myv, v);
    print_variables(myv, v);
    myv.assign((size_t)10, (int)20);
    v.assign((size_t)10, (int)20);
    print_vectors("My vector after assigment: ", "Original vector after assigment: ", myv, v);
    print_variables(myv, v);
    
    std::cout << RED << "Second version: void assign (InputIterator first, InputIterator last):\n" << END;
    ft::vector<int> myv2;
    std::vector<int> v2;
    for (int i=0; i<6; i++) myv2.push_back(i);
    for (int i=0; i<6; i++) v2.push_back(i);
    print_vectors("My vector before assigment: ", "Original vector before assigment: ", myv2, v2);
    print_variables(myv2, v2);
    std::vector<int>::iterator it = v2.begin() + 2;
    std::vector<int>::iterator it2 = v2.end() - 2;
    ft::VectorIterator<int> mit = myv2.begin() + 2;
    ft::VectorIterator<int> mit2 = myv2.end() - 2;
    myv2.assign((ft::VectorIterator<int>)mit, (ft::VectorIterator<int>)mit2);
    v2.assign (it, it2);
    print_vectors("My vector after assigment: ", "Original vector after assigment: ", myv2, v2);
    print_variables(myv2, v2);
}

void capacity_functions_check()
{
    std::cout << RED << "CHECKING CAPACITY FUNCTIONS:\n" << END;
    std::vector<int> v;
    ft::vector<int> myv;
    
    for (int i=0; i<10; i++) v.push_back(i);
    for (int i=0; i<10; i++) myv.push_back(i);
    std::cout << BLUE << "Original vector: " << END << std::endl;
    std::cout << "size: " << v.size() << "\n";
    std::cout << "capacity: " << v.capacity() << "\n";
    std::cout << "max_size: " << v.max_size() << "\n";
    std::cout << "empty? " << v.empty() << "\n";

    std::cout << BLUE << "My vector: " << END << std::endl;
    std::cout << "size: " << myv.size() << "\n";
    std::cout << "capacity: " << myv.capacity() << "\n";
    std::cout << "max_size: " << myv.max_size() << "\n";
    std::cout << "empty? " << myv.empty() << "\n";
}

void erase_check()
{
    std::cout << RED << "CHECKING FUNCTION ERASE:\n" << END;
    std::cout << RED << "First version: iterator erase (iterator position)\n" << END;
    ft::vector<int> myv;
    std::vector<int> v;
    for (int i=0; i<10; i++) myv.push_back(i);
    for (int i=0; i<10; i++) v.push_back(i);
    print_vectors("My vector before erase: ", "Original vector before erase: ", myv, v);
    print_variables(myv, v);
    ft::vector<int>::iterator it = myv.begin();
    std::vector<int>::iterator it2 = v.begin();
    std::cout << BLUE << "Erase in the beginnig\n" << END;
    it = myv.erase(it);
    it2 = v.erase(it2);
    print_vectors("My vector after erase: ", "Original vector after erase: ", myv, v);
    print_variables(myv, v);

    std::cout << RED << "Second version: iterator erase (iterator first, iterator last)\n" << END;
    ft::vector<int>::iterator it3 = myv.end();
    std::vector<int>::iterator it4 = v.end();
    std::cout << BLUE << "Erase in the beginnig\n" << END;
    it3 = myv.erase(it, it3 - 3);
    it4 = v.erase(it2, it4 - 3);
    print_vectors("My vector after erase: ", "Original vector after erase: ", myv, v);
    print_variables(myv, v);
}



void relational_operators_check()
{
    std::vector<int> v;
    std::vector<int> v2;
    
    std::cout << RED << "CHECKING RELATIONAL OPERATORS:\n" << END;
    for (int i=0; i<5; i++) v.push_back(5);
    for (int i=0; i<10; i++) v2.push_back(5);
    //_______________________checking original__________________//
    print_vectors("Original vector: ", "Original vector2: ", v, v2);
    if (v != v2)
        std::cout << "Not equal\n";
    if (v == v2)
        std::cout << "Equal\n";
    if (v < v2)
        std::cout << "Less\n";
    if (v > v2)
        std::cout << "More\n";
    if (v <= v2)
        std::cout << "Less and equal\n";
    if (v >= v2)
        std::cout << "More and equal\n";
    //_______________________checking mine__________________//
    ft::vector<int> myv;
    ft::vector<int> myv2;

    for (int i=0; i<5; i++) myv.push_back(5);
    for (int i=0; i<10; i++) myv2.push_back(5);
    print_vectors("My vector: ", "My vector2: ", myv, myv2);
    if (myv != myv2)
        std::cout << "Not equal\n";
    if (myv == myv2)
        std::cout << "Equal\n";
    if (myv < myv2)
        std::cout << "Less\n";
    if (myv > myv2)
        std::cout << "More\n";
    if (myv <= myv2)
        std::cout << "Less and equal\n";
    if (myv >= myv2)
        std::cout << "More and equal\n";
}

int main ()
{
    constructors_check();
    capacity_functions_check();
    push_back_check();
    pop_back_check();
    clear_check();
    insert_check();
    assign_check();
    erase_check();
    swap_check();
    relational_operators_check();
    //sleep(100);
    
}