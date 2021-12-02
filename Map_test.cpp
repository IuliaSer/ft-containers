#include "Map.hpp"
#include <map>
#include <iostream>
# define RED "\x1b[31m"
# define END "\x1b[0m"
# define BLUE "\x1b[36m"
# define GREEN "\e[92m"
#include <unistd.h>
#include <iomanip>

template <typename T>
void printMap (T & Map)
{
	typename T :: iterator itSys = Map.begin();
	for ( ; itSys != Map.end(); itSys++)
	{
		std::cout << "" << std::setw(7) << itSys->first << "    | ";
	}
	std::cout << RED << itSys->first << END;
	std::cout << '\n' << "            |" ;

	itSys = Map.begin();
	for (; itSys != Map.end(); itSys++)
	{
		std::cout << "" << std::setw(7) << itSys->second << "    | ";
	}
	std::cout << '\n' << '\n';
}
void operations_check()
{
    ft::map<int, char> mym;
    std::map<int, char> m;

    mym[2] = 'a';
    mym[3] = 'a';
    mym[1] = 'a';
    mym[5] = 'a';
    mym[4] = 'a';

    m[2] = 'a';
    m[3] = 'a';
    m[1] = 'a';
    m[5] = 'a';
    m[4] = 'a';
    std::map<int, char>::iterator itlow, itup, itfind;
    ft::map<int, char>::iterator itmlow, itmup, itmfind;

    itmlow = mym.lower_bound (3);  // itlow points to b
    itmup = mym.upper_bound (3);   // itup points to e (not d!)
    itlow = m.lower_bound (3);  // itlow points to b
    itup = m.upper_bound (3);
    itmfind = mym.find(4);
    itfind = m.find(4);

    std::cout << RED <<  "Lower_bound:\n" << END;
    std::cout << "Original:\n";
    std::cout << itlow->first << " => " << itlow->second << '\n';
    std::cout << "My map:\n";
    std::cout << itmlow->first << " => " << itmlow->second << '\n';

    std::cout << RED <<  "Upper_bound:\n" << END;
    std::cout << "Original:\n";
    std::cout << itup->first << " => " << itup->second << '\n';
    std::cout << "My map:\n";
    std::cout << itmup->first << " => " << itmup->second << '\n';

    std::cout << RED <<  "Find:\n" << END;
    std::cout << "Original:\n";
    std::cout << itfind->first << " => " << itfind->second << '\n';
    std::cout << "My map:\n";
    std::cout << itmfind->first << " => " << itmfind->second << '\n';

    std::cout << RED <<  "Count:\n" << END;
    std::cout << "Original:\n";
    std::cout << m.count(5) << std::endl;
    std::cout << "My map:\n";
    std::cout << mym.count(5) << std::endl;
}

void insert_and_operator_check()
{
    ft::map<int, char> mym;
    std::map<int, char> m;
    
    //____________________Operator[]_______________________//
    mym[2] = 'a';
    mym[3] = 'a';
    mym[1] = 'a';
    mym[5] = 'a';
    mym[4] = 'a';

    m[2] = 'a';
    m[3] = 'a';
    m[1] = 'a';
    m[5] = 'a';
    m[4] = 'a';

    //_____________________Single_element_insert____________//
    std::cout << RED <<  "Single_element_insert\n" << END;
    mym.insert(std::make_pair(10, 'a'));
    m.insert(std::make_pair(10, 'a'));

    printMap(mym);
    printMap(m);

    //_____________________Insert_with_hint_________________//
    std::cout << RED <<  "Insert_with_hint\n" << END;
    ft::map<int, char>::iterator it = mym.begin();
    std::map<int, char>::iterator it2 = m.begin();
    mym.insert(it, std::make_pair('a', 7));

    m.insert(it2, std::make_pair('a', 7));
    printMap(mym);
    printMap(m);

    //____________________Range_insert_____________________//

    std::cout << RED <<  "Range_insert\n" << END;
    ft::map<int, char> mym2;
    std::map<int, char> m2;
    ft::map<int, char>::iterator ite = mym.end();
    std::map<int, char>::iterator it2e = m.end();
    ite--;
    it2e--;
    mym2.insert(it, --ite);
    m2.insert(it2, --it2e);

    printMap(mym2);
    printMap(m2);
}

void erase_check()
{
    ft::map<int, char> mym;
    std::map<int, char> m;

    mym[2] = 'a';
    mym[3] = 'a';
    mym[1] = 'a';
    mym[5] = 'a';
    mym[4] = 'a';

    m[2] = 'a';
    m[3] = 'a';
    m[1] = 'a';
    m[5] = 'a';
    m[4] = 'a';
    ft::map<int, char>::iterator it2 = mym.begin();
    ft::map<int, char>::iterator it3 = mym.begin();
    std::map<int, char>::iterator it4 = m.begin();
    std::map<int, char>::iterator it5 = m.begin();
    it3++;
    it5++;
    //________________________Single_element_erase__________________//
    std::cout << RED <<  "Single element erase\n" << END;
    std::cout << RED <<  "Maps before erase\n" << END;

    printMap(mym);
    printMap(m);
    mym.erase(it3);
    m.erase(it5);
    std::cout << RED <<  "Maps after erase\n" << END;

    printMap(mym);
    printMap(m);

    //________________________Range_version_of_erase________________//
    std::cout << RED <<  "Range version of erase:\n" << END;
    mym.erase(it2, ++it2);
    m.erase(it4, ++it4);

    printMap(mym);
    printMap(m);

    //__________________________Base_version_of_erase_______________//
    std::cout << RED <<  "Base version of erase:\n" << END;
    mym.erase(std::make_pair(5, 'a').first);
    m.erase(std::make_pair(5, 'a').first);

    printMap(mym);
    printMap(m);
}

void swap_check()
{
    ft::map<int, char> mym;
    ft::map<int, char> mym2;
    std::map<int, char> m;
    std::map<int, char> m2;

    mym[2] = 'a';
    mym[3] = 'a';
    mym[1] = 'a';
    mym[5] = 'a';
    mym[4] = 'a';

    mym2[10] = 'a';
    mym2[7] = 'a';
    mym2[15] = 'a';

    m[2] = 'a';
    m[3] = 'a';
    m[1] = 'a';
    m[5] = 'a';
    m[4] = 'a';

    m2[10] = 'a';
    m2[7] = 'a';
    m2[15] = 'a';
    std::cout << RED <<  "Before swap\n" << END;

    printMap(mym);
    printMap(mym2);
    printMap(m);
    printMap(m2);

    mym.swap(mym2);
    m.swap(m2);
    std::cout << RED <<  "After swap\n" << END;

    printMap(mym);
    printMap(mym2);
    printMap(m);
    printMap(m2);
}

void iterators_check()
{
    std::map<int, char> m;
    ft::map<int, char> mym;
    m.begin();
    mym.begin();
    m[42] = 'a';
    m[21] = 'a';
    m[30] = 'a';
    m[12] = 'a';
    mym[42] = 'a';
    mym[21] = 'a';
    mym[30] = 'a';
    mym[12] = 'a';
    std::map<int, char>::reverse_iterator it = --m.rend();
    ft::map<int, char>::reverse_iterator itm = mym.rend();
    ft::map<int, char>::reverse_iterator itmg = mym.rbegin();
    std::cout << (*it).first << std::endl;
    std::cout << (*itmg).first << std::endl;

    for (ft::map<int, char>::reverse_iterator it_my = mym.rbegin(); it_my != mym.rend(); it_my++)
        std::cout << "My: " << it_my->first << " -> " << it_my->second << std::endl;
    for (ft::map<int, char>::reverse_iterator it_my = --mym.rend(); it_my != mym.rbegin(); it_my--)
        std::cout << "My: " << it_my->first << " -> " << it_my->second << std::endl;

}

void clear_check()
{
    ft::map<int, char> mym;
    std::map<int, char> m;

    std::cout << RED <<  "Clear check\n" << END;
    mym[2] = 'a';
    mym[3] = 'a';
    mym[1] = 'a';
    mym[5] = 'a';
    mym[4] = 'a';

    m[2] = 'a';
    m[3] = 'a';
    m[1] = 'a';
    m[5] = 'a';
    m[4] = 'a';
    std::cout << RED <<  "Before clear\n" << END;
    printMap(mym);
    printMap(m);

    mym.clear();
    m.clear();
    std::cout << RED <<  "After clear\n" << END;

    printMap(mym);
    printMap(m);
}
int main()
{
    operations_check();
    insert_and_operator_check();
    erase_check();
    swap_check();
    clear_check();
    iterators_check();

    //sleep(100);
}
