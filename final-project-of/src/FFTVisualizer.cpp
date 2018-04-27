//
//  FFTVisualizer.cpp
//  final-project-of
//
//  Created by Dipro Ray on 4/27/18.
//

#include <stdio.h>
#include "FFTVisualizer.h"

/**
 * Constructor for an FFTVisualizer object that initializes
 * resources for the object
 */
FFTVisualizer::FFTVisualizer() noexcept {
    
    // Set the music sample rate to the default, commonly used value - 44,100.
    sample_rate_ = 44100;
    
    // Set the number of bands to 1024.
    //
    // You might notice that I am using 1024 bands instead of the usual 256 bands.
    // This is because, since I have more space for the visualization, I wish to make it more detailed
    // and accurate.
    
    number_of_bands_ = 1024;
    
    // The number of audio channels of the music.
    // It is set to 2. (The left and right channel.)
    //
    // Note that, I only use 1 channel for my visualization currently.
    
    int number_of_channels = 2;
    
    // Set up the audio analyzer (the ofxAddon which uses the Essentia Music Library).
    
    audio_analyzer_.setup(sample_rate_, number_of_bands_, number_of_channels);
    
}

/**
 * The following function updates all the values for
 * the FFT visualizer.
 *
 * @param sound_buffer - the sound buffer which
 *                              contains sound for the moment, to be updated with
 */
void FFTVisualizer::updateValuesForFFTVisualizer(ofSoundBuffer sound_buffer) {
    
    // Let the audio analyzer analyze the current sound buffer.
    audio_analyzer_.analyze(sound_buffer);
    
    // From the analyzer, get the sound spectrum.
    sound_spectrum_ = audio_analyzer_.getValues(SPECTRUM, 0);
    
    // Clear the current time waveform line structure.
    time_waveform_.clear();
    
    // For each sample within the buffer,
    // set a new x and y coordinate for that vertex in the time waveform.
    
    for(int index = 0; index < sound_buffer.getNumFrames(); index += 4) {
        
        // Get the sample at the current index from the first channel.
        float sample = sound_buffer.getSample(index, 0);
        
        // Assign x and y coordinates for the vertex.
        
        float x = ofMap(index, 0, sound_buffer.getNumFrames(), 0, ofGetWidth());
        float y = ofMap(sample, - 0.375, 0.375, 0, ofGetHeight() * 0.5) + (ofGetHeight() * 0.5);
        
        // Add the vertex to the waveform structure.
        time_waveform_.addVertex(x, y);
    }
    
}

/**
 * The following function is responsible for drawing
 * the time waveform and associated
 * frequency bars.
 */
void FFTVisualizer::drawWaveformAndFrequencyBars() {
    
    // Set the background color to gray.
    ofBackground(34, 34, 34);
    
    // Set line width to 2.5 for the waveform.
    ofSetLineWidth(2.5);
    
    // Set color to dark blue for drawing the waveform.
    ofSetColor(51, 51, 255);
    
    // Draw the time waveform.
    time_waveform_.draw();
    
    // Get the width of the screen.
    int length_of_frequency_bar_plot = ofGetWidth();
    
    // Store the coordinate system, then shift it.
    ofPushMatrix();
    ofTranslate(0, 50);
    
    // Set the color to light green.
    ofSetColor(51, 255, 187);
    
    // Decide the width of each bar to be drawn.
    float bar_width = (float) length_of_frequency_bar_plot / sound_spectrum_.size();
    
    // For each band, compute a bar height, then draw it.
    
    for (int band_number = 0; band_number < sound_spectrum_.size(); band_number++){
        
        // Compute the bar height.
        
        float height_multiplier = ofMap(sound_spectrum_[band_number ], DB_MIN, DB_MAX, 0.0, 1.0, true);
        float bar_height = (- 1.25) * (height_multiplier * ofGetHeight()/2);
        
        // Draw the bar.
        
        ofDrawRectangle(band_number * bar_width, ofGetHeight()/2, bar_width, bar_height);
        
    }
    
    // Restore original coordinate system.
    ofPopMatrix();
    
    // Draw a separating line between the waveform and bars plot.
    
    ofSetColor(100);
    ofDrawLine(0, ofGetHeight()/2 + 50, ofGetWidth(), ofGetHeight()/2 + 50);
    
    // Display Time Waveform and Frequency Waveform for the respective visualizations.
    
    // First, load the font.
    
    ofTrueTypeFont temporary_font_loader_;
    temporary_font_loader_.load("helvetica.ttf", 10);
    
    // Then, display the messages.
    
    ofSetColor(255, 255, 255);
    temporary_font_loader_.drawString("Frequency Waveform", 10, 20);
    temporary_font_loader_.drawString("Time Waveform", 10, 20 + ofGetHeight()/2 + 50);
    
}

/**
 * Getter for the number of bands of the visualizer.
 */
int FFTVisualizer::getNumberOfBands() {
    
    return number_of_bands_;
    
}
