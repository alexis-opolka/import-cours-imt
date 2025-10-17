#include <stdio.h>

int main() {
    char prenoms[2] = {};
    int ages[2] = {};
    float time[2] = {};
    float points[2] = {};
    float distance;



    for (int i = 0; i < 2; i++){
        printf("1ere lettre du candidat %d : ", i+1);
        scanf(" %c", &prenoms[i]);
        printf("Son age : ");
        scanf(" %d", &ages[i]);
        printf("Son temps pour un 100 mètre : ");
        scanf(" %f", &time[i]);

        points[i] = ((100/time[i]) * (100/time[i])) / ages[i];
    }



    // 1 - Afficher celui qui a le meilleur score
    if (points[0] > points[1]) {
        printf("%c,%d,%f avec %f points !\n", prenoms[0],ages[0],time[0], points[0]);
    } else if (points[1] > points[0]) {
	    printf("%c,%d,%f avec %f points !\n", prenoms[1],ages[1],time[1], points[1]);
    } else {
	    printf("%c et %c ont le même score, %f points !", prenoms[0], prenoms[1], points[0]);
    }

    // 2 - On demande la distance parcourue maintenant
    printf("Distance parcourue : ");
    scanf(" %f", &distance);

    for (int i = 0; i < 2; i++){
        points[i] = ((distance/time[i]) * (distance/time[i])) / ages[i];
    }

    if (points[0] > points[1]) {
        printf("%c,%d,%f avec %f points pour un %f mètres !\n", prenoms[0],ages[0],time[0], points[0], distance);
    } else if (points[1] > points[0]) {
	    printf("%c,%d,%f avec %f points pour un %f mètres !\n", prenoms[1],ages[1],time[1], points[1], distance);
    } else {
	    printf("%c et %c ont le même score, %f points pour un %f mètres !", prenoms[0], prenoms[1], points[0], distance);
    }

    // 3 - Bravo au gagnant sinon Dommage
}



