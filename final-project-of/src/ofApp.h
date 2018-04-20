#pragma once

#include "ofMain.h"

/**
 * The ofApp class that contains all the functions which are to be run.
 */
class ofApp : public ofBaseApp {
    
    ofSoundPlayer sound_player_; // the sound player for the music to be visualized
    
    ofTrueTypeFont text_font_loader_; // the TTF file loader for
                                      // the font the text is to be displayed in
    
    static const int kNumberOfBands_ = 256;  // Number of bands in the spectrum
    
    float spectrum_values_array_[kNumberOfBands_]; // Array storing
    // smoothed spectrum float values
    
    float graph_radius_;  // Graph radius parameter
    
    float particle_velocity_;  // Graph particle velocity parameter
    
    int band_index_for_graph_radius_; // Band index in spectrum that affects graph radius value
    
    int band_index_for_particle_velocity_; // Band index in spectrum that affects particle velocity value
    
    static const int kNumberOfParticles_ = 300; // Number of graph particles
    
    float particle_offset_x_axis_[kNumberOfParticles_]; // Array storing offsets for Perlin Noise calculation of particles' x-positions
    
    float particle_offset_y_axis_[kNumberOfParticles_]; // Array storing offsets for Perlin Noise calculation of particles' y-positions
    
    ofPoint particles[kNumberOfParticles_]; // Moving graph's particles positions
    
    float current_time_;        // Time value, used for computing delta (time)

    
	public:
    
        /**
         * The following function sets up the resources for the application.
         */
		void setup();
    
        /**
         * The following function updates the resources for the application.
         */
		void update();
    
        /**
         * The following function is responsible for drawing items to the
         * application window.
         */
		void draw();

        /**
         * The following function triggers an action based on the key
         * that is pressed.
         */
		void keyPressed(int key);
    
        void initializeResourcesForMovingGraphVisualizer();
    
        void updateValuesForMovingGraphVisualizer(float * new_spectrum_values);
    
        void drawEqualizerBarsAndMovingGraph();
    
    
        // The below functions are currently not being used.
    
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
