/* plugin1.cpp
 * Author: Shun Terabayashi <shunonymous@gmail.com>
 * License: CC0 1.0 Universal
 */

#include <iostream>
#include <string>

extern "C" void hello()
{
    std::cout << "Hello" << std::endl;
}

extern "C" void miku()
{
    std::cout << "Miku!" << std::endl;
}

// WIP
/*
extern "C" void printmess(std::string mess1)
{
    std::cout << mess1 << std::endl;
}
*/
