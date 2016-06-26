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
	std::map<std::string, void*> Functions;
	void loadLibrary(std::string LibraryName);
    public:
	DynamicLoadLibray(std::string LibraryName, std::vector<std::string> SymbolsName);
	DynamicLoadLibray(){}
	void setupLibrary(std::string LibraryName, std::vector<std::string> SymbolsName);
	inline void loadSymbol(std::string SymbolName);

	Poco::SharedLibrary Library;

	template <typename T1>
	auto Function(std::string FunctionName)
	{
	    return DynamicLoadFunction<T1>(Functions.at(FunctionName));
	}

    }; // class DynamicLoadLibray

    template <typename T2>
    class DynamicLoadFunction
    {
    private:
	std::string FuncName;
	void* Func;
    public:
	template <typename ... Types>
	auto call(Types ... Args);

	template <typename ... Types>
	constexpr auto alias();

	DynamicLoadFunction(void* Function)
	{
	    Func = Function;
	}

    }; // class DynamicLoadFunction

    ///////////////////////////////
    // Define functions in class //
    ///////////////////////////////
    
    void DynamicLoadLibray::loadLibrary(std::string LibraryName)
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
    
    inline void DynamicLoadLibray::loadSymbol(std::string Symbol)
    {
	Functions.insert(std::make_pair(Symbol.c_str(), Library.getSymbol(Symbol)));
    }

    void DynamicLoadLibray::setupLibrary(std::string LibraryName, std::vector<std::string> SymbolsName)
    {
	loadLibrary(LibraryName);
	for(auto&& Symbol:SymbolsName)
	    loadSymbol(Symbol);
    }

    DynamicLoadLibray::DynamicLoadLibray(std::string LibraryName, std::vector<std::string> SymbolsName)
    {
	setupLibrary(LibraryName, SymbolsName);
    } 

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

    template <typename T2>
    template <typename ... Types>
    constexpr auto DynamicLoadFunction<T2>::alias()
    {
	using DlFunc = T2 (*)(Types...);
	return reinterpret_cast<DlFunc>(Func);
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
	void call(Types&& ... Args);

	template <typename ... Types>
	constexpr auto alias();

	DynamicLoadFunction(void* Function)
	{
	    Func = Function;
	}
    };

    template <typename ... Types>
    void DynamicLoadFunction<void>::call(Types&& ... Args)
    {
	using DlFunc = void (*)(Types...);
	DlFunc f = reinterpret_cast<DlFunc>(Func);
	f(Args...);
    }

    template <typename ... Types>
    constexpr auto DynamicLoadFunction<void>::alias()
    {
	using DlFunc = void (*)(Types...);
	return reinterpret_cast<DlFunc>(Func);
    }

} // namespace DynamicLoader
#endif // MIRMIDIVI_DYNAMIC_LOADER_HPP
