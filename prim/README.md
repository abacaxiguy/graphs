<div align="center">
<h1>☆ Algoritmo de Prim ☆</h1>
<img src="https://upload.wikimedia.org/wikipedia/commons/9/9b/PrimAlgDemo.gif" alt="Prim's algorithm">
</div>

---

## 📋 Sobre

O Algortimo de Prim é um algoritmo guloso que encontra uma <i>árvore geradora mínima</i> para um grafo conexo e não direcionado. O algoritmo foi desenvolvido por `Robert Prim` em 1957 e redescoberto por `Edsger Dijkstra` em 1959 e por `Vojtěch Jarník` em 1930.

## ⚙ Como compilar

Para compilar o programa, basta executar o comando:

```
$ make
```

no diretório raiz do projeto. Isso irá gerar um arquivo executável chamado `prim.bin`. Para saber mais detalhes do funcionamento do programa, execute:

```
$ ./prim.bin -h

    ☆ Algoritmo de Prim ☆ <https://pt.wikipedia.org/wiki/Algoritmo_de_Prim>

    -h           : mostra o help
    -o <arquivo> : redireciona a saida para o "arquivo"
    -f <arquivo> : indica o "arquivo" que contém o grafo de entrada
    -s           : mostra a solução (em ordem crescente)
    -i v0        : vértice inicial "v0" (se não for enviado, v0 será 1)

    Para calcular o custo da AGM, use:
    ./prim.bin -f <arquivo> -i v0

    Para imprimir a árvore geradora mínima, use:
    ./prim.bin -f <arquivo> -i v0 -s

    Para salvar o resultado em um arquivo, use:
    ./prim.bin -f <arquivo> -o <arquivo> -i v0
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
$ ./prim.bin -f entrada.mxt

37
```

O resultado impresso é o custo da árvore geradora mínima.
Você pode especificar o vértice inicial usando a opção `-i`:

```
$ ./prim.bin -f entrada.mxt -i 1

37
```

Se não for enviado, o vértice inicial será `1`.

Para imprimir a árvore geradora mínima, use:

```
$ ./prim.bin -f entrada.mtx -i 1 -s

(1, 4) (1, 5) (2, 3) (2, 4) (3, 6)
```

O resultado impresso é a árvore geradora mínima.

Para salvar o resultado em um arquivo, use:

```
$ ./prim.bin -f entrada.mtx -o saida.txt -i 1
$ cat saida.txt

37
```

A saída do programa foi salva no arquivo `saida.txt`.
