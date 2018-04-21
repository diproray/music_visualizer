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
// However, one exception to this general pattern is Moving 3D Graph Visualization.
// Since this 3D Visualizer has a resource and functions overlap with Moving Graph Visualizer,
// to reuse code and reduce no. of functions to be run, 3D Graph uses many of the resources and
// functions of the Moving (2D) Graph Visualizer.
// In a way, Moving 3D Graph "inherits" resources and functions from Moving (2D) Graph Visualizer.
//
//
// Unfortunately, since openFramework elements can only be used in ofApp, there is no way to separate these
// visualizations into classes and implement OOP design. ¯\_(ツ)_/¯
// Hence, I have resorted to Application States and Code Reuse to make up for this shortcoming.

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
        
        // Get the newly updated spectrum values.
        // These are values for various frequencies within the specified number of bands.
        
        float * current_sound_spectrum_values = ofSoundGetSpectrum(number_of_bands_);
        
        // Update the spectrum_value_array_ of the moving graph visualizer with these values
        // by calling the function responsible for it.
        
        updateValuesForMovingGraphVisualizer(current_sound_spectrum_values);
        
        if (current_state_ == MOVING_3D_GRAPH_VIZ) {
            
            updateExtraValuesForMoving3DGraphVisualizer();
            
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
    
        drawEqualizerBarsAndMovingGraph();
        
    } else if (current_state_ == MOVING_3D_GRAPH_VIZ) {
        
        // Set background to turquoise colour.
        ofSetBackgroundColorHex(kBlackColourHexValue);
        
        // Draw the moving graph and equalizer bars
        // for the moving graph visualization.
        
        drawEqualizerBarsAndMoving3DGraph();
        
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
            // Intialize resources and begin the music and visualization!
            
            ofSetWindowTitle("Moving Graph Visualization");
            current_state_ = MOVING_GRAPH_VIZ;
            
            // The below line calls the function that initializes all resources
            // for the moving graph visualizer.
            
            initializeResourcesForMovingGraphVisualizer();
            
            // Start playing the song.
            sound_player_.play();
            
        } else if (current_state_ == MOVING_GRAPH_VIZ) {
            
            // If G is pressed in the Moving Graph visualization screen,
            // return to the Menu screen, after deallocating the Moving Graph Visualizer's resources and stopping the music.
            
            deallocateResourcesForMovingGraphVisualizer();
            ofSetWindowTitle("Menu");
            current_state_ = MENU;
            
            // Stop playing the song.
            sound_player_.stop();
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
            
            initializeResourcesForMovingGraphVisualizer();
            initializeExtraResourcesForMoving3DGraphVisualizer();
            
            // Start playing the song.
            sound_player_.play();
            
        } else if (current_state_ == MOVING_3D_GRAPH_VIZ) {
            
            // If G is pressed in the Moving Graph visualization screen,
            // return to the Menu screen, after deallocating the Moving Graph Visualizer's resources and stopping the music.
            
            deallocateResourcesForMovingGraphVisualizer();
            deallocateExtraResourcesForMoving3DGraphVisualizer();
            
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

/**
 * The following function initializes all the resources for the
 * moving graph visualizer.
 */
void ofApp::initializeResourcesForMovingGraphVisualizer() {
    
    // Set number of bands in the spectrum to 256 (standard number of bands).
    number_of_bands_ = 256;
    
    // Set number of particles to 300.
    total_number_of_particles_ = 300;
    
    // Initialize all index values in spectrum_values_vector_
    // to zero.
    
    for (int index = 0; index < number_of_bands_; index++) {
        spectrum_values_vector_.push_back(0.0);
    }
    
    // Intialize all particles' x and y positions to a random value
    // between 0 and 2000. This uses ofRandom() function of openFrameworks.
    
    for (int particle_number = 0; particle_number < total_number_of_particles_; particle_number++) {
        
        particle_offset_x_axis_vector_.push_back(ofRandom(0, 2000));
        particle_offset_y_axis_vector_.push_back(ofRandom(0, 2000));
        
    }
    
    for (int index = 0; index < total_number_of_particles_; index++) {
        
        particles_vector_.push_back(ofPoint());
    
    }
    
    // Set the moving graph's radius to 500 initially.
    // This changes with the changing spectrum value.
    
    graph_radius_ = 500;
    
    // Set all particles' velocity to 0.1 intially.
    // It is best to keep this pretty small as,
    // otherwise, the particles would move too fast to be viewed nicely.
    
    particle_velocity_ = 0.1;
    
    // Set the index of the spectrum band which decides changes in graph radius to 2.
    // Since this one of the lower frequencies, it is expected that this will change often in a song,
    // and create an effect where the graph becomes bigger as sound becomes
    // "louder" or "faster" (in a colloquial sense).
    
    band_index_for_graph_radius_ = 2;
    
    // Set the index of the spectrum band which decides changes in graph radius to 100.
    // Since this one of the higher frequencies, it is expected that this will NOT change often in a song,
    // changing only at a fewmoments during the visualization. Usually, these changes are not very prominent.
    // In a moving graph visualization, changing radius often is required more than chaging particles' velocity.
    
    band_index_for_particle_velocity_ = 100;
    
    // Set the current time parameter to zero intially.
    // This will be changed in each update to reflect the last time at which the music was visualized.
    // It is required because the change in time is used to calculate changes in particles' position so
    // the visualization appears to be happening in real-time along with the song.
    
    current_time_ = 0;
    
}

/**
 * The following function updates all the values for
 * the moving graph visualizer.
 *
 * @param new_spectrum_values - the updated spectrum values which
 *                              spectrum_values_array_ must be updated with
 */
void ofApp::updateValuesForMovingGraphVisualizer(float * new_spectrum_values) {
    
    // Update the values in spectrum_values_array_
    // to reflect the new spectrum band values.
    
    for (int index = 0; index < number_of_bands_; index++) {
        
        // First, the old spectrum values are multiplied by a factor of 0.96.
        // Then, the new value is set to max(modified old value, new value).
        // This is done to "smooth" out the values.
        // Sounds change way too rapidly to be visually pleasing in its raw form.
        // Such a smoothing ensures visualizations will appear smooth and visually appealing.
        
        spectrum_values_vector_[index] *= kSpectrumSmoothingFactor;
        spectrum_values_vector_[index] = max(spectrum_values_vector_[index], new_spectrum_values[index]);
        
    }
    
    // Update the current_time_ with the current time,
    // and compute the change in time since last drawing of the visualization.
    
    float new_current_time = ofGetElapsedTimef();
    float delta_time = new_current_time - current_time_;
    delta_time = ofClamp(delta_time, 0.0, 0.1); // ofClamp restricts delta (time) values to [0.0, 0.1).
                                                // (Usage of clamp in various places helps "control" the visualization
                                                // and prevent swiftly changing irregularities.)
    current_time_ = new_current_time;
    
    delta_time_ = delta_time;
    
    // The below line finds a value for the graph_radius within the desired range by
    // reading its value and its proportionality with the input range. The boolean parameter
    // is a clamp ensuring values are restricted to the specified output range.
    // From the openFrameworks documentation, ofMap() linearly maps the
    // given value to a new value given an input and output range
    //
    // Example: if the spectrum_value_array_[desired_index] value is 2, it is mid-way (50 %)
    // between 1 and 3. The output is thereforce mid-way between 400 and 800, i.e. 600.
    
    graph_radius_ =
    ofMap(spectrum_values_vector_[band_index_for_graph_radius_], 1, 3, 400, 800, true);
    
    // Using a similar approach to what is shown above,
    // calculate the particle velocity.
    
    particle_velocity_ =
    ofMap(spectrum_values_vector_[band_index_for_particle_velocity_], 0, 0.1, 0.175, 0.6);
    
    // For each particle,
    // compute its news x and y coordinates (its position).
    
    for (int index = 0; index < total_number_of_particles_; index++) {
        
        // Increase offsets by computing the distance moved in that time interval (velocity * delta time).
        
        particle_offset_x_axis_vector_[index] += particle_velocity_ * delta_time;
        particle_offset_y_axis_vector_[index] += particle_velocity_ * delta_time;
        
        // Set each particle's position equal to the graph's radius * (Perlin Noise for offset between [-1, 1])
        // To learn more about Perlin Noise, check out: https://mzucker.github.io/html/perlin-noise-math-faq.html
        // Perlin Noise provides continuous values in the specified range, which is useful for graphics
        // ofSignedNoise() provides a Perlin Noise in [-1, 1]
        
        particles_vector_[index].x = ofSignedNoise(particle_offset_x_axis_vector_[index]) * graph_radius_;
        particles_vector_[index].y = ofSignedNoise(particle_offset_y_axis_vector_[index]) * graph_radius_;
    }
}

/**
 * The following function is responsible for drawing
 * the moving graph and associated
 * equalizer bars.
 */
void ofApp::drawEqualizerBarsAndMovingGraph() {
    
    // NOTE: The values for drawing various objects are tuned for
    // a 1024 x 768 pixels window.
    
    // Draw the background rectangle for the equalizer bars.
    // Fill it with a light gray colour.
    
    ofSetColor(230, 230, 230);
    ofFill();
    ofDrawRectangle(10, 700, ofGetWidth() - 20, - 100);
    
    // For each band within the spectrum,
    // display the value with a rectangle.
    // (This results in the formation of the equalizer bars.)
    
    for (int bandNumber = 0; bandNumber < number_of_bands_; bandNumber++) {
        
        // In case, the band is the index deciding changes in
        // graph radius and particle velocity,
        // set draw colour to black.
        //
        // Else, set draw colour to gray.
        
        if (bandNumber == band_index_for_graph_radius_
            || bandNumber == band_index_for_particle_velocity_) {
            ofSetColor(0, 0, 0); // Black color
        }
        else {
            ofSetColor(128, 128, 128); // Gray color
        }
        
        // Draw the rectangle for the band with the specified colour.

        ofDrawRectangle(20 + bandNumber * 6, 700, 4, -spectrum_values_vector_[bandNumber] * 250);
    }
    
    // Save the current coordinate system, so that it can be restored later.
    ofPushMatrix();
    
    // Translate (0,0) to the center of the application window.
    // This allows us to draw the moving graph in the center of the screen.
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    // For each particle,
    // draw a circle with a random colour at the specified position.
    
    for (int particleNumber = 0; particleNumber < total_number_of_particles_; particleNumber++) {
        
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
        ofFill();
        ofDrawCircle(particles_vector_[particleNumber], 2);
    }
    
    // The below value is the threshold parameter for classifying the distance between two points
    // as "close".
    // (If the distance between two points is close, an edge of a random colour will be drawn between them.)
    
    // TODO: Allow toggling this value.
    
    float threshold_distance = 40;
    
    // For all the particles,
    // if any two particles are close to each other,
    // draw an edge of a random colour between them.
    // (TODO: Visualization Mode can be switched to draw triangles instead.
    // It will result in an entirely different visualization.)
    
    for (int index_one = 0; index_one < total_number_of_particles_; index_one++) {
        for (int index_two = index_one + 1; index_two < total_number_of_particles_; index_two++) {
            if (ofDist(particles_vector_[index_one].x, particles_vector_[index_one].y,
                       particles_vector_[index_two].x, particles_vector_[index_two].y)
                < threshold_distance) {
                
                // Set a random colour.
                
                ofSetColor(rand() % 255, rand() % 255, rand() % 255);
                ofFill();
                
                ofDrawLine(particles_vector_[index_one], particles_vector_[index_two]); // First Visualization Mode
                // ofDrawTriangle(particles[index_one], particles[index_two], particles[index_one + 1]); // Second Visualization Mode
                
            }
        }
    }
    
    // Revert the translated coordinate system to the original system.
    
    ofPopMatrix();
    
    // The coordinate system is now restored. (0,0) is at the upper left corner.
}

/**
 * The following function deallocates allocateed resources to
 * the moving graph visualizer.
 */
void ofApp::deallocateResourcesForMovingGraphVisualizer() {
    
    // Delete all elements within the vectors.
    
    spectrum_values_vector_.clear();
    particle_offset_x_axis_vector_.clear();
    particle_offset_y_axis_vector_.clear();
    particles_vector_.clear();
    
}

/**
 * The following function initializes all the extra resources for the
 * moving 3D graph visualizer.
 */
void ofApp::initializeExtraResourcesForMoving3DGraphVisualizer() {
    
    // After intializing all resources of Moving (2D) graph [which will be used by the 3D graph],
    // for each particle,]
    // intialize z-coordinate value, z-offset value, theta value, phi value,
    // theta-offset value and phi-offset value.
    
    for (int particle_number = 0; particle_number < total_number_of_particles_; particle_number++) {
        
        // Set z-coordinate to be a random number between 0 and 2000.
        particle_offset_z_axis_vector_.push_back(ofRandom(0, 2000));
        
        // Set theta and phi to be random values in [0, 2PI] and [0, PI] respectively
        
        particle_theta_value_vector_.push_back(ofRandom(0, 2 * PI));
        particle_phi_value_vector_.push_back(ofRandom(0, PI));
        
        // Set theta and phi offsets to be a random value in [0, 0.02]
        
        particle_theta_offset_vector_.push_back(ofRandom(0, 0.02));
        particle_phi_offset_vector_.push_back(ofRandom(0, 0.02));
        
        // Assign a random colour for the particle.
        particle_colors_.push_back(ofColor(ofRandom(255),ofRandom(255),ofRandom(255)));
        
    }
}

/**
 * The following function updates all the extra values for
 * the moving 3D graph visualizer.
 */
void ofApp::updateExtraValuesForMoving3DGraphVisualizer() {
    
    // After updating values which overlap with Graph (2D)
    // for all particles,
    // a new (x, y, z) position needs to be given, and theta and phi values have to be updated.
    
    for (int particle_number; particle_number < total_number_of_particles_; particle_number++) {
        
        // Calculate the new z-offset by adding delta distance (= velocity * delta time).
        particle_offset_z_axis_vector_[particle_number] += particle_velocity_ * delta_time_;
        
        // As per spherical coordinates,
        // x, y and z coordinates are calculated as:
        // x = (Perlin Noise b/w [0, 1]) * radius * cos (theta) * sin (phi)
        // y = (Perlin Noise b/w [0, 1]) * radius * sin (theta) * sin (phi)
        // z = (Perlin Noise b/w [0, 1]) * radius * cos (phi)
        
        particles_vector_[particle_number].x = ofNoise(particle_offset_x_axis_vector_[particle_number]) *
                                                graph_radius_ * cos(particle_theta_value_vector_[particle_number]) *
                                                sin(particle_phi_value_vector_[particle_number]);
        
        particles_vector_[particle_number].y = ofNoise(particle_offset_y_axis_vector_[particle_number]) *
                                                graph_radius_ * sin(particle_theta_value_vector_[particle_number]) *
                                                sin(particle_phi_value_vector_[particle_number]);
        
        particles_vector_[particle_number].z = ofNoise( particle_offset_z_axis_vector_[particle_number] ) * graph_radius_ *
                                                cos(particle_phi_value_vector_[particle_number]);
    
        // The theta and phi values for the particle are calculated by adding the respective offsets.
        
        particle_theta_value_vector_[particle_number] += particle_theta_offset_vector_[particle_number];
        particle_phi_value_vector_[particle_number] += particle_phi_offset_vector_[particle_number];
        
    }
}

/**
 * The following function is responsible for drawing
 * the 3D moving graph and associated
 * equalizer bars.
 */
void ofApp::drawEqualizerBarsAndMoving3DGraph() {
    
    // NOTE: The below values are tuned for a 1024 x 768 pixels window.
    
    // The below lines draw equalizer bars (rectangles) for the entire spectrum.
    //
    // For each band within the spectrum,
    // display the value with a rectangle.
    // (This results in the formation of the equalizer bars.)
    
    for (int bandNumber = 0; bandNumber < number_of_bands_; bandNumber++) {
        
        // In case, the band is the index deciding changes in
        // graph radius and particle velocity,
        // set draw colour to black.
        //
        // Else, set draw colour to gray.
        
        if (bandNumber == band_index_for_graph_radius_
            || bandNumber == band_index_for_particle_velocity_) {
            
            ofSetColor(255, 255, 255); // White color
        }
        else {
            ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255)); // Random color
        }
        
        // Draw the rectangle for the band with the specified colour.
        
        ofDrawRectangle(10 + bandNumber * 7, 700, 5, -spectrum_values_vector_[bandNumber] * 150);
    }
    
    // Save the current coordinate system, so that it can be restored later.
    ofPushMatrix();
    
    // Translate (0,0) to the center of the application window.
    // This allows us to draw the moving graph in the center of the screen.
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    //Draw particles as circles.
    
    // For each particle,
    // draw a circle at the specified position.
    // In this case, the circles are very small, and it is the edges that will be
    // more prominent with vibrant colours.
    
    for (int particleNumber = 0; particleNumber < total_number_of_particles_; particleNumber++) {
        ofDrawCircle(particles_vector_[particleNumber], 0.1);
    }
    
    // The below value is the threshold parameter for classifying the distance between two points
    // as "close".
    // (If the distance between two points is close, an edge of a random colour will be drawn between them.)
    
    // TODO: Allow toggling this value.
    
    float threshold_distance = 180;
    
    // For all the particles,
    // if any two particles are close to each other,
    // draw an edge of a random colour between them.
    // (TODO: Visualization Mode can be switched to draw triangles instead.
    // It will result in an entirely different visualization.)
    
    for (int index_one = 0; index_one < total_number_of_particles_; index_one++) {
        for (int index_two = index_one + 1; index_two < total_number_of_particles_; index_two++) {
            
            // Find the distance between the points.
            
            float distance_between_points =
            ofDist(particles_vector_[index_one].x, particles_vector_[index_one].y, particles_vector_[index_one].z,
                   particles_vector_[index_two].x, particles_vector_[index_two].y, particles_vector_[index_two].z);
            
            // If it is less than the threshold distance
            
            if (distance_between_points < threshold_distance) {
                
                // Decide the intensity of the colour of the line.
                float alpha = ofMap(distance_between_points, 0, 180, 150, 0);
                
                // Draw the line with the spcified colour and intensity.
                
                ofSetColor(particle_colors_[index_one], alpha);
                ofSetLineWidth(0.0001);
                
                ofDrawLine(particles_vector_[index_one], particles_vector_[index_two]); // First Visualization Mode
                // ofDrawTriangle(particles[index_one], particles[index_two], particles[index_one + 1]); // Second Visualization Mode
                
            }
        }
    }
    
    // Revert the translated coordinate system to the original system.
    
    ofPopMatrix();
    
    // The coordinate system is now restored. (0,0) is at the upper left corner.
}

/**
 * The following function deallocates allocated resources to
 * the 3D moving graph visualizer.
 */
void ofApp::deallocateExtraResourcesForMoving3DGraphVisualizer() {
    
    // Delete all elements from the vectors.
    
    particle_offset_z_axis_vector_.clear();
    
    particle_theta_value_vector_.clear();
    particle_phi_value_vector_.clear();
    
    particle_theta_offset_vector_.clear();
    particle_phi_offset_vector_.clear();
    
    particle_colors_.clear();
    
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
