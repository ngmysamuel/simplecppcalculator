########################################################################################################################
# simplehttpserver build stage
########################################################################################################################

FROM alpine:3.17.0 AS build

RUN apk update && \
    apk add --no-cache \
    build-base \
    cmake

RUN echo "1"
RUN echo pwd
RUN echo ls -l

WORKDIR /simplecppcalculator

COPY src/ ./src/
COPY CMakeLists.txt .

RUN echo "2"
RUN echo pwd
RUN echo ls -l

WORKDIR /simplecppcalculator/build

RUN echo "3"
RUN echo pwd
RUN echo ls -l

RUN cmake -DCMAKE_BUILD_TYPE=Release ../ && cmake --build ./ --parallel 8

########################################################################################################################
# simplehttpserver image
########################################################################################################################

FROM alpine:3.17.0

RUN apk update && \
    apk add --no-cache \
    libstdc++

RUN addgroup -S shs && adduser -S shs -G shs
USER shs

COPY --chown=shs:shs --from=build \
    ./simplecppcalculator/build/src/simplehttpserver \
    ./app/

ENTRYPOINT [ "./app/simplecppcalculator" ]