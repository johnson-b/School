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
        
        virtual std::string printPretty(int) = 0;
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
        
        virtual std::string printPretty(int tab) {
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
        
        virtual std::string printPretty(int tab) {
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
        
        virtual std::string printPretty(int tab) {
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
        
        virtual std::string printPretty(int tab) {
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
        virtual std::string printPretty(int tab) {
            std::string s(tab, '\t');
            for(std::vector<Value*>::iterator it = this->begin(); it != this->end(); ++it) {
                ret += (*it)->printPretty(tab);
                ret += ", \n";
            }
            ret += s;
            ret += "]";
            return ret;
        }
    };
    
    using Pair = std::pair<std::string, Value*>;
    
    struct Object : std::map<std::string, Value*>, Value{
        std::string ret = "{ \n";
        Object() {
            type = OBJECT;
        }
        
        virtual std::string printPretty(int tab) {
            ++tab;
            std::string s(tab, '\t');
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
    
    Value* parse(const std::string &str);
}


#endif