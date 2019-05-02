bool run_IoTests();
bool test_appendCompressedChunk_noOffset();
bool test_appendCompressedChunk_offset();

bool test_appendOpcode_noOffset();
bool test_appendOpcode_offset();
bool test_appendOpcode_overlappingOffset();
bool test_appendOpcode_onlyLow();
bool test_appendOpcode_offsetLow();
bool test_appendCompressedChunk_onlyLow();
bool test_appendOpcodeAndChunk();

bool test_readCompressedChunk_noOffset();
bool test_readCompressedChunk_offset();
