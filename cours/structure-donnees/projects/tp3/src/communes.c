#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LINE_SIZE 4000
#define MAX_COMMUNES 40000

typedef struct {
    char nom_standard[100];
    char dep_nom[50];
    char reg_nom[50];
    int population;
    float superficie_km2;
    float densite;
} Commune;

char* get_field(char *line, int field_num) {
    static char buffer[256];
    int current_field = 0;
    int in_quotes = 0;
    int buffer_idx = 0;
    
    for (int i = 0; line[i] != '\0' && current_field <= field_num; i++) {
        if (line[i] == '"') {
            in_quotes = !in_quotes;
            continue;
        }
        if (line[i] == ',' && !in_quotes) {
            if (current_field == field_num) {
                buffer[buffer_idx] = '\0';
                return buffer;
            }
            current_field++;
            buffer_idx = 0;
        } else if (current_field == field_num) {
            buffer[buffer_idx++] = line[i];
        }
    }
    buffer[buffer_idx] = '\0';
    return buffer;
}

int compare_densite(const void *a, const void *b) {
    Commune *c1 = (Commune *)a;
    Commune *c2 = (Commune *)b;
    
    if (c2->densite > c1->densite) return 1;
    if (c2->densite < c1->densite) return -1;
    return 0;
}

// lit les ~35000 communes
Commune* read_communes(int* size, char* file){
  FILE *fp;
  char line[MAX_LINE_SIZE];
  Commune *communes;
  communes = (Commune *)malloc(MAX_COMMUNES * sizeof(Commune));
  fp = fopen(file, "r");
  *size = 0;
  
  fgets(line, MAX_LINE_SIZE, fp);// on ignore l'en tête
  while (fgets(line, MAX_LINE_SIZE, fp)) {
      strcpy(communes[*size].nom_standard, get_field(line, 2));
      strcpy(communes[*size].reg_nom, get_field(line, 11));
      strcpy(communes[*size].dep_nom, get_field(line, 13));
      communes[*size].population = atoi(get_field(line, 29));
      communes[*size].superficie_km2 = atof(get_field(line, 31));
      communes[*size].densite = atof(get_field(line, 32));
      
      (*size)++;
  }

  fclose(fp);
  return communes;
}


int main() {
  int size;
//(https://www.data.gouv.fr/api/1/datasets/r/f5df602b-3800-44d7-b2df-fa40a0350325) 
  Commune* communes = read_communes(&size, "communes.csv");
  printf("Nombre de communes lues: %d\n\n", size);
  qsort(communes, size, sizeof(Commune), compare_densite);

  printf("------------------------------------------------------\n");
  printf("20 communes les plus denses:\n");
  printf("%s %s %s %s %s\n", 
         "Commune", "Département", "Population", "Superficie", "Densité");
  printf("------------------------------------------------------\n");
  
  for (int i = 0; i < 20 && i < size; i++) {
      printf("%-60s %-20s %12d %9.2f km² %10.0f\n",
             communes[i].nom_standard,
             communes[i].dep_nom,
             communes[i].population,
             communes[i].superficie_km2,
             communes[i].densite);
  }
  free(communes);
}
