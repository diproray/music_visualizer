# Log/Development of the CS 126 Final Project

## #1 Wednesday 04/18/2018
1. Project set up for initial proposal unsuccessful, because of some problem with the Allegro library's working on OS X. Proposal changed.
2. Downloaded tutorials to learn the basics of music visualization. Made some progress visualizing music as equalizer bars in openFrameworks.


## #2 Thursday 04/19/2018
1. Reasonable progress made on a rudimentary design of the music visualization application. 
    * I have been able to implement two visualizations of the music: one with equalizer level bars, and one with a graph of shifting vertices whose edges and size change with the change in music tone and change colours (I call this the Moving Graph Visualization).
    
2. [SOLVED] Problem faced: graphics shift very abruptly. Took some figure out that this can be solved using the technique of "smoothing" and a very helpful tool called [Perlin Noise](https://en.wikipedia.org/wiki/Perlin_noise).

## #3 Friday 04/20/2018
1. The Moving Graph Visualization works nicely. Added colour for background and random colours for graph edges. Seems to work fine.
2. [UNSOLVED/PARTIALLY SOLVED] Problem faced: I will be doing a few different types of visualizations. I wanted to implement OOP design by separating them into classes. However, openFrameworks elements like of draw functions, ofSoundplayer etc. can only be implemented in ofApp. I'm yet to figure out a way to "compartmentalize" these visualizations. [Edit: I am using Application States in ofApp.cpp to take care of this for now. See (5).]
3. Moving Graph Visualization code added to repository and documentation added.
4. Looking into FFT Transform for audio files. I plan to make a visualization for this, which will take in input from the laptop microphone and execute the transformation and visualization in real time.
5. Thought about how I could solve my problem of separating into classes. Trying that didn't work. Separating them into different files didn't work either. So I decided to create Application States for each visualization and the menu. The Application State guides which functions are to be run.
6. Before working on the FFT Transform, I decided to try and extend my Moving 2D Graph Visualization to a 3D one. I looked up some tutorials and ways in which I could do this - and the method which would allow for most code reuse was adding an extra Z dimension, and theta and phi spherical angles.
7. My Moving 3D graph works, yay! Cleaned up the code for it, ensured I reused as much code as possible, then created an Application State for it.
8. Committed my second visualizations code to the repo! :D
9. Back to working on FFT transform and Visualization. Made progress learning how to use the ofxFft addon for openFrameworks. Thinking about taking audio input in real time through the microphone.
