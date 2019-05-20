#include <string.h>
#include <stdint.h>
#include <iostream>

#include "settings.h"
#include "unittest/test.h"

int nextMultipleOfBlockSize(unsigned int input) {
    return (input + (BLOCK_SIZE-1)) & ~(BLOCK_SIZE-1);
}

int main(int argc, const char* argv[]){

    if(! runTests())
    {
        std::cout << "tests failed!";
        return 1;
    }
    else {
    	std::cout << "unittests successfull!";
    }

    std::cout << "All tests passed, YAAAYYY!";
    return 0;
}
