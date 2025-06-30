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