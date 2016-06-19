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

namespace DynamicLoader
{
    /////////////////////////
    // Classes declaration //
    /////////////////////////
    
    class DynamicLoadLibray;

    template <typename T2>
    class DynamicLoadFunction;

    ////////////////////////
    // Classes Definition //
    ////////////////////////

    class DynamicLoadLibray
    {
    private:
	std::string Path;
	std::map<std::string,void*> Functions;
    public:
	void loadLibrary(std::string LibraryName);
	void loadSymbol(std::string SymbolName);
	void setupLibrary(const std::string LibraryName,std::vector<std::string> SymbolsName);
	Poco::SharedLibrary Library;

	template <typename T1>
	auto Function(const std::string FunctionName)
	{
	    return DynamicLoadFunction<T1>(Functions.at(FunctionName));
	}
    }; // class DynamicLoadLibray

    ///////////////////////////////
    // Define functions in class //
    ///////////////////////////////
    
    template <typename T2>
    class DynamicLoadFunction
    {
    private:
	std::string FuncName;
	void* Func;
    public:
	template <typename ... Types>
	auto call(Types ... Args);

	DynamicLoadFunction(void* Function)
	{
	    Func = Function;
	}

    }; // class DynamicLoadFunction

    void DynamicLoadLibray::loadLibrary(const std::string LibraryName)
    {
	// Try to load lib<name><suffix> or <name><suffix>
	try{
	    Path = "lib" + LibraryName + Poco::SharedLibrary::suffix();
	    Library.load(Path);
	}
	catch(std::exception &e)
	{
	    Path = LibraryName + Poco::SharedLibrary::suffix();
	    Library.load(Path);
	}
	catch(...)
	{
	    std::cerr << "Error:Cannot load library" << std::endl;
	}
    } // void DynamicLoadLibray::loadLibrary
    
    inline void DynamicLoadLibray::loadSymbol(const std::string Symbol)
    {
	Functions.insert(std::make_pair(Symbol,Library.getSymbol(Symbol)));
    }

    void DynamicLoadLibray::setupLibrary(const std::string LibraryName,const std::vector<std::string> SymbolsName)
    {
	loadLibrary(LibraryName);
	for(auto&& Symbol:SymbolsName)
	    loadSymbol(Symbol);
    } // void DynamicLoadLibray::setupLibrary

    template <typename T2>
    template <typename ... Types>
    auto DynamicLoadFunction<T2>::call(Types ... Args)
    {
	using DlFunc = T2 (*)(Types...);
	T2 ReturnVal;
	DlFunc f;
	f = reinterpret_cast<DlFunc>(Func);
	ReturnVal = f(Args...);
	return ReturnVal;
    }

    /////////////////////////////
    // Template specialization //
    /////////////////////////////

    template <>
    class DynamicLoadFunction<void>
    {
    private:
	std::string FuncName;
	void* Func;
    public:
	template <typename ... Types>
	void call(Types ... Args);

	DynamicLoadFunction(void* Function)
	{
	    Func = Function;
	}
    };

    template <typename ... Types>
    void DynamicLoadFunction<void>::call(Types ... Args)
    {
	using DlFunc = void (*)(Types...);
	DlFunc f;
	f = reinterpret_cast<DlFunc>(Func);
	f(Args...);
    }
    
} // namespace DynamicLoader
#endif // MIRMIDIVI_DYNAMIC_LOADER_HPP
