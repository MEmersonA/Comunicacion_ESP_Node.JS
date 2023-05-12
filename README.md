# Comunicacion_ESP_Node.JS

Proyecto de Comunicaciones

Se inicia un servidor en NodeJs con uso del frameworks Express.
Se comunica de forma bidireccional con un microcontrolador ESP32, 
el cual lee por medio de ADC la lectura de un LM35 (Sensor de temperatura) 
y envía estos datos al servidor cada segundo. Al tiempo, el servidor 
toma los datos ingresados a un formulario HTML y los envía al ESP32. 
Dependiendo de los datos ingresados, la ESP32 enciende un arreglo de leds
por medio de 4 de sus canales digitales, puede encenderlo segun un numero binario 
o segundo el número del led que se desea encender.


