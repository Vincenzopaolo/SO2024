#include <ourhdr.h>

void reverse_arr(int arr[], int size){
    for(int i=0; i < size/2;i++){
        int temp=arr[i];
        arr[i] = arr[size -1 -i];
        arr[size -1 -i] = temp;
    }
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

    reverse_arr(array, size);

    for (int i = 0; i < size; i++){
        printf("%d\n", array[i]);
    }

    exit(EXIT_SUCCESS);
}