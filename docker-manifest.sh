#!/bin/bash
# start MacOS docker:
# open -a /Applications/Docker.app
# security -v unlock-keychain ~/Library/Keychains/login.keychain-db
# Headless docker on MacOS doc: https://github.com/docker/for-mac/issues/6504

VERSION="6.2.5"
IMG=urielch/opencv-nodejs;
RED="\e[31m"
GREEN="\e[32m"
NC="\e[0m"
VARIANTS=(-debian -alpine)
# ARCHS=(arm64 amd64 s390x ppc64le mips64le 386 armv5 armv7 armv8)
ARCHS=(arm64 amd64)
LATEST_VARIANT=${VARIANTS[0]}
NAMESPACE=${IMG%/*}
REPO=${IMG#*/}
TOKEN=''
DOCKER_LOGIN="https://hub.docker.com/v2/users/login"
DOCKER_TAG="https://hub.docker.com/v2/namespaces/${NAMESPACE}/repositories/${REPO}/tags"

if [ ! -z "${DOCKER_CLEAN_TOKEN}" ]
then
  login_data() {
  cat <<EOF
{ "username": "${DOCKER_USERNAME}", "password": "${DOCKER_CLEAN_TOKEN}" }
EOF
  }
  TOKEN=`curl -s -H "Content-Type: application/json" -X POST -d "$(login_data)" "${DOCKER_LOGIN}" | jq -r .token`
fi

# $(grep '"version"' package.json | cut -d : -f2 | cut '-d"' -f2)

if [ ! $# -eq 1 ]
then
 printf "Usage ${GREEN}${0} version_number${NC}\n"
 # echo "vesion number not profig using ${VERSION} from package.json"
 printf "Check previous version at https://hub.docker.com/repository/docker/${IMG}\n"
 if [ ! -z "${TOKEN}" ]
 then
  echo last tags:
  curl -s "${DOCKER_TAG}?page_size=5" -H "Authorization: JWT ${TOKEN}" | jq -r .results[].name
 fi
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
if [ $ARCH == 'x86_64' ]; then ARCH=amd64; fi
# TODO add aliases for s390x ppc64le mips64le 386 armv5 armv7 armv8
for VARIANT in "${VARIANTS[@]}"
do
  printf "\nBuilding ${RED}${IMG}${NC} version \"${GREEN}${VERSION}${VARIANT}${NC}\"\n\n"
  # prebuild image:
  time docker build --build-arg VERSION=${VERSION} --pull --rm -f Dockerfile${VARIANT} -t ${IMG}:${VERSION}${VARIANT}-${ARCH} .
  printf "Pushing Image ${RED}${IMG}${NC}:${GREEN}${VERSION}${VARIANT}-${ARCH}${NC}\n"
  docker push ${IMG}:${VERSION}${VARIANT}-${ARCH}
  printf "Image ${RED}${IMG}${NC}:${GREEN}${VERSION}${VARIANT}-${ARCH}${NC} Ready\n"
done

for VARIANT in "${VARIANTS[@]}"
do
  printf "Building manifest for version \"${GREEN}${VERSION}${VARIANT}${NC}\"\n\n"
  TO_PUSH=(${IMG}:${VERSION}${VARIANT})
  [ "${VARIANT}" == "${LATEST_VARIANT}" ] && TO_PUSH+=(${IMG}:latest)
  [ ${VARIANT} == '-debian' ] && TO_PUSH+=(${IMG}:${VERSION})

  for FINAL in ${TO_PUSH[@]}
  do
    docker manifest rm       ${FINAL} 2> /dev/null || true
    CREATE_CMD=(docker manifest create ${FINAL})
    for ARCH in "${ARCHS[@]}"; do CREATE_CMD+=(${IMG}:${VERSION}${VARIANT}-${ARCH}); done
    ${CREATE_CMD[@]}
    for ARCH in "${ARCHS[@]}"; do docker manifest annotate ${FINAL} ${IMG}:${VERSION}${VARIANT}-${ARCH} --arch ${ARCH}; done;
    docker manifest push     ${FINAL};
    docker manifest inspect  ${FINAL};
  done
  printf "${RED}${IMG}${NC} VERSION ${GREEN}${VERSION}${VARIANT}${NC} is now published."
done

printf "You can safely delete single arch tags from:\n${GREEN}https://hub.docker.com/repository/docker/${IMG}/tags${NC}\n"

if [ ! -z "${TOKEN}" ]
then
  printf "${RED}Deleting${NC} temporary tags."
  echo Deleting TMP tags
  for VARIANT in "${VARIANTS[@]}"
  do
    for ARCH in "${ARCHS[@]}"
    do 
     echo DELETE "${DOCKER_TAG}/${VERSION}${VARIANT}-${ARCH}"
     curl -X DELETE -H "Authorization: JWT ${TOKEN}" "${DOCKER_TAG}/${VERSION}${VARIANT}-${ARCH}"
   done
  done 
fi

printf "${GREEN}cleanUP done.${NC}"
