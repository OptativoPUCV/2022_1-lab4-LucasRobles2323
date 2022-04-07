#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
    char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    if(key==NULL) return;
    long index = hash(key, map->capacity);

    while ((map->buckets[index]->key != NULL) || (map->buckets[index] != NULL))
    {
       if(is_equal(key, map->buckets[index]->key))
       {
           return;
       }

       if(index < map->capacity){
           index++;
       }
       else{
           index = 0;
       }
    }
    
    if(map->buckets[index] != NULL){
        strcpy( (char*) map->buckets[index]->key, (char*) key);
        map->buckets[index]->value = value;
        map->size++;
        map->current = index;
    }
    else{
        map->buckets[index] = createPair(key, value);
    }
    
    if(map->size / map->capacity >= 0.70){
        enlarge(map);
    }

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *Map = (HashMap*) malloc (sizeof(HashMap));
    Map->capacity = capacity;
    Map->current = -1;
    Map->size = 0;
    Map->buckets = (Pair**) malloc (sizeof(Pair*) * 10);
    for (size_t i = 0; i < 10; i++)
    {
        Map->buckets[i] = NULL;
    }
    
    return Map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   
    long indice = hash(key, map->capacity);

    while (map->buckets[indice] != NULL)
    {
        if (strcmp( (char*)map->buckets[indice]->key, (char*)key) == 0)
        {
            return map->buckets[indice];
        }
        if(indice < map->capacity){indice++;}
        else{indice = 0;}
    }

    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
