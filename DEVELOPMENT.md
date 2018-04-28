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
2. [SOLVED] Problem faced: I will be doing a few different types of visualizations. I wanted to implement OOP design by separating them into classes. However, openFrameworks elements like of draw functions, ofSoundplayer etc. can only be implemented in ofApp. I'm yet to figure out a way to "compartmentalize" these visualizations. [Edit: I am using Application States in ofApp.cpp to take care of this for now. See (5).] [New edit: Solved! I had to include ofMain.h which I was not doing!]
3. Moving Graph Visualization code added to repository and documentation added.
4. Looking into FFT Transform for audio files. I plan to make a visualization for this, which will take in input from the laptop microphone and execute the transformation and visualization in real time.
5. Thought about how I could solve my problem of separating into classes. Trying that didn't work. Separating them into different files didn't work either. So I decided to create Application States for each visualization and the menu. The Application State guides which functions are to be run.
6. Before working on the FFT Transform, I decided to try and extend my Moving 2D Graph Visualization to a 3D one. I looked up some tutorials and ways in which I could do this - and the method which would allow for most code reuse was adding an extra Z dimension, and theta and phi spherical angles.
7. My Moving 3D graph works, yay! Cleaned up the code for it, ensured I reused as much code as possible, then created an Application State for it.
8. Committed my second visualizations code to the repo! :D **Funnily enough, although it took quite some time, I was able to figure out how to implement my 3D visualization (my ambitious goal for my project) pretty early on! :D**
9. Back to working on FFT transform and Visualization. Made progress learning how to use the ofxFft addon for openFrameworks. Thinking about taking audio input in real time through the microphone.
10. Solved my separation into classes problem. Thankfully, my code was pretty modular so separating them into classes did not take much time. The 3D Visualizer inherits from the 2D Visualizer too!
11. Got a real-time FFT Visualization of time and frequency waveform working but its execution appears to be buggy, though I don't understand what's wrong with my code. For now, I have a simple FFT frequency waveform of real time audio input ready.
12. Added toggling mode between lines and triangle for Moving 2D graph visualization.

## #4 Saturday 04/21/2018 - Wednesday 04/25/2018
1. Tweaked code to make visualization look better.
2. Started looking into addons to use.
3. Found ofxAudioAnalyzer to be the perfect add-on I needed - it's a wrapper for the Essentia library I planned to use in the first place!
4. [SOLVED] Downloaded it, but ran into a few problems setting it up. Took a day to resolve those issues. A dependency failed to compile initially but a few modifications did the trick.
5. Able to build examples, went through the code and documentation.
6. Made a plan for my next steps
   * Time to add the FFT visualization with time and frequency waveforms. 
   * Also, since my application is a music visualization and analysis application, I decided to make use of the various functions of       ofxAudioAnalyzer to return highly technical aspects of the music playing, which I will be displaying as a Technical Analysis Visualization.
   * Need to add sliders for my first two visualizations to allow for customization.
   * Future: Make a better Menu Screen. Maybe, add capability to shuffle/play different songs.

## #5 Thursday 04/26/2018
1. Standalone prototype of the FFT Visualization is ready!
2. Everything works fine, but I encounter a few problems here.
3. [SOLVED] The graphics change way too fast. It's so fast that it doesn't even look nice. I decide that I need to "slow down" the graphics. Looked it up online, and realised I had to change the frame rate (set to 60 by default). Changing the frame rate to 30 makes the graphics look nicer and allows the user to actually see the waveforms for a moment before they change.
4. [SOLVED] Since I am using 1024 bands/buffer size, the frequency waveform looks very detailed but the time waveform is really blurry. Looking it up online, I find that since 1024 is a pretty high band size, plotting the waveform points for alternating points will make it less blurry while still keeping the same time waveform.
5. Time to add this visualization to my application.

## #5 Friday 04/27/2018
1. [SOLVED] Ran into some problems using ofSoundPlayerExtender within an object. Figured out a workaround - use the extended sound player within ofApp itself, and pass the sound buffer as an input to the FFT visualizer.
2. Integrated the FFT visualization into my application.
3. [SOLVED] Couldn't create a new object everytime this visualization is selected. Couldn't assume that the ofxAudioAnalyzer would be deleted automatically. (Evidently, it does not.) Workaround was to only use one object of the FFT visualizer.
4. Decided to do the same for the other visualizers too. It didn't make any difference in the application. Initially, I assumed using the same object every time would cause problems. Guess I was wrong.
5. Added a feature to switch songs between two songs.
6. [SOLVED] ofSoundPlayerExtended caused some problems - unload() did not work properly for it. To solve this, I had to look through the code of ofxSoundPlayerExtended. I found that load() first unloads to remove any previous song, and then loads. That was causing the error. So I removed the unload() command.
7. Song switching works perfectly! (It, however, needs to be done in the menu screen. If done during a visualization, the app crashes, understandably.) Allowed switching feature to work only in menu screen.
8. Looking into using [ofxDatGui](https://github.com/braitsch/ofxDatGui) for toggling various values within my visualizations.

## #6 Saturday 04/28/2018
1. Got the GUI working for the moving 2D graph visualization! Committed the code to the repository.
