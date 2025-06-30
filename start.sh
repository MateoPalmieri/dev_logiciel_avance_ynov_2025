#!/bin/bash

# Démarrer tous les services
docker-compose up -d mqtt server

# Attendre que le serveur soit prêt
sleep 5

# Lancer le client en mode interactif
echo -e "\n\033[1;36m=== LANCEMENT DU CLIENT ===\033[0m"
docker-compose run --rm client
