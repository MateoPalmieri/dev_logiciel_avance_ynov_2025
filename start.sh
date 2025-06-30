#!/bin/bash

# Démarrer les services en arrière-plan
docker-compose up -d mqtt server

# Compiler et lancer le client en mode interactif
docker-compose run --rm client
