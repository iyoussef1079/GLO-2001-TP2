
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "file.h"

File::File()
{
pthread_cond_init(&condition_consommateurs, NULL);
pthread_cond_init(&condition_producteurs, NULL);
pthread_mutex_init(&mutex_stockage, NULL);
    execution_terminee = false;
}

void File::Insere(const ItemFile &item)
{
    pthread_mutex_lock(&mutex_stockage);
    if (stockage.size() == TAILLE_STOCKAGE)
    {
        pthread_cond_wait(&condition_producteurs, &mutex_stockage);
    }
    stockage.push_front(item);
    pthread_cond_signal(&condition_consommateurs);
    pthread_mutex_unlock(&mutex_stockage);
}

bool File::Retire(ItemFile &item)
{


    pthread_mutex_lock(&mutex_stockage);

    if (execution_terminee){
    std::cout<< item.numero_serie << std::endl;
    }

    if (stockage.empty())
    {
            if(execution_terminee){return false;}
            pthread_cond_wait(&condition_consommateurs, &mutex_stockage);

    }
    item = stockage.back();
    stockage.pop_back();
    pthread_cond_signal(&condition_producteurs);
    pthread_mutex_unlock(&mutex_stockage); 
    return true;
}

void File::Termine()
{
    pthread_mutex_lock(&mutex_stockage);
    pthread_cond_broadcast(&condition_consommateurs);
    execution_terminee = true; 
    pthread_mutex_unlock(&mutex_stockage);

}
