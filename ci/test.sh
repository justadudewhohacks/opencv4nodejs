#!/bin/sh
export OPENCV4NODEJS_DISABLE_AUTOBUILD=1
npm install --unsafe-perm
cd ./test
npm install --unsafe-perm
npm run test-docker