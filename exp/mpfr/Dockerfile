FROM alpine:3.5
MAINTAINER Oleks Shturmov <oleks@oleks.info>

RUN adduser -D -u 1000 franko

RUN apk add --update --no-cache \
  g++ make gmp-dev mpfr-dev

WORKDIR /home/franko

COPY src .

ENTRYPOINT ["/bin/ash"]
