


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
# gcc options : 
# -lm : compile/link with mathematical librairies
# -lpthread : compile/link with thread/semaphores librairies
git pull 
gcc cars.c -lm -lpthread -o cars 
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
258) - race 19:Mexico (N) - nb tours: 69 (temps de course : 15:08) - time : x80 

+---+------------------+---+---+----+-------+---------+-------+-------+-------+----------+-------+----------+
|   |                  |Car|Lap|Sect|Pos in |Status   |Sector |Sector |Sector |Total     |Best   |          |
|Pos|Pilot             |Nr |Nr |Nr  |sect(%)|Car      |   1   |   2   |   3   |Time      |Lap    |Delta     |
+---+------------------+---+---+----+-------+---------+-------+-------+-------+----------+-------+----------+
|  1|pilote Ocon       |31 | 11|  2 |  66%  |  Running| 29.138| 24.343| 25.729| 13:16.064| 74.591| 13:16.064|
|  2|pilote Stroll     |18 | 11|  2 |  63%  |  Running| 24.567| 27.752| 29.653| 13:16.592| 75.098|+ 0:00.528|
|  3|pilote Tsunoda    |22 | 11|  2 |  87%  |  Running| 29.394| 24.183| 27.436| 13:23.232| 78.625|+ 0:07.168|
|  4|pilote Magnussen  |20 | 11|  3 |   0%  |  Running| 25.626| 25.321| 29.328| 13:25.697| 77.462|+ 0:09.633|
|  5|pilote Bottas     |77 | 11|  2 |  86%  |  Running| 27.622| 25.039| 24.768| 13:26.560| 75.158|+ 0:10.496|
|  6|pilote Albon      |23 | 11|  2 |  40%  |  Running| 28.905| 25.951| 25.133| 13:27.164| 75.684|+ 0:11.100|
|  7|pilote Gasly      |10 | 11|  2 |  84%  |  Running| 24.909| 26.182| 27.342| 13:27.921| 76.298|+ 0:11.857|
|  8|pilote Pérez      |11 | 11|  2 |  62%  |  Running| 25.720| 27.662| 28.395| 13:28.012| 77.452|+ 0:11.948|
|  9|pilote Ricciardo  | 3 | 11|  2 |  33%  |  Running| 24.476| 25.676| 24.181| 13:28.357| 73.879|+ 0:12.293|
| 10|pilote Alonso     |14 | 11|  1 |  93%  |  Running| 24.362| 24.636| 29.305| 13:29.681| 77.419|+ 0:13.617|
| 11|pilote Sargeant   | 2 | 11|  2 |  44%  |  Running| 24.212| 24.894| 24.870| 13:29.930| 75.670|+ 0:13.866|
| 12|pilote Hamilton   |44 | 11|  2 |  75%  |  Running| 25.251| 27.084| 28.456| 13:30.244| 76.956|+ 0:14.180|
| 13|pilote Piastri    |81 | 11|  2 |  15%  |  Running| 26.742| 26.446| 25.777| 13:30.520| 74.055|+ 0:14.456|
| 14|pilote Hülkenberg |27 | 11|  2 |  63%  |  Running| 26.558| 28.539| 24.547| 13:32.997| 75.729|+ 0:16.933|
| 15|pilote Russell    |63 | 11|  2 |  14%  |  Running| 29.114| 24.220| 29.874| 13:34.757| 75.512|+ 0:18.693|
| 16|pilote Verstappen | 1 | 11|  2 |  33%  |  Running| 26.629| 25.214| 28.495| 13:34.799| 75.589|+ 0:18.735|
| 17|pilote Sainz Jr   |55 | 11|  2 |  76%  |  Running| 24.916| 26.605| 24.809| 13:35.723| 76.580|+ 0:19.659|
| 18|pilote Norris     | 4 | 11|  1 |  68%  |  Running| 24.547| 29.202| 25.311| 13:38.767| 77.428|+ 0:22.703|
| 19|pilote Leclerc    |16 | 11|  2 |  32%  |  Running| 25.444| 24.061| 25.908| 13:40.598| 76.484|+ 0:24.534|
| 20|pilote Zhou       |24 | 11|  2 |   0%  |  Running| 24.656| 25.408| 29.542| 13:45.810| 78.497|+ 0:29.746|
+---+------------------+---+---+----+-------+---------+-------+-------+-------+----------+-------+----------+

voiture   1 - Verstappen    ,    Running,  tour:11 -----------------------------|---------*-------------------|-----------------------------|
voiture   2 - Sargeant      ,    Running,  tour:11 -----------------------------|------------*----------------|-----------------------------|
voiture   3 - Ricciardo     ,    Running,  tour:11 -----------------------------|---------*-------------------|-----------------------------|
voiture   4 - Norris        ,    Running,  tour:11 -------------------*--------q-|-----------------------------|-----------------------------|
voiture  10 - Gasly         ,    Running,  tour:11 -----------------------------|------------------------*----|-----------------------------|
voiture  11 - Pérez         ,    Running,  tour:11 -----------------------------|-----------------*-----------|-----------------------------|
voiture  14 - Alonso        ,    Running,  tour:11 --------------------------*--|-----------------------------|-----------------------------|
voiture  16 - Leclerc       ,    Running,  tour:11 -----------------------------|---------*-------------------|-----------------------------|
voiture  18 - Stroll        ,    Running,  tour:11 -----------------------------|------------------*----------|-----------------------------|
voiture  20 - Magnussen     ,    Running,  tour:11 -----------------------------|-----------------------------|*----------------------------|
voiture  22 - Tsunoda       ,    Running,  tour:11 -----------------------------|-------------------------*---|-----------------------------|
voiture  23 - Albon         ,    Running,  tour:11 -----------------------------|-----------*-----------------|-----------------------------|
voiture  24 - Zhou          ,    Running,  tour:11 -----------------------------|*----------------------------|-----------------------------|
voiture  27 - Hülkenberg    ,    Running,  tour:11 -----------------------------|------------------*----------|-----------------------------|
voiture  31 - Ocon          ,    Running,  tour:11 -----------------------------|-------------------*---------|-----------------------------|
voiture  44 - Hamilton      ,    Running,  tour:11 -----------------------------|---------------------*-------|-----------------------------|
voiture  55 - Sainz Jr      ,    Running,  tour:11 -----------------------------|----------------------*------|-----------------------------|
voiture  63 - Russell       ,    Running,  tour:11 -----------------------------|----*------------------------|-----------------------------|
voiture  77 - Bottas        ,    Running,  tour:11 -----------------------------|------------------------*----|-----------------------------|
voiture  81 - Piastri       ,    Running,  tour:11 -----------------------------|----*------------------------|-----------------------------|

best time for sector 1: time : 24.004, pilote : Piastri 
best time for sector 2: time : 24.026, pilote : Piastri 
best time for sector 3: time : 24.044, pilote : Piastri 
Press q:quit  +:faster -:slower
```

## Contributing

Ephec Students
- Gaspard
- Loan
- Bruno
- Yassa

