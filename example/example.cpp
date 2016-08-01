/* example.cpp
 * Author: Shun Terabayashi <shunonymous@gmail.com>
 * License: CC0 1.0 Universal
 */

#include <Poco/SharedLibrary.h>
#include <string>
#include <iostream>

#include "DynamicLoader.hpp"

int main()
{
    using namespace DynamicLoader;

    ///////////////////////////////
    // Load dynamic load library //
    ///////////////////////////////
    
    DynamicLoadLibray hello;
    hello.setupLibrary("plugin1",{"hello","miku","sum"});
    std::cout << "plugin1 loaded" << std::endl;

    DynamicLoadLibray hello2;
    hello2.Directory = "dir";
    hello2.setupLibrary("plugin2","hello");

    /////////////////
    // Load symbol //
    /////////////////
    
    hello.loadSymbol("strappend");
    hello.loadSymbol("printmess");

    ///////////////////////////////////////////////
    // Call function without argument and return //
    ///////////////////////////////////////////////
    
    hello.Function<void>("hello").call();
    hello.Function<void>("miku").call();

    /////////////////////////////////////////////
    // Call function with arguments and return //
    /////////////////////////////////////////////
    
    int ans;
    // Return type is int
    ans = hello.Function<int>("sum").call(3, 9);
    std::cout << "Answer is " << ans << std::endl;

    std::string str = "3939";
    std::cout << str << std::endl;
    std::string rt_str;
    hello.Function<void>("strappend").call(&str, &rt_str); // Pass reference
    std::cout << rt_str << std::endl;

    std::string str1 = "Hello,C++!!!";
    std::string str2 = "MikuMiku!";
    hello.Function<void>("printmess").call(str1);
    hello.Function<void>("printmess").call(str2);

    // TODO
    //hello.Function<void>("printmess").call("Hello, C++!!!");
    //hello.Function<void>("printmess").call("MikuMiku!");


    ///////////////////////////////////////////
    // Function in Poco::SharedLibrary class //
    ///////////////////////////////////////////
    
    std::cout << "Path:" << hello.Library.getPath() << std::endl;
    std::cout << "Load:" << hello.Library.isLoaded() << std::endl;

    hello2.Function<void>("hello").call();

} // int main()
