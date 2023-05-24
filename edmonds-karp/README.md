<div align="center">
<h1>☆ Algoritmo de Edmonds-Karp ☆</h1>
<img src="https://upload.wikimedia.org/wikipedia/commons/9/97/Fluxo_max_ford_fulkerson.gif" alt="Edmonds-Karp algorithm">
</div>

---

## 📋 Sobre

O Algoritmo de Edmonds-Karp é uma implementação do algoritmo de `Ford-Fulkerson` que utiliza a busca em largura para encontrar o caminho aumentante. O algoritmo de Ford-Fulkerson é um algoritmo que resolve o problema do fluxo máximo em uma rede. O algoritmo de Edmonds-Karp foi publicado em 1972 por `Jack Edmonds` e `Richard Karp`.

## 🧪 Testes

Para executar os testes, basta ir ao diretório [`test`](test) e seguir as instruções do [`README.md`](test/README.md).

## ⚙ Como compilar

Para compilar o programa, basta executar o comando:

```
$ make
```

no diretório raiz do projeto. Isso irá gerar um arquivo executável chamado `edmonds-karp.bin`. Para saber mais detalhes do funcionamento do programa, execute:

```
$ ./edmonds-karp.bin -h

    ☆ Algoritmo de Edmonds-Karp ☆ <https://pt.wikipedia.org/wiki/Algoritmo_de_Edmonds-Karp>
    -h           : mostra o help
    -o <arquivo> : redireciona a saida para o "arquivo"
    -f <arquivo> : indica o "arquivo" que contém o grafo de entrada
    -i v0        : vértice inicial/source "v0" (se não for enviado, v0 será 1)
    -d vi        : vértice final/sink "vi" (se não for enviado, vi será o último vértice)
    -c           : mostra a rede resultante com as arestas que possuem fluxo > 0
    -ct          : mostra a rede resultante com todas as arestas (recomendado para grafos com poucas arestas)
    -a           : (EXPERIMENTAL) calcula o fluxo máximo de todos os vértices possíveis, "v0" e "vi" serão ignorados (AVISO: pode demorar para grafos grandes)

    Para saber o fluxo máximo do vértice v0 para vi, use:
    ./edmonds-karp.bin -f <arquivo> -i v0 -d vi

    Para saber a rede resultante do vértice v0 para vi, use:
    ./edmonds-karp.bin -f <arquivo> -i v0 -d vi -c

    Para salvar o resultado em um arquivo, use:
    ./edmonds-karp.bin -f <arquivo> -o <arquivo> -i v0 -d vi
```

## 🛠 Como usar

Para usar o programa, basta executar o comando que está no help, de acordo com a sua necessidade.

O arquivo de entrada deve seguir o seguinte formato:

```
n m
v1 v2 c12
...
...       // m linhas com as arestas
...
vi vj cij
```

Onde `n` é o número de vértices, `m` é o número de arestas, `vi` e `vj` são os vértices que estão ligados por uma aresta e `cij` é o custo da aresta. `i` e `j` são números inteiros que variam de 1 até `n`.

## 📝 Exemplo de uso

Para calcular o fluxo máximo do vértice 1 para o vértice 6, basta executar o comando:

```
$ ./edmonds-karp.bin -f entrada.mtx -i 1 -d 6

1 -> 6: 23
```

O resultado impresso está no formato: `v0 -> vi: f`. Onde `v0` é o vértice inicial, `vi` é o vértice final e `f` é o fluxo máximo.
Os vértices `v0` e `vi` são opcionais, se não forem enviados, o vértice inicial será o 1 e o vértice final será o último vértice.

Para saber a rede resultante do vértice 1 para o vértice 6, basta executar o comando:

```
$ ./edmonds-karp.bin -f entrada.mtx -i 1 -d 6 -c

1 -> 6:
(1, 2) 10/10
(1, 3) 10/10
(2, 4) 10/10
(2, 5) 10/10
(3, 4) 10/10
(3, 5) 10/10
(4, 6) 10/10
(5, 6) 3/10
```

O resultado impresso está no formato: `(vi, vj) f/c`. Onde `vi` é o vértice inicial, `vj` é o vértice final, `f` é o fluxo e `c` é a capacidade da aresta.

Para saber a rede resultante total, mostrando até as arestas que não possuem fluxo, basta executar o comando:

```
$ ./edmonds-karp.bin -f entrada.mtx -i 1 -d 6 -ct

1 -> 2:
(1, 2) 10/10
(1, 3) 10/10
(2, 4) 10/10
(2, 5) 10/10
(3, 4) 10/10
(3, 5) 10/10
(4, 6) 10/10
(5, 6) 3/10
(2, 3) 0/10
(4, 5) 0/10
```

Para fins experimentais, é possível calcular o fluxo máximo de todos os vértices possíveis, basta executar o comando:

```
$ ./edmonds-karp.bin -f entrada.mtx -a

1 -> 2: 10
1 -> 3: 10
1 -> 4: 10
1 -> 5: 10
1 -> 6: 23
2 -> 3: 0
2 -> 4: 10
2 -> 5: 10
2 -> 6: 10
3 -> 4: 0
3 -> 5: 10
3 -> 6: 10
4 -> 5: 0
4 -> 6: 10
5 -> 6: 3
```

Como foi avisado no help, esse comando pode demorar para grafos grandes. As flags `-i` e `-d` serão ignoradas.

Para salvar o resultado em um arquivo, basta executar o comando:

```
$ ./edmonds-karp.bin -f entrada.mtx -o saida.txt -i 1 -d 6
$ cat saida.txt

1 -> 6: 23
```
