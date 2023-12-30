


# Project Title

OS2 - TP1 : Formula1 championship.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)

## Introduction

This is a group project from Ephec students in TI2, OS2

## Features

- Simulate a Formula1 race
- Max 22 cars; 20 different races across the season
- Manage a full season championship
- Real time display of the race statistics, with graphical representation

## Installation


To install (first time):

```bash
# Sample installation steps
git clone https://github.com/MonsieurLoki/Formule1.git
cd Formule1
gcc cars.c -lm -o cars
```


To update the code :

```bash
# Sample installation steps
# cd ../Formule1
git pull 
gcc cars.c -lm -o cars
```


## Usage

```bash
./cars
Course| Ville             | Date    | Pays                | Nom du circuit                     | Taille (km)
------|-------------------|---------|---------------------|------------------------------------|------------|
1     | Sakhir            | 05-mars | Bahrain             | Bahrain International Circuit      | 5.412      |
2     | Djeddah           | 19-mars | Arabie Saoudite     | Jeddah Corniche Circuit            | 6.174      |
3     | Melbourne         | 02-avr  | Australie           | Albert Park Circuit                | 5.278      |
4     | Bakou             | 30-avr  | Azerbaijan          | Baku City Circuit                  | 6.003      |
5     | Miami             | 07-mai  | Etats-Unis          | Miami International Autodrome      | 5.410      |
6     | Monte-Carlo       | 28-mai  | Monaco              | Circuit de Monaco                  | 3.337      |
7     | Barcelone         | 04-juin | Espagne             | Circuit de Barcelona-Catalunya     | 4.675      |
8     | Montréal          | 18-juin | Canada              | Circuit Gilles-Villeneuve          | 4.361      |
9     | Spielberg         | 02-juil | Autriche            | Red Bull Ring                      | 4.318      |
10    | Silverstone       | 09-juil | Royaume Uni         | Silverstone Circuit                | 5.891      |
11    | Budapest          | 23-juil | Hongrie             | Hungaroring                        | 4.381      |
12    | Spa-Francorchamps | 30-juil | Belgique            | Circuit de Spa-Francorchamps       | 7.004      |
13    | Zandvoort         | 27-août | Pays-Bas            | Circuit Zandvoort                  | 4.259      |
14    | Monza             | 03-sept | Italie              | Autodromo Nazionale di Monza       | 5.793      |
15    | Marina Bay        | 17-sept | Singapour           | Marina Bay Street Circuit          | 5.063      |
16    | Suzuka            | 24-sept | Japon               | Suzuka International Racing Course | 5.807      |
17    | Losail            | 08-oct  | Qatar               | circuit international de Losail    | 5.418      |
18    | Austin            | 22-oct  | Etats-Unis          | Circuit of the Americas            | 5.513      |
19    | Mexico            | 29-oct  | Mexique             | Autódromo Hermanos Rodríguez       | 4.304      |
20    | Sao Paulo         | 05-nov  | Brésil              | Autódromo José Carlos Pace         | 4.309      |
21    | Las Vegas         | 18-nov  | Etats-Unis          | Circuit Silver Las Vegas           | 6.120      |
22    | Yas Marina        | 26-nov  | Emirats Arabes Unis | Yas Marina Circuit                 | 5.281      |
Entrez le numéro de la course que vous souhaitez afficher : 2

Détails de la course numéro 2 :
Ville : Djeddah
Date : 19-mars
Pays : Arabie Saoudite
Nom du circuit : Jeddah Corniche Circuit
Taille (km) : 6.174
Nombre de tours calculés : 49.00


Nb | Num | Prénom    | Nom           | Team         
---|-----|-----------|---------------|---------------|
1  | 1   | Max       | Verstappen    | Red Bull      |
2  | 2   | Logan     | Sargeant      | Williams      |
3  | 3   | Daniel    | Ricciardo     | AlphaTauri    |
4  | 4   | Lando     | Norris        | McLaren       |
5  | 10  | Pierre    | Gasly         | Alpine        |
6  | 11  | Sergio    | Pérez         | Red Bull      |
7  | 14  | Fernando  | Alonso        | Aston Martin  |
8  | 16  | Charles   | Leclerc       | Ferrari       |
9  | 18  | Lance     | Stroll        | Aston Martin  |
10 | 20  | Kevin     | Magnussen     | Haas          |
11 | 22  | Yuki      | Tsunoda       | AlphaTauri    |
12 | 23  | Alexander | Albon         | Williams      |
13 | 24  | Guanyu    | Zhou          | Alfa Romeo    |
14 | 27  | Nico      | Hülkenberg    | Haas          |
15 | 31  | Esteban   | Ocon          | Alpine        |
16 | 44  | Lewis     | Hamilton      | Mercedes      |
17 | 55  | Carlos    | Sainz Jr      | Ferrari       |
18 | 63  | George    | Russell       | Mercedes      |
19 | 77  | Valtteri  | Bottas        | Alfa Romeo    |
20 | 81  | Oscar     | Piastri       | McLaren       |



          |Sakhi|Djedd|Melbo|Bakou|Miami|Monte|Barce|Montr|Spiel|Silve|Budap|Spa-F|Zandv|Monza|Marin|Suzuk|Losai|Austi|Mexic|Sao P|Las V|Yas M|
Verstappen|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|
  Sargeant|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|
 Ricciardo|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|
    Norris|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|    0|

...
...

102) voiture  0, secteur courant : 2, temps secteur1 :  5.826, temps secteur2 :  0.000, temps secteur3 :  0.000, best tour time :  0.000, temps total :  0.000 
102) voiture  1, secteur courant : 2, temps secteur1 :  5.322, temps secteur2 :  0.000, temps secteur3 :  0.000, best tour time :  0.000, temps total :  0.000 
102) voiture  2, secteur courant : 2, temps secteur1 :  5.086, temps secteur2 :  0.000, temps secteur3 :  0.000, best tour time :  0.000, temps total :  0.000 
102) voiture  3, secteur courant : 2, temps secteur1 :  5.793, temps secteur2 :  0.000, temps secteur3 :  0.000, best tour time :  0.000, temps total :  0.000 
  0) voiture, pilote : Verstappen     , status: Running , sect: 2, pos: 88, tour:1 -----------------------------|-------------------------*---|-----------------------------|
  1) voiture, pilote : Sargeant       , status: Running , sect: 2, pos: 92, tour:1 -----------------------------|--------------------------*--|-----------------------------|
  2) voiture, pilote : Ricciardo      , status: Running , sect: 2, pos: 86, tour:1 -----------------------------|------------------------*----|-----------------------------|
  3) voiture, pilote : Norris         , status: Running , sect: 2, pos: 74, tour:1 -----------------------------|---------------------*-------|-----------------------------|
pos 1 : car 1 pilote Sargeant      
pos 2 : car 0 pilote Verstappen    
pos 3 : car 2 pilote Ricciardo     
pos 4 : car 3 pilote Norris        
best time for sector 1: time :  5.086, car : 2 
best time for sector 2: time :  0.000, car : 0 
best time for sector 3: time :  0.000, car : 0 
```

## Contributing

Ephec Students
- Gaspard
- Loan
- Bruno
- Yassa

