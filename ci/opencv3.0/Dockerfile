FROM justadudewhohacks/opencv3.0-node6

RUN apt-get update

COPY ./ ./
RUN npm install --unsafe-perm \
&& npm run build-debug

WORKDIR test
RUN npm install --unsafe-perm
CMD ["npm", "run", "cover"]
