#!/bin/bash

ARTIFACT_NAME="trackle_wrapper.node"
ARTIFACT_BUILD_PATH="./build/Release/${ARTIFACT_NAME}"
TRACKLE_WRAPPER_DIST_PATH="./dist/app/lib/"
ARTIFACT_DIST_PATH="${TRACKLE_WRAPPER_DIST_PATH}/${ARTIFACT_NAME}"

# Build configuration
echo "Build configuration..."
node-gyp configure
# Build Execution
echo "Building ${ARTIFACT_BUILD_PATH}..."
node-gyp build

echo -e "\n"

# Move compiled files to dist
if [ -f ${ARTIFACT_BUILD_PATH} ]; then
    if [ ! -d ${ARTIFACT_DIST_FOLDER} ]; then
        echo "Creating ${ARTIFACT_DIST_FOLDER}..."
        mkdir -p ${ARTIFACT_DIST_FOLDER}
    fi

    echo "Moving ${ARTIFACT_BUILD_PATH} to ${ARTIFACT_DIST_PATH}..."
    mv ${ARTIFACT_BUILD_PATH} ${ARTIFACT_DIST_PATH}

    # Remove build files
    echo "Removing build files..."
    rm -rf ./build
else
    echo "Build failed! ${ARTIFACT_BUILD_PATH} not found!"
fi


