/*
  @file request_srcml.hpp

  Header for request_srcml()
*/

#ifndef INCLUDE_REQUEST_SRCML_HPP
#define INCLUDE_REQUEST_SRCML_HPP

#include <string>

struct srcml_request {
	std::string option_filename;
	std::string local_filename;
	std::string entry_filename;
	std::string option_language;
};

// generates srcml from the src according to the request
bool request_srcml(const srcml_request& request, const std::string& src, std::string& srcml);

#endif
