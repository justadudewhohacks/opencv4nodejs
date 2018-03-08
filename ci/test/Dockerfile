ARG TAG

FROM justadudewhohacks/opencv4nodejs-ci:${TAG}

COPY ./ ./
CMD ["bin/bash", "./ci/test/script/run-test.sh"]
