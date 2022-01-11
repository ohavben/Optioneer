#docker run -v ${pwd}:\Users\ohavb\OneDrive\Documents\Optioneer-Master\optioneer-main\src\quantlib -it --rm qlmaker /bin/bash
#docker run -v ${pwd}:/Users/ohavb/OneDrive/Documents/Optioneer-Master/optioneer-main/src/quantlib -it --rm qlmaker /bin/bash
#docker run -v ${pwd}/src/quantlib:/dist --rm qlmaker cp -r quantlibMod.js quantlibMod.wasm /dist
#docker run -v ${pwd}/src/quantlib:/dist --rm qlmaker cp -r quantlibNoMod.js quantlibNoMod.wasm /dist
FROM emscripten-quantlib

WORKDIR /

COPY /src/quantlib/json.hpp /src/quantlib/quantlib-embind.cpp ./

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
	-o /quantlibMod.js quantlib-embind.cpp ${QUANTLIB}/ql/.libs/libQuantLib.a
CMD [ "/bin/bash" ] 
#emcc --bind -I${EMSCRIPTEN}/system/include -I${QUANTLIB} -I${BOOST} -O3 -s MODULARIZE=1 -s EXPORT_ES6=1 -s BUILD_AS_WORKER=1 -s "EXPORTED_RUNTIME_METHODS=['addOnPostRun']" -s EXPORT_NAME=QuantLib -s TOTAL_MEMORY=64MB -o /quantlibMod.js quantlib-embind.cpp ${QUANTLIB}/ql/.libs/libQuantLib.a