# COMM Services boilerplate

This is a boilerplate of [COMM project services](https://github.com/CommE2E/comm/tree/master/services)
for playground purposes with all dependencies included.

It is tested to be built on macOS, Ubuntu, or inside the Docker container.

# Why?

The COMM services have many dependencies and significant time to build the app.

In case you need to test some of your theory in a small part of the code, it can be built
and tested using this playground boilerplate. Without Docker and long building the whole
service app and complicated install scripts.

# Requirements

## macOS

`cmake, g++, openssl` needs to be installed using the [homebrew](https://brew.sh/) command:

`brew install cmake g++ openssl`

To easily install all the C++ dependencies you need [vcpkg](https://vcpkg.io/) C++ dependency
manager installed on your system. You can install it by the following commands:

`git clone https://github.com/Microsoft/vcpkg.git && ./vcpkg/bootstrap-vcpkg.sh`

You need to install manually `aws-sdk-cpp` before configure due to this bug
by invoking the following command:

`./vcpkg install "aws-sdk-cpp[dynamodb,s3]" --recurse`

## Linux Ubuntu

You need to install required packages using the `apt` package manager:

`apt update && apt -y install build-essential gcc cmake git curl git \ unzip tar zip libssl-dev ninja-build pkg-config python3`

To easily install all the C++ dependencies you need [vcpkg](https://vcpkg.io/) C++ dependency
manager installed on your system. You can install it by the following commands:

`git clone https://github.com/Microsoft/vcpkg.git && ./vcpkg/bootstrap-vcpkg.sh`

# Build and run locally

Before `cmake` you need to export `VCPKG` variable containing your vcpkg location by running:

`export VCPKG_ROOT="path/to/vcpkg"`.

To build and run the `main.cpp` first execute configure command from the
repo's root directory:

`cmake -B build -DCMAKE_BUILD_TYPE=Release`

It will configure and install all the dependencies from `vcpkg.json` manifest file.

Then build using `make -C build -j` command. A Binary app will be built in the
`bin/testapp`.

# Build and run inside the Docker

To build a Docker image you can run:

`docker build -t testapp .`

It will create and build the app inside the docker image. You can run the app after by
running `docker run testapp`.

By default, Dockerfile builds the slim release image.
If you want to build the container for development purposes
(For example, to attach VSCode to) you need to run the build command with the
BULD_TYPE=Debug:

`docker build -t testapp . --build-arg BUILD_TYPE=Debug`

In this case, the dev environment will be installed and not removed after
the app is built. Binary will be built in the debug mode as well.

# Build and run using VSCode integration

To use IntelliSense, debug and build the app from VSCode you need to install the CMake
extension into it. To resolve the requirements installed by the VCPKG you need to add
the vcpkg toolchain to your VSCode JSON settings (Global, User or Workspace):

```
{
  ...
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "/Users/max/Github/vcpkg/scripts/buildsystems/vcpkg.cmake"
    }
  ...
}
```

After these installation steps, you need just open the service repository directory and
VSCode automatically checks the includes and make the configure process.
You can build and debug without any additional setup steps using the internal IDE tools.
