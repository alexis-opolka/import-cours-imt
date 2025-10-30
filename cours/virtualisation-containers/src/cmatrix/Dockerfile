FROM alpine

### OpenContainers Specs
LABEL org.opencontainers.image.authors="Alexis Opolka <contact@alexis-opolka.dev>"
LABEL org.opencontainers.image.source="https://gitlab.com/alexis-opolka/import-cours-imt/-/tree/master/cours/virtualisation-containers/src/cmatrix/Dockerfile"
LABEL org.opencontainers.image.description="Container image for CMatrix"


LABEL maintainer="Alexis Opolka <contact@alexis-opolka.dev>"


RUN apk update &&\
  apk add git autoconf automake alpine-sdk ncurses-dev ncurses-static &&\
  mkdir -pv /usr/lib/kbd/consolefonts
RUN git clone https://github.com/abishekvashok/cmatrix /cmatrix &&\
  cd /cmatrix &&\
  autoreconf -i &&\
  ./configure LDFLAGS="-static" &&\
  make

WORKDIR /cmatrix
ENTRYPOINT ["/cmatrix/cmatrix"]
