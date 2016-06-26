/*
  
****  ***** *****  ***  ****  *****
*   * *     *     *   * *   * *    
****  ****  ****  *   * ****  **** 
*   * *     *     *   * *  *  *    
****  ***** *      ***  *   * *****

*/
#include <Poco/SharedLibrary.h>
#include <iostream>
#include <string>
#include <map>

using VoidFunc = void (*)();
using IntFunc = int (*)(int,int);
using Func = void (*)(std::string);
    
int main()
{
    using Poco::SharedLibrary;

    std::string Path("libplugin1");
    Path.append(SharedLibrary::suffix());

    SharedLibrary Library(Path);

    VoidFunc hello = (VoidFunc)Library.getSymbol("hello");
    IntFunc sum = (IntFunc)Library.getSymbol("sum");
    Func printmess = (Func)Library.getSymbol("printmess");

//    printmess("MikuMiku!!!");

    int x = 0;
    unsigned int t = 1000000001;
    for (int i=0; i<t; i++)
    {
//	std::cerr << x << "\r";
	x = sum(x, 1);
    }
    std::cout << "Answer:" << x << std::endl;
    
    Library.unload();
}
