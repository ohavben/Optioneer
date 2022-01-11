## -*- docker-image-name: "emscripten-quantlib" -*-
FROM emscripten/emsdk:2.0.20

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
	

#wget https://github.com/lballabio/QuantLib/releases/download/QuantLib-v1.22/QuantLib-1.22.tar.gz -O QuantLib-1.22.tar.gz && mkdir 1.22 && tar xzf QuantLib-${QUANTLIB_VERSION}.tar.gz -C 1.22 --strip-components=1 && rm -f QuantLib-1.22.tar.gz 

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

WORKDIR /src
CMD ["/bin/bash"]

#cp -r ./src/quantlib/json.hpp ./src/quantlib/quantlib.cpp ../config/emscripten && docker run -v ${pwd}:/dist --rm ql "emcc --bind -I${EMSCRIPTEN}/system/include -I${QUANTLIB} -I${BOOST} -O3 -s MODULARIZE=1 -s EXPORT_ES6=1 -s BUILD_AS_WORKER=1 -s \"EXPORTED_RUNTIME_METHODS=['addOnPostRun']\" -s EXPORT_NAME=QuantLib -s TOTAL_MEMORY=64MB -o /quantlib.js quantlib-embind.cpp ${QUANTLIB}/ql/.libs/libQuantLib.a"