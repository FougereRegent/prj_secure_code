FROM debian:stable-slim
WORKDIR /compilation
RUN apt-get update \
    && apt-get upgrade -yq \
    && apt-get install gcc make -yq
COPY ./app/. .
RUN make
FROM debian:stable-slim
WORKDIR /app
RUN apt-get update \
    && apt-get install gdb gdbserver -yq
COPY --from=0 /compilation/. /app/.
