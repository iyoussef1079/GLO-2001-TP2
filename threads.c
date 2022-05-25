#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N 8
#define M 10
#define P 5
#define N_THREADS N*P

typedef struct {
    int  iThread;
    int Longueur;
    double Vecteur1[M];
    double Vecteur2[M];
    double *pResultat;
} ParametresThread;

/* Voici la fonction correspondant a chaque thread - à compléter */
void  *ProduitScalaire(void *data) {
    ParametresThread *pParam = (ParametresThread*)data;


    pthread_exit(NULL);
}

/* Une fonction pour afficher une matrice a l'ecran */
void AfficherMatrice(double *pMatrice, int nrangees, int ncolonnes) {
    int i,j;
    printf("Matrice : \n");
    for (i=0; i<nrangees; i++) {
        for (j=0; j<ncolonnes; j++ ) {
            printf("%10.3f ",pMatrice[i*ncolonnes+j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Creation des deux matrices
    printf("Nous allons creer les matrice de %dx%d et %dx%d\n",N,M,M,P);
    int i,j,index;
    double G[N][M];
    double H[M][P];
    double R[N][P];

    // Initialisation de la premiere matrice
    for (i=0;i<N;i++) {
        for (j=0; j<M; j++) {
            G[i][j] = (double)i + (double)j*0.01;
        }
    }
    AfficherMatrice(&G[0][0],N,M);

    // Initialisation de la deuxieme matrice
    for (i=0;i<M;i++) {
        for (j=0; j<P; j++) {
            H[i][j] = (double)i + (double)j*0.01;
        }
    }
    AfficherMatrice(&H[0][0],M,P);
    // Votre code de creation de thread commence ici...



    // Et se termine essentiellement ici...
    printf("Main(): Tous les threads ont termines! On affiche la reponse...\n");
    AfficherMatrice(&R[0][0],N,P);
    exit(0);
}
