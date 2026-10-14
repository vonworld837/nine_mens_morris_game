# Simulador del juego Nine men's morris en C++
## ¿Cómo usarlo?
-Descargar el archivo y ejecutarlo

-Se necesita dos jugadores (símbolos X y O), jugador con símbolo X empieza

-La interacción es en la terminal de comando de C++

-El juego va mostrando mensajes por cada jugada, movimientos inválidos e indicaciones para cada fase del juego

## Tablero
<img width="248" height="176" alt="tablero" src="https://github.com/user-attachments/assets/12117924-b6e5-414f-aa84-6e8b37107cf7" />

Los números representan la posiciones de las fichas, el jugador debe ingresar su número tanto para poner, mover o eliminar fichas. 
Las líneas representan los movimientos permitidos de una ficha de acuerdo a su posición en la fase de movimiento.
## Fases del juego y reglas
> La idea principal es formar tríadas con sus fichas en el tablero para capturar las fichas del oponente hasta ganar

El juego se divide en tres fases:
### Fase de colocación
-Cada jugador comienza con 9 fichas cada uno, las cuales van colocando uno por uno en el tablero.

-Si un jugador forma una tríada (tres fichas alineadas horizontal o verticalmente) puede capturar una ficha del oponente siempre 
y cuando dicha ficha no esté en una tríada. Si todas sus fichas del oponente están en una tríada, puede eliminar cualquier ficha de este.

-Continúan hasta que todas las fichas de los jugadores estén en el tablero y se pasa a la fase de movimiento. 

### Fase de movimiento 
-En esta fase los jugadores por turnos mueven sus fichas solamente a posiciones adyancentes y vacías para formar tríadas y capturar 
fichas del oponente.

### Fase de vuelo
-Cuando un jugador solo tiene 3 fichas, pasa a la fase de vuelo, donde puede mover sus fichas librememente a cualquier posición vacía 
del tablero.

### Gana un jugador cuando:
-Reduzca al oponente a dos fichas

-Cuando el oponente no pueda mover ninguna de sus fichas a posiciones adyacentes en la fase de movimiento.

-En esta versión no hay condiciones para empate, el juego queda en bucle. 

## Mejoras
-Establecer condiciones para empates

-Mejor visualización de la cantidad de fichas totales que tiene el jugador.

-Mejor organización del código (poner en archivos separados).

-Ampliación: Mejorar la interfaz gráfica de usuario (GUI) y la interactividad de las fichas, arrastrálas y colocarlas en vez de
escribir su posición.
