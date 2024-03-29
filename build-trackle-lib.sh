#!/bin/bash

# Check env variables
if [[ ! -n ${TRACKLE_LIB_FOLDER_NAME} ]]; then
    TRACKLE_LIB_FOLDER_NAME="trackle-library-cpp-v4"
fi

if [[ ! -n ${TRACKLE_LIB_DIST_PATH} ]]; then
    TRACKLE_LIB_DIST_PATH="./dist/app/lib/"
fi


# Set variables
TRACKLE_LIB_PATH="./lib/${TRACKLE_LIB_FOLDER_NAME}"

# Create dist path
if [ ! -d ${TRACKLE_LIB_DIST_PATH} ]; then
    mkdir -p ${TRACKLE_LIB_DIST_PATH}
fi

# Build
make TRACKLE_LIB_PATH=${TRACKLE_LIB_PATH} TRACKLE_DIST_PATH=${TRACKLE_LIB_DIST_PATH} 