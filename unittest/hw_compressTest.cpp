#include <cstdlib>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//#include "sds_lib.h"

#include "../hw842.h"
#include "tools.h"
#include "../settings.h"

bool test_hw842_compress_smallInput() {

	auto inputBuffer = (ap_uint<8>*) malloc(BLOCK_SIZE * sizeof(ap_uint<8>));

    //        11100001  00100001  01000001  01100001  10000001  10100001  11000001  11100010
    inputBuffer[0] = 225;
    inputBuffer[1] = 33;
    inputBuffer[2] = 65;
    inputBuffer[3] = 97;
    inputBuffer[4] = 129;
    inputBuffer[5] = 161;
    inputBuffer[6] = 193;
    inputBuffer[7] = 226;
    inputBuffer[8] = 225;
    inputBuffer[9] = 33;
    inputBuffer[10] = 65;
    inputBuffer[11] = 97;
    inputBuffer[12] = 129;
    inputBuffer[13] = 161;
    inputBuffer[14] = 193;
    inputBuffer[15] = 226;

    auto expectedResult = (ap_uint<8>*) malloc(BLOCK_SIZE * sizeof(ap_uint<8>));

    //  00000|111 00001|001 00001|010 00001|011 00001|100 00001|101 00001|110 00001|111 00010|000
    // opcode|      chunk
    expectedResult[0] = 7;
    expectedResult[1] = 9;
    expectedResult[2] = 10;
    expectedResult[3] = 11;
    expectedResult[4] = 12;
    expectedResult[5] = 13;
    expectedResult[6] = 14;
    expectedResult[7] = 15;
    expectedResult[8] = 16;
    expectedResult[9] = 56;
    expectedResult[10] = 72;
    expectedResult[11] = 80;
    expectedResult[12] = 88;
    expectedResult[13] = 96;
    expectedResult[14] = 104;
    expectedResult[15] = 112;
    expectedResult[16] = 120;
    expectedResult[17] = 128;
    expectedResult[18] = 0;

    auto outputBuffer = (ap_uint<8>*) malloc(BLOCK_SIZE * sizeof(ap_uint<8>));

    for(int i = 0; i < 64; i++) {
    	outputBuffer[i] = 0;
    }

    hw842_compress(inputBuffer, outputBuffer, BLOCK_SIZE);
    return assertArraysAreEqual(outputBuffer, expectedResult, BLOCK_SIZE);
}

bool test_hw842_decompress_smallInput() {

	auto inputBuffer = (ap_uint<8>*) malloc(BLOCK_SIZE * sizeof(ap_uint<8>));
    //  00000|111 00001|001 00001|010 00001|011 00001|100 00001|101 00001|110 00001|111 00010|000      00111|000 01001|000 01010|000 01011|000 01100|000 01101|000 01110|000 01111|000 10000|000
    // opcode|      chunk																					56      72		  80		88			96		104			112		120			128
	memset(inputBuffer, 0, sizeof(BLOCK_SIZE * sizeof(ap_uint<8>)));
    inputBuffer[0] = 7;
    inputBuffer[1] = 9;
    inputBuffer[2] = 10;
    inputBuffer[3] = 11;
    inputBuffer[4] = 12;
    inputBuffer[5] = 13;
    inputBuffer[6] = 14;
    inputBuffer[7] = 15;
    inputBuffer[8] = 16;
    inputBuffer[9] = 56;
    inputBuffer[10] = 72;
    inputBuffer[11] = 80;
    inputBuffer[12] = 88;
    inputBuffer[13] = 96;
    inputBuffer[14] = 104;
    inputBuffer[15] = 112;
    inputBuffer[16] = 120;
    inputBuffer[17] = 128;
    inputBuffer[18] = 0;

    auto expectedResult = (ap_uint<8>*) malloc(BLOCK_SIZE * sizeof(ap_uint<8>));
    //        11100001  00100001  01000001  01100001  10000001  10100001  11000001  11100010
    memset(expectedResult, 0, BLOCK_SIZE * sizeof(ap_uint<8>));
    expectedResult[0] = 225;
    expectedResult[1] = 33;
    expectedResult[2] = 65;
    expectedResult[3] = 97;
    expectedResult[4] = 129;
    expectedResult[5] = 161;
    expectedResult[6] = 193;
    expectedResult[7] = 226;
    expectedResult[8] = 225;
    expectedResult[9] = 33;
    expectedResult[10] = 65;
    expectedResult[11] = 97;
    expectedResult[12] = 129;
    expectedResult[13] = 161;
    expectedResult[14] = 193;
    expectedResult[15] = 226;

    auto outputBuffer = (ap_uint<8>*) malloc(BLOCK_SIZE * sizeof(ap_uint<8>));
    memset(outputBuffer, 0, BLOCK_SIZE * sizeof(ap_uint<8>));

    hw842_decompress(&inputBuffer[0], &outputBuffer[0], BLOCK_SIZE);

    return assertArraysAreEqual(outputBuffer, expectedResult, BLOCK_SIZE);
}

bool test_compress_decompress_withRandomData() {
	// declare databuffers
	auto inputBuffer = (ap_uint<8>*) malloc(BLOCK_SIZE * sizeof(ap_uint<8>));
	auto expectedResult = (ap_uint<8>*) malloc(2 * BLOCK_SIZE * sizeof(ap_uint<8>));
    auto intermediateBuffer = (ap_uint<8>*) malloc(BLOCK_SIZE * sizeof(ap_uint<8>));
    auto outputBuffer = (ap_uint<8>*) malloc(BLOCK_SIZE * sizeof(ap_uint<8>));

    // zero initialise data buffers
    memset(inputBuffer, 0, BLOCK_SIZE * sizeof(ap_uint<8>));
    memset(outputBuffer, 0, BLOCK_SIZE * sizeof(ap_uint<8>));
    memset(intermediateBuffer, 0, BLOCK_SIZE * sizeof(ap_uint<8>));
    memset(expectedResult, 0, BLOCK_SIZE * sizeof(ap_uint<8>));

    srand (time(NULL));

    // set random input buffer
    for(int i = 0; i < BLOCK_SIZE; i++) {
    	inputBuffer[i] = expectedResult[i] = rand();
    }

    hw842_compress(inputBuffer, intermediateBuffer, BLOCK_SIZE);
    hw842_decompress(intermediateBuffer, outputBuffer, BLOCK_SIZE);

    return assertArraysAreEqual(outputBuffer, expectedResult, BLOCK_SIZE);
}

bool run_hw_compressTests() {
    return      test_hw842_compress_smallInput()
            &&  test_hw842_decompress_smallInput()
			&&	test_compress_decompress_withRandomData();
}
