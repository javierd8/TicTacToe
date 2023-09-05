# TicTacToe
UACJ Inteligencia Artificial - Busqueda Semi-informada (TicTacToe)


***Reglas de comportamiento***
- IA siempre es primer movimiento  
- El 2do jugador tendra movimientos random (aka otro jugador)  
- La IA seleccionara su movimiento segun lo siguiente
- > (Prioridad: Contraataque -> Centro -> Esquina -> Borde)
  - Contraataque   
    - Tomar una WIN cuando se tenga la oportunidad
    - Evitar un WIN del otro jugador en su sig turno (aka bloquearlo)
  - Centro  
    - Tomarlo en el primer turno o cuando se de la oportunidad
  - Esquina  
    - Cuando el otro jugador haya jugado borde una esquina adyacente a su movimiento dando prioridad a la casilla con el menor numero segun la enumeracion del tablero
  - Borde  
    - Cuando el otro jugador haya jugado esquina jugamos un borde adyacente a su movimiento dando prioridad a la casilla con el menor numero segun la enumeracion del tablero  
