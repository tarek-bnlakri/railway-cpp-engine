
FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    protobuf-compiler-grpc \
    libgrpc++-dev \
    protobuf-compiler \
    libprotobuf-dev

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make -j$(nproc)

FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    libgrpc++1 \
    libprotobuf23 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build/railway_server .

EXPOSE 50051

CMD ["./railway_server"]
