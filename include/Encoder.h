#pragma once
#include "opus.h"
#include <vector>

#include <iostream>
#include "opus.h"
#include "vector"
int main() {

}

class Encoder {
private:
	OpusEncoder* encoder;
	uint32_t frequency;
	uint8_t frameDuration;

public:
	int encode(std::vector<opus_int16> in, std::vector<unsigned char> out);

	Encoder(uint32_t frequency, uint8_t frameDuration);
	~Encoder();
};