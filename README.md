# Reserva de Assentos de uma Sessão

**Aluno:** João Paulo de Medeiros Neto  
**Disciplina:** Introdução às Técnicas de Programação (ITP)  
**Projeto:** Opção 3 — Reserva de assentos de uma sessão  
**Linguagem:** C  
**Repositório:** [itp_avaliacao2](https://github.com/joaopaul0dev/itp_avaliacao2)

## Sobre o projeto

Este projeto consiste no desenvolvimento de um programa em C para gerenciar a reserva de assentos de uma sessão de cinema. O sistema permitirá visualizar a disponibilidade dos assentos, realizar reservas, cancelar reservas existentes e consultar um resumo da ocupação da sala.

A aplicação será executada no terminal e utilizará uma matriz para representar os assentos, permitindo identificar quais estão livres e quais estão reservados. O projeto faz parte da segunda avaliação da disciplina de Introdução às Técnicas de Programação (ITP) e tem como objetivo aplicar conceitos de programação estruturada, matrizes, strings, funções, ponteiros e alocação dinâmica de memória.


## Funcionalidades

- Cadastro do título da sessão.
- Definição da quantidade de filas, entre 1 e 6, com oito assentos por fila.
- Exibição do mapa de assentos e de seus respectivos estados.
- Reserva de um assento disponível.
- Cancelamento de uma reserva existente.
- Exibição do total de assentos livres e reservados, além da porcentagem de ocupação.

## Representação dos assentos

Os assentos serão representados por uma matriz de inteiros, com capacidade máxima de 6 filas e 8 assentos por fila.

| Valor | Significado |
|---|---|
| `0` | Assento livre |
| `1` | Assento reservado |

Na interação com o usuário, as filas e os assentos serão numerados a partir de 1. Antes de acessar a matriz, essas posições serão convertidas para índices iniciados em 0, conforme a convenção da linguagem C.

O sistema também utilizará um vetor alocado dinamicamente para armazenar a quantidade de assentos livres de cada fila, conforme a quantidade de filas escolhida.


## Compilação e execução

O projeto será compilado utilizando o GCC. Considerando que o arquivo principal se chame `main.c`, os comandos serão:

```bash
gcc -std=c11 -Wall -Wextra main.c -o reserva
./reserva
```

## Testes 

Em andamento.

## Vídeo de apresentação

O vídeo demonstrando o funcionamento do programa e explicando as decisões de implementação será disponibilizado no YouTube após a conclusão do projeto.

**Link:** A definir.

Projeto acadêmico desenvolvido individualmente para a segunda avaliação da disciplina de Introdução às Técnicas de Programação.
