/*
  @file generate_srcml.cpp

  Implementation of generate_srcml()
*/

#include "generate_srcml.hpp"

// converts src from a given filename in a given language to srcml
// returns success
bool generate_srcml(const std::string& filename,
					const std::string& language,
					const std::string& src,
					std::string& srcml)
{
    srcml = "Filename:" + filename + ",Language:" + language;

    return true;
}
