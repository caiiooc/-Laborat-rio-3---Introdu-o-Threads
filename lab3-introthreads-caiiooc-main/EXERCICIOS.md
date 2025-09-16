# Exercícios - Laboratório de Threads

## Parte 1: Fundamentos de Threads

### Exercício 1: Hello Thread

**Objetivo**: Criar sua primeira thread usando pthread_create.

**Arquivo**: `src/ex1_hello_thread.c`

**Descrição**: 
Implemente um programa que cria uma thread para imprimir "Hello from thread!". A thread principal deve imprimir "Hello from main!" e criar a thread filha.

**Tarefas**:
1. Implemente a função `print_hello` que será executada pela thread
2. Use `pthread_create` para criar a thread
3. Observe o comportamento sem sincronização

**Compilação e Execução**:
```bash
make ex1
./ex1_hello_thread
```

**Questões para Análise**:
- O que acontece se você executar o programa várias vezes?

R: Sempre aparecem as duas mensagens


- A ordem das mensagens é sempre a mesma?

R: Na minha máquina sim, apareceu primeiro a mensagem da main e depois a da thread varias vezes.


- Por que isso ocorre?

Isso acontece porque após chamar pthread_create, a thread principal continua executando imediatamente e imprime sua mensagem antes da thread criada ter tempo de rodar, assim o printf da main sai primeiro. 

Porém, essa ordem não é garantida e pode variar em outras máquinas ou situações de concorrência já que a execução depende do escalonador do sistema operacional.

---

### Exercício 2: Sincronização com pthread_join

**Objetivo**: Aprender a sincronizar threads usando pthread_join.

**Arquivo**: `src/ex2_hello_join.c`

**Descrição**:
Modifique o exercício anterior para garantir que a thread principal espere a thread filha terminar antes de encerrar o programa.

**Tarefas**:
1. Adicione `pthread_join` após criar a thread
2. Compare o comportamento com o exercício anterior
3. Entenda por que pthread_join é importante

**Compilação e Execução**:
```bash
make ex2
./ex2_hello_join
```

**Questões para Análise**:
- Qual a diferença no comportamento comparado ao exercício 1?

R: No exercício 1, a thread principal poderia terminar antes da thread filha imprimir sua mensagem. Na minha máquina, a saída aparecia sempre na mesma ordem. No exercício 2, com a adição de pthread_join, a thread principal espera explicitamente a thread filha finalizar antes de continuar garantindo que a mensagem final da main seja exibida apenas após a conclusão da thread filha.


- O que pthread_join está fazendo?

R: O pthread_join faz com que a thread que o chama (no caso a main) bloqueie sua execução até que a thread especificada termine.
Na prática, isso garante que a main não finalize o programa antes que a thread filha execute sua função e imprima sua mensagem, proporcionando sincronização entre threads.


- O que aconteceria sem pthread_join em um programa maior?

R: Sem pthread_join, a thread principal poderia terminar antes das threads filhas, o que pode causar problemas como mensagens sendo exibidas fora de ordem, threads filhas sendo interrompidas prematuramente, liberação de recursos ou memória ainda em uso pelas threads, comportamento imprevisível em programas com múltiplas threads acessando dados compartilhados.

Mesmo que na minha máquina a ordem tenha permanecido correta, não há garantia de execução ordenada sem o uso de pthread_join.


---

### Exercício 3: Múltiplas Threads

**Objetivo**: Gerenciar múltiplas threads simultaneamente.

**Arquivo**: `src/ex3_multiple_threads.c`

**Descrição**:
Crie um programa que lança N threads (definido por uma constante), onde cada thread imprime seu ID único.

**Tarefas**:
1. Defina `NUM_THREADS` como 5
2. Crie um array de `pthread_t` para armazenar os IDs das threads
3. Use um loop para criar todas as threads
4. Use outro loop para fazer join em todas as threads
5. Cada thread deve imprimir seu número de identificação

**Compilação e Execução**:
```bash
make ex3
./ex3_multiple_threads
```

**Questões para Análise**:
- A ordem de execução das threads é determinística?

R: R: Não, a ordem de execução das threads não é determinística, cada thread é escalonada pelo sistema operacional então a sequência em que elas imprimem suas mensagens pode variar a cada execução.


- Como você garantiria uma ordem específica de execução?

R: Para garantir uma ordem específica seria necessário usar mecanismos de sincronização como pthread_join em sequência (criar e esperar threads uma a uma), mutexes e variáveis de condição para controlar quando cada thread pode executar, semáforos para liberar threads em uma ordem predeterminada.


- O que acontece se aumentar NUM_THREADS para 100 ou 1000?

R: Ao aumentar NUM_THREADS o programa cria muitas threads simultaneamente o que causa aumento da concorrência e saída imprevisível, com mensagens possivelmente misturadas.


---

## Parte 2: Comunicação entre Threads

### Exercício 4: Passagem de Argumentos

**Objetivo**: Passar argumentos únicos para cada thread corretamente.

**Arquivo**: `src/ex4_thread_args.c`

**Descrição**:
Aprenda a passar argumentos individuais para cada thread. Cada thread deve receber um ID único e realizar algum processamento baseado nesse ID.

**Tarefas**:
1. Declare um array para armazenar os argumentos de cada thread
2. Inicialize cada elemento com um valor único (1 a NUM_THREADS)
3. Passe o endereço de cada elemento para sua respectiva thread
4. Dentro da thread, converta o void* para int* e use o valor
5. Faça cada thread imprimir seu ID e realizar algum cálculo simples

**Compilação e Execução**:
```bash
make ex4
./ex4_thread_args
```

**Questões para Análise**:
- Por que precisamos de um array para armazenar os argumentos?

R: Cada thread precisa de seu próprio argumento único. Usar um array garante que cada thread receba um endereço de memória diferente, evitando que todas compartilhem o mesmo valor e garantindo que cada thread use corretamente seu ID ou dado específico.


- O que aconteceria se usássemos uma única variável para todas as threads?

R: Se todas as threads usassem o mesmo endereço de uma única variável, elas poderiam ler o mesmo valor ou valores alterados por outra thread causando resultados incorretos ou inconsistentes. Por exemplo, várias threads poderiam imprimir o mesmo ID ou calcular resultados errados.


- Como o cast de void* para int* funciona?

R: O cast converte o ponteiro genérico (void*) para o tipo correto (int*) que a função da thread espera, isso permite acessar o valor original passado para a thread.


---

### Exercício 5: Passando Estruturas

**Objetivo**: Passar dados complexos para threads usando estruturas.

**Arquivo**: `src/ex5_struct_args.c`

**Descrição**:
Crie uma estrutura com múltiplos campos e passe para cada thread. Cada thread deve processar seus dados únicos.

**Tarefas**:
1. Defina uma estrutura `thread_data` com campos: id, name, value
2. Aloque memória para cada estrutura
3. Inicialize com dados únicos para cada thread
4. Passe as estruturas para as threads
5. Libere a memória apropriadamente

**Compilação e Execução**:
```bash
make ex5
./ex5_struct_args
```

**Questões para Análise**:
- Por que usamos alocação dinâmica para as estruturas?

R: A alocação dinâmica (malloc) permite criar um espaço de memória que persiste enquanto as threads estão em execução, cada thread recebe um ponteiro para sua própria estrutura garantindo que os dados não sejam sobrescritos ou corrompidos independentemente do tempo de execução da thread.


- O que aconteceria se usássemos variáveis locais?

R: Se usássemos variáveis locais dentro da função main, elas poderiam ser substituídas ou destruídas quando a função retornasse ou quando múltiplas threads acessassem a mesma memória, isso poderia causar dados incorretos ou comportamento imprevisível, já que todas as threads compartilhariam o mesmo espaço de memória temporário.


- Quando é seguro liberar a memória?

R: A memória alocada dinamicamente deve ser liberada apenas após todas as threads terem terminado de usar os dados, no código isso é feito depois do pthread_join em todas as threads garantindo que nenhuma thread tente acessar memória já liberada.


---

### Exercício 6: Valores de Retorno

**Objetivo**: Obter valores de retorno das threads.

**Arquivo**: `src/ex6_return_value.c`

**Descrição**:
Implemente threads que calculam valores e retornam resultados para a thread principal.

**Tarefas**:
1. Cada thread calcula o quadrado de seu ID
2. Aloque memória para o resultado no heap
3. Retorne o ponteiro para o resultado
4. A thread principal coleta e imprime todos os resultados
5. Libere a memória apropriadamente

**Compilação e Execução**:
```bash
make ex6
./ex6_return_value
```

**Questões para Análise**:
- Por que o resultado deve ser alocado no heap?

R: O resultado precisa ser alocado no heap para que ele persista mesmo após a função da thread terminar. Se usássemos uma variável local, ela seria destruída ao final da função, e a main não conseguiria acessar o valor retornado.


- O que aconteceria se retornássemos endereço de variável local?

R: Retornar o endereço de uma variável local causaria comportamento indefinido. A variável deixaria de existir quando a função da thread terminasse, então qualquer acesso posterior na main poderia ler lixo na memória ou gerar falhas.


- Como pthread_join obtém o valor de retorno?

R: A função pthread_join recebe um ponteiro para void* como segundo argumento. Ela armazena o valor retornado pela thread nesse ponteiro, permitindo que a main acesse o resultado.

---

## Parte 3: Análise e Reflexão

## Questões de Reflexão

1. **Sincronização**: Por que pthread_join é necessário?

R: pthread_join garante que a thread principal espere a conclusão de uma thread filha antes de continuar, sem o pthread_join a main poderia terminar antes das threads, fazendo com que mensagens ou resultados não fossem exibidos corretamente ou mesmo causando acesso a memória já liberada.


2. **Passagem de Argumentos**: Qual a diferença entre passar valores e ponteiros?

R:

Valores: Cada thread recebe uma cópia do dado; alterações locais não afetam outras threads.

Ponteiros: Threads recebem o endereço da memória; alterações podem ser vistas por outras threads permitindo compartilhamento de dados, mas exigindo cuidado para evitar conflitos ou condições de corrida.


3. **Compartilhamento de Memória**: O que as threads compartilham e o que é privativo?

R:

Compartilhado: memória global, heap e quaisquer variáveis acessadas por ponteiros.

Privativo: memória local de cada thread (variáveis locais dentro da função da thread) e registradores da CPU. Cada thread tem seu próprio contexto de execução.


4. **Ordem de Execução**: Por que a ordem de execução das threads é não-determinística?

R: A ordem é determinada pelo escalonador do sistema operacional que decide quando cada thread será executada. Por isso, a sequência de impressão ou execução pode variar entre execuções principalmente quando há múltiplas threads concorrendo pelo processador.


5. **Alocação de Memória**: Por que devemos alocar no heap para retornar valores?

R: Variáveis alocadas no heap permanecem válidas mesmo após o término da função da thread, permitindo que a main acesse o valor retornado. Variáveis locais seriam destruídas ao final da função, resultando em acesso inválido ou comportamento indefinido.


6. **Aplicabilidade**: Quando vale a pena usar threads em vez de processos?

R: Threads são indicadas quando:

Precisamos de execução paralela leve, com baixo overhead de criação e troca de contexto;

Threads podem compartilhar dados facilmente sem precisar de mecanismos complexos de comunicação entre processos (IPC);

O programa exige alta responsividade ou processamento paralelo de pequenas tarefas.
Já processos são mais seguros em termos de isolamento, mas mais custosos para comunicação e criação.


---

## Entrega

1. Complete todos os exercícios (1-6)
2. Preencha o relatório com suas observações e análises
3. Documente problemas encontrados e soluções