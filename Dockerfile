FROM debian:stable-slim
WORKDIR /compilation
COPY ./app/. .
RUN apt-get update \
    && apt-get upgrade -yq \
    && apt-get install gcc make -yq

RUN make
FROM debian:stable-slim
WORKDIR /app
COPY --from=0 /compilation/. /app/.
RUN apt-get update \
    && apt-get upgrade -yq

CMD ["ls"]