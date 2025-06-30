const express = require('express');
const mqtt = require('mqtt');
const path = require('path');
const app = express();

// let currentWinner = null;

// const mqttClient = mqtt.connect('mqtt://localhost:1883');
// mqttClient.on('connect', () => {
//   mqttClient.subscribe('buzzers/winner');
// });

// mqttClient.on('message', (topic, message) => {
//   if (!currentWinner) {
//     currentWinner = message.toString();
//     console.log(`Le joueur ${currentWinner} a buzzé !`);
//   }
// });

let currentWinner = null;
let playerCount = 0;

const mqttClient = mqtt.connect('mqtt://localhost:1883');
mqttClient.on('connect', () => {
  mqttClient.subscribe('buzzers/winner');
  mqttClient.subscribe('buzzers/playerCount');
});

mqttClient.on('message', (topic, message) => {
  if (topic === 'buzzers/winner' && !currentWinner) {
    currentWinner = message.toString();
    console.log(`🎯 Joueur ${currentWinner} a buzzé !`);
  }

  if (topic === 'buzzers/playerCount') {
    playerCount = parseInt(message.toString());
    console.log(`👥 Nombre de joueurs : ${playerCount}`);
  }
});

app.get('/players', (req, res) => {
  res.json({ count: playerCount });
});


app.use(express.static(path.join(__dirname, 'public')));
app.use(express.json());

app.get('/winner', (req, res) => {
  res.json({ winner: currentWinner });
});

app.post('/reset', (req, res) => {
  currentWinner = null;
  res.status(204).end();
});

app.listen(3000, () => {
  console.log('Serveur lancé sur http://localhost:3000');
});
