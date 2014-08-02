# Phylogenetic Trees Visualization

This is the code and documentation for the project I created in 2006 as a minor project.

## Documentation

Please read README.md and [project documentation](doc/index.asciidoc).

## Sequence Alignment

The sequence alignment and tree building is actually done using ClustalW. So first we need to build clustalw1.83.

Download it:

    wget -c http://www.microextreme.net/software/clustalw1.83.UNIX.tar.gz.tar

Unzip it to a folder

    tar zxf clustalw1.83.UNIX.tar.gz.tar
	cd clustalw1.83
	make

Now invoke the clustalw program:

	bin/clustalw

## How to build the visualization tools?

On Ubuntu 14.04

    $ apt-get install cmake libsoqt-dev
    $ cd path/to/source/

Now we will build two binaries:

    phyloviz$ mkdir build
    phyloviz$ cd build/
    phyloviz/build$ cmake ../
    -- The C compiler identification is GNU 4.8.2
    -- The CXX compiler identification is GNU 4.8.2
    -- Check for working C compiler: /usr/bin/cc
    -- Check for working C compiler: /usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Found PkgConfig: /usr/bin/pkg-config (found version "0.26") 
    -- Looking for Q_WS_X11
    -- Looking for Q_WS_X11 - found
    -- Looking for Q_WS_WIN
    -- Looking for Q_WS_WIN - not found
    -- Looking for Q_WS_QWS
    -- Looking for Q_WS_QWS - not found
    -- Looking for Q_WS_MAC
    -- Looking for Q_WS_MAC - not found
    -- Found Qt4: /usr/bin/qmake (found version "4.8.6") 
    -- Found Coin3D: /usr/lib/x86_64-linux-gnu/libCoin.so  
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/saleem/work/learn/mine/phyloviz/build
    phyloviz/build$ make
    Scanning dependencies of target ev-iv
    [ 50%] Building CXX object CMakeFiles/ev-iv.dir/src/ev-iv/ev-iv.cc.o
    Linking CXX executable ev-iv
    [ 50%] Built target ev-iv
    Scanning dependencies of target ph2iv
    [100%] Building C object CMakeFiles/ph2iv.dir/src/ph2iv/ph2iv.c.o
    Linking C executable ph2iv
    [100%] Built target ph2iv

The two executables have been built by now:

    phyloviz/build$ ls ph2iv ev-iv

Further details on using these tools is show in [documentation](doc/index.asciidoc) file. Please refer that document for "Generation and Visualization of Phylogenetic Trees".

## Sample Data and other software

You can find some sample data and other software at: http://tuxdna.in/files/bioinformatics/


## Debugging

If you like to build debug the code using a debugger you may want to generate debug binaries:

    $ cmake -DCMAKE_BUILD_TYPE=Debug ../

