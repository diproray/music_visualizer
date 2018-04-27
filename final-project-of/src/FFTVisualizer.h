//
//  FFTVisualizer.h
//  final-project-of
//
//  Created by Dipro Ray on 4/27/18.
//

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAudioAnalyzer.h"
#include "ofSoundPlayerExtended.h"
#include <iostream>

#ifndef FFTVisualizer_h
#define FFTVisualizer_h

class FFTVisualizer {
    
    ofxAudioAnalyzer audio_analyzer_;
    
    ofSoundBuffer sound_buffer_;
    
    std::vector<float> sound_spectrum_;
    
    ofPolyline time_waveform_;
    
    int sample_rate_;
    
    int number_of_bands_;
    
  public:
    
    FFTVisualizer() noexcept;
    
    void updateValuesForFFTVisualizer(ofSoundBuffer sound_buffer);
    
    void drawWaveformAndFrequencyBars();
    
    int getNumberOfBands();
    
};

#endif /* FFTVisualizer_h */
