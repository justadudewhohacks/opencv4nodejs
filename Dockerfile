FROM node:18.8.0-alpine3.16 As build

WORKDIR /usr/src/app
RUN npm install -g rimraf pnpm
COPY binding.gyp package.json pnpm-lock.yaml tsconfig.json ./
COPY lib ./lib
COPY bin ./bin
COPY cc ./cc
COPY install ./install
COPY typings ./typings
RUN pnpm install --frozen-lockfile
# RUN apt update && apt -y upgrade && apt -y install build-essential cmake
RUN apk add --no-cache alpine-sdk cmake linux-headers
ENV OPENCV_BUILD_ROOT=/usr/src/opencv
ENV OPENCV4NODEJS_AUTOBUILD_OPENCV_VERSION=4.5.5
RUN npm run install
RUN rimraf src
RUN rimraf node_modules/**/*.{md,ts,map,h,c,cc,cpp,gyp,yml,txt}
RUN rimraf node_modules/{types,@eslint}
RUN rimraf node_modules/**/{LICENSE,.github,.npmignore,LICENSE.txt,.travis.yml,.eslintrc,sponsors}
RUN rimraf node_modules/*/{test,binding.gyp}
RUN find . -type f -empty -print -delete
RUN find . -type d -empty -print -delete
RUN rimraf /usr/src/opencv/opencv-*/build/{doc,3rdparty,*.txt,*.cmake,*.tmp,tmp,downloads,opencv_python_tests.cfg}
RUN rimraf /usr/src/opencv/opencv-*/**/{cmake,*.txt,*.cmake,*.make,*.tmp,*.o,*.md,*.cpp,Makefile,CMakeFiles,*.sh}
RUN rimraf /usr/src/opencv/opencv-*/build/modules/.firstpass/
RUN rimraf /usr/src/opencv/opencv-4.5.5-ecae4/build/share/opencv4/testdata
RUN rimraf /usr/src/opencv/opencv-4.5.5-ecae4/build/share/
RUN find /usr/src/opencv/ -type d -empty -delete

FROM node:18.8.0-alpine3.16 As production
ARG NODE_ENV=production
ENV NODE_ENV=${NODE_ENV}
WORKDIR /usr/src/app
COPY --from=build /usr/src/opencv /usr/src/opencv
ENV OPENCV_BUILD_ROOT=/usr/src/opencv
ENV OPENCV4NODEJS_AUTOBUILD_OPENCV_VERSION=4.5.5
# RUN cd test; pnpm install
# CMD ["node", "dist/main"]
