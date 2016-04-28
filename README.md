Dynamic Loader
==============

What's this?
------------

This is a header for loading plugins. 

Features
--------

* Cross platform
* Very easy to use
* Ofcourse, this is free software. 

Required
--------

* Poco C++ libraries (http://pocoproject.org/)
* decent C++ compiler (clang was recommended)

How to use
----------

Show example code.

Classes
-------

#### Description

The DynamicLoadLibrary class dynamically loads shared libraries at run-time.

#### Member Functions

    void SetupLibrary(std::string SharedLibraryName,std::vector<std::string> SymbolNames):

Loads shared library and set parameters.

	Poco::SharedLibrary Library():
	
http://pocoproject.org/docs/Poco.SharedLibrary.html

    std::map<std::string,DlFunc> Function:
	
Pairs of the symbol's name and the symbol's addres. 

Copylights
----------

This software is licensed under [Boost software License v1.0](http://www.boost.org/LICENSE_1_0.txt)
	
Authed by shunonymous(Shun Terabayashi)

Twitter:[@shunonymous](https://twitter.com/shunonymous)

GitHub:https://github.com/shunonymous

Mail:shunonymous@gmail.com
