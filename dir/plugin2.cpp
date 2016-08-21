/* plugin2.cpp
 * Author: Shun Terabayashi <shunonymous@gmail.com>
 * License: CC0 1.0 Universal
 */

#include <iostream>
#include <string>

extern "C" void hello()
{
    std::cout << "Hello, 2nd!!" << std::endl;
}

extern "C" void miku()
{
    std::cout << "Miku!" << std::endl;
}

extern "C" int sum(int num1,int num2)
{
    int ans;
    ans = num1 + num2;
    return ans;
}

extern "C" void strappend(std::string& str,std::string& rt_str)
{
    rt_str = str;
    rt_str.append("mikumiku.");
}

extern "C" void printmess(std::string mess1)
{
    std::cout << mess1 << std::endl;
}

