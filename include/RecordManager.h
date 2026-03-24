#pragma once
#include "portaudio.h"

class RecordManager {
private:
	PaStream* stream ;

public:
	static PaStreamCallback callback;

	int start(PaDeviceIndex inDeviceId, PaDeviceIndex outDeviceId);
	int stop();

	RecordManager();
	~RecordManager();
};

