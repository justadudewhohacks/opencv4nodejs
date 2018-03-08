ARG TAG

FROM justadudewhohacks/opencv4nodejs-ci:${TAG}

RUN apt-get update
RUN apt-get install lcov -y

COPY ./ ./
CMD ["bin/bash", "./ci/cover/script/run-cover.sh"]





