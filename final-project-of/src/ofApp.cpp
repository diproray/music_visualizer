#include "ofApp.h"
#include <cstdlib>

// Constants:

const int kDefaultTextSize = 20; // the int constant storing the default font display size

const float kDefaultSongPlaySpeed = 1.0f; // the float constant storing the default play speed for music

const float kSpectrumSmoothingFactor = 0.96f; // the float constant storing the smoothing factor for
                                              // the moving graph visualizer

const int kTurquoiseColourHexValue = 0xC9E9F6; // the int (hex) value for turquoise colour.

const int kBlackColourHexValue = 0x000000; // the int (hex) value for black colour.

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
    
    // Load the font (.ttf file from ../bin/data directory)
    // which the text is to be displayed in.
    
    text_font_loader_.load("freight-sans.ttf", kDefaultTextSize);
    
    // Load the song to be visualized and played.
    sound_player_.load("all_my_love.mp3");
    
    // Set the song playing to a loop.
    // This means that if the song ends, it will restart playing.
    // This will continuously go on till the application is closed.
    
    sound_player_.setLoop(true);
    
    // Set the speed to default value (1.0f).
    // TODO: Add capability to change song speed through a slider in later functions.
    
    sound_player_.setSpeed(kDefaultSongPlaySpeed);
    
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
        
    }
    else if (current_state_ == MOVING_3D_GRAPH_VIZ) {

        // Set background to black colour.
        ofSetBackgroundColorHex(kBlackColourHexValue);

        // Draw the moving graph and equalizer bars
        // for the moving graph visualization.

        moving_3d_graph_visualizer_.drawEqualizerBarsAndMoving3DGraph();

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
    
    string menu_message = "MUSIC VISUALIZER\n";
    menu_message += "1. Moving Graph Visualization (Press G)\n";
    menu_message += "2. Moving 3D Graph Visualization (Press D)";
    
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
