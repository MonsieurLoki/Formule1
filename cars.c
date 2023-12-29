// test pipes bloquants
// ps -aux | grep "myprocess"
// echo   $(ps -aux | grep "pipeBlo" | awk '{ print $2 }')
// kill   $(ps -aux | grep "pipeBlo" | awk '{ print $2 }')
// tutorial: https://www.youtube.com/watch?v=WgVSq-sgHOc&ab_channel=JacobSorber

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <locale.h>
#include <wchar.h>
#include <math.h>
#include <stdbool.h>

#define IPC_RESULT_ERROR (-1)
#define NB_VOITURE 4
#define NB_TOUR 2
#define STATUS_FINISHED 2
#define STATUS_RUNNING 1
#define STATUS_READY 0

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

// attach a shared memory block
// associated with filename
// create it if it doesn't exist

// all of the programs will share these values
#define BLOCK_SIZE 4096
#define FILENAME "cars.c"

#define MAX_LINE_SIZE 1000 // Taille maximale d'une ligne dans le fichier CSV
#define MAX_COLUMNS 10     // Nombre maximal de colonnes dans une ligne du CSV
#define MAX_ROWS 100       // Nombre maximal de lignes dans le fichier CSV

#define MAX_NAME_LENGTH 50
#define MAX_DATE_LENGTH 11
#define MAX_NATIONALITY_LENGTH 20

#endif

// nombre de courses qu'on a lu dans le fichier csv
int nb_courses;

// nombre de pilotes qu'on a lu dans le fichier csv
int nb_pilotes;

// definition of the car structure
struct Car
{
    int car_nr;
    char pilote[20];
    float time_sector1;
    float time_sector2;
    float time_sector3;
    int position;
    int secteur_courant;
    int tour_courant;
    int best_tour_time_ms;
    int total_time_de_la_course_ms;
    int status;
};

// Structure représentant une ligne du fichier CSV
typedef struct
{
    int course;
    char ville[MAX_LINE_SIZE];
    char date[MAX_LINE_SIZE];
    char pays[MAX_LINE_SIZE];
    char nom_circuit[MAX_LINE_SIZE];
    float taille_km;
    char race[MAX_LINE_SIZE];
    char circuit[MAX_LINE_SIZE];
    char date_range[MAX_LINE_SIZE];
} F1Race;

F1Race races[MAX_ROWS];

typedef struct
{
    int nb;
    int num;
    char prenom[MAX_NAME_LENGTH];
    char nom[MAX_NAME_LENGTH];
    char team[MAX_NAME_LENGTH];
    char naissance[MAX_DATE_LENGTH];
    char nationalite[MAX_NATIONALITY_LENGTH];
} Pilote;

Pilote pilotes[MAX_ROWS];

int scores[MAX_ROWS][MAX_ROWS];

int choisirCourse(F1Race races[], int num_races, int num_course)
{
    for (int i = 0; i < num_races; ++i)
    {
        if (races[i].course == num_course)
        {
            double nombre = 300 / races[i].taille_km;
            double arrondi = ceil(nombre);
            printf("\nDétails de la course numéro %d :\n", num_course);
            printf("Ville : %s\n", races[i].ville);
            printf("Date : %s\n", races[i].date);
            printf("Pays : %s\n", races[i].pays);
            printf("Nom du circuit : %s\n", races[i].nom_circuit);
            printf("Taille (km) : %.3f\n", races[i].taille_km);
            printf("Nombre de tours calculés : %.2f\n", arrondi);
            return 1; // Course trouvée et affichée
        }
    }
    return 0; // Aucune course trouvée
}
// generic functions ------------------------------------------------------------------------------------

int strwlen(char *narrowStr)
{
    setlocale(LC_ALL, ""); // Set the locale to support wide characters

    // const char *narrowStr = "Hello, world!";  // Your regular string
    // const char *narrowStr = "Café";  // Your regular string
    // const char *narrowStr = "Montréal";  // Your regular string
    size_t maxWideSize = mbstowcs(NULL, narrowStr, 0); // Determine the required buffer size

    if (maxWideSize != (size_t)-1)
    {
        wchar_t *wideStr = (wchar_t *)malloc((maxWideSize + 1) * sizeof(wchar_t));
        if (wideStr)
        {
            mbstowcs(wideStr, narrowStr, maxWideSize + 1);

            // Now wideStr contains the wide character string
            // wprintf(L"%ls (len normal : %d, len wide : %d)\n", wideStr, strlen(narrowStr), wcslen(wideStr));
            int wlen = wcslen(wideStr);

            free(wideStr); // Don't forget to free the allocated memory
            return wlen;
        }
    }
    else
    {
        fprintf(stderr, "Error converting string to wide character string\n");
    }

    return -1;
}

char space0[] = "";
char space1[] = " ";
char space2[] = "  ";
char space3[] = "   ";

char *compensate_for_accents(char *str)
{
    int lg = strlen(str);
    int wlg = strwlen(str);

    switch (lg - wlg)
    {
    case 0:
        return space0;
    case 1:
        return space1;
    case 2:
        return space2;
    case 3:
        return space3;
    }
}

int lireCircuits(F1Race races[])
{
    // variable de type file pour gérer le fichier CSV
    FILE *file;
    // buffer pour être sûr qu'on a réservé la place suffisante (MAX_LINE_SIZE) pour être
    // capable de lire en mémoire toute une ligne du fichier
    char line[MAX_LINE_SIZE];
    // le tableau pour contenir l'information du fichier, de façon structurée
    // chaque élément de ce tableau contiendra une structure de type F1Race, càd
    // avec les différentes propriété de cette structure
    // par exemple, races[5].pays contiendra le pays de la course 5
    // il peut y avoir maximum MAX_ROWS éléments dans ce tableau
    // F1Race races[MAX_ROWS]; // Tableau de structures F1Race

    // Ouvrir le fichier CSV en mode lecture
    file = fopen("listCircuit.csv", "r");
    // on s'assure que le fichier a été ouvert sans problème
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    // au départ, il y a 0 course de déjà lue
    int num_races = 0;

    // Ignorer la première ligne (en-têtes)
    // on lit dans le buffer line une ligne pour rien
    fgets(line, MAX_LINE_SIZE, file);

    // Lire et stocker chaque ligne du fichier CSV dans la structure
    while (fgets(line, MAX_LINE_SIZE, file) != NULL && num_races < MAX_ROWS)
    {
        F1Race race;
        race.course = -1; // Initialisation

        // Utilise strtok pour séparer les valeurs par point-virgule
        char *token = strtok(line, ";");

        // Stocker chaque valeur dans la structure
        int column = 0;
        while (token != NULL && column < MAX_COLUMNS)
        {
            switch (column)
            {
            case 0:
                // Convertit la chaîne de caractères token en un entier à l'aide de la fonction atoi() et stocke la valeur dans le champ course de la structure F1Race
                race.course = atoi(token);
                break;
            case 1:
                // Copie la chaîne de caractères token dans les champs correspondants de la structure F1Race (ville, date, pays, etc.) en utilisant strcpy() pour la copie.
                strcpy(race.ville, token);
                break;
            case 2:
                strcpy(race.date, token);
                break;
            case 3:
                strcpy(race.pays, token);
                break;
            case 4:
                strcpy(race.nom_circuit, token);
                break;
            case 5:
                // Convertit la chaîne de caractères token en un nombre flottant (à virgule flottante) à l'aide de la fonction atof() et stocke la valeur dans le champ taille_km de la structure F1Race
                race.taille_km = atof(token);
                break;
            case 6:
                strcpy(race.race, token);
                break;
            case 7:
                strcpy(race.circuit, token);
                break;
            case 8:
                strcpy(race.date_range, token);
                break;
            }
            // trouve le prochain morceau de texte dans la chaîne, en utilisant le point-virgule comme séparateur, pour une découpe ultérieure.
            // La fonction strtok est utilisée pour découper une chaîne de caractères en "tokens" (morceaux) basés sur un délimiteur spécifié.
            token = strtok(NULL, ";");
            column++;
        }

        // Stocker la ligne dans le tableau de structures F1Race
        // stocke la structure de données représentant une course dans le tableau races, puis incrémente le compteur pour la prochaine course à enregistrer.
        // voici en plusieurs étapes : F1Race tempRace = race;
        //    races[num_races] = tempRace;
        //    num_races++;
        races[num_races++] = race;
    }

    // Fermer le fichier
    fclose(file);
    return num_races;
}
int afficherCircuits(F1Race races[], int num_races)
{
    // Affichage des en-têtes du tableau avec des largeurs de champ fixes
    printf("%-6s| %-18s| %-8s| %-20s| %-35s| %-11s\n",
           "Course", "Ville", "Date", "Pays", "Nom du circuit", "Taille (km)");

    // Affichage des séparateurs
    printf("------|-------------------|---------|---------------------|------------------------------------|------------|\n");

    // Affichage des données de chaque course
    for (int i = 0; i < num_races; ++i)
    {
        printf("%-6d| %-18s%s| %-8s%s| %-20s%s| %-35s%s| %-11.3f|\n",
               races[i].course, races[i].ville, compensate_for_accents(races[i].ville), races[i].date, compensate_for_accents(races[i].date), races[i].pays, compensate_for_accents(races[i].pays), races[i].nom_circuit, compensate_for_accents(races[i].nom_circuit), races[i].taille_km);
    }

    return 0;
}

int lirePilotes(Pilote circuits[])
{
    FILE *file;
    char line[MAX_LINE_SIZE];

    // Ouvrir le fichier CSV en mode lecture
    file = fopen("listPilotes.csv", "r");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return 0;
    }

    int num_circuits = 0;

    // Ignorer la première ligne (en-têtes)
    fgets(line, MAX_LINE_SIZE, file);

    // Lire et stocker chaque ligne du fichier CSV dans la structure
    while (fgets(line, MAX_LINE_SIZE, file) != NULL && num_circuits < NB_VOITURE)
    {
        Pilote circuit;
        circuit.nb = -1; // Initialisation

        // Utilise strtok pour séparer les valeurs par point-virgule
        char *token = strtok(line, ";");

        // Stocker chaque valeur dans la structure
        int column = 0;
        while (token != NULL && column < 7)
        {
            switch (column)
            {
            case 0:
                circuit.nb = atoi(token);
                break;
            case 1:
                circuit.num = atoi(token);
                break;
            case 2:
                strcpy(circuit.prenom, token);
                break;
            case 3:
                strcpy(circuit.nom, token);
                break;
            case 4:
                strcpy(circuit.team, token);
                break;
            case 5:
                strcpy(circuit.naissance, token);
                break;
            case 6:
                strcpy(circuit.nationalite, token);
                break;
            }
            token = strtok(NULL, ";");
            column++;
        }

        // Stocker la ligne dans le tableau de structures Pilote
        circuits[num_circuits++] = circuit;
    }

    // Fermer le fichier
    fclose(file);

    return num_circuits;
}

void afficherPilotes(Pilote pilotes[], int num_pilotes)
{
    printf("%-2s | %-3s | %-10s | %-13s | %-13s\n",
           "Nb", "Num", "Prénom", "Nom", "Team");
    printf("---|-----|-----------|---------------|---------------|\n");

    // Affichage des données de chaque pilote sous forme de tableau
    for (int i = 0; i < num_pilotes; ++i)
    {
        printf("%-2d | %-3d | %-9s%s | %-13s%s | %-13s%s |\n",
               pilotes[i].nb, pilotes[i].num, pilotes[i].prenom, compensate_for_accents(pilotes[i].prenom), pilotes[i].nom, compensate_for_accents(pilotes[i].nom), pilotes[i].team, compensate_for_accents(pilotes[i].team));
    }
}

int classement[NB_VOITURE];
char *char_status_desc[] = {"ready", "Running", "Finished"};

// definition of the Best_sector times
struct Best_sector
{
    // int time;      // best time for this sector in secs
    int time_ms; // best time for this sector in ms
    int car_nr;  // car having done the best time for this sector
};

// definition of the structure of the shared memmory
// malgré que trois secteurs on créer un tableau avec quatres lignes pour simplifier la programmation
typedef struct
{
    struct Car cars[NB_VOITURE + 1];
    struct Best_sector best_sectors[4];
} Shmem_data;

Shmem_data *shmem_data;

// shared memomry
static int get_shared_block(char *filename, int size)
{
    key_t key;
    // Request a key
    // The key is linked to a filename, so that other programs can access it.
    key = ftok(filename, 0);
    if (key == IPC_RESULT_ERROR)
    {
        return IPC_RESULT_ERROR;
    }
    // get shared block create it if it doesn't exist
    return shmget(key, size, 0644 | IPC_CREAT);
}

void *attach_memory_block(char *filename, int size)
{
    int shared_block_id = get_shared_block(filename, size);
    void *result;
    if (shared_block_id == IPC_RESULT_ERROR)
    {
        return NULL;
    }
    // map the shared block into this process's memory
    // and give me a pointer to it
    result = shmat(shared_block_id, NULL, 0);
    if (result == (char *)IPC_RESULT_ERROR)
    {
        return NULL;
    }
    return result;
}

bool detach_memory_block(char *block)
{
    return (shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_memory_block(char *filename)
{
    int shared_block_id = get_shared_block(filename, 0);
    if (shared_block_id == IPC_RESULT_ERROR)
    {
        return NULL;
    }
    return (shmctl(shared_block_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}

void destroy_shmem()
{
    if (destroy_memory_block(FILENAME))
    {
        printf("Destroyed block: %s\n", FILENAME);
    }
    else
    {
        printf("Could not destroy block: %s\n", FILENAME);
    }
}

int myRandom(int min, int max)
{
    int nombreAlea = rand() % (max - min + 1) + min;
    return nombreAlea;
}

// cette fonction gère le secteur nr_secteur de la voiture car_nr et retourne le temps en millisecondes que la voiture a pris pour parcourir le secteur
int gererSecteur(int car_nr, int nr_secteur)
{
    int dureeSecteur_ms = myRandom(4000, 6000);
    int passed_ms = 0; // nb of ms passed since beginning of the sector
    int delay_ms = 100;
    int position;
    shmem_data->cars[car_nr].secteur_courant = nr_secteur;
    while (passed_ms <= dureeSecteur_ms)
    {
        position = ((100 * passed_ms) / dureeSecteur_ms);
        shmem_data->cars[car_nr].position = position;
        usleep(delay_ms * 1000); // attendre x microsecond
        passed_ms += delay_ms;
    }
    shmem_data->cars[car_nr].position = 100;
    // shmem_data->cars[car_nr].time_sector1 = dureeSecteur_ms;
    switch (nr_secteur)
    {
    case 1:
        shmem_data->cars[car_nr].time_sector1 = dureeSecteur_ms;
        break;
    case 2:
        shmem_data->cars[car_nr].time_sector2 = dureeSecteur_ms;
        break;
    case 3:
        shmem_data->cars[car_nr].time_sector3 = dureeSecteur_ms;
        break;
    default:
        printf("Erreur dans switch(nr_secteur) : ceci ne devrait jamais arriver !");
        exit(1);
        break;
    }

    if (dureeSecteur_ms < shmem_data->best_sectors[nr_secteur].time_ms || shmem_data->best_sectors[nr_secteur].time_ms == 0)
    {
        shmem_data->best_sectors[nr_secteur].time_ms = dureeSecteur_ms;
        shmem_data->best_sectors[nr_secteur].car_nr = car_nr;
    }
    return dureeSecteur_ms;
}

void dessiner(int car_nr, int position)
{
    int status = shmem_data->cars[car_nr].status;
    int tour_courant = shmem_data->cars[car_nr].tour_courant;
    int secteur_courant = shmem_data->cars[car_nr].secteur_courant;
    const int nombreTirets = 30;
    char secteur_1[nombreTirets + 1];
    char secteur_2[nombreTirets + 1];
    char secteur_3[nombreTirets + 1];

    // fill sectors
    for (int i = 0; i < nombreTirets; i++)
    {
        secteur_1[i] = '-';
    }
    secteur_1[nombreTirets] = '\0';
    secteur_1[nombreTirets - 1] = '|';

    for (int i = 0; i < nombreTirets; i++)
    {
        secteur_2[i] = '-';
    }
    secteur_2[nombreTirets] = '\0';
    secteur_2[nombreTirets - 1] = '|';

    for (int i = 0; i < nombreTirets; i++)
    {
        secteur_3[i] = '-';
    }
    secteur_3[nombreTirets] = '\0';
    secteur_3[nombreTirets - 1] = '|';

    // compute where to put the car
    int positionEtoile = (nombreTirets - 1) * position / 100;
    if (secteur_courant == 1)
    {
        secteur_1[positionEtoile] = '*';
    }
    if (secteur_courant == 2)
    {
        secteur_2[positionEtoile] = '*';
    }
    if (secteur_courant == 3)
    {
        secteur_3[positionEtoile] = '*';
    }

    printf("%3d) voiture, pilote : %-15s, status: %- 8s, sect:%2d, pos:%3d, tour:%d ",
           car_nr, shmem_data->cars[car_nr].pilote, char_status_desc[status], secteur_courant, position, tour_courant);

    printf("%s%s%s\n", secteur_1, secteur_2, secteur_3);
}

void vivre_ma_vie_de_voiture(int car_nr)
{
    int temps_tour_courant_ms;
    char *block;
    int tour_courant = 0;
    int temps_total_ms = 0;
    block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL)
    {
        printf("ERROR: couldn't get block\n");
        exit(1);
    }

    shmem_data = (Shmem_data *)block;
    srand(time(NULL) + car_nr);
    shmem_data->cars[car_nr].status = STATUS_RUNNING;
    while (tour_courant < NB_TOUR)
    {
        tour_courant += 1;
        shmem_data->cars[car_nr].tour_courant = tour_courant;
        temps_tour_courant_ms = 0;
        temps_tour_courant_ms += gererSecteur(car_nr, 1);
        temps_tour_courant_ms += gererSecteur(car_nr, 2);
        temps_tour_courant_ms += gererSecteur(car_nr, 3);
        if (temps_tour_courant_ms < shmem_data->cars[car_nr].best_tour_time_ms || tour_courant == 1)
        {
            shmem_data->cars[car_nr].best_tour_time_ms = temps_tour_courant_ms;
        }
        temps_total_ms += temps_tour_courant_ms;
        shmem_data->cars[car_nr].total_time_de_la_course_ms = temps_total_ms;
    }
    shmem_data->cars[car_nr].status = STATUS_FINISHED;
    detach_memory_block(block);
}

// cette fonction renvoit 1 si toutes les voitures ont terminé, c'est-à-dire que le position est à 100% du secteur
// et renvoit 0 autrement
int toutesLesVoituresOntTermine()
{
    for (int i = 0; i < NB_VOITURE; i++)
    {
        if (shmem_data->cars[i].position < 100)
        {
            return 0;
        }
    }
    return 1;
}

// returns 1 if car a has a better ranking than car b
int estMeilleurQue(int a, int b)
{
    struct Car voit_a;
    struct Car voit_b;

    voit_a = shmem_data->cars[a];
    voit_b = shmem_data->cars[b];

    if (voit_a.status == STATUS_FINISHED && voit_b.status == STATUS_FINISHED)
    {
        if (voit_a.total_time_de_la_course_ms < voit_b.total_time_de_la_course_ms)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    // if other cases...

    if (voit_a.status == STATUS_FINISHED && voit_b.status != STATUS_FINISHED)
    {
        return 1;
    }

    if (voit_a.status != STATUS_FINISHED && voit_b.status == STATUS_FINISHED)
    {
        return 0;
    }
    // here we are sure that both status are different than the finished status
    if (voit_a.tour_courant != voit_b.tour_courant)
    {
        if (voit_a.tour_courant > voit_b.tour_courant)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        // here we are sure that the tour_courant are the same
        if (voit_a.secteur_courant != voit_b.secteur_courant)
        {
            if (voit_a.secteur_courant > voit_b.secteur_courant)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            // here we are sur that the tour_courant and the secteur_courant are the same
            if (voit_a.position > voit_b.position)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

void classer()
{
    for (int i = 0; i < NB_VOITURE; i++)
    {
        classement[i] = i;
    }
    for (int i = 0; i < NB_VOITURE - 1; i++)
    {
        for (int j = i + 1; j < NB_VOITURE; j++)
        {
            if (estMeilleurQue(classement[j], classement[i]))
            {
                int temp = classement[i];
                classement[i] = classement[j];
                classement[j] = temp;
            }
        }
    }
}

void afficherClassement()
{
    classer();
    for (int i = 0; i < NB_VOITURE; i++)
    {
        printf("pos %d : car %d pilote %-13s \n", i + 1, classement[i], shmem_data->cars[classement[i]].pilote);
    }
}

void monitorerVoitures()
{
    int iter = 0;
    while (1)
    {
        printf("\n");
        iter++;

        for (int i = 0; i < NB_VOITURE; i++)
        {
            int secteur_courant = shmem_data->cars[i].secteur_courant;
            int position = shmem_data->cars[i].position;
            int time_sector1 = shmem_data->cars[i].time_sector1;
            int time_sector2 = shmem_data->cars[i].time_sector2;
            int time_sector3 = shmem_data->cars[i].time_sector3;
            int best_tour_time = shmem_data->cars[i].best_tour_time_ms;
            int temps_total = shmem_data->cars[i].total_time_de_la_course_ms;
            printf("%3d) voiture %2d, secteur courant : %d, temps secteur1 : %6.3f, temps secteur2 : %6.3f, temps secteur3 : %6.3f, best tour time : %6.3f, temps total : %6.3f \n",
                   iter, i, secteur_courant, (time_sector1 * 1.0) / 1000, (time_sector2 * 1.0) / 1000, (time_sector3 * 1.0) / 1000, (best_tour_time * 1.0) / 1000, (temps_total * 1.0) / 1000);
        }

        for (int i = 0; i < NB_VOITURE; i++)
        {
            dessiner(i, shmem_data->cars[i].position);
        }

        afficherClassement();

        printf("best time for sector 1: time : %6.3f, car : %d \n", (shmem_data->best_sectors[1].time_ms * 1.0) / 1000, shmem_data->best_sectors[1].car_nr);
        printf("best time for sector 2: time : %6.3f, car : %d \n", (shmem_data->best_sectors[2].time_ms * 1.0) / 1000, shmem_data->best_sectors[2].car_nr);
        printf("best time for sector 3: time : %6.3f, car : %d \n", (shmem_data->best_sectors[3].time_ms * 1.0) / 1000, shmem_data->best_sectors[3].car_nr);
        if (toutesLesVoituresOntTermine() == 1)
        {
            break;
        }
        usleep(100 * 1000); // attendre x microsecond
    }
}

// initialisation de la mémoire partagée pour être sur de ne pas les afficher avant initialisation
void initialiser_shm_pour_voiture(int nr_voiture)
{
    shmem_data->cars[nr_voiture].best_tour_time_ms = 0;
    shmem_data->cars[nr_voiture].time_sector1 = 0;
    shmem_data->cars[nr_voiture].time_sector2 = 0;
    shmem_data->cars[nr_voiture].time_sector3 = 0;
    shmem_data->cars[nr_voiture].secteur_courant = 0;
    shmem_data->cars[nr_voiture].position = 0;
    shmem_data->cars[nr_voiture].tour_courant = 0;
    shmem_data->cars[nr_voiture].status = STATUS_READY;
}

int lancerVoiture(int nr_voiture)
{
    int pid;
    pid = fork();

    initialiser_shm_pour_voiture(nr_voiture);

    if (pid == -1)
    {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        vivre_ma_vie_de_voiture(nr_voiture);
        exit(0);
    }
    else
    {
        return pid;
    }
}

void initialisation_best_sectors_time()
{
    shmem_data->best_sectors[1].car_nr = 0;
    shmem_data->best_sectors[1].time_ms = 0;
    shmem_data->best_sectors[2].car_nr = 0;
    shmem_data->best_sectors[2].time_ms = 0;
    shmem_data->best_sectors[3].car_nr = 0;
    shmem_data->best_sectors[3].time_ms = 0;
}

// cette fonction assigne les pilotes aux voitures
void assignerLesPilotesAuxVoitures()
{
    for (int i = 0; i < NB_VOITURE; i++)
    {
        strcpy(shmem_data->cars[i].pilote, pilotes[i].nom);
    }
}

void init_scores()
{
    for (int i = 0; i < nb_pilotes; i++)
    {
        for (int j = 0; j < nb_courses; j++)
        {
            scores[i][j] = 0;
        }
    }
}

void afficher_scores()
{

    char short_name[30];

    printf("\n");
    printf("          |");
    for (int i = 0; i < nb_courses; i++)
    {
        strncpy(short_name, races[i].ville, 6);
        short_name[5] = '\0';
        printf("%-5s|", short_name);
    }
    printf("\n");
    for (int i = 0; i < nb_pilotes; i++)
    {
        printf("%10s|", shmem_data->cars[i].pilote);
        for (int j = 0; j < nb_courses; j++)
        {
            printf("%5d|", scores[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    destroy_shmem();

    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL)
    {
        printf("ERROR: couldn't get block\n");
        exit(1);
    }

    // mapping the Shmem_data structure on the shared memory block
    shmem_data = (Shmem_data *)block;
    initialisation_best_sectors_time();

    nb_courses = lireCircuits(races);
    afficherCircuits(races, nb_courses);

    // Demander à l'utilisateur de choisir une course
    int course_demandee;
    printf("Entrez le numéro de la course que vous souhaitez afficher : ");
    // scanf("%d", &course_demandee);
    course_demandee = 2;

    // Afficher les détails de la course sélectionnée
    int resultat = choisirCourse(races, nb_courses, course_demandee);
    if (!resultat)
    {
        printf("La course demandée n'a pas été trouvée.\n");
        return 1; // Quitter le programme si la course n'est pas trouvée
    }

    // F1Race races[MAX_ROWS];
    // int num_races = lireEnMemoire(races);
    // afficherCircuits(races, num_races);
    printf("\n\n");
    nb_pilotes = lirePilotes(pilotes);
    afficherPilotes(pilotes, nb_pilotes);
    assignerLesPilotesAuxVoitures();
    init_scores();
    afficher_scores();

    // exit(0);

    pid_t pid[NB_VOITURE];
    for (int i = 0; i < NB_VOITURE; i++)
    {
        pid[i] = lancerVoiture(i);
    }
    monitorerVoitures();
    detach_memory_block(block);

    destroy_shmem();

    return 0;
}
