#!/bin/zsh
if [ -z $VCPKG_PATH ]; then 
    echo "Please export \$VCPKG_PATH variable with your vcpkg installation path.";
    echo "Example command: export VCPKG_PATH=~/Github/vcpkg";
    exit 1;
fi
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_PATH/scripts/buildsystems/vcpkg.cmake
