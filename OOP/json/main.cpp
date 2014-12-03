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

    std::map<std::string, json::Value*>::iterator obj_it = dynamic_cast<json::Object*>(v)->find("data");
    json::Value *data = (*obj_it).second;
    std::map<std::string, json::Value*>::iterator arr_it = dynamic_cast<json::Object*>(data)->find("children");
    json::Value *children = (*arr_it).second;

    if(argc > 1) {
    	for(std::vector<json::Value*>::iterator it = dynamic_cast<json::Array*>(children)->begin(); it != dynamic_cast<json::Array*>(children)->end(); ++it) {
	    	json::Value *value = (*it);
	    	std::map<std::string, json::Value*>::iterator data_it = dynamic_cast<json::Object*>(value)->find("data");
	    	json::Value *object = (*data_it).second;
	    	std::map<std::string, json::Value*>::iterator iter = dynamic_cast<json::Object*>(object)->begin();
	    	while(iter != dynamic_cast<json::Object*>(object)->end()) {
	    		if((*iter).first != argv[1]) {
	    			dynamic_cast<json::Object*>(object)->erase(iter);
	    		}
	    		iter++;
	    	}
    	}	
    }
    std::cout << v->printPretty(0) << std::endl;
    
    
    return 0;
}
