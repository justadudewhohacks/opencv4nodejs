FROM justadudewhohacks/opencv3.2-contrib-node6

RUN apt-get update
RUN apt-get install lcov -y

COPY ./ ./
CMD ["bin/bash", "./ci/cover.sh"]




