/*
  @file generate_srcml.hpp

  Header for generate_srcml()
*/

#ifndef INCLUDE_GENERATE_SRCML_HPP
#define INCLUDE_GENERATE_SRCML_HPP

#include <string>

// converts src from a given filename in a given language to srcml
// returns success
bool generate_srcml(const std::string& filename,
					const std::string& language,
					const std::string& src,
					std::string& srcml);

#endif
