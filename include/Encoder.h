#pragma once
#include "opus.h"
#include <vector>

class Encoder {
private:
	OpusEncoder* encoder;

public:
	int encode(opus_int16*, std::vector<unsigned char>);

	Encoder();
	~Encoder();
};