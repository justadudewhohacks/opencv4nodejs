ARG TAG

FROM justadudewhohacks/opencv:${TAG}

ARG NODE_MAJOR_VERSION

RUN \
apt-get update && \
apt-get install -y build-essential git curl && \
echo installing node: ${NODE_MAJOR_VERSION} && \
curl -sL https://deb.nodesource.com/setup_${NODE_MAJOR_VERSION}.x | bash && \
apt-get install -y nodejs python

COPY ./ ./
CMD ["bin/bash", "./ci/test/script/run-test.sh"]
