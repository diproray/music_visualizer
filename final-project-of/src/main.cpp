#include "ofMain.h"
#include "ofApp.h"

// Final Project for CS 126
// Music Visualization
//
// by Dipro Ray
// 04/19/2018

/**
 * The main function to be run.
 */
int main() {
    
    // Set up the openFrameworks/openGL window
    // which is the display for the application.
    //
    // (The first two parameters are the Height and Width of the screen
    // while the last parameter is the display mode:
    // OF_WINDOW (display of specified width and height) or
    // OF_FULLSCREEN (full-screen display).)
    
    ofSetupOpenGL(1024,768,OF_WINDOW);

	// The below line kicks off
    // the running of my application.
    
	ofRunApp(new ofApp());

}
