/*
  @file request_srcml.cpp

  Implementation of request_srcml()
*/

#include "request_srcml.hpp"
#include "generate_srcml.hpp"
#include "get_language_from_filename.hpp"
#include <iostream>

// generates srcml from the src according to the request
bool request_srcml(const srcml_request& request,
                   const std::string& src,
                   std::string& srcml) {

    // TODO: determine the proper filename and language from the request
    std::string filename;
    std::string language;
    
    if(request.local_filename == "-") { // standard input
        if(request.entry_filename == "data") {
            filename = !request.option_filename.empty()
                ? request.option_filename : "";
        } else {
            filename = request.entry_filename;
        }
        
        language = get_language_from_filename(filename);
        
        if(language.empty()) {
            std::cerr << "Using stdin requires a declared language\n";
            return false;
        }
    } else {
        // option_filename trumps everything else
        if(!request.option_filename.empty()) {
            filename = request.option_filename;
        } else {
            filename = request.entry_filename == "data" ?
                request.local_filename : request.entry_filename;
        }
        
        // option_language trumps everything else
        if(!request.option_language.empty()) {
            language = request.option_language;
        } else if(!filename.empty()) {
            language = get_language_from_filename(filename);
        }
    }
    
    // error
    if(language.empty()) {
        std::cerr << "Extension not supported\n";
        return false;
    }
    
    // generate the srcml
    return generate_srcml(filename, language, src, srcml);
}
