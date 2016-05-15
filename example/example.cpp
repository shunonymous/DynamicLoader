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
    hello.setupLibrary("plugin1",{"hello","miku","sum","strappend","printmess"});
    hello.callFunction<void>("hello")();
    hello.callFunction<void>("miku")();

    int ans;
    ans = hello.callFunction<int,int,int>("sum")(3,9);
    std::cout << "Answer is " << ans << std::endl;

    std::string str = "3939";
    std::cout << str << std::endl;
    std::string rt_str;
    hello.callFunction<void,std::string&,std::string&>("strappend")(str,rt_str);
    std::cout << rt_str << std::endl;

    hello.callFunction<void,std::string>("printmess")("Hello, C++!!!");
    hello.callFunction<void,std::string>("printmess")("MukuMiku!");

    // Function in Poco::SharedLibrary class
    std::cout << "Path:" << hello.Library.getPath() << std::endl;
    std::cout << "Load:" << hello.Library.isLoaded() << std::endl;
}
    
