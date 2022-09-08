#!/bin/sh
VERSION=6.2.4
IMG=urielch/opencv-nodejs
FINAL=${IMG}:${VERSION}
FINAL=${IMG}:latest
docker manifest create ${FINAL} ${IMG}:arm64-${VERSION} ${IMG}:${VERSION}-AMD64
docker manifest annotate ${FINAL} ${IMG}:arm64-${VERSION} --arch arm64
docker manifest annotate ${FINAL} ${IMG}:${VERSION}-AMD64 --arch amd64
docker manifest push ${FINAL}
docker manifest inspect ${FINAL}

# debug with:
# ocker run -it --rm urielch/opencv-nodejs:latest /bin/bash
# ls /usr/local/lib/node_modules/@u4/opencv4nodejs/build/Release
