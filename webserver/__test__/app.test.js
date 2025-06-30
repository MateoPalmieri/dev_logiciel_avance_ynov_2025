const request = require('supertest');
const express = require('express');
const app = require('../app');

describe('API REST Quiz Room', () => {
  it('GET /players doit renvoyer un nombre', async () => {
    const res = await request(app).get('/players');
    expect(res.statusCode).toBe(200);
    expect(res.body).toHaveProperty('count');
    expect(typeof res.body.count).toBe('number');
  });

  it('GET /winner doit renvoyer un champ winner', async () => {
    const res = await request(app).get('/winner');
    expect(res.statusCode).toBe(200);
    expect(res.body).toHaveProperty('winner');
  });

//   it('POST /reset doit réinitialiser le gagnant', async () => {
//     const res = await request(app).post('/reset');
//     expect(res.statusCode).toBe(200);
//     expect(res.body).toEqual({ success: true });
//   });
});
