# IN204-ObjectOrientedRayTracing

![View](https://github.com/titiloltiti/IN204-ObjectOrientedRayTracing/doc/image.ppm"View rendered with this Ray Tracing engine")

This is the repository for our IN204 Object Oriented Ray Tracing project.

## Getting started

### Prerequisites

This project is written in C++ and doesn't need any specific library to be compiled. However the images rendered use the extension .ppm which is convenient in the case of this project. To be able to display the output on Linux, please install the following package: ImageMagick.
To do so:
```shell
$ apt install imagemagick
```

### Installation

Clone this repository then run the renderer using make.
```shell
$ make
```

This command will compile the sources, compile the binary and display the output. In case you wish to only compile:
```shell
$ make exec
```
You can then produce an image using the following commands:
```shell
$ ./bin/main
$ display resut/image.ppm
```
You can clean the outputs with:
```shell
$ make clean
```

## Authors

* Quentin BIHARÉ - Active member - [Github](https://github.com/titiloltiti)
* Pierre-Élisée FLORY - Active member - [Github](https://github.com/flory-ensta)

## Licence

There is no licence for this project, do whatever you want with it.

## Tasks

### Etude de faisabilité/Analyse du projet 

* Analyse d'usage
* Analyse fonctionnelle 
* Architecture gros grains

### Realisation d'un démonstrateur

### Amélioration de l'outil 

## Project Descripion

[Here](doc/projet_informatique_-_oort.pdf)
