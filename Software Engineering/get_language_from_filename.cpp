/*
  @file get_language_from_filename.cpp

  Implementation of get_language_from_filename()
*/

#include "get_language_from_filename.hpp"
#include <map>
#include <string>

namespace {

    struct Language {

        typedef std::map<std::string, std::string> map_t;

        static Language::map_t create_map() {

            Language::map_t m;

            m[".c"]    = "C";
            m[".h"]    = "C";
            m[".i"]    = "C";
            m[".cpp"]  = "C++";
            m[".CPP"]  = "C++";
            m[".cp"]   = "C++";
            m[".hpp"]  = "C++";
            m[".cxx"]  = "C++";
            m[".hxx"]  = "C++";
            m[".cc"]   = "C++";
            m[".hh"]   = "C++";
            m[".c++"]  = "C++";
            m[".h++"]  = "C++";
            m[".C"]    = "C++";
            m[".H"]    = "C++";
            m[".tcc"]  = "C++";
            m[".ii"]   = "C++";
            m[".java"] = "Java";
            m[".aj"]   = "AspectJ";
            m[".cs"]   = "C#";

            return m;
        }

        static Language::map_t map;
    };

    Language::map_t Language::map = Language::create_map();
}

// The language from the extension of the given file
// returns an empty string if no associated language
std::string get_language_from_filename(const std::string& filename) {

    // find the last extension (including the '.')
    int pos = filename.rfind('.');
    if (pos == std::string::npos)
        return "";
    std::string extension = filename.substr(pos);

    // empty string if not found
    if (Language
        ::map.count(extension) == 0)
        return "";

    return Language::map[extension];
}
