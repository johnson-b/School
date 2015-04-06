/*
  @file get_language_from_filename.hpp

  Declaration of get_language_from_filename()
*/

#ifndef INCLUDE_GET_LANGUAGE_FROM_FILENAME_HPP
#define INCLUDE_GET_LANGUAGE_FROM_FILENAME_HPP

#include <string>

// language from the extension of the given file
// returns an empty string if no associated language
std::string get_language_from_filename(const std::string& filename);

#endif
