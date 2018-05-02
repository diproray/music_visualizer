//
//  TechnicalVisualizer.cpp
//  final-project-of
//
//  Created by Dipro Ray on 5/2/18.
//

#include <stdio.h>
#include "TechnicalVisualizer.h"

/**
 * Constructor for an TechnicalVisualizer object that initializes
 * resources for the object
 */
TechnicalVisualizer::TechnicalVisualizer() noexcept {
    
    // Set smoothing to zero intially.
    smoothing_value_ = 0;
    
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
 * Getter for the number of bands of the visualizer.
 */
int TechnicalVisualizer::getNumberOfBands() {
    
    return number_of_bands_;
    
}

/**
 * The following function updates all the values for
 * the Technical visualizer.
 *
 * @param sound_buffer - the sound buffer which
 *                              contains sound for the moment, to be updated with
 */
void TechnicalVisualizer::update(ofSoundBuffer sound_buffer) {
    
    // Let the audio analyzer analyze the current sound buffer.
    audio_analyzer_.analyze(sound_buffer);
    
    // From the analyzer, get all the required values..
    
    sound_spectrum_ = audio_analyzer_.getValues(SPECTRUM, 0, smoothing_value_);
    
    tristimulus_ = audio_analyzer_.getValues(TRISTIMULUS, 0, smoothing_value_);
    
    mel_bands_ = audio_analyzer_.getValues(MEL_BANDS, 0, smoothing_value_);
    mfcc_ = audio_analyzer_.getValues(MFCC, 0, smoothing_value_);
    
    hpcp_ = audio_analyzer_.getValues(HPCP, 0, smoothing_value_);
    
    rms_ = audio_analyzer_.getValue(RMS, 0, smoothing_value_);
    rms_normalized_ = audio_analyzer_.getValue(RMS, 0, smoothing_value_, TRUE);
    
    power_ = audio_analyzer_.getValue(POWER, 0, smoothing_value_);
    
    pitch_frequency_ = audio_analyzer_.getValue(PITCH_FREQ, 0, smoothing_value_);
    pitch_frequency_normalized_ = audio_analyzer_.getValue(PITCH_FREQ, 0, smoothing_value_, TRUE);
    
    pitch_confidence_ = audio_analyzer_.getValue(PITCH_CONFIDENCE, 0, smoothing_value_);
    
    hfc_ = audio_analyzer_.getValue(HFC, 0, smoothing_value_);
    hfc_normalized_ = audio_analyzer_.getValue(HFC, 0, smoothing_value_, TRUE);
    
    odd_to_even_harmonic_ratio_ = audio_analyzer_.getValue(ODD_TO_EVEN, 0, smoothing_value_);
    odd_to_even_harmonic_ratio_normalized_ = audio_analyzer_.getValue(ODD_TO_EVEN, 0, smoothing_value_, TRUE);
    
    inharmonicity_ = audio_analyzer_.getValue(INHARMONICITY, 0, smoothing_value_);
    dissonance_ = audio_analyzer_.getValue(DISSONANCE, 0, smoothing_value_);
    
    strong_peak_ = audio_analyzer_.getValue(STRONG_PEAK, 0, smoothing_value_);
    strong_peak_normalized_ = audio_analyzer_.getValue(STRONG_PEAK, 0, smoothing_value_, TRUE);
    
    strong_decay_ = audio_analyzer_.getValue(STRONG_DECAY, 0, smoothing_value_);
    strong_decay_normalized_ = audio_analyzer_.getValue(STRONG_DECAY, 0, smoothing_value_, TRUE);
}

/**
 * The following function is responsible for drawing
 * the technical visualization
 */
void TechnicalVisualizer::draw() {
    
    int left_column_x_offset = 10;
    int initial_plot_y_position = 15;
    
    // Set a width and height for all graphs/plots
    int graph_width = 450;
    int graph_height = 150;
    
    int plot_y_offset = graph_height + 50;
    
    // First, load the font to be used.
    
    ofTrueTypeFont temporary_font_loader_;
    temporary_font_loader_.load("helvetica.ttf", 10);
    
    // Set the background color to light gray.
    //ofBackground(240,240,240);
    
    ofBackground(34, 34, 34);
    
    // Set drawing color to dark blue.
    ofSetColor(255, 105, 180);
    
    // For each plot/bar,
    // translate the coordinate system to the desired point.
    // Draw the plot/bar.
    // Restore the original system.
    
    // Do this for all technical qualities being visualized.
    // Unfrotunately, there isn't a simpler way to do this due to the way openFrameworks works, so I can't put repeated code (which
    // shifts coordinates and changes value normalizations) in a loop.
    
    drawPlot(sound_spectrum_, graph_width, graph_height, left_column_x_offset,
             initial_plot_y_position, true, false);
    
    drawPlot(tristimulus_, graph_width, graph_height, left_column_x_offset,
             initial_plot_y_position + plot_y_offset, false, false);
    
    drawPlot(mel_bands_, graph_width, graph_height, left_column_x_offset,
             initial_plot_y_position + 2 * plot_y_offset, true, false);
    
    drawPlot(mfcc_, graph_width, graph_height, left_column_x_offset,
             initial_plot_y_position + 3 * plot_y_offset - ((plot_y_offset - graph_height) / 2),
             true, true);
    
    ofPushMatrix();
    
    int right_column_x_offset = 550;
    int right_column_initial_y_offset = 30;
    
    ofTranslate(left_column_x_offset + right_column_x_offset, right_column_initial_y_offset + initial_plot_y_position);
    
    float bar_width = (float) graph_width / hpcp_.size();
    
    for (int index = 0; index < hpcp_.size(); index++){
        
        float scaled_value = hpcp_[index];
        
        float bar_height = (- 1) * scaled_value * graph_height;
        ofDrawRectangle(index * bar_width, graph_height, bar_width, bar_height);
    }
    
    ofPopMatrix();
    
    int bar_height = 20;
    int bar_y_offset = 50;
    
    drawBar(rms_normalized_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset,
            graph_width, bar_height);
    
    drawBar(power_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + bar_y_offset,
            graph_width, bar_height);
    
    drawBar(pitch_frequency_normalized_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset
            + 2 * bar_y_offset,
            graph_width, bar_height);
    
    drawBar(pitch_confidence_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset
            + 3 * bar_y_offset,
            graph_width, bar_height);
    
    drawBar(hfc_normalized_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset
            + 4 * bar_y_offset,
            graph_width, bar_height);
    
    drawBar(odd_to_even_harmonic_ratio_normalized_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset
            + 5 * bar_y_offset,
            graph_width, bar_height);
    
    drawBar(inharmonicity_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset
            + 6 * bar_y_offset,
            graph_width, bar_height);
    
    drawBar(dissonance_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset
            + 7 * bar_y_offset,
            graph_width, bar_height);
    
    drawBar(strong_peak_normalized_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset
            + 8 * bar_y_offset,
            graph_width, bar_height);
    
    drawBar(strong_decay_normalized_,left_column_x_offset + right_column_x_offset,
            right_column_initial_y_offset + initial_plot_y_position + plot_y_offset
            + 9 * bar_y_offset,
            graph_width, bar_height);
    
    // After drawing all the visualizations, display the texts.
    
    ofSetColor(255, 255, 255);
    temporary_font_loader_.drawString("Spectrum: ", left_column_x_offset, initial_plot_y_position);
    
    temporary_font_loader_.drawString("Tristimulus: ", left_column_x_offset, initial_plot_y_position + plot_y_offset);
    
    temporary_font_loader_.drawString("Mel Bands: ", left_column_x_offset, initial_plot_y_position + 2 * plot_y_offset);
    
    temporary_font_loader_.drawString("MFCC: ", left_column_x_offset,
                                      initial_plot_y_position + 3 * plot_y_offset - ((plot_y_offset - graph_height) / 2));
    
    temporary_font_loader_.drawString("HPCP: ", left_column_x_offset + right_column_x_offset,
                                       right_column_initial_y_offset + initial_plot_y_position);
    
    temporary_font_loader_.drawString("RMS: " + ofToString(rms_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset);
    
    temporary_font_loader_.drawString("Power: " + ofToString(power_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + bar_y_offset);
    
    temporary_font_loader_.drawString("Pitch Frequency: " + ofToString(pitch_frequency_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + 2 * bar_y_offset);
    
    temporary_font_loader_.drawString("Pitch Confidence: " + ofToString(pitch_confidence_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + 3 * bar_y_offset);
    
    temporary_font_loader_.drawString("HFC: " + ofToString(hfc_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + 4 * bar_y_offset);
    
    temporary_font_loader_.drawString("Odd to Even Harmonic Energy Ratio: " +
                                      ofToString(odd_to_even_harmonic_ratio_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + 5 * bar_y_offset);
    
    temporary_font_loader_.drawString("Inharmonicity: " +
                                      ofToString(inharmonicity_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + 6 * bar_y_offset);
    
    temporary_font_loader_.drawString("Dissonance: " +
                                      ofToString(dissonance_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + 7 * bar_y_offset);
    
    temporary_font_loader_.drawString("Strong Peak: " +
                                      ofToString(strong_peak_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + 8 * bar_y_offset);
    
    temporary_font_loader_.drawString("Strong Decay: " +
                                      ofToString(strong_decay_, 2), left_column_x_offset + right_column_x_offset,
                                      right_column_initial_y_offset + initial_plot_y_position + plot_y_offset + 9 * bar_y_offset);
    
}

/**
 * Helper function to draw plots.
 */
void TechnicalVisualizer::drawPlot(const std::vector<float> & values,
                                   int graph_width, int graph_height, int x, int y, bool should_scale, bool is_mfcc) {
    
    ofPushMatrix();
    
    ofTranslate(x, y);
    
    float bar_width = (float) graph_width / values.size();
    
    for (int index = 0; index < values.size(); index++){
        
        float scaled_value;
        
        if (should_scale) {
            
            if (is_mfcc) {
                scaled_value = ofMap(values[index], 0, MFCC_MAX_ESTIMATED_VALUE, 0.0, 1.0, true);
            } else {
                scaled_value = ofMap(values[index], DB_MIN, DB_MAX, 0.0, 1.0, true);
            }
            
        } else {
            scaled_value = values[index];
        }
        
        float bar_height = (- 1) * scaled_value * graph_height;
        ofDrawRectangle(index * bar_width, graph_height, bar_width, bar_height);
    }
    
    ofPopMatrix();
    
}

/**
 * Helper function to draw bars.
 */
void TechnicalVisualizer::drawBar(float value, int x, int y, int bar_width, int bar_height) {
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofDrawRectangle(0, 5, value * bar_width, bar_height);
    
    ofPopMatrix();
    
}
