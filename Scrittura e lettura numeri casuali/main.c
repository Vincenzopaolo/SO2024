/*
 ============================================================================
 Name        : RandomInts
 Author      : Vincenzopaolo Esposito
 Description : Genera n numeri interi random, scrivili in un file,
  	  	  	   li rileggi e li stampi a righe di sei sulla stdout(?)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>


int print_six_per_row(int *buffer, int size){
	char str_buffer[12];
	for(int i = 0; i < size; i++){
		if(i % 6  == 0 && i != 0){
			ssize_t new_line_byte = write(1, "\n", sizeof(char));
			if (new_line_byte == -1){
				perror("Errore nella scrittura sulla stdout");
				return 1;
			}
		}
		sprintf(str_buffer, "%d", buffer[i]);
		ssize_t data = write(1, str_buffer, sizeof(str_buffer));
		if (data == -1){
			perror("Errore nella scrittura sulla stdout");
			return 1;
		}
		ssize_t spacing;
		if (i == size-1){
			spacing = write(1, "\n", sizeof(char)*2);
		}
		else{
			spacing = write(1, ",\t", sizeof(char)*2);
		}
		if (spacing == -1){
			perror("Errore nella scrittura sulla stdout");
			return 1;
		}
	}
	return 0;
}

int main(void) {
	srand(time(NULL));
	int size;
	int *numeri_casuali;
	printf("Inserisci il numero di interi casuali: ");
	scanf("%d", &size);
	numeri_casuali = (int*)malloc(size * sizeof(int));
	if (numeri_casuali == NULL){
		perror("Errore, memoria non allocata");
	}
	else{
		for(int i = 0; i < size; i++){
			numeri_casuali[i] = rand();
		}
		int fd = open("test.txt", O_CREAT | O_RDWR, 0644);
		if (fd == -1){
			perror("Errore nell'apertura del file\n");
			return 1;
		}
		else{
			//printf("Apertura file avvenuta con successo!\n");
			ssize_t numero = write(fd, numeri_casuali, sizeof(numeri_casuali));
			if (numero == -1){
				perror("Errore nella scrittura su file");
				return 1;
			}
			//printf("Scrittura buffer completata!\n");
			if (close(fd) == -1){
				perror("Errore chiusura file!\n");
				return 1;
			}
			else{
				printf("Numeri scritti su file:\n");
				print_six_per_row(numeri_casuali, size);
				printf("_______________________\n");
				//printf("Chiusura file avvenuta con successo!\n");
				free(numeri_casuali);
				numeri_casuali = NULL;
				//printf("Svuotamento buffer avvenuto con successo!\n");
				fd = open("test.txt", O_CREAT | O_RDWR, 0644);
				if (fd == -1){
					perror("Errore nell'apertura del file\n");
					return 1;
				}
				else{
					//printf("File riaperto con successo!\n");
					numeri_casuali = (int*)malloc(size * sizeof(int));
					ssize_t lettura = read(fd, numeri_casuali, sizeof(numeri_casuali));
					if(lettura != -1){
						//printf("Lettura avvenuta correttamente!\n");
						printf("Numeri letti dal file:\n");
						print_six_per_row(numeri_casuali, size);
						printf("_______________________\n");
						free(numeri_casuali);
						numeri_casuali = NULL;
						//printf("Svuotamento buffer avvenuto con successo!\n");
						if (close(fd) == -1){
							perror("Errore chiusura file!\n");
							return 1;
						}
					}
					else{
						perror("errore lettura");
						return -1;
					}
				}
			}
		}
	}
}

