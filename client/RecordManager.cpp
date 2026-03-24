#include <iostream>
#include <string>
#include "RecordManager.h"


AudioSystem::AudioSystem() {
    int err = Pa_Initialize();
    if (err < 0) {
        throw std::runtime_error("[ERROR] PortAudio initialization failed with error: " + std::string(Pa_GetErrorText(err)));
    }
}

AudioSystem::~AudioSystem() {
    Pa_Terminate();
}

RecordManager::RecordManager(PaDeviceIndex inDeviceId, PaDeviceIndex outDeviceId) {
    const PaDeviceInfo* inDevice = Pa_GetDeviceInfo(inDeviceId);
    const PaDeviceInfo* outDevice = Pa_GetDeviceInfo(outDeviceId);

    if (inDevice == nullptr) {
        throw  std::runtime_error("[ERROR] Unknown input device.");
    }
    if (outDevice == nullptr) {
        throw  std::runtime_error("[ERROR] Unknown output device.");
    }

    PaStreamParameters inParams;
    inParams.device = inDeviceId;
    inParams.channelCount = 1;
    inParams.hostApiSpecificStreamInfo = NULL;
    inParams.sampleFormat = paInt16;
    inParams.suggestedLatency = inDevice->defaultLowInputLatency;

    PaStreamParameters outParams;
    outParams.device = outDeviceId;
    outParams.channelCount = 1;
    outParams.hostApiSpecificStreamInfo = NULL;
    outParams.sampleFormat = paInt16;
    outParams.suggestedLatency = outDevice->defaultLowOutputLatency;

    int err = Pa_OpenStream(&stream, &inParams, &outParams, 44100, 256, paNoFlag, callback, nullptr);
    if (err < 0) {
        throw std::runtime_error("[ERROR] Stream opening failed with error: " + std::string(Pa_GetErrorText(err)));
    }
}

int RecordManager::start() {
    int err = Pa_StartStream(stream);
    if (err < 0) {
        throw std::runtime_error("[ERROR] Stream starting failed with error: " + std::string(Pa_GetErrorText(err)));
    }

    return 0;
}

int RecordManager::stop() {
    if (stream) {
        if (Pa_IsStreamActive(stream) == 1) {
            int err = Pa_StopStream(stream);
            if (err < 0) {
                throw std::runtime_error("[ERROR] Stream stopped with error: " + std::to_string(err));
            }
        }
    }

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
    return paContinue;
}

RecordManager::~RecordManager() {
    if (stream) {
        if (Pa_IsStreamActive(stream) == 1) {
            int err = Pa_StopStream(stream);
            if (err < 0) {
                throw std::runtime_error("[ERROR] Stream stop failed with error: " + std::to_string(err));
            }
        }
        int err = Pa_CloseStream(stream);
        if (err < 0) {
            throw std::runtime_error("[ERROR] Stream close failed with error: " + std::to_string(err));
        }
    }
}