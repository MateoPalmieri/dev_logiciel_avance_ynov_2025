FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y g++ mosquitto-clients && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY main.cpp .

RUN g++ -std=c++11 -o main main.cpp -lpthread

CMD ["./main"]