#include "ofApp.h"
#include <cstdlib>

// Constants:

const int kDefaultTextSize = 20; // the int constant storing the default font display size

const float kDefaultSongPlaySpeed = 1.0f; // the float constant storing the default play speed for music

const float kSpectrumSmoothingFactor = 0.96f; // the float constant storing the smoothing factor for
                                              // the moving graph visualizer

const int kTurquoiseColourHexValue = 0xC9E9F6; // the int (hex) value for turquoise colour.

const int kBlackColourHexValue = 0x000000; // the int (hex) value for black colour.

const std::string kSongToPlay = "indian_summer.mp3"; // string containing the name of the song to be played

// TODO: integrate time waveform into FFT visualization

// int channelsOut = 0;        // number of requested output channels (i.e. 2 for stereo).
// int channelsIn = 1;         // number of requested input channels.
// int sampleRate = 44100;     // requested sample rate (44100 is typical).
// int bufferSize = 256;       // requested buffer size (256 is typical).
// int numOfBuffers = 4;       // number of buffers to queue, less buffers will be more responsive, but less stable.



// Functions to be run are decided based on the state of the application.
// E.g. if the state is MENU, functions pertaining to the Menu screen are run.
//      The same applies for the other states.
//
// Moving2DGraphVisualizer is a class having functions to create the Moving 2D Graph Visualization.
//
// Moving3DGraphVisualizer is a class having functions to create the Moving 3D Graph Visualization.
// As you might guess, Moving3DGraphVisualizer inherits from Moving2DGraphVisualizer.

/**
 * The following function sets up the resources for the application.
 */
void ofApp::setup() {
    
    current_state_ = MENU; // set the current state to the menu
    
    ofSetWindowTitle("Menu");
    fft_visualizer_ = FFTVisualizer();
    
    // Load the font (.ttf file from ../bin/data directory)
    // which the text is to be displayed in.
    
    text_font_loader_.load("helvetica.ttf", kDefaultTextSize);
    
    // Load the song to be visualized and played.
    sound_player_.load(kSongToPlay);
    
    // Set the song playing to a loop.
    // This means that if the song ends, it will restart playing.
    // This will continuously go on till the application is closed.
    
    sound_player_.setLoop(true);
    
    // Set the speed to default value (1.0f).
    // TODO: Add capability to change song speed through a slider in later functions.
    
    sound_player_.setSpeed(kDefaultSongPlaySpeed);
    
    extended_sound_player_.load("indian_summer.mp3");
    extended_sound_player_.setLoop(true);
    extended_sound_player_.setSpeed(kDefaultSongPlaySpeed);
    
}

/**
 * The following function updates the resources for the application.
 */
void ofApp::update() {
    
    if (current_state_ == MOVING_GRAPH_VIZ || current_state_ == MOVING_3D_GRAPH_VIZ) {
        
        // Update the sound player's states.
        // This updates the current time value in the ofSoundPlayer
        // and updates the spectrum band values for the next time interval.
        
        ofSoundUpdate();
        
        if (current_state_ == MOVING_GRAPH_VIZ) {
            
            // Get the newly updated spectrum values.
            // These are values for various frequencies within the specified number of bands.
            
            float * current_sound_spectrum_values = ofSoundGetSpectrum(moving_2d_graph_visualizer_.getNumberOfBands());
            
            // Update the spectrum_value_array_ of the moving 2D graph visualizer with these values
            // by calling the function responsible for it.
            
            moving_2d_graph_visualizer_.updateValuesForMovingGraphVisualizer(current_sound_spectrum_values);
            
        }
        
        if (current_state_ == MOVING_3D_GRAPH_VIZ) {

            // Get the newly updated spectrum values.
            // These are values for various frequencies within the specified number of bands.
            
            float * current_sound_spectrum_values = ofSoundGetSpectrum(moving_3d_graph_visualizer_.getNumberOfBands());
            
            // Update the spectrum_value_array_ of the moving graph visualizer with these values
            // by calling the function responsible for it.
            
            moving_3d_graph_visualizer_.updateValuesForMoving3DGraphVisualizer(current_sound_spectrum_values);

        }
        
    } else if (current_state_ == FFT_TRANSFORMER_AND_VIZ) {
        
//        // Update the intenral state of the FFT object to reflect new music played at this moment
//        // through the microphone.
//
//        fft_live_.update();
////        fft_base_.update();
        
        ofSoundBuffer current_sound_buffer = extended_sound_player_.getCurrentSoundBuffer(fft_visualizer_.getNumberOfBands());
        
        fft_visualizer_.updateValuesForFFTVisualizer(current_sound_buffer);
    }

}

/**
 * The following function is responsible for drawing items to the
 * application window.
 */
void ofApp::draw() {
    
    if (current_state_ == MENU) {
        
        drawMenuAndOptions();
        
    } else if (current_state_ == MOVING_GRAPH_VIZ) {
        
        // Set background to turquoise colour.
        ofSetBackgroundColorHex(kTurquoiseColourHexValue);
    
        // Draw the moving graph and equalizer bars
        // for the moving graph visualization.
    
        moving_2d_graph_visualizer_.drawEqualizerBarsAndMovingGraph();
        
        // Display a "Now Playing :" + the song's name, in Helvetica font.
        
        ofTrueTypeFont temporary_font_loader_;
        temporary_font_loader_.load("helvetica.ttf", 10);
        
        ofSetColor(0, 0, 0);
        temporary_font_loader_.drawString("Now Playing: " + kSongToPlay, 800, 20);
        
    }
    
    else if (current_state_ == MOVING_3D_GRAPH_VIZ) {

        // Set background to black colour.
        ofSetBackgroundColorHex(kBlackColourHexValue);

        // Draw the moving graph and equalizer bars
        // for the moving graph visualization.

        moving_3d_graph_visualizer_.drawEqualizerBarsAndMoving3DGraph();
        
        // Display a "Now Playing :" + the song's name, in Helvetica font.
        
        ofTrueTypeFont temporary_font_loader_;
        temporary_font_loader_.load("helvetica.ttf", 10);
        
        ofSetColor(255, 255, 255);
        temporary_font_loader_.drawString("Now Playing: " + kSongToPlay, 800, 20);

    }
    else if (current_state_ == FFT_TRANSFORMER_AND_VIZ) {
        
//        // Draw the frequency waveform computed through FFT
//        // and display it.
//
//        // Set background to turquoise colour.
//        ofSetBackgroundColorHex(kTurquoiseColourHexValue);
//
//        fft_live_.draw(12, ofGetHeight() / 3, 1000, 400);
        ////      drawWaveforms();
        
        fft_visualizer_.drawWaveformAndFrequencyBars();
        
        // Display a "Now Playing :" + the song's name, in Helvetica font.
        
        ofTrueTypeFont temporary_font_loader_;
        temporary_font_loader_.load("helvetica.ttf", 10);
        
        ofSetColor(255, 255, 255);
        temporary_font_loader_.drawString("Now Playing: " + kSongToPlay, 800, 20);
        
    }
}

/**
 * The following function triggers an action based on the key
 * that is pressed.
 */
void ofApp::keyPressed(int key) {
    
    int uppercase_key = toupper(key);
    
    // If the key is G
    
    if (uppercase_key == 'G') {
        
        // If G is pressed while in the menu
        
        if (current_state_ == MENU) {
            
            // Move to the Moving Graph Visualization screen.
            // Intialize the object and begin the music and visualization!
            
            ofSetWindowTitle("Moving Graph Visualization");
            current_state_ = MOVING_GRAPH_VIZ;
            
            // The below line calls the function that initializes the object
            // for the moving graph visualizer.
            
            moving_2d_graph_visualizer_ = Moving2DGraphVisualizer();
            
            // Start playing the song.
            sound_player_.play();
            sound_player_.setPositionMS(60000); // For demo purposes - plays song from the 1 minute mark
            
        } else if (current_state_ == MOVING_GRAPH_VIZ) {
            
            // If G is pressed in the Moving Graph visualization screen,
            // return to the Menu screen, after stopping the music.
            
            ofSetWindowTitle("Menu");
            current_state_ = MENU;
            
            // Stop playing the song.
            sound_player_.stop();
            
            // Resources allocated for the object will be automatically deallocated.
            
        }
    }
    
    else if (uppercase_key == 'C') {
        
        moving_2d_graph_visualizer_.mode = (moving_2d_graph_visualizer_.mode == 1) ? 2 : 1;
        
    }
    // If the key is D

    else if (uppercase_key == 'D') {

        // If D is pressed while in the menu

        if (current_state_ == MENU) {

            // Move to the Moving 3D Graph Visualization screen.
            // Intialize resources and begin the music and visualization!

            ofSetWindowTitle("Moving 3D Graph Visualization");
            current_state_ = MOVING_3D_GRAPH_VIZ;

            // The below line calls the function that initializes all resources
            // for the moving graph visualizer.

            moving_3d_graph_visualizer_ = Moving3DGraphVisualizer();

            // Start playing the song.
            sound_player_.play();
            sound_player_.setPositionMS(60000); // For demo purposes - plays song from the 1 minute mark

        }
        else if (current_state_ == MOVING_3D_GRAPH_VIZ) {

            // If G is pressed in the Moving Graph visualization screen,
            // return to the Menu screen, after deallocating the Moving Graph Visualizer's resources and stopping the music.

            ofSetWindowTitle("Menu");
            current_state_ = MENU;

            // Stop playing the song.
            sound_player_.stop();
        }
    }
    
    else if (uppercase_key == 'F') {
        
        if (current_state_ == MENU) {
            
            // Move to the Moving 3D Graph Visualization screen.
            // Intialize resources and begin the music and visualization!
            
            ofSetWindowTitle("FFT, Time and Frequency Waveform Visualization");
            current_state_ = FFT_TRANSFORMER_AND_VIZ;
            
            // Start playing the song.
            extended_sound_player_.play();
            extended_sound_player_.setPositionMS(60000); // For demo purposes - plays song from the 1 minute mark
            
            
        }
        else if (current_state_ == FFT_TRANSFORMER_AND_VIZ) {
            
            // fft_visualizer_.~FFTVisualizer();
            
            ofSetWindowTitle("Menu");
            current_state_ = MENU;
            
            ofSetLineWidth(1);
            extended_sound_player_.stop();
            
        }
        
    }
    // TODO: Add capability to pause, triggering a menu screen.
    
    // TODO: Add switching feature for different visualizations.

}

/**
 * This function is responsible for drawing the menu screen and displaying options
 * for different visualizations.
 */
void ofApp::drawMenuAndOptions() {
    
    // Set the background colour to white.
    ofSetBackgroundColor(255, 255, 255);
    
    // Set the text colour to black.
    ofSetColor(0, 0, 0);
    
    // Form the string to be displayed.
    
    string menu_message = "                 MUSIC VISUALIZER\n\n";
    menu_message += "1. Moving Graph Visualization (Press G)\n\n";
    menu_message += "2. Moving 3D Graph Visualization (Press D)\n\n";
    menu_message += "3. FFT, Time and Frequency Waveform Visualization (Press F)";
    
    // Display the string.
    text_font_loader_.drawString(menu_message, ofGetWidth() / 4, ofGetHeight() / 4);
    
}


// The below functions are currently not being used.


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
