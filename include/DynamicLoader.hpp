/* DynamicLoader.hpp
 * Author: Shun Terabayashi <shunonymous@gmail.com>
 * License: Boost Software License Version 1.0
 */

#ifndef MIRMIDIVI_DYNAMIC_LOADER_HPP
#define MIRMIDIVI_DYNAMIC_LOADER_HPP

#include <string>
#include <map>
#include <vector>
#include <Poco/SharedLibrary.h>

using DlFunc = void (*)(...);

class DynamicLoadLibray
{
private:
    std::string Path;
    std::string Symbol;
    std::map<std::string,void*> Function;
public:
    void setupLibrary(std::string SharedLibraryName,std::vector<std::string> SymbolNames);
    Poco::SharedLibrary Library;

    inline auto callFunction(std::string FunctionName)
    {
	return reinterpret_cast<DlFunc>(Function.at(FunctionName));
    }

    ~DynamicLoadLibray()
    {
	Library.unload();
	std::cerr << Path << " was unloaded." << std::endl;
    }
};

void DynamicLoadLibray::setupLibrary(std::string SharedLibraryName,std::vector<std::string> SymbolNames)
{
    // Try to load lib<name><suffix> or <name><suffix>
    try{
	Path = "lib" + SharedLibraryName + Poco::SharedLibrary::suffix();
	Library.load(Path);
    }
    catch(std::exception &e)
    {
	Path = SharedLibraryName + Poco::SharedLibrary::suffix();
	Library.load(Path);
    }
    catch(...)
    {
	std::cerr << "Error:Cannot load library" << std::endl;
    }

    for(std::string Symbol : SymbolNames)
	Function.insert(std::make_pair(Symbol,Library.getSymbol(Symbol)));

} // void DynamicLoadLibray::SetupLibrary(std::string SharedLibraryName,std::vector<std::string> SymbolNames)

#endif // MIRMIDIVI_DYNAMIC_LOADER_HPP
