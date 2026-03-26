#include "Encoder.h"

Encoder::Encoder(uint32_t frequency, uint8_t frameDuration):
	frequency(frequency), 
	frameDuration(frameDuration){

	int err;
	encoder = opus_encoder_create(frequency, 1, OPUS_APPLICATION_RESTRICTED_LOWDELAY, &err);
	if (err != OPUS_OK) {
		throw "[ERROR] Encoder creation failed.";
	}

}

int Encoder::encode(std::vector<opus_int16> in, std::vector<unsigned char> out) {
	uint16_t maxPacketSize = 3000;
	uint16_t frameSize = (static_cast<float>(frequency) / 1000) * frameDuration;

	std::vector<opus_int16> pcm;
	std::vector<unsigned char> compressed(maxPacketSize);
	int len = opus_encode(encoder, pcm.data(), frameSize, compressed.data(), maxPacketSize);
	return len;
}

Encoder::~Encoder() {
	opus_encoder_destroy(encoder);
}