#!/bin/sh
npm install --unsafe-perm
npm run build-debug
cd ./test
npm install --unsafe-perm
npm run cover
lcov -c -d ../build/Debug -o coverage/capture.info
lcov -e coverage/capture.info '*/cc/*' -o coverage/capturedcc.info
lcov -t opencv4nodejs -a coverage/capturedcc.info -o coverage/opencv4nodejs.info
genhtml --output-directory coverage coverage/opencv4nodejs.info
mv coverage/opencv4nodejs.info coverage-report