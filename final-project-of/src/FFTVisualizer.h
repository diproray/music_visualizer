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

/**
 * Class that models an FFT, time and frequency waveform visualization.
 */
class FFTVisualizer {
    
    ofxAudioAnalyzer audio_analyzer_; // the audio analyzer that obtains frequency band values and spectrum
    
    std::vector<float> sound_spectrum_; // the float array storing the sound spectrum values
    
    ofPolyline time_waveform_; // the line structure storing the current time waveform
    
    int sample_rate_; // the sample rate of the music
    
    int number_of_bands_; // the number of bands for the music spectrum
    
  public:
    
    /**
     * Constructor for an FFTVisualizer object that initializes
     * resources for the object
     */
    FFTVisualizer() noexcept;
    
   /**
    * The following function updates all the values for
    * the FFT visualizer.
    *
    * @param sound_buffer - the sound buffer which
    *                              contains sound for the moment, to be updated with
    */
    void update(ofSoundBuffer sound_buffer);
    
    /**
     * The following function is responsible for drawing
     * the time waveform and associated
     * frequency bars.
     */
    void draw();
    
    /**
     * Getter for the number of bands of the visualizer.
     */
    int getNumberOfBands();
    
};

#endif /* FFTVisualizer_h */
