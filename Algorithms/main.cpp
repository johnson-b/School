#include "BigIntBase.h"	
#include <assert.h>
#include <cmath>

int main(int argc, const char * argv[]) {

	if(argc == 1) {
		std::cout << "Invalid argument" << std::endl;
	}

	if(argc == 2) {
		std::cout << BigIntBase::randomPrime(atoi(argv[1])) << std::endl;	
	}

    return 0;
}