# Makefile for request_srcml() problem
#
# To build:
#   make
#
# To clean build:
#   make clean
#
# To test both get_language_from_filename() and request_srcml_t
#   make test

all : request_srcml_t get_language_from_filename_t

# main program
request_srcml_t : request_srcml_t.o request_srcml.o generate_srcml.o get_language_from_filename.o
	g++ request_srcml_t.o request_srcml.o generate_srcml.o get_language_from_filename.o -o request_srcml_t

request_srcml_t.o : request_srcml_t.cpp
	g++ -c request_srcml_t.cpp

request_srcml.o : request_srcml.cpp request_srcml.hpp generate_srcml.hpp
	g++ -c request_srcml.cpp

generate_srcml.o : generate_srcml.cpp generate_srcml.hpp
	g++ -c generate_srcml.cpp

# test program for get_language_from filename
get_language_from_filename_t : get_language_from_filename_t.o get_language_from_filename.o
	g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

get_language_from_filename.o : get_language_from_filename.cpp get_language_from_filename.hpp
	g++ -c get_language_from_filename.cpp

get_language_from_filename_t.o : get_language_from_filename_t.cpp get_language_from_filename.hpp
	g++ -c get_language_from_filename_t.cpp

clean :
	rm -f request_srcml_t.o request_srcml_t get_language_from_filename.o get_language_from_filename_t.o get_language_from_filename_t generate_srcml.o request_srcml.o


test : get_language_from_filename_t request_srcml_t
	./get_language_from_filename_t
	./request_srcml_t
