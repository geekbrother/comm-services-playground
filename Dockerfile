FROM ubuntu:22.04

ARG SERVICE_NAME=tunnelbroker
ENV VCPKG_ROOT=/opt/vcpkg
ENV TZ=US/Eastern
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && apt -y install build-essential gcc cmake git curl git\
  unzip tar zip ninja-build pkg-config python3

# Vcpkg installation
RUN git clone https://github.com/Microsoft/vcpkg.git $VCPKG_ROOT
WORKDIR $VCPKG_ROOT
ENV VCPKG_FORCE_SYSTEM_BINARIES 1
RUN ./bootstrap-vcpkg.sh
RUN ./vcpkg integrate install
RUN ./vcpkg integrate bash && echo "export PATH=\$PATH:$VCPKG_ROOT" >>~/.bashrc

# Server building
RUN mkdir /opt/$SERVICE_NAME
WORKDIR /opt/$SERVICE_NAME
COPY . .
RUN ./clean
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release -G Ninja
RUN ninja -C build

CMD ["bash"]
