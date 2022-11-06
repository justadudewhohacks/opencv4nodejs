#!/bin/bash
VERSION="6.2.5"
IMG=urielch/opencv-nodejs;
BASE=debian
RED="\e[31m"
GREEN="\e[32m"
NC="\e[0m"

# $(grep '"version"' package.json | cut -d : -f2 | cut '-d"' -f2)

if [ ! $# -eq 1 ]
then
 printf "Usage ${GREEN}${0} version_number${NC}\n"
 # echo "vesion number not profig using ${VERSION} from package.json"
 printf "Check previous version at https://hub.docker.com/repository/docker/${IMG}\n"
 exit 1;
else
 VERSION="$1"
fi

git pull

if ! [[ "$VERSION" =~ ^[0-9]+\.[0-9]+\.[0-9]+$ ]]
then
 printf "version_number \"${GREEN}${VERSION}${NC}\" must be a like 1.0.0\n"
 exit 1
fi

set -e

printf \n"Building ${RED}${IMG}${NC} version \"${GREEN}${BASE}-${VERSION}${NC}\"\n\n"

ARCH=$(arch)
if [ $ARCH == 'aarch64' ]; then ARCH=arm64; fi
if [ $ARCH == 'x86_64'  ]; then ARCH=amd64; fi

# prebuild image:
time docker build --build-arg VERSION=${VERSION} --pull --rm -f Dockerfile-${BASE}  -t ${IMG}:${VERSION}-${BASE}-${ARCH} .

printf "Pushing Image ${RED}:${VERSION}-${BASE}-${ARCH}${NC}\n"
docker push ${IMG}:${VERSION}-${BASE}-${ARCH}

printf "Image ${RED}${IMG}${NC}:${GREEN}${VERSION}-${BASE}-${ARCH}${NC} Ready\n"
printf "Building manifest for version \"${GREEN}${VERSION}-${BASE}${NC}\"\n\n"

for FINAL in ${IMG}:${VERSION}-${BASE} ${IMG}:latest
do
  docker manifest rm       ${FINAL} 2> /dev/null || true
  docker manifest create   ${FINAL} ${IMG}:${VERSION}-${BASE}-arm64 ${IMG}:${VERSION}-${BASE}-amd64;
  docker manifest annotate ${FINAL} ${IMG}:${VERSION}-${BASE}-arm64 --arch arm64;
  docker manifest annotate ${FINAL} ${IMG}:${VERSION}-${BASE}-amd64 --arch amd64;
  docker manifest push     ${FINAL};
  docker manifest inspect  ${FINAL};
done

printf "${RED}${IMG}${NC} VERSION ${GREEN}${VERSION}-${BASE}${NC} is now published. You can safely delete single arch tags from:\n"
printf "${GREEN}https://hub.docker.com/repository/docker/${IMG}/tags${NC}\n"
