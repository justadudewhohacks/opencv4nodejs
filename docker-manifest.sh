#!/bin/bash
VERSION="6.2.5"
IMG=urielch/opencv-nodejs;
VARIANT="-debian"
VARIANT="-alpine"
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
ARCH=$(arch)
if [ $ARCH == 'aarch64' ]; then ARCH=arm64; fi
if [ $ARCH == 'x86_64'  ]; then ARCH=amd64; fi

printf "\nBuilding ${RED}${IMG}${NC} version \"${GREEN}${VERSION}${VARIANT}${NC}\"\n\n"
# prebuild image:
time docker build --build-arg VERSION=${VERSION} --pull --rm -f Dockerfile${VARIANT}  -t ${IMG}:${VERSION}${VARIANT}-${ARCH} .

printf "Pushing Image ${RED}:${VERSION}${VARIANT}-${ARCH}${NC}\n"
docker push ${IMG}:${VERSION}${VARIANT}-${ARCH}

printf "Image ${RED}${IMG}${NC}:${GREEN}${VERSION}${VARIANT}-${ARCH}${NC} Ready\n"
printf "Building manifest for version \"${GREEN}${VERSION}${VARIANT}${NC}\"\n\n"

TO_PUSH=(${IMG}:${VERSION}${VARIANT})
[ ${VARIANT} == '-debian' ] && TO_PUSH+=(${IMG}:latest)
[ ${VARIANT} == '-debian' ] && TO_PUSH+=(${IMG}:${VERSION})
for FINAL in ${TO_PUSH[@]}
do
  docker manifest rm       ${FINAL} 2> /dev/null || true
  docker manifest create   ${FINAL} ${IMG}:${VERSION}${VARIANT}-arm64 ${IMG}:${VERSION}${VARIANT}-amd64;
  docker manifest annotate ${FINAL} ${IMG}:${VERSION}${VARIANT}-arm64 --arch arm64;
  docker manifest annotate ${FINAL} ${IMG}:${VERSION}${VARIANT}-amd64 --arch amd64;
  docker manifest push     ${FINAL};
  docker manifest inspect  ${FINAL};
done

printf "${RED}${IMG}${NC} VERSION ${GREEN}${VERSION}${VARIANT}${NC} is now published. You can safely delete single arch tags from:\n"
printf "${GREEN}https://hub.docker.com/repository/docker/${IMG}/tags${NC}\n"
