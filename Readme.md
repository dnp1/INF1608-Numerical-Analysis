### Informações gerais



## Objetivo
O objetivo deste trabalho é gerar a imagem resultante de uma visualização volumétrica por
traçado de raio do dado de CT scan disponibilizado.
Os dados do CT scan estão num arquivo binário com 256 × 256 × 99 valores do tipo
unsigned char , que devem ser carregados e armazenados num vetor em memória. Neste ve-
tor, o acesso ao valor de ı́ndice (i, j, k) é dado pelo ı́ndice (kn y n x + jn x + i).
A imagem resultante deve ter resolução n x = 128 × n z = 99 com os raios sendo traçados
na direção y. Assim, o valor de cada pixel (i, k) da imagem, para i ∈ [0, 127] e k ∈ [0, 98], é
obtido pelo valor médio da integral de dois raios traçados no volume: os raios com origem em
(2i, 0, k) e (2i + 1, 0, k), com direção de traçado igual a (0, 1, 0), até que se alcance o final dos
raios (2i, n y − 1, k) e (2i + 1, n y − 1, k). Note então que o comprimento total do raio será de
n y −1 = 255 unidades; no entanto, o intervalo de integração pode ser dado por um número ponto
flutuante h. Isso significa que é necessário acessar o valor de densidade d(·) de ı́ndice (i, j f , k),
onde j f é um “ı́ndice’ ponto flutuante. O valor associado a este ı́ndice deve ser a interpolação
linear dos valores nos ı́ndices (i, j, k) e (i, j + 1, k), onde j = f loor(j f ). Para o cálculo das
integrais, considere o Método de Simpson com h = 4.5. Numa primeira etapa, no entanto, use
um valor de h inteiro, evitando assim a necessidade de interpolação.
Considere uma função de transferência que especifica:



