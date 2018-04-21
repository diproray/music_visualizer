# CS 126 Project Proposal: Music Visualization
## By Dipro Ray
A C++ application that loads stored music and creates visualizations about them, revealing technical aspects of the music in a very visually appealing manner.

## Description
This application is suited to the graphics capabilities of openFrameworks. I plan to use various 2d shapes and figures, graphs and maybe, 3d figures too. The application will provide a nice GUI allowing for customization in colors, shapes, different technical aspects of the sound being used. Here comes the necessity of the library I will be using, [Essentia](http://essentia.upf.edu/documentation/#) (I may use the openFrameworks add-on for Essentia instead of the library itself). It allows for extracting desired technical qualities (Perlin noise, time waveform, beats rate) of the audio files in a variety of way, allowing different kinds of visualization and analysis to be done.

## Libraries
1. [openFrameworks](http://openframeworks.cc/): The framework used to build the music environment and GUIs.
2. [Essentia](http://essentia.upf.edu/documentation/#): To extract float values for different qualities of the music OR another major music analysis library for C++
3. ofXAddons: ofXGui, ofX 3D Graphics

## Expected Features
1. A few visualizations (graph-based, textures etc.) based on the Perlin Noise of the music.
2. A visual display of the input and output signals of the Fast Fourier Transform on audio files in real-time (audio to be passed in through the microphone). This will make use of the ofxFFT addon of openFrameworks.
3. A nice GUI for using all visualization and analysis features as a stand-alone application.
4. (Hopefully/Additional Harder Goal) 3D visualizations of various aspects of the sound.


## Rough Checkpoints
1. Week 1 Code Review: Implementation of 3 or 4 different types of visualizations with a simple GUI for controlling features of these visualizations.
2. Week 2 Code Review: Comparative Visualizations of different technical aspects of the audio files, using Essentia. Nicer GUI - more visually pleasing, sliders to control different values.
3. Slightly Ambitious Goal (to be worked on in the final week): Combine music visualizations with particle visualizations to simulate how particles would vibrate naturally in the presence of such music. Might use Box2D library here!


------------------------------------------------------
------------------------------------------------------
------------------------------------------------------
# Old Proposal
__I shall not be working on this project due to technical difficulties I have been facing in setting up the required libraries, such as Allegro. I spent quite a few hours in Office Hours trying to get it to work but there is some problem for Allegro on OS X, so I am not able to run it. As I am losing out on precious time for the project, I am choosing to not proceed with this project.__

# CS 126 Project Proposal: Flappy Illini :large_orange_diamond: :baby_chick: :large_blue_diamond:
A C++ application remake of the iconic [Flappy Bird](https://en.wikipedia.org/wiki/Flappy_Bird)! :bird:

## Summary (or tl;dr)
__A C++ game of Flappy Bird, using [openFrameworks](http://openframeworks.cc/) and [ofBox2d](https://github.com/vanderlin/ofxBox2d) (and possibly, [Allegro](http://liballeg.org/)). The project will include special features beyond a basic Flappy Bird game such as: coin collection, level demarcations, game layout customizations, and hopefully [dynamic game difficulty balancing (DGB)](https://en.wikipedia.org/wiki/Dynamic_game_difficulty_balancing) and split-screen multiplayer mode.__

## Description
The C++ application will be similar to Flappy Bird. 
There is a character, the bird, which has to be saved from hitting tubes as it "jumps" through the holes in these tubes. Attached below is a simple gif depiction of Flappy Bird.  
  
<p align="center"> 
<img src="https://raw.githubusercontent.com/mchakravarty/lazy-lambda/master/images/LazyLambdaLoop.gif">
</p>
  
Implementing this basic Flappy Bird game will require thinking about:
1. **Superimposition of the tubes over the background layout.** I intend to let the background be "built" in the application, rather than an image.
2. **An endless building of the game environment.** I need to figure out how to randomly generate the tubes and the holes in them to ensure a game of reasonable difficulty. 
3. **Physics behind the jumps of the bird.** I have to figure out how to model these jumps as minor trajectories the bird is thrown into.
After implementing a basic Flappy Bird game, I intend to add additional features, which are described below.
4. **Implementing a simple, yet fun, GUI** for Welcome screen, Game Over screen, Paused screen with some fun features beyond the ordinary expectations from a game.

I intend to add quite a few additional features to the basic Flappy Bird game.

## Additional Features
1. **Game Layout Elements Customization**: Customization of background layout, colors of background and tubes, bird etc.
2. **Level Demarcations**: Demarcate environment into levels, and adjust scores accoordingly.
3. **Collection of Coins, Jackpots, Mystery Boxes, Power Packs**: Common game elements which can be incorporated into Flappy Bird. Power packs - allowing the user to fly through a certain number of tubes automatically - will require some thinking as to how the system would display the animation for passing through tubes with holes at random heights.
4. **Split-screen Mulitplayer mode**: Splitting the window into half, vertically or horizontally, to allow two (or possibly, more) players to play the game simultaneously.
5. **[Dynamic Game Difficulty Balancing (DGB)](https://en.wikipedia.org/wiki/Dynamic_game_difficulty_balancing)**: This one of the more complex extra features I would like to add, and it would be cool if it can be pulled off. DGB tries to adapt the game environment to the player's proficiency. Doing so would require a mathematical approach to determining what variation in the heights of adjacent tube holes corresponds to what degree of difficulty. A way I thought I could tune my game to increase in difficulty is to model a "cost" function which on minimizing increases difficulty by a bit, and use past tube hole heights data to perform stochastic gradient descent on the coefficients of the function to generate an increasingly difficult game environment. As is evident, I am trying to apply the notion of [stochastic gradient descent](https://en.wikipedia.org/wiki/Stochastic_gradient_descent) from machine learning here. In case this turns out to be very complex or very time consuming, I hope to figure out a more intuitive/practical way or increasing game difficulty.

## Libraries Being Used
1. [openFrameworks](http://openframeworks.cc/): The framework used to build the game environment and GUIs.
2. [ofBox2d](https://github.com/vanderlin/ofxBox2d): An openFrameworks add-on that can help simulate the physics of the bird jumping.
3. [Allegro](http://liballeg.org/): A game-engine library for C++. I am not yet sure if I will use this, but it is potentially very useful in making game environment customizations easy (primarily because of it being able to parse TMX files generated by [Map Editor](http://www.mapeditor.org/)).
4. An ML library for C++ to perform Stochastic Gradient Descent. I am still looking into any alternative lightweight libraries (game data shouldn't be too large), but for now, [mlpack](https://github.com/mlpack/mlpack) is what I plane to use for DGB.

My development environment will be [Xcode](https://developer.apple.com/xcode/).

## Rough (Ideal) Plan / Checkpoints for the next 4 Weeks
1. **Week 1: Running Prototype of a basic Flappy Bird game, Detailed Plan for Next Phase**
    * Get a Flappy Bird game up and running as an openFrameworks application.
    * Plan the next phase - adding GUIs, improving game engine code, etc.
2. **Week 2: Running, Visually Pleasing Prototype of the game mentioned in Decription**
3. **Week 3: Tweaking Code for Layout Customizations, and Adding Code for non-trivial, but non-difficult, additional features**
4. **[Final] Week 4: Achieve DGB. Ensure extensive documentation and project file structures. Polish any rough game details.**

## Relevant Personal Background
1. Significant programming experience in C++ (approx. 2 years)
2. Knowledge of stochastic gradient descent and popular ML techniques (courtesy of [CS 361](https://courses.engr.illinois.edu/cs361/sp2018/))
