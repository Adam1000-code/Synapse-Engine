# <!-- ![](assets/synapselogo2.png) -->Synapse Engine

<!-- ![](assets/synapselogo2.png) -->

The Synapse Engine is an open-source game engine written in C++ using SDL2 as it's core graphics library. Default assets made by @CarlBirch from the BirchEngine

## Announcements
3/4/2024: The engine is going to be overhauled soon. Is there a reason I'm doing this? Yes. It's very limited, it can only be used to make RPG style games, and it just didn't really live up to my expectations. I'm hoping that the overhaul makes it function the way I want to and makes it easier for new game developers to use.

11/4/2024: The engine's overhaul has begun and I'm actively changing it. As of now, I've finished the rendering and texture manager for it, and I'm going to begin working on the movement code for transformations and vectors.

## Recent Updates
Beta 0.65 adds a better map parser, some bug fixes, and a camera movement system.

## Small Reminder
Currently, all of the releases are labeled as pre-releases because the engine is still in beta. so please remember that they're unstable versions of the engine and there's a chance that there's bugs in the code.

## Getting Started
To use the engine, you must be using MacOS or Linux, this doesn't work with Windows(sorry windows users). In addition, you must have either the GCC/G++ or Clang/Clang++ installed on your device. If you're using MacOS, then Xcode and HomeBrew must be installed on your device. Once you have these dependencies installed and working, you're ready to move onto the next step. Start off by installing SDL2 and SDL2_Image on your device.

Apt package manager:

```
$ sudo apt-get install libsdl2-dev
$ sudo apt-get install libsdl2-image-2.0-0-dev
```

DNF package manager:

```
$ sudo dnf install SDL2-devel
$ sudo dnf install SDL2_image-devel
```

Yum package manager:

```
$ yum install SDL2-devel
$ yum install SDL2_image-devel
```

HomeBrew (MacOS)

```
$ brew install sdl2
$ brew install sdl2_image
```

## Downloading The Engine

Next, download the latest release of the engine's source code from the releases tab.
Once you have the source code zip, unzip it using what ever you would normally use.
Next, open your prefered text editor/IDE, open the source code folder and open up the main.cpp file.
Now You're ready to start your game!

<!-- ## Using The Engine -->