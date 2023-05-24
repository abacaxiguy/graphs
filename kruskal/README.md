<div align="center">
<h1>☆ Algoritmo de Kruskal ☆</h1>
<img src="https://upload.wikimedia.org/wikipedia/commons/b/bb/KruskalDemo.gif" alt="Kruskal's algorithm">
</div>

---

## 📋 Sobre

O Algortimo de Kruskal é um algoritmo guloso que encontra uma <i>árvore geradora mínima</i> para um grafo conexo e não direcionado. O algoritmo foi desenvolvido por `Joseph Kruskal` em 1956.

## ⚙ Como compilar

Para compilar o programa, basta executar o comando:

```
$ make
```

no diretório raiz do projeto. Isso irá gerar um arquivo executável chamado `kruskal.bin`. Para saber mais detalhes do funcionamento do programa, execute:

```
$ ./kruskal.bin -h

    ☆ Algoritmo de Kruskal ☆ <https://pt.wikipedia.org/wiki/Algoritmo_de_Kruskal>

    -h           : mostra o help
    -o <arquivo> : redireciona a saida para o "arquivo"
    -f <arquivo> : indica o "arquivo" que contém o grafo de entrada
    -s           : mostra a solução (em ordem crescente)

    Para calcular o custo da AGM, use:./kruskal.bin -f <arquivo>

    Para imprimir a árvore geradora mínima, use: ./kruskal.bin -f <arquivo> -s

    Para salvar o resultado em um arquivo, use: ./kruskal.bin -f <arquivo> -o <arquivo>
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

Para calcular o custo da AGM, use:

```
$ ./kruskal.bin -f entrada.mxt

37
```

O resultado impresso é o custo da árvore geradora mínima.

Para imprimir a árvore geradora mínima, use:

```
$ ./kruskal.bin -f entrada.mtx -s

(1, 4) (1, 5) (2, 3) (2, 4) (3, 6)
```

O resultado impresso é a árvore geradora mínima.

Para salvar o resultado em um arquivo, use:

```
$ ./kruskal.bin -f entrada.mtx -o saida.txt
$ cat saida.txt

37
```

A saída do programa foi salva no arquivo `saida.txt`.
