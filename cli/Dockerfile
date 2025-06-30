FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y g++ mosquitto-clients && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copier uniquement le fichier source
COPY main.cpp .

# Compiler et produire main.exe
RUN g++ -std=c++11 -o main.exe main.cpp -lpthread

# Commande par défaut - lance le programme compilé
CMD ["./main.exe"]
