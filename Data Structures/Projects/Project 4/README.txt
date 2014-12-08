In order to run the huffman tree, you must be running c++ 11. This can be done either using command line or cmake. The inputted string should be via command line. The two available options to run this program are below:

Option A:
	g++ -std=c++11 main.cpp
	./a.out MISSISSIPPI

Option B:
	mkdir build
	cd build
	cmake ..
	make
	./huffman MISSISSIPPI
