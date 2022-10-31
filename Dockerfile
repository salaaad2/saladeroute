FROM alpine:latest
    MAINTAINER Filemon <qwe@asd.com>

RUN mkdir -p /opt/ft_traceroute/

RUN apk update && apk upgrade

RUN apk add --no-cache bash make cmake alpine-sdk strace

WORKDIR /opt/ft_traceroute

ENTRYPOINT tail -f /dev/null
