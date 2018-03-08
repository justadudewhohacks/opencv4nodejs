#!/bin/sh
image=opencv4nodejs-ci_$1
docker build -t $image -f ./Dockerfile --build-arg TAG=$1 ../../
docker run $image