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
    
    std::cout << v->toString();
    
    return 0;
}
