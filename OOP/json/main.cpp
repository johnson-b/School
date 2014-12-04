//
//  main.cpp
//  JSON Parser
//
//  Created by Bryan Johnson on 11/15/14.
//  
// This program is used to parse a json object that is returned from any reddit subreddit page.
// If just the json object is given with no arguments, the json is just formatted correctly and
// then returned. If arguments are found, it will first parse the json and then filter out any
// object that does NOT contain a value that matches the arguments given; then it prints out the
// filtered version of the json. 
//

#include <iostream>
#include <string>
#include <iterator>
#include "json.h"

int main(int argc, const char * argv[]) {
    
    using iter = std::istreambuf_iterator<char>;
    std::string s(iter(std::cin), iter());
    
    json::Value *v = json::parse(s);

    if(argc > 1) {
 		std::cout << json::filter(argc, argv, v)->printPretty(0) << std::endl;
    } else
    	std::cout << v->printPretty(0) << std::endl;
    
    
    return 0;
}
