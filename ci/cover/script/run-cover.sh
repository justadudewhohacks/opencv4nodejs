#!/bin/sh
export OPENCV4NODEJS_DISABLE_AUTOBUILD=1
npm install --unsafe-perm
npm run build-debug
cd ./test
npm install --unsafe-perm
npm run cover
lcov -c -d ../build/Debug -o $(pwd)/coverage/capture.info
lcov -e coverage/capture.info '*/cc/*' -o $(pwd)/coverage/capturedcc.info
lcov -t opencv4nodejs -a coverage/capturedcc.info -o $(pwd)/coverage/opencv4nodejs.info
genhtml --output-directory coverage $(pwd)/coverage/opencv4nodejs.info
mv coverage/opencv4nodejs.info coverage-report
exit $?