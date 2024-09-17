# ![](assets/synapselogo2.png)<!-- Synapse Engine -->

<!-- ![](assets/synapselogo2.png) -->

The Synapse Engine is an open-source game engine written in C++ using SDL2 as it's core graphics library.<!-- Default assets made by @CarlBirch from the BirchEngine -->

## Announcements
### 9/13/2024
I added the tilemap parser that uses TinyXML. If you clone the engine, DO NOT USE THE TILEMAP PARSER AT ALL. IT WILL RESULT IN A SEGMENTATION FAULT. As of now I'm actively trying to fix the issue and in the engine, I commented out the map functions that run with the engine.

### 9/17/2024
So it wasn't the tilemap parser that was broken, it was just the format of the engine map xml file. So I had to correct that and now it should be showing up fine, but it won't. I'll fix it later. But as of now, it seems that the issue is semi-fixed.

## Recent Updates
Beta 0.65 adds a better map parser, some bug fixes, and a camera movement system.

## Small Reminder
Currently, all of the releases are labeled as pre-releases because the engine is still in beta. so please remember that they're unstable versions of the engine and there's a chance that there's bugs in the code.

## Getting Started
To use the engine, you must be using MacOS or Linux, this doesn't work with Windows(sorry windows users). In addition, you must have either the GCC/G++ or Clang/Clang++ installed on your device. If you're using MacOS, then Xcode and HomeBrew must be installed on your device. Once you have these dependencies installed and working, you're ready to move onto the next step. Start off by installing SDL2 and SDL2_Image on your device.

Apt package manager:

```
$ sudo apt install libsdl2-dev
$ sudo apt install libsdl2-image-dev
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
