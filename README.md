


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
178) - race 11:Budapest (Q1)  max time : 18(temps de course :  1:28) - time : x10 

+---+------------------+---+---+----+-------+---------+-------+-------+-------+--------+-------+--------+
|   |                  |Car|Lap|Sect|Pos in |Status   |Sector |Sector |Sector |Total   |Best   |        |
|Pos|Pilot             |Nr |Nr |Nr  |sect(%)|Car      |   1   |   2   |   3   |Time    |Lap    |Delta   |
+---+------------------+---+---+----+-------+---------+-------+-------+-------+--------+-------+--------+
|  1|pilote Stroll     | 0 |  2|  1 |  39%  |  Running| 24.728| 27.873| 24.812|  77.413| 77.413|  77.413|
|  2|pilote Pérez      | 0 |  2|  1 |  36%  |  Running| 24.917| 28.421| 24.512|  77.850| 77.850|+  0.437|
|  3|pilote Bottas     | 0 |  2|  1 |  36%  |  Running| 26.744| 26.384| 24.722|  77.850| 77.850|+  0.437|
|  4|pilote Gasly      | 0 |  2|  1 |  38%  |  Running| 26.718| 26.028| 25.462|  78.208| 78.208|+  0.795|
|  5|pilote Magnussen  | 0 |  2|  1 |  34%  |  Running| 26.748| 25.823| 26.067|  78.638| 78.638|+  1.225|
|  6|pilote Hülkenberg | 0 |  2|  1 |  37%  |  Running| 27.712| 25.694| 25.380|  78.786| 78.786|+  1.373|
|  7|pilote Russell    | 0 |  2|  1 |  39%  |  Running| 27.470| 24.755| 26.660|  78.885| 78.885|+  1.472|
|  8|pilote Ocon       | 0 |  2|  1 |  32%  |  Running| 27.553| 24.005| 27.659|  79.217| 79.217|+  1.804|
|  9|pilote Albon      | 0 |  2|  1 |  30%  |  Running| 24.590| 26.772| 28.269|  79.631| 79.631|+  2.218|
| 10|pilote Alonso     | 0 |  2|  1 |  26%  |  Running| 28.856| 24.864| 27.062|  80.782| 80.782|+  3.369|
| 11|pilote Ricciardo  | 0 |  2|  1 |  22%  |  Running| 28.860| 24.014| 29.344|  82.218| 82.218|+  4.805|
| 12|pilote Sargeant   | 0 |  2|  1 |  17%  |  Running| 24.235| 29.003| 29.591|  82.829| 82.829|+  5.416|
| 13|pilote Sainz Jr   | 0 |  2|  1 |  20%  |  Running| 27.239| 28.460| 27.510|  83.209| 83.209|+  5.796|
| 14|pilote Verstappen | 0 |  2|  1 |  18%  |  Running| 26.475| 27.129| 29.628|  83.232| 83.232|+  5.819|
| 15|pilote Norris     | 0 |  2|  1 |  22%  |  Running| 29.341| 29.878| 24.371|  83.590| 83.590|+  6.177|
| 16|pilote Hamilton   | 0 |  2|  1 |  19%  |  Running| 29.861| 25.903| 27.903|  83.667| 83.667|+  6.254|
| 17|pilote Zhou       | 0 |  2|  1 |   8%  |  Running| 26.568| 29.841| 29.015|  85.424| 85.424|+  8.011|
| 18|pilote Leclerc    | 0 |  2|  1 |  10%  |  Running| 29.466| 28.175| 27.822|  85.463| 85.463|+  8.050|
| 19|pilote Piastri    | 0 |  2|  1 |   6%  |  Running| 28.767| 28.175| 29.139|  86.081| 86.081|+  8.668|
| 20|pilote Tsunoda    | 0 |  1|  3 |  96%  |  Running| 29.749| 29.641|  0.000|   0.000|  0.000|   -    |
+---+------------------+---+---+----+-------+---------+-------+-------+-------+--------+-------+--------+

voiture   0 - Verstappen    ,    Running,  tour: 2 -----*-----------------------|-----------------------------|-----------------------------|
voiture   1 - Sargeant      ,    Running,  tour: 2 ----*------------------------|-----------------------------|-----------------------------|
voiture   2 - Ricciardo     ,    Running,  tour: 2 ------*----------------------|-----------------------------|-----------------------------|
voiture   3 - Norris        ,    Running,  tour: 2 ------*----------------------|-----------------------------|-----------------------------|
voiture   4 - Gasly         ,    Running,  tour: 2 -----------*-----------------|-----------------------------|-----------------------------|
voiture   5 - Pérez         ,    Running,  tour: 2 ----------*------------------|-----------------------------|-----------------------------|
voiture   6 - Alonso        ,    Running,  tour: 2 -------*---------------------|-----------------------------|-----------------------------|
voiture   7 - Leclerc       ,    Running,  tour: 2 --*--------------------------|-----------------------------|-----------------------------|
voiture   8 - Stroll        ,    Running,  tour: 2 -----------*-----------------|-----------------------------|-----------------------------|
voiture   9 - Magnussen     ,    Running,  tour: 2 ---------*-------------------|-----------------------------|-----------------------------|
voiture  10 - Tsunoda       ,    Running,  tour: 1 -----------------------------|-----------------------------|---------------------------*-|
voiture  11 - Albon         ,    Running,  tour: 2 --------*--------------------|-----------------------------|-----------------------------|
voiture  12 - Zhou          ,    Running,  tour: 2 --*--------------------------|-----------------------------|-----------------------------|
voiture  13 - Hülkenberg    ,    Running,  tour: 2 ----------*------------------|-----------------------------|-----------------------------|
voiture  14 - Ocon          ,    Running,  tour: 2 ---------*-------------------|-----------------------------|-----------------------------|
voiture  15 - Hamilton      ,    Running,  tour: 2 -----*-----------------------|-----------------------------|-----------------------------|
voiture  16 - Sainz Jr      ,    Running,  tour: 2 -----*-----------------------|-----------------------------|-----------------------------|
voiture  17 - Russell       ,    Running,  tour: 2 -----------*-----------------|-----------------------------|-----------------------------|
voiture  18 - Bottas        ,    Running,  tour: 2 ----------*------------------|-----------------------------|-----------------------------|
voiture  19 - Piastri       ,    Running,  tour: 2 -*---------------------------|-----------------------------|-----------------------------|

best time for sector 1: time : 24.235, car : 1 
best time for sector 2: time : 24.005, car : 14 
best time for sector 3: time : 24.371, car : 3 
Press q:quit  +:faster -:slower

Your choice: ```

## Contributing

Ephec Students
- Gaspard
- Loan
- Bruno
- Yassa

