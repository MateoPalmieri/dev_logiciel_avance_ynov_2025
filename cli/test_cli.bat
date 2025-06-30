@echo off
echo Test CLI Quiz Room

:: Simulate a game with 2 players, question, player 1 buzz then quit

(
echo 2
echo Quelle est la capitale de la France ?
echo 1
echo n
) | main.exe > test_output.txt

findstr "Joueur 1 a buzzé" test_output.txt >nul
if %errorlevel%==0 (
  echo ✅ Test réussi
) else (
  echo ❌ Joueur gagnant non détecté
)
