/*
  MONITOR DE PULSO ESP32 + SENSOR DE PULSO ANALOGICO + ST7789 240x280 - VERSION 1

  >>> PEGA AQUI EL CODIGO DE LA VERSION 1 <<<

  Diferencias de la version 1 respecto a la version 2 (segun el informe):
   - Indicador: circulo rojo que se enciende 150 ms despues de cada latido.
   - Sin buzzer.
   - Serial Plotter con las series Pulso y BPM a 100 datos por segundo.
   - Mismo procesamiento de senal y calculo de BPM.

  Conexiones: igual que la version 2, pero sin el buzzer (GPIO25).
*/
