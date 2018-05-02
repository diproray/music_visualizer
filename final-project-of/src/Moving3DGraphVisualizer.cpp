//
//  Moving3DGraphVisualizer.cpp
//  final-project-diproray
//
//  Created by Dipro Ray on 4/20/18.
//

#include <stdio.h>
#include "Moving3DGraphVisualizer.h"

/**
 * The following function initializes all the extra resources for the
 * moving 3D graph visualizer.
 */
Moving3DGraphVisualizer::Moving3DGraphVisualizer() noexcept {
    
    Moving2DGraphVisualizer();
    
    // After intializing all resources of Moving (2D) graph [which will be used by the 3D graph],
    // for each particle,]
    // intialize z-coordinate value, z-offset value, theta value, phi value,
    // theta-offset value and phi-offset value.
    
    for (int particle_number = 0; particle_number < total_number_of_particles_; particle_number++) {
        
        // Set z-coordinate to be a random number between 0 and 2000.
        particle_offset_z_axis_vector_.push_back(ofRandom(0, 2000));
        
        // Set theta and phi to be random values in [0, 2PI] and [0, PI] respectively
        
        particle_theta_value_vector_.push_back(ofRandom(0, 2 * PI));
        particle_phi_value_vector_.push_back(ofRandom(0, PI));
        
        // Set theta and phi offsets to be a random value in [0, 0.02]
        
        particle_theta_offset_vector_.push_back(ofRandom(0, 0.02));
        particle_phi_offset_vector_.push_back(ofRandom(0, 0.02));
        
        // Assign a random colour for the particle.
        particle_colors_.push_back(ofColor(ofRandom(255),ofRandom(255),ofRandom(255)));
        
    }
}

/**
 * The following function updates all the extra values for
 * the moving 3D graph visualizer.
 */
void Moving3DGraphVisualizer::updateValuesForMoving3DGraphVisualizer(float * new_spectrum_values) {
    
    updateValuesForMovingGraphVisualizer(new_spectrum_values);
    
    // After updating values which overlap with Graph (2D)
    // for all particles,
    // a new (x, y, z) position needs to be given, and theta and phi values have to be updated.
    
    for (int particle_number; particle_number < total_number_of_particles_; particle_number++) {
        
        // Calculate the new z-offset by adding delta distance (= velocity * delta time).
        particle_offset_z_axis_vector_[particle_number] += particle_velocity_ * delta_time_;
        
        // As per spherical coordinates,
        // x, y and z coordinates are calculated as:
        // x = (Perlin Noise b/w [0, 1]) * radius * cos (theta) * sin (phi)
        // y = (Perlin Noise b/w [0, 1]) * radius * sin (theta) * sin (phi)
        // z = (Perlin Noise b/w [0, 1]) * radius * cos (phi)
        
        particles_vector_[particle_number].x = ofNoise(particle_offset_x_axis_vector_[particle_number]) *
        graph_radius_ * cos(particle_theta_value_vector_[particle_number]) *
        sin(particle_phi_value_vector_[particle_number]);
        
        particles_vector_[particle_number].y = ofNoise(particle_offset_y_axis_vector_[particle_number]) *
        graph_radius_ * sin(particle_theta_value_vector_[particle_number]) *
        sin(particle_phi_value_vector_[particle_number]);
        
        particles_vector_[particle_number].z = ofNoise( particle_offset_z_axis_vector_[particle_number] ) * graph_radius_ *
        cos(particle_phi_value_vector_[particle_number]);
        
        // The theta and phi values for the particle are calculated by adding the respective offsets.
        
        particle_theta_value_vector_[particle_number] += particle_theta_offset_vector_[particle_number];
        particle_phi_value_vector_[particle_number] += particle_phi_offset_vector_[particle_number];
        
    }
}

/**
 * The following function is responsible for drawing
 * the 3D moving graph and associated
 * equalizer bars.
 */
void Moving3DGraphVisualizer::drawEqualizerBarsAndMoving3DGraph() {
    
    // NOTE: The below values are tuned for a 1024 x 768 pixels window.
    
    // The below lines draw equalizer bars (rectangles) for the entire spectrum.
    //
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
            
            ofSetColor(255, 255, 255); // White color
        }
        else {
            ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255)); // Random color
        }
        
        // Draw the rectangle for the band with the specified colour.
        
        ofDrawRectangle(bandNumber * 7, 700, 5, -spectrum_values_vector_[bandNumber] * 150);
    }
    
    // Save the current coordinate system, so that it can be restored later.
    ofPushMatrix();
    
    // Translate (0,0) to the center of the application window.
    // This allows us to draw the moving graph in the center of the screen.
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    //Draw particles as circles.
    
    // For each particle,
    // draw a circle at the specified position.
    // In this case, the circles are very small, and it is the edges that will be
    // more prominent with vibrant colours.
    
    for (int particleNumber = 0; particleNumber < total_number_of_particles_; particleNumber++) {
        ofDrawCircle(particles_vector_[particleNumber], 0.1);
    }
    
    // The below value is the threshold parameter for classifying the distance between two points
    // as "close".
    // (If the distance between two points is close, an edge of a random colour will be drawn between them.)
    
    // TODO: Allow toggling this value.
    
    float threshold_distance = 140;
    
    // For all the particles,
    // if any two particles are close to each other,
    // draw an edge of a random colour between them.
    // (TODO: Visualization Mode can be switched to draw triangles instead.
    // It will result in an entirely different visualization.)
    
    for (int index_one = 0; index_one < total_number_of_particles_; index_one++) {
        for (int index_two = index_one + 1; index_two < total_number_of_particles_; index_two++) {
            
            // Find the distance between the points.
            
            float distance_between_points =
            ofDist(particles_vector_[index_one].x, particles_vector_[index_one].y, particles_vector_[index_one].z,
                   particles_vector_[index_two].x, particles_vector_[index_two].y, particles_vector_[index_two].z);
            
            // If it is less than the threshold distance
            
            if (distance_between_points < threshold_distance) {
                
                // Decide the intensity of the colour of the line.
                float alpha = ofMap(distance_between_points, 0, 180, 150, 0);
                
                // Draw the line with the spcified colour and intensity.
                
                ofSetColor(particle_colors_[index_one], alpha);
                ofSetLineWidth(0.0001);
                
                ofDrawLine(particles_vector_[index_one], particles_vector_[index_two]); // First Visualization Mode
                // ofDrawTriangle(particles[index_one], particles[index_two], particles[index_one + 1]); // Second Visualization Mode
                
            }
        }
    }
    
    // Revert the translated coordinate system to the original system.
    
    ofPopMatrix();
    
    // The coordinate system is now restored. (0,0) is at the upper left corner.
}

int Moving3DGraphVisualizer::getNumberOfBands() {
    return number_of_bands_;
}
