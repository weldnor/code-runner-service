FROM ubuntu:latest as build

WORKDIR /root

COPY . .

RUN apt update && \
    apt  install cmake gcc -y && \
    cmake -S . -B ./build -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=FALSE && \
    cmake --build ./build --config Release -j8


FROM ubuntu:latest

WORKDIR /root

COPY --from=build /root/app/CRS /root/CRS

RUN chmod +x /root/CRS

ENTRYPOINT /root/CRS

EXPOSE 8000