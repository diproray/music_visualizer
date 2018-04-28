//
//  Moving2DGraphVisualizer.cpp
//  final-project-of
//
//  Created by Dipro Ray on 4/20/18.
//

#include "Moving2DGraphVisualizer.h"

const float kSpectrumSmoothingFactor = 0.96f; // the float constant storing the smoothing factor for
                                              // the moving graph visualizer

/**
 * The following function initializes all the resources for the
 * moving graph visualizer.
 */
Moving2DGraphVisualizer::Moving2DGraphVisualizer() noexcept {
    
    // Set number of bands in the spectrum to 256 (standard number of bands).
    number_of_bands_ = 256;
    
    // Set number of particles to 300.
    total_number_of_particles_ = 300;
    
    // Initialize all index values in spectrum_values_vector_
    // to zero.
    
    for (int index = 0; index < number_of_bands_; index++) {
        spectrum_values_vector_.push_back(0.0);
    }
    
    // Intialize all particles' x and y positions to a random value
    // between 0 and 2000. This uses ofRandom() function of openFrameworks.
    
    for (int particle_number = 0; particle_number < total_number_of_particles_; particle_number++) {
        
        particle_offset_x_axis_vector_.push_back(ofRandom(0, 2000));
        particle_offset_y_axis_vector_.push_back(ofRandom(0, 2000));
        
    }
    
    for (int index = 0; index < total_number_of_particles_; index++) {
        
        particles_vector_.push_back(ofPoint());
        
    }
    
    // Set the moving graph's radius to 500 initially.
    // This changes with the changing spectrum value.
    
    graph_radius_ = 500;
    
    // Set all particles' velocity to 0.1 intially.
    // It is best to keep this pretty small as,
    // otherwise, the particles would move too fast to be viewed nicely.
    
    particle_velocity_ = 0.1;
    
    // Set the index of the spectrum band which decides changes in graph radius to 2.
    // Since this one of the lower frequencies, it is expected that this will change often in a song,
    // and create an effect where the graph becomes bigger as sound becomes
    // "louder" or "faster" (in a colloquial sense).
    
    band_index_for_graph_radius_ = 2;
    
    // Set the index of the spectrum band which decides changes in graph radius to 100.
    // Since this one of the higher frequencies, it is expected that this will NOT change often in a song,
    // changing only at a fewmoments during the visualization. Usually, these changes are not very prominent.
    // In a moving graph visualization, changing radius often is required more than chaging particles' velocity.
    
    band_index_for_particle_velocity_ = 100;
    
    // Set the current time parameter to zero intially.
    // This will be changed in each update to reflect the last time at which the music was visualized.
    // It is required because the change in time is used to calculate changes in particles' position so
    // the visualization appears to be happening in real-time along with the song.
    
    current_time_ = 0;
    
    threshold_distance_ = 40;
    
}

/**
 * The following function updates all the values for
 * the moving graph visualizer.
 *
 * @param new_spectrum_values - the updated spectrum values which
 *                              spectrum_values_array_ must be updated with
 */
void Moving2DGraphVisualizer::updateValuesForMovingGraphVisualizer(float * new_spectrum_values) {
    
    // Update the values in spectrum_values_array_
    // to reflect the new spectrum band values.
    
    for (int index = 0; index < number_of_bands_; index++) {
        
        // First, the old spectrum values are multiplied by a factor of 0.96.
        // Then, the new value is set to max(modified old value, new value).
        // This is done to "smooth" out the values.
        // Sounds change way too rapidly to be visually pleasing in its raw form.
        // Such a smoothing ensures visualizations will appear smooth and visually appealing.
        
        spectrum_values_vector_[index] *= kSpectrumSmoothingFactor;
        spectrum_values_vector_[index] = max(spectrum_values_vector_[index], new_spectrum_values[index]);
        
    }
    
    // Update the current_time_ with the current time,
    // and compute the change in time since last drawing of the visualization.
    
    float new_current_time = ofGetElapsedTimef();
    float delta_time = new_current_time - current_time_;
    delta_time = ofClamp(delta_time, 0.0, 0.1); // ofClamp restricts delta (time) values to [0.0, 0.1).
    // (Usage of clamp in various places helps "control" the visualization
    // and prevent swiftly changing irregularities.)
    current_time_ = new_current_time;
    
    delta_time_ = delta_time;
    
    // The below line finds a value for the graph_radius within the desired range by
    // reading its value and its proportionality with the input range. The boolean parameter
    // is a clamp ensuring values are restricted to the specified output range.
    // From the openFrameworks documentation, ofMap() linearly maps the
    // given value to a new value given an input and output range
    //
    // Example: if the spectrum_value_array_[desired_index] value is 2, it is mid-way (50 %)
    // between 1 and 3. The output is thereforce mid-way between 400 and 800, i.e. 600.
    
    graph_radius_ =
    ofMap(spectrum_values_vector_[band_index_for_graph_radius_], 1, 3, 400, 800, true);
    
    // Using a similar approach to what is shown above,
    // calculate the particle velocity.
    
    particle_velocity_ =
    ofMap(spectrum_values_vector_[band_index_for_particle_velocity_], 0, 0.1, 0.25, 0.55);
    
    // For each particle,
    // compute its news x and y coordinates (its position).
    
    for (int index = 0; index < total_number_of_particles_; index++) {
        
        // Increase offsets by computing the distance moved in that time interval (velocity * delta time).
        
        particle_offset_x_axis_vector_[index] += particle_velocity_ * delta_time;
        particle_offset_y_axis_vector_[index] += particle_velocity_ * delta_time;
        
        // Set each particle's position equal to the graph's radius * (Perlin Noise for offset between [-1, 1])
        // To learn more about Perlin Noise, check out: https://mzucker.github.io/html/perlin-noise-math-faq.html
        // Perlin Noise provides continuous values in the specified range, which is useful for graphics
        // ofSignedNoise() provides a Perlin Noise in [-1, 1]
        
        particles_vector_[index].x = ofSignedNoise(particle_offset_x_axis_vector_[index]) * graph_radius_;
        particles_vector_[index].y = ofSignedNoise(particle_offset_y_axis_vector_[index]) * graph_radius_;
    }
}

/**
 * The following function is responsible for drawing
 * the moving graph and associated
 * equalizer bars.
 */
void Moving2DGraphVisualizer::drawEqualizerBarsAndMovingGraph() {
    
    ofTrueTypeFont temporary_font_loader_;
    temporary_font_loader_.load("helvetica.ttf", 10);
    
    ofSetColor(0, 0, 0);
    // temporary_font_loader_.drawString("Press C to switch display between lines and triangles visualizations.", 20, 20);
    
    // NOTE: The values for drawing various objects are tuned for
    // a 1024 x 768 pixels window.
    
    // Draw the background rectangle for the equalizer bars.
    // Fill it with a light gray colour.
    
    ofSetColor(230, 230, 230);
    ofFill();
    ofDrawRectangle(10, 700, ofGetWidth() - 20, - 100);
    
    // For each band within the spectrum,
    // display the value with a rectangle.
    // (This results in the formation of the equalizer bars.)
    
    for (int bandNumber = 0; bandNumber < number_of_bands_; bandNumber++) {
        
        // In case, the band is the index deciding changes in
        // graph radius and particle velocity,
        // set draw colour to black.
        //
        // Else, set draw colour to gray.
        
        if (bandNumber == band_index_for_graph_radius_
            || bandNumber == band_index_for_particle_velocity_) {
            ofSetColor(0, 0, 0); // Black color
        }
        else {
            ofSetColor(128, 128, 128); // Gray color
        }
        
        // Draw the rectangle for the band with the specified colour.
        
        ofDrawRectangle(20 + bandNumber * 6, 700, 4, -spectrum_values_vector_[bandNumber] * 250);
    }
    
    // Save the current coordinate system, so that it can be restored later.
    ofPushMatrix();
    
    // Translate (0,0) to the center of the application window.
    // This allows us to draw the moving graph in the center of the screen.
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    // For each particle,
    // draw a circle with a random colour at the specified position.
    
    for (int particleNumber = 0; particleNumber < total_number_of_particles_; particleNumber++) {
        
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
        ofFill();
        ofDrawCircle(particles_vector_[particleNumber], 2);
    }
    
    // The below value is the threshold parameter for classifying the distance between two points
    // as "close".
    // (If the distance between two points is close, an edge of a random colour will be drawn between them.)
    
    // For all the particles,
    // if any two particles are close to each other,
    // draw an edge of a random colour between them.
    // (TODO: Visualization Mode can be switched to draw triangles instead.
    // It will result in an entirely different visualization.)
    
    for (int index_one = 0; index_one < total_number_of_particles_; index_one++) {
        for (int index_two = index_one + 1; index_two < total_number_of_particles_; index_two++) {
            if (ofDist(particles_vector_[index_one].x, particles_vector_[index_one].y,
                       particles_vector_[index_two].x, particles_vector_[index_two].y)
                < threshold_distance_) {
                
                // Set a random colour.
                
                ofSetColor(rand() % 255, rand() % 255, rand() % 255);
                ofFill();
                
                if (mode == 1) {
                    
                    ofDrawLine(particles_vector_[index_one], particles_vector_[index_two]); // First Visualization Mode
                    
                } else {
                    
                    ofDrawTriangle(particles_vector_[index_one], particles_vector_[index_two], particles_vector_[index_one + 1]);
                    // Second Visualization Mode
                    
                }

            }
        }
    }
    
    // Revert the translated coordinate system to the original system.
    
    ofPopMatrix();
    
    // The coordinate system is now restored. (0,0) is at the upper left corner.
    
}

/**
 * Getter for the number of bands of the visualizer.
 */
int Moving2DGraphVisualizer::getNumberOfBands() {
    
    return number_of_bands_;
    
}

/**
 * The following function is responsible for updating
 * the threshold distance value.
 */
void Moving2DGraphVisualizer::updateThresholdDistanceValue(float new_value) {
    
    threshold_distance_ = new_value;
    
}

/**
 * The following function is responsible for updating
 * the display mode.
 */
void Moving2DGraphVisualizer::updateDisplayMode(int new_mode) {
    
    mode = new_mode;
    
}
