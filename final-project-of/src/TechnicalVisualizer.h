//
//  TechnicalVisualizer.h
//  final-project-of
//
//  Created by Dipro Ray on 5/2/18.
//

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAudioAnalyzer.h"
#include "ofSoundPlayerExtended.h"
#include <iostream>

#ifndef TechnicalVisualizer_h
#define TechnicalVisualizer_h

/**
 * Class that models an technical visualization.
 */
class TechnicalVisualizer {
    
    ofxAudioAnalyzer audio_analyzer_; // the audio analyzer that obtains frequency band values and spectrum
    
    int sample_rate_; // the sample rate of the music
    
    int number_of_bands_; // the number of bands for the music spectrum
    
    std::vector<float> sound_spectrum_; // the float array storing the sound spectrum values
    
    std::vector<float> hpcp_; // the float array storing a Harmonic Pitch Class Profile (HPCP), that is a k*12 dimensional vector which
                              // represents the intensities of the twelve (k==1) semitone pitch classes
    
    std::vector<float> tristimulus_; // the float array storing the tristimulus of a signal given its harmonic peaks
    
    std::vector<float> mel_bands_; // the float array storing the frequency/intensity values for each mel band
    std::vector<float> mfcc_; // the float array storing the mel-frequency cepstrum coefficients
    
    float smoothing_value_; // the smoothing value for the different computations
    
    float rms_; // RMS value of the music
    float rms_normalized_;
    
    float power_; // the power value of the music
    
    float pitch_frequency_; // the pitch frequency of the music
    float pitch_frequency_normalized_;
    
    float pitch_confidence_; // the pitch confidence of the music
    
    float hfc_; // the HFC of the music
    float hfc_normalized_;
    
    float odd_to_even_harmonic_ratio_; // the odd to even harmonic enery ratio of the music
    float odd_to_even_harmonic_ratio_normalized_;
    
    float inharmonicity_; // the inharmonicity of the music
    float dissonance_; // the dissonance of the music
    
    float strong_peak_; // the strong peak of the music
    float strong_peak_normalized_;
    
    float strong_decay_; // the strong decay of the music
    float strong_decay_normalized_;
    
public:
    
    /**
     * Constructor for an TechnicalVisualizer object that initializes
     * resources for the object
     */
    TechnicalVisualizer() noexcept;
    
    /**
     * The following function updates all the values for
     * the Technical visualizer.
     *
     * @param sound_buffer - the sound buffer which
     *                              contains sound for the moment, to be updated with
     */
    void update(ofSoundBuffer sound_buffer);
    
    /**
     * The following function is responsible for drawing
     * the technical visualization.
     */
    void draw();
    
    /**
     * Getter for the number of bands of the visualizer.
     */
    int getNumberOfBands();
    
    /**
     * Helper function to draw plots.
     */
    void drawPlot(const std::vector<float> & values,
                                       int graph_width, int graph_height,
                                       int x, int y, bool should_scale, bool is_mfcc);
    
    
    /**
     * Helper function to draw bars.
     */
    void drawBar(float value, int x, int y, int bar_width, int bar_height);
    
};

#endif /* TechnicalVisualizer_h */
