## -*- docker-image-name: "oby1/optioneer:1" -*-
# run this docker with the command: 
# docker run -it -p 3000:3000 optioneer

FROM oby1/emscripten_2.0.22-quantlib_1.22:1 As stage-build

ENV OPTIONEER /optioneer

WORKDIR ${OPTIONEER}
RUN mkdir ${OPTIONEER}/dist
# adding the cpp files first to not trigger a build on any file change
ADD ./src/quantlib .

RUN emcc \
	--bind \
	-I${EMSCRIPTEN}/system/include \
	-I${QUANTLIB} \
	-I${BOOST} \
	-O3 \
	-s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
	-s BUILD_AS_WORKER=1 \
	-s "EXPORTED_RUNTIME_METHODS=['addOnPostRun']" \
	-s EXPORT_NAME=QuantLib \
	-s TOTAL_MEMORY=64MB \
	-o ${OPTIONEER}/dist/quantlib.js quantlib-embind.cpp ${QUANTLIB}/ql/.libs/libQuantLib.a

# This image is a version of node:17.3.1-bullseye-slim 
# sha256:2ce3d9c4d432e462e9f0b4c20f531203221e35e339c98e0a895821dc95c64098
FROM node:17.3.1-bullseye-slim

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get autoclean 

WORKDIR /usr/src/app
ADD package.json package-lock.json /usr/src/app/
RUN npm install

ADD .. /usr/src/app/
COPY --from=Stage-Build optioneer/dist ./public

EXPOSE 3000

CMD "npm" "start"
#CMD ["npm run start"]
#CMD [ "/bin/bash" ]

# run this docker with the command: 
# docker run -it -p 3000:3000 optioneer