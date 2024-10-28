/*
* Scrivere un programma che prende da riga di comando una sequenza di N interi, dopo crea un processo figlio
* che esegue il programma order_n (messo in /usr/local/bin). Quando "termina" il figlio, viene comunicato tramite pipe
* al processo padre l'output di order_n che viene poi passato al programma reverse_arr (messo in /usr/local/bin),
* stampando così un array ordinato in senso decrescente
*/

#include<ourhdr.h>

char **crea_argomenti(const char *str, int num_w){
    char ** argomenti = (char **) malloc(num_w * sizeof(char *));
    int  indice = 0;
    for(int i = 0; i< num_w;i++){
        int dim_w =0, arr_start=0;
        while(str[indice] != '\0'){
            if(str[indice]!= ' ')dim_w++;
            else break;
            indice++;
        }
        argomenti[i] = (char*) malloc(dim_w*sizeof(char*));
        for(int j=indice-dim_w; j <= indice;j++){
            argomenti[i][arr_start] = str[j];
            arr_start++;
        }
        indice++;
    }  
    return argomenti;
}

int main(int argc, char *argv[]){
    if (argc < 2){
        err_quit("Usage:\n%s N [...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int fd[2], pid, size = argc - 1;
    if (pipe(fd)<0){
        err_sys("[Error] pipe");
        exit(EXIT_FAILURE);
    }
    int read_fd = fd[0], write_fd = fd[1];
    if((pid = fork())<0){
        err_sys("[Error] fork");
        exit(EXIT_FAILURE);
    }
    else{
        if(pid > 0){ // processo padre
            wait(); // aspetto che termini il figlio
            close(write_fd);
            int buffer_size = (size * size) + 1;
            char buffer[MAXLINE];
            if(read(read_fd, &buffer, sizeof(buffer)) < 0){
                err_sys("[Error] read %d", read_fd);
                exit(EXIT_FAILURE);
            }
            else{
                // blocco conversione output figlio in argomenti
                int i = 0, b_size = 0, words_no = 0;
                while(buffer[i] != '\n'){
                    i++;
                    b_size++;
                    if(buffer[i] == ' ')words_no++;
                }
                char *new_args = (char *) malloc(b_size);
                for(int j =0; j < b_size;j++){
                    new_args[j] = buffer[j];
                }
                char **args_arr = crea_argomenti(new_args, words_no);   
                // fine blocco            
                if(execvp("reverse_arr", args_arr) == -1){
                    err_sys("[Error] execvp");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else{ // processo figlio
            close(read_fd);
            dup2(write_fd, 1);
            close(write_fd);
            if(execvp("order_n", argv) == -1){
                err_sys("[Error] execvp");
                exit(EXIT_FAILURE);
            }
            return NULL; // ??????
        }
    }
    exit(EXIT_SUCCESS);
}