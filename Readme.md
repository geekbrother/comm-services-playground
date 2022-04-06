# COMM Services boilerplate

This is a boilerplate of [COMM project services](https://github.com/CommE2E/comm/tree/master/services) for playground purposes with all dependencies included.

It tested to be usable on macOS, but Linux OS can be good too.

## Why?

The COMM services have many dependencies and significant time to build the app. 

In case you need to test some of your theory in a small part of the code it can be built and tested using this playground boilerplate. Without Docker and long building the whole service app.

## Requirements

**Cmake** needs to be installed using the [homebrew](https://brew.sh/).

To easily install all dependencies you need [vcpkg](https://vcpkg.io/) C++ dependency manager on your system.

Before running package bash scripts you need to export `VCPKG` variable containing your vcpkg location by running: 

`export VCPKG_ROOT="where vcpkg is installed"`.

After you need to install all dependencies by running `./install.sh` script from the project root directory.

## Build and run

To build and run the `main.cpp` you can run `./build.sh`. 

It will build the `testapp` and run it after successfully being built.

## Dependencies included

- folly
- boost
- amqpcpp
- cryptopp
- libuv
- glog
- aws-cpp-sdk-[core, dynamodb, s3]
