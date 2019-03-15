#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NB_GEN 1000
#define D_SIZE 100

void init_damier(int dam[D_SIZE][D_SIZE]) {
	int i, j;
	for (i = 0; i < D_SIZE; i++) {
		for (j = 0; j < D_SIZE; j++) {
			dam[i][j] = rand() % 2;
		}
	}
}

int voisins(int dam[][D_SIZE], int i, int j) {
	int k, l, k_modif, l_modif;
	int v = 0;
	for (k = i - 1; k < i + 2; k++) {
		k_modif = k;
		switch (k) {
		case -1:
			k_modif = D_SIZE - 1;
			break;
		case D_SIZE:
			k_modif = 0;
			break;
		}
		for (l = j - 1; l < j + 2; l++) {
			l_modif = l;
			switch (l) {
			case -1:
				l_modif = D_SIZE - 1;
				break;
			case D_SIZE:
				l_modif = 0;
				break;
			}
			if (!(k_modif == i && l_modif == j)) {
				v += dam[k_modif][l_modif];
			}
		}
	}
	return v;
}

void afficher_damier(int dam[][D_SIZE]) {
	int i, j;
	printf(" ");
	for (i = 0; i < D_SIZE; i++) {
		printf("-");
	}
	printf("\n");
	for (i = 0; i < D_SIZE; i++) {
		printf("|");
		for (j = 0; j < D_SIZE; j++) {
			if (dam[i][j] == 1) {
				printf("%d", dam[i][j]);
			} else {
				printf(" ");
			}
		}
		printf("|\n");
	}
	printf(" ");
	for (i = 0; i < D_SIZE; i++) {
		printf("-");
	}
	printf("\n");
}

void next_gen(int dam[][D_SIZE]) {
	int i, j;
	int temp[D_SIZE][D_SIZE];
	int v;
	i = 0, j = 0;
	for (i = 0; i < D_SIZE; i++) {
		for (j = 0; j < D_SIZE; j++) {
			v = voisins(dam, i, j);
			if (v == 3) {
				temp[i][j] = 1; // birth
			} else if (v == 2) {
				if (dam[i][j] == 1) {
					temp[i][j] = 1; // survive
				}
			} else if (v >= 4) {
				temp[i][j] = 0;
			} else {
				temp[i][j] = 0;
			}
		}
	}
	for (i = 0; i < D_SIZE; i++) {
		for (j = 0; j < D_SIZE; j++) {
			dam[i][j] = temp[i][j];
		}
	}

}

int main() {
	srand(time(NULL));
	int dam[D_SIZE][D_SIZE];
	init_damier(dam);
	int i = 0;
	while (i < NB_GEN) {
		next_gen(dam);
		system("clear");
		afficher_damier(dam);
		usleep(50000);
		i++;
	}
	return 0;
}

