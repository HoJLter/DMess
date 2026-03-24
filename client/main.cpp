#include <iostream>
#include <string>
#include "RecordManager.h"

 
int main() {
    try {
        AudioSystem audioSystem;
        auto input = Pa_GetDefaultInputDevice();
        auto output = Pa_GetDefaultOutputDevice();

        RecordManager recorder(input, output);
        recorder.start();
        std::cin.get();
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
    }
}