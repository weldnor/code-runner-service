FROM ubuntu:latest as build

WORKDIR /root

COPY . .

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt  install cmake clang gcc -y && \
    cmake -S . -B ./build -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=FALSE && \
    cmake --build ./build --config Release -j8


FROM ubuntu:latest

WORKDIR /root

RUN apt update && \
    apt install python3 -y

COPY --from=build /root/app/CRS /root/CRS

RUN chmod +x /root/CRS

ENTRYPOINT /root/CRS

EXPOSE 8000