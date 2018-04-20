#include "ofApp.h"

const int kDefaultTextSize = 20;
const float kDefaultSongPlaySpeed = 1.0f;
const float kSpectrumSmoothingFactor = 0.96f;

/**
 * The following function sets up the resources for the application.
 */
void ofApp::setup(){
    
    initializeResourcesForMovingGraphVisualizer();
    text_font_loader_.load("freight-sans.ttf", kDefaultTextSize);
    sound_player_.load("all_my_love.mp3");
    sound_player_.play();
    sound_player_.setLoop(true);
    sound_player_.setSpeed(kDefaultSongPlaySpeed);
    
}

/**
 * The following function updates the resources for the application.
 */
void ofApp::update(){
    
    ofSoundUpdate();
    
    float * current_sound_spectrum_values = ofSoundGetSpectrum(kNumberOfBands_);
    updateValuesForMovingGraphVisualizer(current_sound_spectrum_values);;
    
}

/**
 * The following function is responsible for drawing items to the
 * application window.
 */
void ofApp::draw(){
    ofSetBackgroundColorHex(0xC9E9F6); // Set background to turquoise colour.
    drawEqualizerBarsAndMovingGraph();
}

/**
 * The following function triggers an action based on the key
 * that is pressed.
 */
void ofApp::keyPressed(int key){

}

void ofApp::initializeResourcesForMovingGraphVisualizer() {
    
    for (int index = 0; index < kNumberOfBands_; index++) {
        spectrum_values_array_[index] = 0.0;
    }
    
    for (int index = 0; index < kNumberOfParticles_; index++) {
        
        particle_offset_x_axis_[index] = ofRandom(0, 2000);
        particle_offset_y_axis_[index] = ofRandom(0, 2000);
        
    }
    
    graph_radius_ = 500;
    
    particle_velocity_ = 0.1;
    
    band_index_for_graph_radius_ = 2;
    
    band_index_for_particle_velocity_ = 100;
    
    current_time_ = 0;
    
}

void ofApp::updateValuesForMovingGraphVisualizer(float * new_spectrum_values) {
    
    for ( int index = 0; index < kNumberOfBands_; index++ ) {
        
        spectrum_values_array_[index] *= kSpectrumSmoothingFactor;
        spectrum_values_array_[index] = max(spectrum_values_array_[index], new_spectrum_values[index]);
        
    }
    
    float new_current_time = ofGetElapsedTimef();
    float delta_time = new_current_time - current_time_;
    delta_time = ofClamp(delta_time, 0.0, 0.1);
    current_time_ = new_current_time;
    
    graph_radius_ =
        ofMap(spectrum_values_array_[band_index_for_graph_radius_], 1, 3, 400, 800, true);
    
    particle_velocity_ =
        ofMap(spectrum_values_array_[band_index_for_particle_velocity_], 0, 0.1, 0.05, 0.5);
    
    for (int index = 0; index < kNumberOfParticles_; index++) {
        
        particle_offset_x_axis_[index] += particle_velocity_ * delta_time;
        particle_offset_y_axis_[index] += particle_velocity_ * delta_time;
        
        // Calculate Perlin's noise in [-1, 1] and
        // Multiply it by the graph radius to get the new position of the particle.
        
        particles[index].x = ofSignedNoise(particle_offset_x_axis_[index]) * graph_radius_;
        particles[index].y = ofSignedNoise(particle_offset_y_axis_[index]) * graph_radius_;
    }
}

void ofApp::drawEqualizerBarsAndMovingGraph() {
    
    ofSetColor(230, 230, 230);
    ofFill();
    ofDrawRectangle(10, 700, kNumberOfBands_ * 5.5, - 100);
    
    ofSetColor(0, 0, 0);
    for (int index = 0; index < kNumberOfBands_; index++) {
        
        if (index == band_index_for_graph_radius_
                || index == band_index_for_particle_velocity_) {
            ofSetColor(0, 0, 0); // Black color
        }
        else {
            ofSetColor(128, 128, 128); // Gray color
        }
        
        ofDrawRectangle(10 + index * 5, 700, 3, -spectrum_values_array_[index] * 200);
    }

    
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    
    for (int index = 0; index < kNumberOfParticles_; index++) {
        
        ofSetColor(rand() % 255, rand() % 255, rand() % 255);
        ofFill();
        ofDrawCircle(particles[index], 2);
    }

    
    float threshold_distance = 40;    // Threshold parameter of "close" distance
    
    for (int index_one = 0; index_one < kNumberOfParticles_; index_one++) {
        for (int index_two = index_one + 1; index_two < kNumberOfParticles_; index_two++) {
            if (ofDist(particles[index_one].x, particles[index_one].y, particles[index_two].x, particles[index_two].y)
                < threshold_distance) {
                
                ofSetColor(rand() % 255, rand() % 255, rand() % 255);
                ofFill();
                
                // ofDrawTriangle(particles[index_one], particles[index_two], particles[index_one + 1]);
                ofDrawLine(particles[index_one], particles[index_two]);
            }
        }
    }
    
    // Revert the coordinate system to original system
    ofPopMatrix();
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
