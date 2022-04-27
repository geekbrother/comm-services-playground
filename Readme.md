# COMM Services boilerplate

This is a boilerplate of [COMM project services](https://github.com/CommE2E/comm/tree/master/services)
for playground purposes with all dependencies included.

It is tested to be built on macOS, Ubuntu, or inside the Docker container.

## Why?

The COMM services have many dependencies and significant time to build the app.

In case you need to test some of your theory in a small part of the code, it can be built
and tested using this playground boilerplate. Without Docker and long building the whole service app
and complicated install scripts.

## Requirements

`cmake` and `g++` needs to be installed using the [homebrew](https://brew.sh/) command:

`brew install cmake g++`

To easily install all dependencies you need [vcpkg](https://vcpkg.io/) C++ dependency
manager installed on your system.

Before `cmake` you need to export `VCPKG` variable containing your vcpkg location by running:

`export VCPKG_ROOT="where vcpkg is installed"`.

## Build and run locally

To build and run the `main.cpp` first execute configure command
`cmake -B build -DCMAKE_BUILD_TYPE=Release` from the repo's root directory.
It will configure and install all the dependencies from `vcpkg.json` manifest file.

Then build using `make -C build -j` command.
A Binary app will be built in the `bin/testapp`.

## Build and run inside the Docker

To build a Docker image you can run:

`docker build -t testapp .`

It will create and build the app inside the docker image. You can run the app after by
running `docker run testapp /opt/tunnelbroker/bin/testapp`.

## VSCode integration

To use IntelliSense, debug and build the app from VSCode you need to install the CMake
extension. After installation, you need just open the repository directory and VSCode
automatically checks the includes.
You can build and debug without any additional setup steps.
