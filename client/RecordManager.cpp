#include <iostream>
#include "RecordManager.h"


RecordManager::RecordManager() {
	int err = Pa_Initialize();
	if (err < 0) {
		throw std::runtime_error("[ERROR] PortAudio initialization failed with error: " + std::string(Pa_GetErrorText(err)));
	}
}

int RecordManager::start(PaDeviceIndex inDeviceId, PaDeviceIndex outDeviceId) {
    const PaDeviceInfo* inDevice = Pa_GetDeviceInfo(inDeviceId);
    const PaDeviceInfo* outDevice = Pa_GetDeviceInfo(inDeviceId);

    if (outDevice == nullptr) {
        throw  std::runtime_error("[ERROR] Unknown output device.");
    }
    if (inDevice == nullptr) {
        throw  std::runtime_error("[ERROR] Unknown input device.");
    }

    PaStreamParameters iparams;
    iparams.device = inDeviceId;
    iparams.channelCount = 1;
    iparams.hostApiSpecificStreamInfo = NULL;
    iparams.sampleFormat = paInt16;
    iparams.suggestedLatency = inDevice->defaultLowInputLatency;

    PaStreamParameters oparams;
    oparams.device = outDeviceId;
    oparams.channelCount = 1;
    oparams.hostApiSpecificStreamInfo = NULL;
    oparams.sampleFormat = paInt16;
    oparams.suggestedLatency = outDevice->defaultLowOutputLatency;

    int err = Pa_OpenStream(&stream, &iparams, &oparams, 44100, 256, paNoFlag, callback, nullptr);
    if (err < 0) {
        throw std::runtime_error("[ERROR] Stream opening failed with error: " + std::string(Pa_GetErrorText(err)));
    }


    err = Pa_StartStream(stream);
    if (err < 0) {
        throw std::runtime_error("[ERROR] Stream starting failed with error: " + std::string(Pa_GetErrorText(err)));
    }

    return 0;
}

int RecordManager::stop() {
    Pa_StopStream(stream);
    return 0;
}

int RecordManager::callback(
    const void* input, void* output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {

    int16_t* in = (int16_t*)input;
    int16_t* out = (int16_t*)output;

    for (int i = 0; i < frameCount; i++) {
        out[i] = in[i];
    }
    return 0;
}

RecordManager::~RecordManager() {
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
}