#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"

typedef struct Vector {
  int taille;
  int reserve;
  char* valeurs;
} Vector;

Vector* vector_new() {
  Vector* v = malloc(sizeof(Vector));
  v->taille = 0;
  v->valeurs = malloc(3);
  v->reserve = 3;
  return v;
}


Vector* vector_from_buffer(char* buffer, int size) {
  Vector* v = malloc(sizeof(Vector));
  v->taille = size;
  v->valeurs = buffer;
  v->reserve = size;
  return v;
}

void vector_add_elem(Vector* v, char elem) {
  v->taille++;
  if (v->taille > v->reserve) {
    v->reserve *= 2;
    char* new_tab = malloc(v->reserve);
    memcpy(new_tab, v->valeurs, v->taille);
    free(v->valeurs);
    v->valeurs = new_tab;
  }
  v->valeurs[v->taille - 1] = elem;
}

int vector_rechercher(Vector* v, int starting_at, char elem) {
  for (int i = starting_at; i < v->taille; i++) {
    if (elem == v->valeurs[i]) {
      return i;
    }
  }
  return -1;
}

void vector_free(Vector* v) {
  free(v->valeurs);
  free(v);
}

int vector_used_memory(Vector* v) {
  return sizeof(v) + sizeof(char) * v->reserve;
}


char* read_file(char* path, int* length){
  char * buffer;
  FILE * f = fopen (path, "rb");
  if (f)
  {
    fseek (f, 0, SEEK_END);
    *length = ftell (f);
    buffer = malloc (*length + 1);
    fseek (f, 0, SEEK_SET);
    if (buffer)
    {
      fread (buffer, 1, *length, f);
    }
    buffer[*length] = 0;
    fclose (f);
  } else {
    printf("file not oppened : %s\n", path);
  }
  return buffer;
}

void print_time(char* format, double time) {
  if (time < 0.001) {
    printf(format, time * 1000.0 * 1000.0, "us");
  } else if (time < 1.0) {
    printf(format, time * 1000.0, "ms");
  } else {
    printf(format, time, "s");
  }
}

 
int main() {
  double cpu_time_used;
  clock_t start, end;
 
  start = clock();
  // de https://github.com/chrplr/openlexicon/blob/master/datasets-info/Liste-de-mots-francais-Gutenberg/liste.de.mots.francais.frgut.txt
  int size;
  char* buffer = read_file("dict.txt", &size);
  Vector* v = vector_from_buffer(buffer, size);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  
  print_time("Tableau chargé en %.3lf %s\n", cpu_time_used);
  printf("Memoire utilisée pour %d elements: %.3fMo\n", v->taille, ((float)vector_used_memory(v)) / 1000000.0);

  int total = 0;

  start = clock();
  for (char c = 'a'; c < 'z'; c++) {
    for (int pos = 0;(pos = vector_rechercher(v, pos + 1, c)) != -1; total++);
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("26 parcours de tableau et %d appels à la fonction rechercher ", total);
  print_time("en %.3lf %s\n", cpu_time_used);

  vector_free(v);
}

