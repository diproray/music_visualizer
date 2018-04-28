//
//  Moving2DGraphVisualizer.h
//  final-project-diproray
//
//  Created by Dipro Ray on 4/20/18.
//

#include "ofMain.h"
#include "ofxGui.h"
#include <iostream>
#ifndef Moving2DGraphVisualizer_h
#define Moving2DGraphVisualizer_h

class Moving2DGraphVisualizer {
    
       protected:
    /* ***************** Moving Graph Visualizer resources ********************* */
    
            int number_of_bands_;  // Number of bands in the spectrum
            
            std::vector<float> spectrum_values_vector_; // Vector storing
            // smoothed spectrum float values
            
            float graph_radius_;  // Graph radius parameter
            
            float particle_velocity_;  // Graph particle velocity parameter
            
            int band_index_for_graph_radius_; // Band index in spectrum that affects the graph radius value
            
            int band_index_for_particle_velocity_; // Band index in spectrum that affects the particle velocity value
            
            int total_number_of_particles_; // Number of graph particles
            
            std::vector<float> particle_offset_x_axis_vector_; // Vector storing offsets for
            // Perlin Noise calculation of particles' x-positions
            
            std::vector<float> particle_offset_y_axis_vector_; // Vector storing offsets for
            // Perlin Noise calculation of particles' y-positions
            
            std::vector<ofPoint> particles_vector_; // Moving graph's particles positions
            
            float current_time_; // Current time value, used for computing delta (time)
    
            float delta_time_; // stores the last updated time change
    
            float threshold_distance_;
    
        public:
    
            int mode = 1; // display mode 1: lines, display mode 2: triangles
            
            /* ******************** Moving Graph Visualizer important functions ******************** */
    
            /**
             * The following function initializes all the resources for the
             * moving graph visualizer.
             */
            Moving2DGraphVisualizer() noexcept;
    
            /**
             * The following function updates all the values for
             * the moving graph visualizer.
             *
             * @param new_spectrum_values - the updated spectrum values which
             *                              spectrum_values_array_ must be updated with
             */
            void updateValuesForMovingGraphVisualizer(float * new_spectrum_values);
    
            /**
             * The following function is responsible for drawing
             * the moving graph and associated
             * equalizer bars.
             */
            void drawEqualizerBarsAndMovingGraph();
    
            /**
             * Getter for the number of bands of the visualizer.
             */
            int getNumberOfBands();
    
            /**
             * The following function is responsible for updating
             * the threshold distance value.
             */
            void updateThresholdDistanceValue(float new_value);
    
            /**
             * The following function is responsible for updating
             * the display mode.
             */
            void updateDisplayMode(int new_mode);
    
};

#endif /* Moving2DGraphVisualizer_h */
