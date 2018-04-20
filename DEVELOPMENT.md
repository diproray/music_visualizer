# Log/Development of the CS 126 Final Project

## #1
1. Project set up for initial proposal unsuccessful, because of some problem with the Allegro library's working on OS X. Proposal changed.
2. Downloaded tutorials to learn the basics of music visualization. Made some progress visualizing music as equalizer bars in openFrameworks.


## #2
1. Reasonable progress made on a rudimentary design of the music visualization application. 
    * I have been able to implement two visualizations of the music: one with equalizer level bars, and one with a graph of shifting vertices whose edges and size change with the change in music tone and change colours (I call this the Moving Graph Visualization).
    
2. [SOLVED] Problem faced: graphics shift very abruptly. Took some figure out that this can be solved using the technique of "smoothing" and a very helpful tool called [Perlin Noise](https://en.wikipedia.org/wiki/Perlin_noise).

## #3
1. The Moving Graph Visualization works nicely. Added colour for background and random colours for graph edges. Seems to work fine.
2. [UNSOLVED] Problem faced: I will be doing a few different types of visualizations. I wanted to implement OOP design by separating them into classes. However, openFrameworks elements like of draw functions, ofSoundplayer etc. can only be implemented in ofApp. I'm yet to figure out a way to "compartmentalize" these visualizations.
3. Moving Graph Visualization code added to repository and documentation added.
4. Looking into FFT Transform for audio files. I plan to make a visualization for this, which will take in input from the laptop microphone and execute the transformation and visualization in real time.
