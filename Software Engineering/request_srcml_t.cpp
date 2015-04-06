/*
  @file request_srcml_t.cpp

  Test program for request_srcml()
*/

#include "request_srcml.hpp"
#include <cassert>
#include <iostream>

int main() {
    
    // base test case
    {
        srcml_request request;
        std::string src = "";
        std::string srcml = "";
        assert(!request_srcml(request, src, srcml));
    }
    
    // option_language / option_filename test case
    {
        srcml_request request;
        request.option_language = "C++";
        request.option_filename = "filename.cpp";
        
        std::string src = "";
        std::string srcml = "";
        
        assert(request_srcml(request, src, srcml));
        assert(srcml == "Filename:" + request.option_filename
               +",Language:"+request.option_language);
    }
    
    // test case for when option_filename/option_language is empty
    {
        srcml_request request;
        request.entry_filename = "data";
        request.local_filename = "filename.hpp";
        
        std::string src = "";
        std::string srcml = "";
        
        assert(request_srcml(request, src, srcml));
        assert(srcml == "Filename:" + request.local_filename
              + ",Language:C++");
    }
    
    // test case for invalid filename extension
    {
        srcml_request request;
        request.entry_filename = "data";
        request.local_filename = "invalid.xxx";
        
        std::string src = "";
        std::string srcml = "";
        
        assert(!request_srcml(request, src, srcml));
    }
    
    return 0;
}
