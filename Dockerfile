FROM alpine:latest

RUN apk add --no-cache \
    g++ \
    make \
    automake \
    autoconf \
    libstdc++ 

WORKDIR /app

COPY . /app

RUN autoreconf -i && ./configure && make clean && make

ENTRYPOINT ["./lr1"]

