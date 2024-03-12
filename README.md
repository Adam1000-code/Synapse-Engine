# <!-- ![](assets/synapselogo2.png) -->Synapse Engine

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

<!-- ![](assets/synapselogo2.png) -->

The Synapse Engine is an open-source game engine written in C++ using SDL2 as it's core graphics library. Default assets made by @CarlBirch from the BirchEngine

## Recent Updates
Beta 0.58 adds sprite animation, layers and also makes a small syntax change to the ECS(Entity Component System).

## Small Reminder
Currently, all of the releases are labeled as pre-releases because the engine is still in beta. so please remember that they're unstable versions of the engine and there's a chance that there's bugs in the code.

## Getting Started
To use the engine, you must be using MacOS or Linux, this doesn't work with Windows(sorry windows users). In addition, you must have either the GCC/G++ or Clang/Clang++ installed on your device, If you're using MacOS, then Xcode and HomeBrew must be installed on your device. Once you have these dependencies installed and working, you're ready to move onto the next step. Start off by installing SDL2 and SDL2_Image on your device.

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
brew install sdl2
brew install sdl2_image
```

## Downloading The Engine

Next, download the latest release of the engine's source code from the releases tab.
Once you have the source code zip, unzip it using what ever you would normally use.
Next, open your prefered text editor/IDE, open the source code folder and open up the main.cpp file.
Now You're ready to start your game!

## Using The Engine
