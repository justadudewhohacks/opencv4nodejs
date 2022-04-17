#!/bin/sh
export OPENCV4NODEJS_DISABLE_AUTOBUILD=1
npm install -g pnpm &&\
echo installing &&\
pnpm install --unsafe-perm &&\
echo running tests &&\
cd ./test &&\
pnpm install --unsafe-perm &&\
pnpm run test-docker &&\
pnpm run test-externalMemTracking