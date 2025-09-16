#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// Função que será executada por cada thread
// Recebe um ponteiro para um inteiro como argumento
void* worker_thread(void* arg) {
    // TODO: Converta o argumento de void* para int*
    
    // Converte o argumento para inteiro
    int* thread_num = (int*) arg;

    // TODO: Use o valor apontado para identificar a thread
    // printf("Thread %d: Iniciando trabalho\n", ...);

    printf("Thread %d: Iniciando trabalho\n", *thread_num);
    
    // TODO: Simule algum trabalho
    // Por exemplo, calcular algo baseado no ID da thread
    // int result = ...;
    // printf("Thread %d: Resultado = %d\n", *thread_num, result);

    int result = (*thread_num) * (*thread_num);
    printf("Thread %d: Resultado = %d\n", *thread_num, result);
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    // TODO: Declare um array para armazenar os argumentos das threads
    // Cada thread precisa de seu próprio espaço de memória

    int thread_args[NUM_THREADS];
    
    printf("Main: Criando %d threads com argumentos diferentes\n\n", NUM_THREADS);
    
    // TODO: Crie as threads passando argumentos únicos
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        thread_args[i] = i + 1; 

        // Crie a thread passando o endereço do argumento
        if (pthread_create(&threads[i], NULL, worker_thread, &thread_args[i]) != 0) 
        {
            perror("pthread_create");
            return 1;
        }

    }
    
    
    printf("Main: Aguardando todas as threads terminarem\n\n");
    
    // TODO: Aguarde todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        pthread_join(threads[i], NULL);
    }
    
    
    printf("\nMain: Todas as threads completaram\n");
    
    return 0;
}