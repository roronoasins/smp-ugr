# Sistemas con Microprocesadores UGR

> Escuela Técnica Superior de Ingeniería Informática y Telecomunicaciones, Universidad de Granada.

## Herramientas utilizadas

- [CCS_5.008](http://www.ccsinfo.com/content.php?page=compilers) - Code Optimizing C Compilers for Microchip PIC® and dsPIC® DSCs
- USB Bootloader Programmer

## Robot de sumo: Spud

> Spud
![spud](link)

### Diseño

Se trata de un robot con un diseño muy sencillo. Su tarea es la de explorar y empujar al rival con el parachoques.

Para que pueda llevar a cabo su labor, se han usado sensores de ultrasonidos(SRF02) a los laterales para detectar presencia y poder encarar a los oponentes.
> SRF02
![srf](https://github.com/roronoasins/smp-ugr/blob/master/media/srf.jpg)

También tiene sensores ópticos(CNY70) en cada esquina para poder detectar las lineas negras del ring y poder permanecer dentro de este.

El parachoques tiene un sistema retráctil para aumentar el área de choque, usando dos bumpers para controlar cuando chocamos.
> Parachoques retráctil
![Parachoques](https://github.com/roronoasins/smp-ugr/blob/master/media/parachoques3.jpg)
![Parachoques](https://github.com/roronoasins/smp-ugr/blob/master/media/parachoques2.jpg)

Para el movimiento, usamos dos servomotores en la parte delantera. Para añadir agarre, cubrimos las ruedas con globo. Además, añadimos un desodorante roll-on en la parte trasera para reducir la fricción con el suelo y que sirva de pivote.
> Pivote Roll-on
![Pivote](https://github.com/roronoasins/smp-ugr/blob/master/media/pivote.jpg)

> Ruedas con globo
![Globo](https://github.com/roronoasins/smp-ugr/blob/master/media/rueda-globo.jpg)

### Estrategia

Al igual que el diseño, es bastante sencilla. El robot explora siempre en linea recta, cuando detecta la linea negra hace una maniobra. Durante la exploracion y maniobra comprueba si tiene rivales a sus lados. Si detecta presencia, gira y los encara. Si en cualquier momento detectase un choque con los bumpers, pasaria a empujar. Si detectase en cualquier momento linea negra, dejaria lo que estaba haciendo, y se pone a explorar.

### Comportamiento
> 1v1
![1v1](https://github.com/roronoasins/smp-ugr/blob/master/media/1v1.gif)

> Battleroyale
![Battleroyale](https://github.com/roronoasins/smp-ugr/blob/master/media/battleroyale.gif)


## License
Este proyecto está licenciado bajo GNU General Public License v3.0 - ver el fichero [LICENSE.md](LICENSE.md) para más detalles
