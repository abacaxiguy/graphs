<div align="center">
<h1>☆ Algoritmo de Dijkstra ☆</h1>
<img src="https://upload.wikimedia.org/wikipedia/commons/5/57/Dijkstra_Animation.gif" alt="Dijkstra's algorithm">
</div>

---

## 📋 Sobre

O Algortimo de Dijkstra é um algoritmo guloso que encontra o caminho mais curto entre dois vértices em um grafo direcionado ou não direcionado com arestas de peso não negativo. O algoritmo foi desenvolvido por `Edsger Dijkstra` em 1956.

## ⚙ Como compilar

Para compilar o programa, basta executar o comando:

```
$ make
```

no diretório raiz do projeto. Isso irá gerar um arquivo executável chamado `dijkstra.bin`. Para saber mais detalhes do funcionamento do programa, execute:

```
$ ./dijkstra.bin -h

    ☆ Algoritmo de Dijkstra ☆ <https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra>

    -h           : mostra o help
    -o <arquivo> : redireciona a saida para o "arquivo"
    -f <arquivo> : indica o "arquivo" que contém o grafo de entrada
    -i v0        : vértice inicial "v0" (se não for enviado, v0 será 1)

    Para saber a distância mínima do vértice v0 para todos os demais, use:
    ./dijkstra.bin -f <arquivo> -i v0

    Para salvar a distância mínima em um arquivo, use:
    ./dijkstra.bin -f <arquivo> -o <arquivo> -i v0;
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

Para saber a distância mínima do vértice `3` para todos os demais, use:

```
$ ./dijkstra.bin -f entrada.txt -i 3

1:3 2:7 3:0 4:1 5:4 6:3 7:5 8:6 9:8 10:9
```

O resultado impresso é uma lista de vértices e suas respectivas distâncias mínimas do vértice `3`.
Se não for passado o vértice inicial, o programa assume que o vértice inicial é o vértice `1`.

Se não houver um caminho entre o vértice inicial e o vértice destino, o programa imprime `v:-1` para o vértice `v`.

Para salvar a distância mínima em um arquivo, use:

```
$ ./dijkstra.bin -f entrada.txt -o saida.txt -i 3
$ cat saida.txt

1:3 2:7 3:0 4:1 5:4 6:3 7:5 8:6 9:8 10:9
```
