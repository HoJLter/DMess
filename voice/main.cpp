#include <iostream>
#include <string>
#include "portaudio.h"


int callback(
    const void* input, void* output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {
    
    int16_t* in = (int16_t*)input;
    int16_t* out = (int16_t*)output;

    for (int i = 0; i < frameCount; i++) {
        out[i] = in[i];
        std::cout << out[i];
    }
    return 0;
}


int opening() {
    int err = Pa_Initialize();
    if (err < 0) {
        throw std::runtime_error("[ERROR] PortAudio initialization failed with error: " + std::string(Pa_GetErrorText(err)));
    }

    PaStreamParameters iparams;
    iparams.device = Pa_GetDefaultInputDevice();
    iparams.channelCount = 1;
    iparams.hostApiSpecificStreamInfo = NULL;
    iparams.sampleFormat = paInt16;
    iparams.suggestedLatency = 0.1;

    PaStreamParameters oparams;
    oparams.device = Pa_GetDefaultOutputDevice();
    oparams.channelCount = 1;
    oparams.hostApiSpecificStreamInfo = NULL;
    oparams.sampleFormat = paInt16;
    oparams.suggestedLatency = 0.1;

    PaStream* stream;

    struct CallbackData {

    } cbData;

    err = Pa_OpenStream(&stream, &iparams, &oparams, 44100, 256, paNoFlag, &callback, &cbData);

    if (err < 0) {
        throw std::runtime_error("[ERROR] Stream opening failed with error: " + std::string(Pa_GetErrorText(err)));
    }
    err = Pa_StartStream(stream);
    if (err < 0) {
        throw std::runtime_error("[ERROR] Stream starting failed with error: " + std::string(Pa_GetErrorText(err)));
    }

    auto a = Pa_GetDeviceInfo((Pa_GetDefaultInputDevice()));

    std::cin.get(); // подождать
    Pa_StopStream(stream);
    Pa_Terminate();

    return 0;
}

int main() {
    try {
        opening();
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
    }
}