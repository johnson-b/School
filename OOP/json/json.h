//
//  json.h
//  JSON Parser
//
//  Created by Bryan Johnson on 11/28/14.
//

#ifndef JSON_Parser__json__
#define JSON_Parser__json__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

namespace json {
    // Base struct, holds a type, one virtual function to get the Value's value as well
    // as a pure virtual function that prints out the json in a 'pretty' format.
    struct Value{
        enum Type {
            STRING,
            ARRAY,
            OBJECT,
            BOOLEAN,
            NUMBER,
            NIL
        };
        Type type;
        
        virtual std::string getValue() {
            return "";
        }
        
        virtual std::string printPretty(int) = 0; // int argument is to keep track of 'tabbing'
    };
    
    /* Will hold a value for every json value found that is a string */
    struct String : std::string, Value {
        std::string value;
        std::string ret;
        String(std::string s) {
            this->type = STRING;
            value = s;
        }
        String(std::string begin, std::string end) {
            this->type = STRING;
            std::string::size_type pos = begin.find(end);
            if(pos != std::string::npos)
                value = begin.substr(1, pos - 2);
            else
                value = begin.substr(1, pos - 2);
        }
        
        virtual std::string getValue() {
            return value;
        }
        
        virtual std::string printPretty(int tab) {
            ret += "\"" + value + "\"";
            return ret;
        }
    };
    
    /* We don't care about doing any mathematical operations on a json
       value, so therefore we treat a Number like a String except it 
       contains only characters that resemble digits. */
    struct Number : Value {
        std::string value;
        std::string ret;
        Number(std::string begin, std::string end) {
            this->type = NUMBER;
            std::string::size_type pos = begin.find(end);
            value = begin.substr(0, pos);
        }
        virtual std::string getValue() {
            return value;
        }
        
        virtual std::string printPretty(int tab) {
            ret += " " + value;
            return ret;
        }
    };
    
    /* Stands for an empty object that simply holds the value 'null'.
       Otherwise it remains empty. */
    struct Null : Value{
        Null() {
            type = NIL;
        }
        virtual std::string getValue() {
            return "null";
        }
        
        virtual std::string printPretty(int tab) {
            return "null";
        }
    };
    
    /* Holds a value either true or false, pretty basic. */
    struct Boolean : Value {
        bool value = false;
        Boolean() = default;
        Boolean(bool *b) {
            this->type = BOOLEAN;
            value = b;
        }
        
        virtual std::string printPretty(int tab) {
            if(value)
                return "true";
            else
                return "false";
        }
    };
    
    /* Holds multiple Values, in a std::vector. */
    struct Array : std::vector<Value*>, Value {
        std::string ret = "[ \n"; // Every new Array, we want its contents to print on a new line.
        Array() {
            type = ARRAY;
        }
        virtual std::string printPretty(int tab) {
            std::string s(tab, '\t');
            // recursively prints each Value inside of it, 'pretty'
            for(std::vector<Value*>::iterator it = this->begin(); it != this->end(); ++it) {
                ret += (*it)->printPretty(tab);
                ret += ", \n";
            }
            ret += s;
            ret += "]";
            return ret;
        }
    };
    
    using Pair = std::pair<std::string, Value*>; // utility used to add each key, value pair to an Object (std::map)
    
    /* This is the root 'object' of json. Each json key value pair is represented here by using std::map. */
    struct Object : std::map<std::string, Value*>, Value{
        std::string ret = "{ \n";
        Object() {
            type = OBJECT;
        }
        
        virtual std::string printPretty(int tab) {
            ++tab;
            std::string s(tab, '\t');

            // Recursively pretty prints each key value pair that it contains while keeping track of tabs and
            // adding to tabs for every 'nested' object
            for (std::map<std::string, Value*>::iterator it = this->begin(); it != this->end(); it++)
            {   
                ret += s;
                ret += it->first;
                ret += ": ";
                ret += it->second->printPretty(tab);
                ret += ", \n";  
            }
            ret += s;
            ret += "}";
            --tab;
            return ret;
        }
    };

    Value* filter(int argc, const char* argv[], Value *v);
    
    Value* parse(const std::string &str);
}


#endif