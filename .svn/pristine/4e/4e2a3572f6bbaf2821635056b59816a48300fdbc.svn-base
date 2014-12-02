//
//  json.h
//  JSON Parser
//
//  Created by Bryan Johnson on 11/28/14.
//  Copyright (c) 2014 Bryan Johnson. All rights reserved.
//

#ifndef JSON_Parser__json__
#define JSON_Parser__json__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

namespace json {
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
        
        virtual std::string toString() = 0;
    };
    
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
        
        virtual std::string toString() {
            ret += "\"" + value + "\"";
            return ret;
        }
    };
    
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
        
        virtual std::string toString() {
            ret += " " + value;
            return ret;
        }
    };
    
    struct Null : Value{
        Null() {
            type = NIL;
        }
        virtual std::string getValue() {
            return "null";
        }
        
        virtual std::string toString() {
            return "null";
        }
    };
    
    struct Boolean : Value {
        bool value = false;
        Boolean() = default;
        Boolean(bool *b) {
            this->type = BOOLEAN;
            value = b;
        }
        
        virtual std::string toString() {
            if(value)
                return "true";
            else
                return "false";
        }
    };
    
    struct Array : std::vector<Value*>, Value {
        std::string ret = "[ \n";
        Array() {
            type = ARRAY;
        }
        int index = 0;
        virtual std::string toString() {
            for (size_t i = 0; i < this->size() - 1; i++) {
                
                ret += this[i].toString() + ", ";
            }
            ret += "\n]";
            
            return ret;
        }
    };
    
    using Pair = std::pair<std::string, Value*>;
    
    struct Object : std::map<std::string, Value*>, Value{
        std::string ret = "{ \n";
        Object() {
            type = OBJECT;
        }
        
        virtual std::string toString() {
            for (std::map<std::string, Value*>::iterator it = this->begin(); it != this->end(); ++it)
            {
                ret += it->first + ": " + it->second->toString() + ", \n" + "\n} ";
            }
            return ret;
        }
    };
    
    Value* parse(const std::string &str);
}


#endif