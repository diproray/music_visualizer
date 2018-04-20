#pragma once

#include "ofMain.h"

/**
 * The ofApp class that contains all the functions which are to be run.
 */
class ofApp : public ofBaseApp {

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
