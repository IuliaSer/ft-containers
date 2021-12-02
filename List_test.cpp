#include "List.hpp"
#include <list>
#include <iostream>
#define RED "\x1b[31m"
#define END "\x1b[0m"
#define BLUE "\x1b[36m"
# define GREEN "\e[92m"
#include <unistd.h>

template <typename T>
void print_lists(std::string message, std::string message2, ft::list<T> &myl, std::list<T> &l)
{
    std::cout << BLUE << message << END << std::endl;
    ft::list<int>::iterator it = myl.begin();
    ft::list<int>::iterator ite = myl.end();
    while (it != ite)
    {
         std::cout << *it << " ";
         it++;
    }
    std::cout << std::endl;
    std::cout << BLUE << message2 << END << std::endl;
    std::list<int>::iterator it2 = l.begin();
    std::list<int>::iterator it2e = l.end();
    while (it2 != it2e)
    {
         std::cout << *it2 << " ";
         it2++;
    }
    std::cout << std::endl;
}

template <typename T>
void print_lists(std::string message, std::string message2, ft::list<T> &myl, ft::list<T> &myl2)
{
    std::cout << BLUE << message << END << std::endl;
    ft::list<int>::iterator it = myl.begin();
    ft::list<int>::iterator ite = myl.end();
    while (it != ite)
    {
         std::cout << *it << " ";
         it++;
    }
    std::cout << std::endl;
    std::cout << BLUE << message2 << END << std::endl;
    ft::list<int>::iterator it2 = myl2.begin();
    ft::list<int>::iterator it2e = myl2.end();
    while (it2 != it2e)
    {
         std::cout << *it2 << " ";
         it2++;
    }
    std::cout << std::endl;
}

template <typename T>
void print_lists(std::string message, std::string message2, std::list<T> &l, std::list<T> &l2)
{
    std::cout << BLUE << message << END << std::endl;
    std::list<int>::iterator it = l.begin();
    std::list<int>::iterator ite = l.end();
    while (it != ite)
    {
         std::cout << *it << " ";
         it++;
    }
    std::cout << std::endl;
    std::cout << BLUE << message2 << END << std::endl;
    std::list<int>::iterator it2 = l2.begin();
    std::list<int>::iterator it2e = l2.end();
    while (it2 != it2e)
    {
         std::cout << *it2 << " ";
         it2++;
    }
    std::cout << std::endl;
}

void constructors_check()
{
    //___________________fill_constructor_____________//
    ft::list<int> myl(5, 100);
    std::list<int> l(5, 100);
    print_lists("My list fill constructor: ", "Original list fill constructor: ", myl, l);
    //__________________range_constructor_____________//
    ft::list<int>::iterator it = myl.begin();
    ft::list<int>::iterator ite = myl.end();
    std::list<int>::iterator it2 = l.begin();
    std::list<int>::iterator it2e = l.end();
    ft::list<int> myl2(++it, --ite);
    std::list<int> l2(++it2, --it2e);
    print_lists("My list range constructor: ", "Original list range constructor: ", myl2, l2);
    //__________________copy_constructor_____________//
    ft::list<int> myl3(myl);
    std::list<int> l3(l);
    print_lists("My list copy constructor: ", "Original list copy constructor: ", myl3, l3);
    //_________________equality_operator____________//
    ft::list<int> myl4(5, 55);
    std::list<int> l4(5, 55);
    myl4 = myl3;
    l4 = l3;
    print_lists("My list equality_operator: ", "Original list equality_operator: ", myl4, l4);
}


void push_back_check()
{
    std::cout << RED << "CHECKING FUNCTION PUSH_BACK:\n" << END;
    std::list<int> l;
    ft::list<int> myl;
    
    l.push_back(100);
    myl.push_back(100);
    print_lists("My list before push_back: ", "Original list before push_back: ", myl, l);
    for (int i=0; i<10; i++) l.push_back(i);
    for (int i=0; i<10; i++) myl.push_back(i);
    print_lists("My list after push_back: ", "Original list after push_back: ", myl, l);
}

void pop_back_check()
{
    std::cout << RED << "CHECKING FUNCTION POP_BACK:\n" << END;
    std::list<int> l(10, 100);
    ft::list<int> myl(10, 100);
    
    print_lists("My list before pop_back: ", "Original list before pop_back: ", myl, l);
    for (int i=0; i<5; i++) l.pop_back();
    for (int i=0; i<5; i++) myl.pop_back();
    print_lists("My list after pop_back: ", "Original list after pop_back: ", myl, l);
}

void push_front_check()
{
    std::cout << RED << "CHECKING FUNCTION PUSH_FRONT:\n" << END;
    std::list<int> l;
    ft::list<int> myl;
    
    l.push_front(100);
    myl.push_front(100);
    print_lists("My list before push_front: ", "Original list before push_front: ", myl, l);
    for (int i=0; i<10; i++) l.push_front(i);
    for (int i=0; i<10; i++) myl.push_front(i);
    print_lists("My list after push_front: ", "Original list after push_front: ", myl, l);
}

void pop_front_check()
{
    std::cout << RED << "CHECKING FUNCTION POP_FRONT:\n" << END;
    std::list<int> l(10, 100);
    ft::list<int> myl(10, 100);
    
    print_lists("My list before pop_front: ", "Original list before pop_front: ", myl, l);
    for (int i=0; i<5; i++) l.pop_front();
    for (int i=0; i<5; i++) myl.pop_front();
    print_lists("My list after pop_front: ", "Original list after pop_front: ", myl, l);
}

void clear_check()
{
    std::cout << RED << "CHECKING FUNCTION CLEAR:\n" << END;
    std::list<int> l;
    ft::list<int> myl;
    
    for (int i=0; i<10; i++) l.push_back(i);
    for (int i=0; i<10; i++) myl.push_back(i);
    print_lists("My list before clear: ", "Original list before clear: ", myl, l);
    l.clear();
    myl.clear();
    print_lists("My list after clear: ", "Original list after clear ", myl, l);
}

void assign_check()
{
    std::cout << RED << "CHECKING FUNCTION assign:\n" << END;
    //________________________First_version_______________________//
    
    std::cout << RED << "Checking fill assign\n";
    std::list<int> l(5, 5);
    ft::list<int> myl(5, 5);
    print_lists("My list before fill assign: ", "Original list before fill assign" , myl, l);
    myl.assign(5, 1000);
    l.assign(5, 1000);
    print_lists("My list after assign: ", "Original list after assign: " , myl, l);

    //________________________Second_version_______________________//

    std::cout << RED << "Checking range assign\n";
    print_lists("My list before range assign: ", "Original list before range assign" , myl, l);
    ft::list<int>::iterator it = myl.begin();
    ft::list<int>::iterator ite = myl.end();
    std::list<int>::iterator it2 = l.begin();
    std::list<int>::iterator it2e = l.end();
    myl.assign(it, ite);
    l.assign(it2, it2e);
    print_lists("My list after assign in the beginning: ", "Original list after assign in the beginning: " , myl, l);
}

void insert_check()
{
    std::cout << RED << "CHECKING FUNCTION INSERT:\n" << END;
    //________________________First_version_______________________//
    std::cout << RED << "Checking single element insert\n";
    std::list<int> l(5, 5);
    ft::list<int> myl(5, 5);
    print_lists("My list before insert: ", "Original list before insert" , myl, l);
    ft::list<int>::iterator it = myl.begin();
    ft::list<int>::iterator ite = myl.end();
    std::list<int>::iterator it2 = l.begin();
    std::list<int>::iterator it2e = l.end();
    myl.insert(it, 100);
    l.insert(it2, 100);
    print_lists("My list after insert in the beginning: ", "Original list after insert in the beginning: " , myl, l);
    myl.insert(ite, 100);
    l.insert(it2e, 100);
    print_lists("My list after insert in the end: ", "Original list after insert in the end: " , myl, l);
    myl.insert(--it, 100);
    l.insert(--it2, 100);
    print_lists("My list after insert in the middle: ", "Original list after insert in the middle: " , myl, l);

    //________________________Second_version_______________________//
    std::cout << RED << "Checking fill insert\n";
    print_lists("My list before fill insert: ", "Original list before fill insert" , myl, l);
    myl.insert(it, 5, 1000);
    l.insert(it2, 5, 1000);
    print_lists("My list after insert in the beginning: ", "Original list after insert in the beginning: " , myl, l);
    myl.insert(ite, 5,1000);
    l.insert(it2e, 5, 1000);
    print_lists("My list after insert in the end: ", "Original list after insert in the end: " , myl, l);

    //________________________Third_version_______________________//
    std::cout << RED << "Checking range insert\n";
    std::list<int> l2(5, 5);
    ft::list<int> myl2(5, 5);

    ft::list<int>::iterator it3 = myl2.begin();
    ft::list<int>::iterator it3e = myl2.end();
    std::list<int>::iterator it4 = l2.begin();
    std::list<int>::iterator it4e = l2.end();
    print_lists("My list before range insert: ", "Original list before range insert" , myl2, l2);
    myl2.insert(it3, ++it, ++it);
    l2.insert(it4, ++it2, ++it2);
    print_lists("My list after insert in the beginning: ", "Original list after insert in the beginning: " , myl2, l2);
    myl2.insert(it3e, ++it, ++it);
    l2.insert(it4e, ++it2, ++it2);
    print_lists("My list after insert in the end: ", "Original list after insert in the end: " , myl2, l2);
}

void erase_check()
{
    std::cout << RED << "CHECKING FUNCTION erase:\n" << END;
    std::cout << RED << "Checking single element erase\n";
    std::list<int> l;
    ft::list<int> myl;
    for (int i=0; i<5; i++) l.push_back(i);
    for (int i=0; i<5; i++) myl.push_back(i);
    print_lists("My list before erase: ", "Original list before erase" , myl, l);
    ft::list<int>::iterator it = myl.begin();
    ft::list<int>::iterator ite = myl.end();
    std::list<int>::iterator it2 = l.begin();
    std::list<int>::iterator it2e = l.end();
    myl.erase(it);
    l.erase(it2);
    print_lists("My list after erase in the beginning: ", "Original list after erase in the beginning: " , myl, l);
    myl.erase(--ite);
    l.erase(--it2e);
    print_lists("My list after erase in the middle: ", "Original list after erase in the middle: " , myl, l);

}

void resize_check()
{
    std::cout << RED << "Checking resize\n";
    std::list<int> l(5, 5);
    ft::list<int> myl(5, 5);
    print_lists("My list before resize: ", "Original list before resize" , myl, l);
    l.resize(10, 100);
    myl.resize(10, 100);
    print_lists("My list after resize(make bigger): ", "Original list after resize(make bigger)" , myl, l);
    l.resize(2, 100);
    myl.resize(2, 100);
    print_lists("My list after resize(make smaller): ", "Original list after resize(make smaller)" , myl, l);
}

bool single_digit (const int& value) { return (value<5); }
void remove_check()
{
    std::cout << RED << "Checking remove\n";
    //__________________First_version_____________//
    std::list<int> l;
    ft::list<int> myl;
    for (int i=0; i<10; i++) l.push_back(i);
    for (int i=0; i<10; i++) myl.push_back(i);
    print_lists("My list before remove: ", "Original list before remove" , myl, l);
    l.remove(5);
    myl.remove(5);
    print_lists("My list after remove: ", "Original list after remove" , myl, l);
    //__________________Second_version_____________//
    std::cout << RED << "Checking remove with predicate\n";
    // std::list<int> l;
    // ft::list<int> myl;
    // for (int i=0; i<10; i++) l.push_back(i);
    // for (int i=0; i<10; i++) myl.push_back(i);
    print_lists("My list before remove: ", "Original list before remove" , myl, l);
    l.remove_if(single_digit);
    myl.remove_if(single_digit);
    print_lists("My list after remove: ", "Original list after remove" , myl, l);
}

bool same_integral_part (double first, double second)
    { return ( int(first)==int(second)); }
void unique_check()
{
    std::cout << RED << "Checking unique\n";
    std::list<int> l(5, 5);
    ft::list<int> myl(5, 5);
    for (int i=0; i<10; i++) l.push_back(i);
    for (int i=0; i<10; i++) myl.push_back(i);
    print_lists("My list before unique: ", "Original list before unique" , myl, l);
    l.unique();
    myl.unique();
    print_lists("My list after unique: ", "Original list after unique" , myl, l);
    //_______________________Second_version_________________________//
    // a binary predicate implemented as a function:
    std::cout << RED << "Checking unique with binary predicate\n";
    std::list<int> l2(5, 5);
    ft::list<int> myl2(5, 5);
    print_lists("My list before unique: ", "Original list before unique" , myl2, l2);
    l2.unique(same_integral_part);
    myl2.unique(same_integral_part);
    print_lists("My list after unique: ", "Original list after unique" , myl2, l2);
}

void reverse_check()
{
    std::cout << RED << "Checking reverse\n";
    std::list<int> l;
    ft::list<int> myl;
    for (int i=0; i<5; i++) l.push_back(i);
    for (int i=0; i<5; i++) myl.push_back(i);
    print_lists("My list before reverse: ", "Original list before reverse" , myl, l);
    l.reverse();
    myl.reverse();
    print_lists("My list after reverse: ", "Original list after reverse" , myl, l);
}

void splice_check()
{
    std::cout << RED << "Checking splice entire list\n";
    std::list<int> l;
    ft::list<int> myl;
    std::list<int> l2(5, 10);
    ft::list<int> myl2(5, 10);
    for (int i=0; i<5; i++) l.push_back(i);
    for (int i=0; i<5; i++) myl.push_back(i);
    print_lists("My list before splice: ", "Original list before splice" , myl, l);
    l.splice(l.begin(), l2);
    myl.splice(myl.begin(), myl2);
    print_lists("My list after splice: ", "Original list after splice" , myl, l);
    print_lists("My list2 after splice: ", "Original list2 after splice" , myl2, l2);
    //________________________Single_element________________________________//
    std::cout << RED << "Checking splice single element\n";
    std::list<int> l3(5, 20);
    ft::list<int> myl3(5, 20);
    l.splice(l.begin(), l3, ++l3.begin());
    myl.splice(myl.begin(), myl3, ++myl3.begin());
    print_lists("My list after splice: ", "Original list after splice" , myl, l);
    //________________________Range_element________________________________//
    std::cout << RED << "Checking splice range element\n";
    l.splice(++l.begin(), l3, ++l3.begin(), l3.end());
    myl.splice(++myl.begin(), myl3, ++myl3.begin(), myl3.end());
    print_lists("My list after splice: ", "Original list after splice" , myl, l);
}

bool mycomparison (double first, double second)
    { return ( int(first)<int(second) ); }

void merge_check()
{
    std::cout << RED << "Checking merge(1)\n";
    std::list<int> l;
    ft::list<int> myl;
    std::list<int> l2;
    ft::list<int> myl2;
    for (int i=0; i<5; i++) l.push_back(i);
    for (int i=0; i<5; i++) myl.push_back(i);
    for (int i=0; i<5; i++) l2.push_back(i);
    for (int i=0; i<5; i++) myl2.push_back(i);
    print_lists("My list before merge: ", "Original list before merge" , myl, l);
    l.merge(l2);
    myl.merge(myl2);
    print_lists("My list after merge: ", "Original list after merge" , myl, l);
    //________________________Merge with comp________________________________//
    std::cout << RED << "Checking merge(2)\n";
    l.merge(l2, mycomparison);
    myl.merge(myl2, mycomparison);
    print_lists("My list after merge: ", "Original list after merge" , myl, l);
}

bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}
void sort_check()
{
    std::cout << RED << "Checking sort(1)\n";
    std::list<int> l;
    ft::list<int> myl;
    for (int i=3; i>0; i--) l.push_back(i);
    for (int i=3; i>0; i--) myl.push_back(i);
    print_lists("My list before sort: ", "Original list before sort" , myl, l);
    l.sort();
    myl.sort();
    print_lists("My list after sort: ", "Original list after sort" , myl, l);
    //________________________sort with comp________________________________//
    std::cout << RED << "Checking sort(2)\n";
    std::list<std::string> l2;
    ft::list<std::string> myl2;
    l2.push_back("abc");
    myl2.push_back("bcd");
    l2.sort(compare_nocase);
    myl2.sort(compare_nocase);
    print_lists("My list after sort: ", "Original list after sort" , myl, l);
}

void relational_operators_check()
{
    std::list<int> l;
    std::list<int> l2;
    ft::list<int> myl;
    ft::list<int> myl2;
    
    std::cout << RED << "CHECKING RELATIONAL OPERATORS:\n" << END;
    for (int i=0; i<5; i++) l.push_back(5);
    for (int i=0; i<10; i++) l2.push_back(5);
    for (int i=0; i<5; i++) myl.push_back(5);
    for (int i=0; i<10; i++) myl2.push_back(5);
    //_______________________checking original__________________//
    print_lists("Original list: ", "Original list2: ", l, l2);
    print_lists("My list: ", "My list2: ", myl, myl2);
    if (l != l2)
        std::cout << "Not equal\n";
    if (myl != myl2)
        std::cout << "Not equal\n";
    if (l == l2)
        std::cout << "Equal\n";
    if (myl == myl2)
        std::cout << "Equal\n";
    if (l < l2)
        std::cout << "Less\n";
    if (myl < myl2)
        std::cout << "Less\n";
    if (l > l2)
        std::cout << "More\n";
    if (myl > myl2)
        std::cout << "More\n";
    if (l <= l2)
        std::cout << "Less and equal\n";
    if (myl <= myl2)
        std::cout << "Less and equal\n";
    if (l >= l2)
        std::cout << "More and equal\n";
    if (myl >= myl2)
        std::cout << "More and equal\n";
}

void swap_check()
{
    std::cout << RED << "CHECKING FUNCTION SWAP:\n" << END;
    ft::list<int> myl;
    ft::list<int> myl2;
    std::list<int> l;
    std::list<int> l2;
    for (int i=0; i<5; i++) myl.push_back(i);
    for (int i=0; i<5; i++) myl2.push_back(10);
    for (int i=0; i<5; i++) l.push_back(i);
    for (int i=0; i<5; i++) l2.push_back(10);
    print_lists("My list before swap: ", "My list2 before swap: ", myl, myl2);
    myl.swap(myl2);
    print_lists("My list after swap: ", "My list2 after swap: ", myl, myl2);
    print_lists("Original list before swap: ", "Original list2 before swap: ", l, l2);
    l.swap(l2);
    print_lists("Original list after swap: ", "Original list2 after swap: ", l, l2);
}
int main ()
{
    constructors_check();
    push_back_check();
    pop_back_check();
    push_front_check();
    pop_front_check();
    clear_check();
    assign_check();
    insert_check();
    erase_check();
    resize_check();
    remove_check();
    unique_check();
    reverse_check();
    splice_check();
    merge_check();
    sort_check();
    relational_operators_check();
    swap_check();
    //sleep(100);
}