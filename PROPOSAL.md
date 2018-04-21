# CS 126 Project Proposal: Music Visualization
## By Dipro Ray
A C++ application that loads stored music and creates visualizations about them, revealing technical aspects of the music in a very visually appealing manner.

## Description
This application is suited to the graphics capabilities of openFrameworks. I plan to use various 2d shapes and figures, graphs and maybe, 3d figures too. The application will provide a nice GUI allowing for customization in colors, shapes, different technical aspects of the sound being used. Here comes the necessity of the library I will be using, [Essentia](http://essentia.upf.edu/documentation/#) (I may use the openFrameworks add-on for Essentia instead of the library itself). It allows for extracting desired technical qualities (Perlin noise, time waveform, beats rate) of the audio files in a variety of way, allowing different kinds of visualization and analysis to be done.

## Libraries
1. [openFrameworks](http://openframeworks.cc/): The framework used to build the music environment and GUIs.
2. [Essentia](http://essentia.upf.edu/documentation/#): To extract float values for different qualities of the music OR another major music analysis library for C++
3. ofXAddons: ofXGui, ofxFft, ofX 3D Graphics

## Expected Features
1. A few visualizations (graph-based, textures etc.) based on the Perlin Noise of the music.
2. A visual display of the input and output signals of the Fast Fourier Transform on audio files in real-time (audio to be passed in through the microphone). This will make use of the ofxFFT addon of openFrameworks.
3. A nice GUI for using all visualization and analysis features as a stand-alone application.
4. (Hopefully/Additional Harder Goal) 3D solid-body visualizations of some technical aspects of the sound.


## Rough Checkpoints
1. Week 1 Code Review: Implementation of 3 or 4 different types of visualizations with a simple GUI for controlling features of these visualizations.
2. Week 2 Code Review: Nicer GUI - more visually pleasing, sliders to control different values. Overall, nicer application. More visualizations if time permits.
3. Slightly Ambitious Goal (to be worked on in the final week): 3D visualizations of various aspects of the sound.


------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
# Old Proposal
__I shall not be working on my old propsal project due to technical difficulties I have been facing in setting up the required libraries, such as Allegro. I spent quite a few hours in Office Hours trying to get it to work but there is some problem for Allegro on OS X, so I am not able to run it. As I am losing out on precious time for the project, I am choosing to not proceed with the old proposal.__


