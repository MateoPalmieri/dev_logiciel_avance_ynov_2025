const express = require('express');
const mqtt = require('mqtt');
const path = require('path');
const app = express();

let currentWinner = null;
let currentQuestion = null;
let playerCount = 0;

const mqttClient = mqtt.connect('mqtt://localhost:1883');
mqttClient.on('connect', () => {
  mqttClient.subscribe('buzzers/winner');
  mqttClient.subscribe('buzzers/playerCount');
  mqttClient.subscribe('buzzers/question');
});

mqttClient.on('message', (topic, message) => {
  if (topic === 'buzzers/winner' && !currentWinner) {
    currentWinner = message.toString();
    console.log(`Joueur ${currentWinner} a buzzé !`);
  }

  if (topic === 'buzzers/playerCount') {
    playerCount = parseInt(message.toString());
    console.log(`Nombre de joueurs : ${playerCount}`);
  }

  if (topic === 'buzzers/question') {    
    currentQuestion = message.toString();
    console.log(`Question : ${currentQuestion}`);
  }
});

app.get('/players', (req, res) => {
  res.json({ count: playerCount });
});

app.get('/question', (req, res) => {
  res.json({ question: currentQuestion });
});

app.use(express.static(path.join(__dirname, 'public')));
app.use(express.json());

app.get('/winner', (req, res) => {
  res.json({ winner: currentWinner });
});

// Should communicate with the CLI to reset the game
app.post('/reset', (req, res) => {
  currentWinner = null;
  res.status(204).end();
});

app.listen(3000, () => {
  console.log('Serveur lancé sur http://localhost:3000');
});

module.exports = app; // Export the app for testing