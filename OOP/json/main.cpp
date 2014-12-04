//
//  main.cpp
//  JSON Parser
//
//  Created by Bryan Johnson on 11/15/14.
//  Copyright (c) 2014 Bryan Johnson. All rights reserved.
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
