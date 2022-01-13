<<<<<<< HEAD
## -*- docker-image-name: "oby1/optioneer:1" -*-
# run this docker with the command: 
# docker run -it -p 3000:3000 optioneer

FROM oby1/emscripten_2.0.22-quantlib_1.22:1 As stage-build

ENV OPTIONEER /optioneer

=======
## -*- This image is based on work done by CaptorAB https://github.com/CaptorAB/quantlib-wasm -*-
## -*- docker-image-name: "optioneer" -*-
# run this docker with the command: 
# docker run -p 3000:3000 optioneer

# use the sha if you are logged in to dockerHub
# FROM sha256:052d71743ca6d4be41b87a3b2fdff9622e4ab7cdfb6d1c3205385ddfc238c08a As stage-build
FROM emscripten/emsdk:2.0.20 As stage-build

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get -y install automake autoconf libtool && \
    apt-get autoclean && \
    apt-get clean

ENV EMSCRIPTEN /emsdk_portable/sdk
ENV BOOST /boost
ENV BOOST_VERSION 1.75
ENV BOOST_UNDERSCORE_VERSION 1_75
ENV QUANTLIB /quantlib
ENV QUANTLIB_VERSION 1.22
ENV OPTIONEER /optioneer

# Download and unzip Boost
# Remove unwanted files. Keep Emscripten as is.
# Keep Boost and QuantLib header files and lib files.

# Boost
WORKDIR /tmp
RUN wget -c https://boostorg.jfrog.io/artifactory/main/release/${BOOST_VERSION}.0/source/boost_${BOOST_UNDERSCORE_VERSION}_0.tar.bz2 && \
    mkdir /boost && \
    tar --bzip2 -xf boost_1_75_0.tar.bz2 -C /boost --strip-components=1 && \
    rm -f boost_1_75_0.tar.bz2 && \
    rm -rf /boost/doc

# Build Boost for Emscripten

# [Getting Started on Unix Variants](https://www.boost.org/doc/libs/1_70_0/more/getting_started/unix-variants.html)
# [Testing Emscripten with C++11 and Boost](https://gist.github.com/arielm/69a7488172611e74bfd4)

WORKDIR ${EMSCRIPTEN}
RUN embuilder.py build zlib
ENV NO_BZIP2 1

WORKDIR ${BOOST}
RUN ./bootstrap.sh && rm -rf stage && \
	# ./b2 -a -j8 toolset=clang-emscripten link=static threading=single variant=release --with-system --with-filesystem --with-iostreams stage && \
	./b2 -a -j8 toolset=clang-emscripten link=static threading=single variant=release \
	--with-date_time --with-system --with-filesystem --with-iostreams --with-timer --with-math --with-random --with-thread stage && \
	rm -rf libs && \
	rm -rf lib/emscripten && \
	mkdir -p lib/emscripten && \
	cp stage/lib/*.a lib/emscripten && \
	find ${BOOST}/boost -type f  ! \( -name "*.h" -o -name "*.hpp" -o -name "*.ipp" \) -delete

# QuantLib

WORKDIR /tmp
RUN wget https://github.com/lballabio/QuantLib/releases/download/QuantLib-v${QUANTLIB_VERSION}/QuantLib-${QUANTLIB_VERSION}.tar.gz -O QuantLib-${QUANTLIB_VERSION}.tar.gz && \
	mkdir ${QUANTLIB} && \
	tar xzf QuantLib-${QUANTLIB_VERSION}.tar.gz -C ${QUANTLIB} --strip-components=1 && \
	rm -f QuantLib-${QUANTLIB_VERSION}.tar.gz 

# UNSETENV NO_BZIP2

# Build QuantLib with Boost and Emscripten

# How to use emconfigure and emmake, [see](https://emscripten.org/docs/compiling/Building-Projects.html)
# Also a good [guide](https://adamrehn.com/articles/creating-javascript-bindings-for-c-cxx-libraries-with-emscripten/)

WORKDIR ${QUANTLIB}
RUN echo $PWD
RUN emconfigure ./configure --with-boost-include=${BOOST} --with-boost-lib=${BOOST}/lib/emscripten --disable-shared && \
	emmake make -j4 && \
	# emmake make install && \
	# ldconfig && \
	rm -rf ${QUANTLIB}/Examples && \
	mv ${QUANTLIB}/ql/.libs/libQuantLib.a /tmp && \
	find ${QUANTLIB}/ql -type f  ! \( -name "*.h" -o -name "*.hpp" \) -delete && \
	mv /tmp/libQuantLib.a ${QUANTLIB}/ql/.libs && \
	rm -rf /usr/local/lib/libQuant*.* 

RUN apt-get clean

>>>>>>> dcdcf149a35e34447d3c884a56e99d3ef0de3e9c
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
<<<<<<< HEAD
# sha256:2ce3d9c4d432e462e9f0b4c20f531203221e35e339c98e0a895821dc95c64098
FROM node:17.3.1-bullseye-slim

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get autoclean 

=======
# use the sha if you are logged in to dockerHub
#FROM sha256:2ce3d9c4d432e462e9f0b4c20f531203221e35e339c98e0a895821dc95c64098
FROM node:17.3.1-bullseye-slim

>>>>>>> dcdcf149a35e34447d3c884a56e99d3ef0de3e9c
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
<<<<<<< HEAD
# docker run -it -p 3000:3000 optioneer
=======
# docker run -it -p 3000:3000 optioneer
>>>>>>> dcdcf149a35e34447d3c884a56e99d3ef0de3e9c
