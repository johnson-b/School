//
//  json.cpp
//  JSON Parser
//
//  Created by Bryan Johnson on 11/28/14.
//  Copyright (c) 2014 Bryan Johnson. All rights reserved.
//

#include "json.h"
#include <stdexcept>
#include <string.h>
namespace json {

    Value* parse_json_value(const char*& first, const char* last);

    void
    parse_white_space(const char*& first, const char* last) {
        while (first != last && std::isspace(*first))
            ++first;
    }
    
    Pair parse_json_pair(const char*& first, const char* last) {
        Pair p;
        Value *key = parse_json_value(first, last);
        // TODO: check to make sure val.type is string?
        if(key->type != Value::STRING) 
            throw std::runtime_error("invalid type, expected STRING");
        parse_white_space(first, last);
        if(*first != ':') {
            std::string error = "parse object error: ";
            error.append(first);
            throw std::runtime_error(error);
        }
        parse_white_space(first, last);
        ++first;
        
        Value *value = parse_json_value(first, last);
        return {key->getValue(), value};
    }
    
    Value* parse_json_string(const char*& first, const char* last) {
        const char* init = first++; // move past start quote: "
        
        while (first != last) {
            if (*first == '\\') {
                if (first == last){
                    std::string error = "invalid string: ";
                    error.append(first);
                    throw std::runtime_error(error);
                }
                // move over escape char
                first += 2;
            }
            
            // stop when we reach end quote
            if (*first == '"') {
                ++first;
                break;
            }
            ++first;
        }
        return new String(init, first);
    }
    
    Value* parse_json_object(const char*& first, const char* last){
        ++first; // move past opening '{'
        Object *object = new Object();
        while(true) {
            if(*first != '}')
                object->insert(parse_json_pair(first, last));
            
            parse_white_space(first, last);
            if(first == last) {
                std::string error = "invalid object: ";
                error.append(first);
                throw std::runtime_error(error);
            }
            
            // continue if there is comma
            if (*first == ',') {
                ++first;
                continue;
            }
            
            // stop when we reach end of object (closing brace: })
            if (*first == '}') {
                ++first;
                break;
            }
            
            throw std::runtime_error(first);
        }
        return object;
    }
    Value* parse_json_array(const char*& first, const char* last) {
        first++; // move past opening bracket: [
        
        Array *a = new Array();
        while(true) {
            if(*first != ']')
                a->push_back(parse_json_value(first, last));
            
            parse_white_space(first, last);
            if(first == last) {
                std::string error = "invalid array: ";
                error.append(first);
                throw std::runtime_error(error);
            }
            
            // continue if there is a comma
            if (*first == ',') {
                ++first;
                continue;
            }
            
            // stop when we reach end of array (closing bracket: ])
            if (*first == ']') {
                ++first;
                break;
            }
            std::string error = "parse array error: ";
            error.append(first);
            throw std::runtime_error(error);
        }
        
        return a;
    }
    
    Value* parse_json_boolean(const char*& first, const char* last) {
        Boolean *b = new Boolean();
        parse_white_space(first, last);
        if(*first == 't')
            b->value = true;
        if(*first == 'f')
            b->value = false;
        do
            ++first;
        while(*first != 'e');
        ++first;
        return b;
    }
    Value* parse_json_null(const char*& first, const char* last) {
        Null *n = new Null(); 
        n->type = Value::NIL;
        do
            ++first;
        while(*first != 'l');
        ++first; ++first;
        return n;
    }
    Value* parse_json_number(const char*& first, const char* last) {
        const char* init = first++; // move past start quote: "
        while (first != last && (std::isdigit(*first) || *first == '.'))
            ++first;
        return new Number(init, first);
    }
    
    Value* parse_json_value(const char*& first, const char* last) {
        parse_white_space(first, last);
        switch(*first) {
            case '"':
                return parse_json_string(first, last);
            case '{':
                return parse_json_object(first, last);
            case '[':
                return parse_json_array(first, last);
            case 't':
                return parse_json_boolean(first, last);
            case 'f':
                return parse_json_boolean(first, last);
            case 'n':
                return parse_json_null(first, last);
            default:
                return parse_json_number(first, last);
        }
    }
    
    Value* parse(const std::string &str) {
        const char* json_string = str.c_str();
        return parse_json_value(json_string, json_string + str.size());
    }
}
