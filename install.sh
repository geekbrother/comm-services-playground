#!/bin/zsh
if [ -z $VCPKG_ROOT ]; then 
    echo "Please export \$VCPKG_ROOT variable with your vcpkg installation path.";
    echo "Example command: export VCPKG_ROOT=~/Github/vcpkg";
    exit 1;
fi
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
