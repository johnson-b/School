/*
  @file get_language_from_filename_t.cpp

  Test program for get_language_from_filename()
*/

#include "get_language_from_filename.hpp"
#include <assert.h>

int main() {

    // known proper values
    assert(get_language_from_filename("file.c")    == "C");
    assert(get_language_from_filename("file.h")    == "C");
    assert(get_language_from_filename("file.i")    == "C");
    assert(get_language_from_filename("file.cpp")  == "C++");
    assert(get_language_from_filename("file.CPP")  == "C++");
    assert(get_language_from_filename("file.cp")   == "C++");
    assert(get_language_from_filename("file.hpp")  == "C++");
    assert(get_language_from_filename("file.cxx")  == "C++");
    assert(get_language_from_filename("file.hxx")  == "C++");
    assert(get_language_from_filename("file.cc")   == "C++");
    assert(get_language_from_filename("file.hh")   == "C++");
    assert(get_language_from_filename("file.c++")  == "C++");
    assert(get_language_from_filename("file.h++")  == "C++");
    assert(get_language_from_filename("file.C")    == "C++");
    assert(get_language_from_filename("file.H")    == "C++");
    assert(get_language_from_filename("file.tcc")  == "C++");
    assert(get_language_from_filename("file.ii")   == "C++");
    assert(get_language_from_filename("file.java") == "Java");
    assert(get_language_from_filename("file.aj")   == "AspectJ");
    assert(get_language_from_filename("file.cs")   == "C#");

    // known non-language extensinos
    assert(get_language_from_filename("file.cs480") == "");
    assert(get_language_from_filename("file.txt")   == "");
    assert(get_language_from_filename("file.doc")   == "");
    assert(get_language_from_filename("file.docx")  == "");

    // just the extension
    assert(get_language_from_filename(".c")    == "C");
    assert(get_language_from_filename(".h")    == "C");
    assert(get_language_from_filename(".i")    == "C");
    assert(get_language_from_filename(".cpp")  == "C++");
    assert(get_language_from_filename(".CPP")  == "C++");
    assert(get_language_from_filename(".cp")   == "C++");
    assert(get_language_from_filename(".hpp")  == "C++");
    assert(get_language_from_filename(".cxx")  == "C++");
    assert(get_language_from_filename(".hxx")  == "C++");
    assert(get_language_from_filename(".cc")   == "C++");
    assert(get_language_from_filename(".hh")   == "C++");
    assert(get_language_from_filename(".c++")  == "C++");
    assert(get_language_from_filename(".h++")  == "C++");
    assert(get_language_from_filename(".C")    == "C++");
    assert(get_language_from_filename(".H")    == "C++");
    assert(get_language_from_filename(".tcc")  == "C++");
    assert(get_language_from_filename(".ii")   == "C++");
    assert(get_language_from_filename(".java") == "Java");
    assert(get_language_from_filename(".aj")   == "AspectJ");
    assert(get_language_from_filename(".cs")   == "C#");

    return 0;
}
