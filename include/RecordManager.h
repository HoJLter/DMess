#pragma once
#include "portaudio.h"

class AudioSystem {
public:
	AudioSystem();
	~AudioSystem();
};

class RecordManager {
private:
	PaStream* stream = nullptr;

public:
	static PaStreamCallback callback;

	int start();
	int stop();

	RecordManager(PaDeviceIndex inDeviceId, PaDeviceIndex outDeviceId);
	~RecordManager();
};

