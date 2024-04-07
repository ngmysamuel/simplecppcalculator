########################################################################################################################
# simplehttpserver build stage
########################################################################################################################

FROM alpine:3.17.0 AS build

RUN apk update && \
    apk add --no-cache \
    build-base \
    cmake

RUN echo "1"
RUN pwd
RUN ls -l

WORKDIR /simplecppcalculator

COPY src/ ./src/
COPY CMakeLists.txt .

RUN echo "2"
RUN pwd
RUN ls -l

WORKDIR /simplecppcalculator/build

RUN echo "3"
RUN pwd
RUN ls -l

RUN cmake -DCMAKE_BUILD_TYPE=Release ../ && cmake --build ./ --parallel 8

RUN echo "4"
RUN pwd
RUN ls -l
########################################################################################################################
# simplehttpserver image
########################################################################################################################

FROM alpine:3.17.0

RUN apk update && \
    apk add --no-cache \
    libstdc++

RUN addgroup -S shs && adduser -S shs -G shs
USER shs

RUN echo "5"
RUN pwd
RUN ls -l

COPY --chown=shs:shs --from=build \
    ./simplecppcalculator/build/src/simplecppcalculator \
    ./app/

ENTRYPOINT [ "./app/simplecppcalculator" ]