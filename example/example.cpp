/* example.cp
 * Author: Shun Terabayashi <shunonymous@gmail.com>
 * License: CC0 1.0 Universal
 */

#include <Poco/SharedLibrary.h>
#include <string>
#include <iostream>

#include "DynamicLoader.hpp"

int main()
{
    DynamicLoadLibray hello;
    hello.SetupLibrary("plugin1",{"hello","miku","printmess"});
    hello.Function.at("hello")();
    hello.Function.at("miku")();
//WIP    hello.Function.at("printmess")();

    // Function in Poco::SharedLibrary class
    std::cout << hello.Library.getPath() << std::endl;
    std::cout << hello.Library.isLoaded() << std::endl;
}
    
