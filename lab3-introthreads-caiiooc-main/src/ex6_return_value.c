#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// TODO: Implemente a função que calcula e retorna um resultado
void* calculate_square(void* arg) {
    int num = *(int*)arg;
    
    // TODO: Aloque memória no heap para o resultado
    int* result = malloc(sizeof(int));
    
    
    // TODO: Verifique se a alocação foi bem-sucedida
    if (result == NULL) 
    {
        perror("malloc");
        pthread_exit(NULL); // encerra a thread em caso de erro
    }
    
    
    // TODO: Calcule o quadrado e armazene no resultado
    *result = num * num;
    
    
    printf("Thread %d: Calculando %d^2 = %d\n", num, num, *result);
    
    return result;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    
    printf("Main: Criando threads para calcular quadrados\n\n");
    
    // Criar threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i + 1; // Valores: 1, 2, 3, 4, 5
        
        if (pthread_create(&threads[i], NULL, calculate_square, &thread_args[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }
    
    printf("\nMain: Coletando resultados\n");
    
    // TODO: Coletar resultados das threads
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        // TODO: Declare uma variável para receber o resultado
        void* thread_result;

        // TODO: Use pthread_join para obter o valor de retorno
        if (pthread_join(threads[i], &thread_result) != 0) 
        {
            perror("pthread_join");
            return 1;
        }
        
        // TODO: Converta o resultado para int* e imprima
        int* result = (int*)thread_result;
        
        // TODO: Libere a memória alocada pela thread
        if (result != NULL) 
        {
            printf("Main: Resultado da thread %d = %d\n", i + 1, *result);
            free(result);
        }
    }
        
    printf("\nMain: Todos os cálculos completados\n");
    
    return 0;
}