#!/bin/sh
image=opencv4nodejs-ci:$1-node$2-with-coverage
docker build -t $image -f ./Dockerfile --build-arg TAG=$1 --build-arg NODE_MAJOR_VERSION=$2 ../../
docker run -v $PWD/coverage-report:/test/coverage-report $image