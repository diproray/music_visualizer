//
//  Moving3DGraphVisualizer.h
//  final-project-diproray
//
//  Created by Dipro Ray on 4/20/18.
//

#ifndef Moving3DGraphVisualizer_h
#define Moving3DGraphVisualizer_h

#include "Moving2DGraphVisualizer.h"

class Moving3DGraphVisualizer : protected Moving2DGraphVisualizer {
    
    protected:
    
        std::vector<ofColor> particle_colors_; // Vector storing the color of each particle
    
        std::vector<float> particle_offset_z_axis_vector_; // Vector storing offsets for
                                                           // Perlin Noise calculation of particles' z-positions
    
        std::vector<float> particle_theta_value_vector_; // Vector storing theta (spherical angle) value
                                                         // for each particle
    
        std::vector<float> particle_phi_value_vector_; // Vector storing phi (spherical angle) value
                                                       // for each particle
    
        std::vector<float> particle_theta_offset_vector_; // Vector storing theta (spherical angle) offset
                                                          // for each particle
    
        std::vector<float> particle_phi_offset_vector_; // Vector storing phi (spherical angle) offset
                                                        // for each particle
    
    public:
    
        /**
         * The following function initializes all the extra resources for the
         * moving 3D graph visualizer.
         */
        Moving3DGraphVisualizer() noexcept;
    
        /**
         * The following function updates all the extra values for
         * the moving 3D graph visualizer.
         */
        void updateValuesForMoving3DGraphVisualizer(float * new_spectrum_values);
    
        /**
         * The following function is responsible for drawing
         * the 3D moving graph and associated
         * equalizer bars.
         */
        void drawEqualizerBarsAndMoving3DGraph();
    
        /**
         * Getter for the number of bands of the visualizer.
         */
        int getNumberOfBands();

};

#endif /* Moving3DGraphVisualizer_h */
