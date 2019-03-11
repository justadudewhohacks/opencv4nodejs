#!/bin/sh
if [[ "$TRAVIS_OS_NAME" == "linux" ]];
then
    image=opencv4nodejs-ci_$1
    docker build -t $image -f ./Dockerfile --build-arg TAG=$1 ../../
    docker run $image
elif [[ "$TRAVIS_OS_NAME" == "osx" ]];
then
    cd ../../test &&\
    npm install --unsafe-perm &&\
    npm run test-appveyor &&\
    npm run test-externalMemTracking
fi
