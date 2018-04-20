#pragma once

#include "ofMain.h"

/**
 * The ofApp class that contains all the functions which are to be run.
 */
class ofApp : public ofBaseApp {
    
    enum ApplicationState {
        MENU,
        MOVING_GRAPH_VIZ
    };
    
    ApplicationState current_state_; // this variable tracks the current state of the application
    
    ofSoundPlayer sound_player_; // the sound player for the music to be visualized
    
    ofTrueTypeFont text_font_loader_; // the TTF file loader for
                                      // the font the text is to be displayed in
    
    /* ***** Moving Graph Visualizer resources ***** */
    
    bool isMovingGraphInitialized; // Tracks whether resources have already been set up for the moving graph visualization
    
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
    
    std::vector<float> particle_offset_y_axis_vector_; // Vector storing offsets for Perlin Noise calculation of particles' y-positions
    
    std::vector<ofPoint> particles_vector_; // Moving graph's particles positions
    
    float current_time_; // Current time value, used for computing delta (time)
    
    /* ********************************************** */
    
    
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
    
        /**
         * This function is responsible for drawing the menu screen and displaying options
         * for different visualizations.
         */
        void drawMenuAndOptions();
    
        /* ***** Moving Graph Visualizer functions ***** */
    
        /**
         * The following function initializes all the resources for the
         * moving graph visualizer.
         */
        void initializeResourcesForMovingGraphVisualizer();
    
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
         * The following function deallocates allocateed resources to
         * the moving graph visualizer.
         */
        void deallocateResourcesForMovingGraphVisualizer();
    
        /* ********************************************** */
    
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
