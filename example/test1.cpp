/*

  ***  ***** ***** ***** **** 
 *   * *       *   *     *   *
 ***** ****    *   ****  **** 
 *   * *       *   *     *  * 
 *   * *       *   ***** *   *

*/
#include <string>
#include <iostream>

#include "DynamicLoader.hpp"

int main()
{
    using namespace DynamicLoader;

    DynamicLoadLibray hello("plugin1",{"hello","sum","printmess"});
//    hello("plugin1",{"hello","sum","printmess"});

//    hello.Function<void>("printmess").call(static_cast<std::string>("MikuMiku!!!"));

    auto sum = hello.Function<int>("sum").alias<int, int>();

    int x=0;
    unsigned int t=1000000001;
    for (int i=0; i<t; i++)
    {
//	std::cerr << x << "\r";
	x = sum(x, 1);
    }
    std::cout << "Answer:" << x << std::endl;

} // int main()
    
