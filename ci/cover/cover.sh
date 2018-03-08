#!/bin/sh
image=opencv4nodejs-ci_$1-with-coverage
docker build -t $image -f ./Dockerfile --build-arg TAG=$1 ../../
docker run -v $PWD/coverage-report:/test/coverage-report $image