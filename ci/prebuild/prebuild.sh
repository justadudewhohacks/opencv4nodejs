#!/bin/sh
if [[ "$TRAVIS_OS_NAME" == "linux" ]];
then
    unset OPENCV4NODEJS_DISABLE_AUTOBUILD
fi
cd ../../ &&\
npm install --unsafe-perm &&\
npm run prebuild -- --tag-prefix "" -u $GITHUB_TOKEN;
