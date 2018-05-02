# Music Visualizer :musical_note: :notes:
## CS 126 Final Project by Dipro Ray

### Application Summary
The application is a music visualizer. It contains 4 different types of visualizations that extract different technical features (such as intensity values for given frequency range, amplitude values, melody bands, rms etc.) from the audio, and uses this data to create visually appealing structures that move/change in relation with the sound (for example, using features such as Perlin Noise).

### Application Description
Going into a bit more detail, it has the following visualizations:
  * A bunch of randomly moving nodes of a graph that dynamically alters its edges, radius and shape with changes in intensity values of the music. I call this the Moving 2D Graph Visualization, because it is a moving/changing graph whose nodes move about in two dimensions according to variations in intensity value in a particular frequency band. This visualization is aesthetic, and draws on basic human notions of audio visualizations.
  * Built on top of the first visualization, the Moving 3D Graph Visualization is similar to the Moving 2D Graph Visualizations, but it has nodes that move about in three dimensions and has permanent edges. When visualized, it looks like a sphere mesh whose nodes on the sphere's surface look like they move about and rotate with the music. This visualization, too, is meant to be aesthetic in nature, with some more complex graphics work involved behind-the-scenes
  * A visualization displaying the amplitude waveform of the audio along with frequency (intensity) bars. This is called the FFT Visualization as it shows the input to the Fast Fourier Transform (the amplitude waveform) and its output (the intensity values for frequency bands). This visualization uses the ofxAudioAnalyzer add-on to perform the transform and get input and output data. This visualization is particularly interesting to note how the actual audio, input and output vary with each other.
  * A visualization displaying various technical, numerical aspects of the audio data. Its purpose is similar to the third visualization, in that it is meant to reveal intuitive relationships between the actual audio, intensity spectrum and other technical aspects (RMS, Pitch Confidence, Mel Bands, HPCP, MFCC, etc.)
  
### Building the Project
* The repository ```final-project-diproray``` contains a folder ```final-project-of``` that contains all files required to run the openFrameworks application. The easiest way to build and run the application is through Xcode.
* In ```final-project-of```, a ```.xcodeproj``` is present, which can be used to build and run the project on Xcode.
* Simply import the ```final-project-of``` in the openFrameworks project generator and insert the following add-ons:
    * [ofxAudioAnalyzer](https://github.com/leozimmerman/ofxAudioAnalyzer).
    * ofxAudioAnalyzer has a dependency on [ofxAudioDecoder](https://github.com/leozimmerman/ofxAudioDecoder). 
        * In ofxAudioDecoder, inside ```./libs/include/audiodecoder.h```, the preprocessor directive ```#include <MobileCoreServices/MobileCoreServices.h>``` has to be commented out to prevent a build error.
    * [ofxDatGui](https://github.com/braitsch/ofxDatGui)
    * ofxGui (included in the ```addons``` folder of openFrameworks)
    * ofxSvg (included in the ```addons``` folder of openFrameworks)

### Application Usage
Simply follow the instructions provided on screen to open various visualizations. Some visualizations have GUIs which allow you to modify a few visual features.

### Significant Libraries/Addons Used
* openFrameworks:- special default classes/add-ons used include:
  * ofSoundPlayer - to play various music files.
  * ofxSvg -  to display a SVG file as a background image for the Menu screen.
  * ofxGui - used to build a GUI in my application.
* Other openFrameworks add-ons: 
  * [ofxAudioAnalyzer](https://github.com/leozimmerman/ofxAudioAnalyzer) - used to analyze the music data and extract various technical data from it. It provided a openFrameworks wrapper for [Essentia](http://essentia.upf.edu/documentation/), the library I initially wanted to use.
  * [ofxAudioDecoder](https://github.com/leozimmerman/ofxAudioDecoder) - used by the audio analyzer to make use of a specialized sound player called ```ofSoundPlayerExtended```
  * [ofxDatGui](https://github.com/braitsch/ofxDatGui) - used to create a visually appealing GUI in a simpler manner than the default ofxGui.

### Relationship b/w the final application and my proposal
I'm fortunate to have been able to pull off all the features I had initially proposed, including the harder/ambitious goal I had set for myself.

### Acknowledgements
1. A lot of thanks to my code review moderator and code review peers for their valuable feedback that helped me improve the application.
2. This [book](https://www.safaribooksonline.com/library/view/mastering-openframeworks-creative/9781849518048/apb.html) whose Perlin Noise chapter helped me discover this wonderful technical concept, playing around with which allowed me think of music visualizations in a very innovative manner.
