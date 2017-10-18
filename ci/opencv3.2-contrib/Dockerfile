FROM justadudewhohacks/opencv3.2-contrib-node6

RUN apt-get update

COPY ./ ./
RUN npm install --unsafe-perm \
&& npm run build-debug

WORKDIR test
RUN npm install --unsafe-perm
CMD ["npm", "run", "cover"]
