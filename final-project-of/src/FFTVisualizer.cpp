//
//  FFTVisualizer.cpp
//  final-project-of
//
//  Created by Dipro Ray on 4/27/18.
//

#include <stdio.h>
#include "FFTVisualizer.h"

FFTVisualizer::FFTVisualizer() noexcept {
    
    sample_rate_ = 44100;
    
    number_of_bands_ = 1024;
    
    int number_of_channels = 2;
    
    audio_analyzer_.setup(sample_rate_, number_of_bands_, number_of_channels);
    
}

void FFTVisualizer::updateValuesForFFTVisualizer(ofSoundBuffer sound_buffer) {
    
    audio_analyzer_.analyze(sound_buffer);
    sound_spectrum_ = audio_analyzer_.getValues(SPECTRUM, 0);
    
    time_waveform_.clear();
    
    for(size_t i = 0; i < sound_buffer.getNumFrames(); i += 4) {
        
        float sample = sound_buffer.getSample(i, 0);
        float x = ofMap(i, 0, sound_buffer.getNumFrames(), 0, ofGetWidth());
        float y = ofMap(sample, -0.375, 0.375, 0, ofGetHeight() * 0.5) + ofGetHeight()*0.5;
        time_waveform_.addVertex(x, y);
    }
    
}

void FFTVisualizer::drawWaveformAndFrequencyBars() {
    
    ofBackground(34, 34, 34);
    
    ofSetLineWidth(2.5);
    ofSetColor(51, 51, 255);
    
    time_waveform_.draw();
    
    int length_of_frequency_bar_plot = ofGetWidth();
    
    ofPushMatrix();
    ofTranslate(0, 50);
    
    ofSetColor(51, 255, 187);
    
    float bar_width = (float) length_of_frequency_bar_plot / sound_spectrum_.size();
    
    for (int band_number = 0; band_number < sound_spectrum_.size(); band_number++){
        
        float height_multiplier = ofMap(sound_spectrum_[band_number ], DB_MIN, DB_MAX, 0.0, 1.0, true);
        float bar_height = (- 1.25) * (height_multiplier * ofGetHeight()/2);
        
        ofDrawRectangle(band_number * bar_width, ofGetHeight()/2, bar_width, bar_height);
        
    }
    
    ofPopMatrix();
    
    ofSetColor(100);
    ofDrawLine(0, ofGetHeight()/2 + 50, ofGetWidth(), ofGetHeight()/2 + 50);
    ofSetColor(255);
}

int FFTVisualizer::getNumberOfBands() {
    return number_of_bands_;
}
