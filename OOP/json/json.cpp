//
//  json.cpp
//  JSON Parser
//
//  Created by Bryan Johnson on 11/28/14.
//

#include "json.h"
#include <stdexcept>
#include <string.h>
namespace json {

    Value* parse_json_value(const char*& first, const char* last);
    
    /* Consumes any whitespace in a pair. */
    void parse_white_space(const char*& first, const char* last) {
        while (first != last && std::isspace(*first))
            ++first;
    }
    
    /* Every json object is a pair between a string and some value,
       by using std::pair, we can just insert this into the object struct
       which is a std::map */
    Pair parse_json_pair(const char*& first, const char* last) {
        Pair p;
        Value *key = parse_json_value(first, last); // find key
        if(key->type != Value::STRING) // assume every json object contains string key
            throw std::runtime_error("invalid type, expected STRING");
        parse_white_space(first, last);
        if(*first != ':') { // assume character after key is a ':', if not, throw
            std::string error = "parse object error: ";
            error.append(first);
            throw std::runtime_error(error);
        }
        parse_white_space(first, last);
        ++first;
        
        Value *value = parse_json_value(first, last); // find value
        return {key->getValue(), value}; // return the key, value pair
    }
    
    /* Parses char values between two quotations and returns its value */
    Value* parse_json_string(const char*& first, const char* last) {
        const char* init = first++; // move past start quote: "
        
        while (first != last) { // continue parsing string until we reach end
            if (*first == '\\') { // skip any escape characters found in string
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
        return new String(init, first); // return contents of parsed string
    }
    
    /* Every json object has a key (string) and a value (multiple types). This
       is where the recursive parsing begins and ends. We continue to parse an
       object until we reach a closing '}'. */
    Value* parse_json_object(const char*& first, const char* last){
        ++first; // move past opening '{'
        Object *object = new Object();
        while(true) {
            if(*first != '}') // insert the parsed pair into the object(start recursion)
                object->insert(parse_json_pair(first, last));
            
            parse_white_space(first, last);
            if(first == last) { 
                // after parsing a pair, we should be left with either a comma or an ending brace
                // if not, throw exception
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
            
            // The only time we should get here is if we are given an invalid json object
            throw std::runtime_error(first);
        }
        return object;
    }

    /* Parses an array and of objects. Also recursive, doesn't stop until ending ']'. */
    Value* parse_json_array(const char*& first, const char* last) {
        first++; // move past opening bracket: [
        
        Array *a = new Array();
        while(true) {
            if(*first != ']') // ending condition
                a->push_back(parse_json_value(first, last));
            
            parse_white_space(first, last);
            if(first == last) {
                // we should be left with either a comma or an ending brace, anything
                // else and we throw exception
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

            // The only time we should reach here is if we were given invalid json
            std::string error = "parse array error: ";
            error.append(first);
            throw std::runtime_error(error);
        }
        
        return a;
    }
    
    /* Parses any value that begins with a 't' or 'f'. We must continue to parse until
       we reach the end of the value.

       ***NOTE: I got lazy and decided to stop at the letter 'e' since both true and
                false end in 'e'. This should probably be changed in the future... */
    Value* parse_json_boolean(const char*& first, const char* last) {
        Boolean *b = new Boolean();
        parse_white_space(first, last);
        if(*first == 't') // making an ass out of you and me, im assuming 't' means true
            b->value = true;
        if(*first == 'f') // also assuming here 'f' means false
            b->value = false;
        do
            ++first;
        while(*first != 'e'); // stop when we reach an 'e'
        ++first;
        return b;
    }

    /* Parses an object that begins with n, again, assumes n is for null. Returns
       a completely empty object. */
    Value* parse_json_null(const char*& first, const char* last) {
        Null *n = new Null(); 
        n->type = Value::NIL;
        do
            ++first;
        while(*first != 'l'); // continue until we reach a 'l', then move two chars past
                              // because null has two 'l's. I know, this is awful....TODO!
        ++first; ++first;
        return n;
    }

    /* Parses any value that either begins with a digit, '-', or '.'(for decimal values) */
    Value* parse_json_number(const char*& first, const char* last) {
        const char* init = first++; 
        // continue to parse until the end of the number, number can include decimal or
        // be negative
        while (first != last && (std::isdigit(*first) || *first == '.' || *first == '-'))
            ++first;
        return new Number(init, first);
    }
    
    /* Begins the parsing from each object, we check to see what the first character is
       so we know what kind of value we are dealing with. */
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
    
    /* Main parse function that is made public to the user */
    Value* parse(const std::string &str) {
        const char* json_string = str.c_str(); // convert into 'c string' before parsing
        return parse_json_value(json_string, json_string + str.size());
    }

    /* Function to handle filtering out any given arguments. Handles unlimited number of arguments.
       Assumes the json we get back is from reddit.com.

       TODO: change this to accomodate any form of json */
    Value* filter(int argc, const char* argv[], Value *v) {
        // main object inside every reddit json contains 'data', its kind of the sub root of the json
        std::map<std::string, json::Value*>::iterator obj_it = dynamic_cast<json::Object*>(v)->find("data");
        json::Value *data = (*obj_it).second;
        // every 'data' value contains 'children' which nests numerous objects of inner json
        std::map<std::string, json::Value*>::iterator arr_it = dynamic_cast<json::Object*>(data)->find("children");
        json::Value *children = (*arr_it).second;

        /* For each object inside children, we want to find its value and compare it to the argument(s) that were
           given. If we go through every object of each 'data' value, and DO NOT find a match, we delete it. We only
           care to keep, objects that contain a value that matches the arguments given. */
        for(std::vector<json::Value*>::iterator it = dynamic_cast<json::Array*>(children)->begin(); it != dynamic_cast<json::Array*>(children)->end(); ++it) {
            json::Value *value = (*it);
            std::map<std::string, json::Value*>::iterator data_it = dynamic_cast<json::Object*>(value)->find("data");
            json::Value *object = (*data_it).second;
            std::map<std::string, json::Value*>::iterator iter = dynamic_cast<json::Object*>(object)->begin();
            while(iter != dynamic_cast<json::Object*>(object)->end()) {
                int counter = 0; // used to keep track of how many 'misses' we get from searching
                for (int i = 1; i < argc; ++i)
                {
                    if((*iter).first != argv[i]) {
                        counter++;  
                    }       
                }
                // We keep track of a counter for every object that we do not find a match, if that counter is the 
                // same as the amount of arguments given, we know that the argument given doesn't match any object
                // that resides in that object; therefore we can delete it from the object. 
                if(counter == argc - 1)
                    dynamic_cast<json::Object*>(object)->erase(iter);   
                iter++;
            }
        }
        return v; // return the 'filtered' value
    }
}
