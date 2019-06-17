#!/bin/sh
image=opencv4nodejs-ci:$1-node$2
docker build -t $image -f ./Dockerfile --build-arg TAG=$1 --build-arg NODE_MAJOR_VERSION=$2 ../../
docker run $image -e TEST_MODULE_LIST=$TEST_MODULE_LIST