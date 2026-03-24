#include <iostream>
#include <string>
#include "RecordManager.h"

 
int main() {
    try {
        RecordManager recorder;

        auto in = Pa_GetDefaultInputDevice();
        auto out = Pa_GetDefaultOutputDevice();

        recorder.start(in, out);
        std::cin.get();
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
    }
}