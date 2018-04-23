#!/bin/sh
export OPENCV4NODEJS_DISABLE_AUTOBUILD=1
echo installing
npm install --unsafe-perm
echo running tests
cd ./test
npm install --unsafe-perm
npm run test-docker
npm run test-externalMemTracking
exit $?