#pragma once

#include "ofMain.h"
#include "ofxFFTLive.h"
#include "Moving2DGraphVisualizer.h"
#include "Moving3DGraphVisualizer.h"

/**
 * The ofApp class that contains all the functions which are executed when main() is run.
 */
class ofApp : public ofBaseApp {
    
    enum ApplicationState {
        MENU,
        MOVING_GRAPH_VIZ,
        MOVING_3D_GRAPH_VIZ,
        FFT_TRANSFORMER_AND_VIZ
    };
    
    ApplicationState current_state_; // this variable tracks the current state of the application
    
    ofSoundPlayer sound_player_; // the sound player for the music to be visualized
    
    ofTrueTypeFont text_font_loader_; // the TTF file loader for
                                      // the font the text is to be displayed in

    Moving2DGraphVisualizer moving_2d_graph_visualizer_; // an object which runs the moving 2D graph visualizer
    
    Moving3DGraphVisualizer moving_3d_graph_visualizer_; // an object which runs the moving 3D graph visualizer
    
    ofxFFTLive fft_live_; // the ofxFFT addon object used to visualize frequency waveforms after applying FFT
                          // on real time data
    
//    ofSoundStream sound_streamer_;
//
//    ofxFFTBase fft_base_;
//
//    std::vector<float> samples_channel_;
    
	public:
    
//    void drawWaveforms();
//    void audioIn(float * input, int bufferSize, int nChannels);
    
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
