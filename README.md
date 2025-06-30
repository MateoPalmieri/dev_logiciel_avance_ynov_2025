# 🧠 Quiz Room avec Buzzers

Ce projet simule une salle de quiz avec des buzzers virtuels. Il utilise :

- Un **client CLI en C++** pour simuler les joueurs
- Un **serveur Node.js** qui écoute les buzzers via MQTT
- Une **IHM Web (HTML/JS)** pour afficher le gagnant et le nombre de joueurs
- Un **broker MQTT (Mosquitto)** pour la communication temps réel

---

## 📁 Structure du projet

rendu_final/
├── cli/ # Programme C++ des joueurs
│ ├── main.cpp
│ └── main.exe
├── server/ # Serveur Node.js + MQTT + IHM
│ ├── app.js
│ ├── package.json
│ └── public/
│ └── index.html
├── .vscode/ # Tâches de compilation pour VS Code (optionnel)
│ └── tasks.json
├── install.bat # Script d'installation Windows (optionnel)
└── README.md

---

## ⚙️ Prérequis

Il faut avoir installé :

### 🟢 Node.js

- Télécharger depuis [https://nodejs.org](https://nodejs.org)
- Vérifier : `node -v`, `npm -v`

### 🟦 Compilateur C++ (MinGW recommandé)

- Installe via [MSYS2](https://www.msys2.org) ou [MinGW](https://sourceforge.net/projects/mingw/)
- Vérifier : `g++ --version`

### 🔁 Mosquitto (broker MQTT)

- Télécharger ici : [https://mosquitto.org/download/](https://mosquitto.org/download/)
- Inclure les **tools** (`mosquitto_pub`, `mosquitto_sub`)
- Ajouter `C:\Program Files\mosquitto` à la variable `PATH`
- Vérifier :
    - `mosquitto`
    - `mosquitto_pub --help`

---

## 🚀 Lancement du projet

### 1. Lancer le broker MQTT

Dans un terminal :

```bash
mosquitto
```

Dans un autre terminal :

```bash
cd rendu_final/server
npm install     # à faire une seule fois
npm start
```

```bash
cd rendu_final/cli
g++ -std=c++11 -o main.exe main.cpp -lpthread    # À faire si il n'y a pas de fichier main.exe
./main.exe
```

## 🐳 Compilation automatique du C++ avec Docker

Le système Docker compile automatiquement le programme C++ lors de la construction de l'image :

1. Lors du premier lancement (`docker-compose up --build`), le Dockerfile :
    - Installe g++ et les outils MQTT
    - Compile `main.cpp` en `main.exe`
    - Stocke l'exécutable dans le volume partagé

2. Lors des lancements suivants :
    - Le fichier `main.exe` compilé est réutilisé
    - Pour forcer une recompilation, utilisez :
      ```bash
      docker-compose up --build client
      ```

3. Pour nettoyer et recompiler :
   ```bash
   docker-compose build --no-cache client
      ```


### Fonctionnement :

1. Lorsque vous lancez `docker-compose up --build` :
   - Docker crée une image avec le compilateur C++
   - Compile `main.cpp` en `main.exe`
   - Monte le fichier exécutable dans votre dossier local via le volume

2. Le fichier `main.exe` généré sera :
   - Disponible dans le conteneur (`/app/main.exe`)
   - Copié dans votre dossier `cli/` local grâce au volume monté

3. Pour développer :
   - Modifiez `main.cpp` localement
   - Pour recompiler :
     ```bash
     docker-compose up --build client
     ```

Cette solution offre le meilleur des deux mondes : compilation automatique dans un environnement contrôlé tout en gardant l'exécutable disponible localement.

## 🐳 Lancement Automatique

1. **Première utilisation** :
```bash
chmod +x start.sh  # Rendre le script exécutable
./start.sh
