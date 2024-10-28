#include <ourhdr.h>
#include <stdbool.h>

void bubble_sort(int *array, int size){
    bool to_swap = false;
    int j = size-1;
    do{
        to_swap=false;
        for(int i = 0; i < j; i++){
            int temp = 0;
            if(array[i]>array[i+1]){
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                to_swap=true;
            }
        }
        j=j-1;
    }while (to_swap == true);
}

int main(int argc, char *argv[]){
    if(argc < 2){
        err_quit("Usage:\n%s N [...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int size = argc - 1, *array = (int *) malloc(sizeof(int)*size);
    if(array == NULL){
        err_sys("[Error] malloc\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++){
        array[i] = atoi(argv[i+1]);
    }
    bubble_sort(array, size); 
    int buffer_size = (size * 20) + size+1;
    char *buffer = (char *) malloc(sizeof(char) * buffer_size);
    for(int i =0;i< size;i++){
        sprintf(buffer +strlen(buffer), "%d ", array[i]);
    }
    sprintf(buffer +strlen(buffer), "%c ", '\n');    
    if(write(STDOUT_FILENO, buffer, buffer_size) < 0){
        err_sys("[Error] write of buffer: %s", buffer);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}