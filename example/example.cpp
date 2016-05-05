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
    hello.setupLibrary("plugin1",{"hello","miku","sum"});
    hello.callFunction("hello")();
    hello.callFunction("miku")();

    int ans;
    hello.callFunction("sum")(1,2,&ans);
    std::cout << "Answer is " << ans << std::endl;

//WIP    hello.callFunction("printmess")("Hello, C++!!!");
    
    // Function in Poco::SharedLibrary class
    std::cout << hello.Library.getPath() << std::endl;
    std::cout << hello.Library.isLoaded() << std::endl;
}
    
