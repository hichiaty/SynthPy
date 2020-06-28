# SynthPy

SynthPy is a Python3 library that hosts vst2/vst3/AU in a C++ shared library with python bindings using [JUCE](https://github.com/juce-framework/JUCE), [Maximilian](https://github.com/micknoise/Maximilian) and [Boost C++](https://www.boost.org/). The plan is to build this into a modern neural network for synthesizers library with maximum DSP compatibility across operating systems.

## Getting Started

To begin using this library you must build the C++ back-end for your OS then simply import in python.

### Prerequisites

* Boost C++ compiled with python (>=1.73)
* Python libraries (>=3.6)
* msvc-14.2 for windows

## Installing

### Windows

* Assuming you have the Boost C++ binaries compiled with Python and the Visual Studio IDE, open up the build solution and add header includes and library paths for Boost and your Python installation.

* Press Build project!

* Rename the .dll binary to .pyd and copy it to your python project path.


### MacOS

If you don't have it already, [get brew](https://brew.sh/).

Get Boost with Brew (Trust me, it's way easier than compiling yourself)
```
brew install boost-python
```

If you want to suffer, you can also install boost manually [see here.](https://www.boost.org/doc/libs/1_73_0/doc/html/quickbook/install.html)

Now just open the Xcode project and build it! 


### Linux

Gotta get the old boost headers and libs

Ubuntu:
```
sudo apt-get install libboost-all-dev
```

Arch:
```
sudo pacman -Ss boost
```

Fedora:
```
sudo yum install boost-devel
```

If your distribution's package manager doesn't have boost [you can compile from source here](https://www.boost.org/doc/libs/1_73_0/more/getting_started/unix-variants.html)

[JUCE](https://github.com/juce-framework/JUCE) itself has a list of dependancies for Linux; it's a gigantic library. Depending on your distribution and setup you may already have some / all of the following libraries. If you are on Ubuntu, the following commands will install all your dependancies. If you are on another distro, check the JUCE docs.

```
sudo apt-get -y install llvm
sudo apt-get -y install clang
sudo apt-get -y install libfreetype6-dev
sudo apt-get -y install libx11-dev
sudo apt-get -y install libxinerama-dev
sudo apt-get -y install libxrandr-dev
sudo apt-get -y install libxcursor-dev
sudo apt-get -y install mesa-common-dev
sudo apt-get -y install libasound2-dev
sudo apt-get -y install freeglut3-dev
sudo apt-get -y install libxcomposite-dev
sudo apt-get -y install libcurl4-gnutls-dev
```


So now to build the actual SynthPy library for Linux:
```
cd Builds/LinuxMakefile/
make
```

Congrats if you have made it this far without losing your sanity! If you still have problems, file an issue and I'll try my best to help, although you're probably just better off googling your problem.

## Does It Even Work?

Change directory to where the library (.pyd/.so) file is and run:
```
python
```
```
import SynthPy as sp
```
If this doesn't scream at you, you're good to go!

## TODO:
* Generate some data
* Process data
* Write model
* Test
* Pray to the ML gods that it works


## Acknowledgments

* This code is mostly based off [RenderMan](https://github.com/fedden/RenderMan/blob/master/README.md) just modernized and more compatible with different OSes and VSTs.