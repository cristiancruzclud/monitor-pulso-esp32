<div align="center">

# 💓 Monitor de Pulso Cardíaco con ESP32

### Sensor de pulso analógico · Pantalla TFT ST7789 · Corazón animado · Buzzer

*Un latido, una señal, una pantalla: fotopletismografía educativa hecha con un microcontrolador de bolsillo.*

![ESP32](https://img.shields.io/badge/ESP32-DevKit-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-C%2B%2B-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Display](https://img.shields.io/badge/TFT-ST7789-ff69b4?style=for-the-badge)
![Uso](https://img.shields.io/badge/Uso-Educativo-3fb950?style=for-the-badge)

**Fundación Universitaria de San Gil – UNISANGIL, sede Yopal** · Yopal, Casanare, Colombia

</div>

---

## ✨ ¿De qué trata este proyecto?

Cada vez que el corazón late, el volumen de sangre en la yema del dedo cambia un poco. Un sensor óptico lo detecta como una variación de luz (**fotopletismografía, PPG**), y un **ESP32** convierte esa señal en algo que se puede ver y escuchar:

- 📈 La **onda de pulso** dibujada en tiempo real en una pantalla TFT a color.
- 🔢 La frecuencia cardíaca en **BPM**, calculada con la mediana de los últimos intervalos.
- ❤️ Un **corazón animado** que late en dos tiempos (*lub-dub*) con cada pulsación.
- 🔔 Un **pitido** corto del buzzer en cada latido, sin bloquear el programa.
- 📊 Una salida al **Serial Plotter** de Arduino para analizar la señal desde el computador.

> ⚠️ **Prototipo educativo.** No es un dispositivo médico y sus lecturas no deben usarse con fines clínicos. A diferencia del montaje con MAX30102, este sistema **no mide SpO₂**.

## 👥 Autores

| Nombre |
| --- |
| Cristian Enrique Cruz Fernandez |
| Samuel Felipe Diaz Galindo |
| Santiago Reina Socha |

---

## 🗺️ Mapa de conexiones

![Mapa de conexiones](docs/mapa_conexiones.svg)

| Módulo / señal | Pin ESP32 | Interfaz |
| --- | --- | --- |
| Sensor + | 3,3 V | Alimentación |
| Sensor S | GPIO 34 | ADC |
| Buzzer + *(solo V2)* | GPIO 25 | Salida digital |
| Sensor – y buzzer – | GND | Común |
| TFT SDA / MOSI | GPIO 23 | SPI |
| TFT SCL / SCK | GPIO 18 | SPI |
| TFT CS | GPIO 5 | Control |
| TFT DC | GPIO 2 | Control |
| TFT RES | GPIO 4 | Control |
| TFT VCC / BLK | 3,3 V | Alimentación |
| TFT GND | GND | Común |

> Confirma el pinout impreso en cada módulo antes de energizar el circuito. El diagrama supone una ESP32 DevKit de 38 pines.

---

## 🎬 Videos de funcionamiento

<table>
<tr>
<td width="50%" align="center">

### Versión 1
*Círculo rojo como indicador, sin buzzer.*

<!-- 👇 Arrastra tu video aquí al editar el README en GitHub, o pega el enlace -->

`[ PEGA AQUÍ EL VIDEO DE LA VERSIÓN 1 ]`

</td>
<td width="50%" align="center">

### Versión 2
*Corazón animado en dos tiempos y buzzer.*

<!-- 👇 Arrastra tu video aquí al editar el README en GitHub, o pega el enlace -->

`[ PEGA AQUÍ EL VIDEO DE LA VERSIÓN 2 ]`

</td>
</tr>
</table>

> 💡 **Cómo agregarlos:** abre este archivo con el lápiz ✏️ en GitHub, arrastra el video dentro del editor y GitHub generará el enlace. También puedes subirlo a YouTube y pegar `[![Video](miniatura.jpg)](https://youtu.be/XXXX)`.

---

## 🔀 Dos versiones del prototipo

| Aspecto | Versión 1 | Versión 2 |
| --- | --- | --- |
| Indicador | Círculo rojo de 150 ms | Corazón animado en dos tiempos |
| Aviso sonoro | No tiene | Buzzer de 40 ms por latido |
| Serial Plotter | Pulso y BPM, 100 datos/s | Pulso, BPM, Latido y Techo, 25 datos/s |
| Latidos en el Plotter | Pocos | Más latidos por ventana |
| Procesamiento y BPM | Igual | Igual |

### 💻 Código

| Versión | Archivo |
| --- | --- |
| Versión 1 | [`v1/monitor_pulso_v1/monitor_pulso_v1.ino`](v1/monitor_pulso_v1/monitor_pulso_v1.ino) |
| Versión 2 | [`v2/monitor_pulso_v2/monitor_pulso_v2.ino`](v2/monitor_pulso_v2/monitor_pulso_v2.ino) |

**Bibliotecas necesarias** (Arduino IDE → Administrar bibliotecas): `Adafruit GFX Library` y `Adafruit ST7735 and ST7789 Library`. Velocidad serie: **115200 baudios**.

---

## ⚙️ Cómo funciona

1. **Muestreo** del sensor a 100 Hz con el ADC de 12 bits (atenuación 11 dB).
2. **Acondicionamiento:** suavizado exponencial y resta de una línea base lenta para quedarse con la componente pulsátil.
3. **Detección de dedo:** si el pico de la señal supera 30 cuentas, hay dedo.
4. **Detección de latido:** cruce ascendente de un umbral adaptativo (50 % del pico) con periodo refractario de 300 ms.
5. **BPM:** mediana de los últimos 6 intervalos válidos (333–1500 ms), validando que la desviación sea ≤ 20 %.
6. **Presentación:** pantalla TFT, corazón animado, buzzer y Serial Plotter.

| Parámetro | Valor |
| --- | --- |
| Muestreo | 100 Hz |
| ADC | 12 bits, 11 dB |
| Amplitud mínima (dedo) | 30 cuentas |
| Umbral de latido | 50 % del pico |
| Intervalo válido | 333–1500 ms (180 a 40 BPM) |
| Regularidad | ≤ 20 % |
| Caducidad sin latidos | 3 s |

---

## 📄 Documento

El informe completo en formato IEEE, con materiales, objetivos, diagramas, parámetros y el código explicado bloque por bloque:

👉 [**Informe_Monitor_Pulso_IEEE.docx**](docs/Informe_Monitor_Pulso_IEEE.docx)

---

## 🚀 Cómo usarlo

1. Arma el circuito siguiendo el [mapa de conexiones](#️-mapa-de-conexiones).
2. Instala las dos bibliotecas de Adafruit en el Arduino IDE.
3. Selecciona la placa **ESP32 Dev Module** y abre el `.ino` de la versión que quieras probar.
4. Sube el código y coloca el dedo sobre el sensor, quieto y sin apretar demasiado.
5. Para ver la señal: **Herramientas → Serial Plotter** a 115200 baudios.

> Con `MODO_PLOTTER=false` el Monitor Serie muestra texto con el valor crudo (`Raw`), útil para depurar.

---

## 📦 Estructura del repositorio

```
monitor-pulso-esp32/
├── README.md
├── docs/
│   ├── Informe_Monitor_Pulso_IEEE.docx
│   └── mapa_conexiones.svg
├── v1/monitor_pulso_v1/monitor_pulso_v1.ino
├── v2/monitor_pulso_v2/monitor_pulso_v2.ino
└── media/            ← fotos y videos
```

---

## 🤖 Uso de inteligencia artificial

Se utilizó Claude (Anthropic) como apoyo en el desarrollo y la depuración del código, la redacción y el formato del informe, y la elaboración de los diagramas. Los autores revisaron el contenido y asumen la responsabilidad total del trabajo.

<div align="center">

*Hecho con ❤️ en Yopal, Casanare*

</div>
