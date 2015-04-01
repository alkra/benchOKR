Pour (aider à) choisir le langage utilisé, étant donné que nous aurons de nombreux appels récursifs à faire, j'ai codé un test dans différents langages.

J'ai utilisé un exemple simple nécéssitant beaucoup d'appels récursifs mais ne générant pas de trop gros nombres : la suite de Fibonacci. Elle est définie pour n >= 0 ainsi :

F(n+2) := F(n+1) + F(n)
F(0) := 1
F(1) := 1

L'algorithme naïf utilisé génère 2^n appels récursifs. Il a été codé de manière semblable en C, en Python, et en Javascript, puis compilé/interprété. Le temps a été mesuré fiablement en C et approximativement (par un musicien) en Python et Javascript.

Le résultat de l'exécution de F(40) est : 2s en C, plus de 30s en Python et Javascript.
