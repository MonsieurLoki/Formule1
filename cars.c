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

#define IPC_RESULT_ERROR (-1)
#define NB_VOITURE 4
#define NB_TOUR 2
#define STATUS_FINISHED 2
#define STATUS_RUNNING 1
#define STATUS_READY 0

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <stdbool.h>

// attach a shared memory block
// associated with filename
// create it if it doesn't exist

// all of the programs will share these values
#define BLOCK_SIZE 4096
#define FILENAME "cars.c"

#endif

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

char *char_status_desc[] = {"ready ", "Running", "Finished"};

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

    printf("%3d) voiture, status: %s, sect:%2d, pos:%3d, tour:%d ", car_nr, char_status_desc[status], secteur_courant, position, tour_courant);

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
