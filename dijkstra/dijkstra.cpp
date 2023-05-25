#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include <list>
#include <queue>

#define inf 9999999

using namespace std;

class Grafo
{
private:   // os menbro de uma classe são privados
    int v; // numero de vertices

    // ponteiro para um array contendo as listas de adjacencias
    list<pair<int, int>> *adj; // pair para indicar qual vertice liga a qual vertice com custo x

public:
    // construtor
    Grafo(int v)
    {
        this->v = v; // atribuindo o numero de vertices
        /* cria as lista on de cada lista é uma lista de pairs onde cada pair é formado pelo vertice de destino e o custo*/
        adj = new list<pair<int, int>>[v];
    }

    ~Grafo()
    {
        delete[] adj;
    }

    // adiciona uma aresta ao grafo de v1 a v2
    void adicionar(int v1, int v2, int custo)
    {
        adj[v1].push_back(make_pair(v2, custo)); // tem um vertice saindo de v1 ate v2 com um custo x
    }

    // Dijkstra retornando as distancias minimas de um vertice origem a todos os outros
    vector<int> dijkstra(int orig)
    {
        vector<int> dist(v, inf);        // vetor de distancias iniciado com infinito
        vector<int> visitados(v, false); // vetor de visitados iniciado com false

        // heap minima c++
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap_min;

        // distancia de origem para origem é 0
        dist[orig] = 0;

        // insere na heap
        heap_min.push(make_pair(dist[orig], orig));

        while (!heap_min.empty())
        {
            pair<int, int> p = heap_min.top(); // extrair o pair do topo
            int u = p.second;                  // obtendo o vertice que é o segundo elemento do pair
            heap_min.pop();                    // removendo da fila

            // verifica se o vertice foi visitado
            if (visitados[u] == false)
            {
                // marca como visitado
                visitados[u] = true;

                // percorre os vertices v vizinhos de u
                for (auto it = adj[u].begin(); it != adj[u].end(); it++)
                {
                    // obtem o vertice visinho e o custo da aresta
                    int v = it->first;
                    int custo_aresta = it->second;

                    // relaxamento (u, v)
                    if (dist[v] > (dist[u] + custo_aresta))
                    {
                        // atualiza a distacia de v e insere na fila
                        dist[v] = dist[u] + custo_aresta;
                        heap_min.push(make_pair(dist[v], v));
                    }
                }
            }
        }
        // retorna a distancia minima ao destino
        return dist;
    }
};

void help()
{
    cout << "☆ Algoritmo de Dijkstra ☆ <https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra>\n\n"
            "-h           : mostra o help\n"
            "-o <arquivo> : redireciona a saida para o \"arquivo\"\n"
            "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada\n"
            "-i v0        : vértice inicial \"v0\" (se não for enviado, v0 será 1)\n\n"
            "Para saber a distância mínima do vértice v0 para todos os demais, use: \n./dijkstra.bin -f <arquivo> -i v0\n\n"
            "Para salvar a distância mínima em um arquivo, use: \n./dijkstra.bin -f <arquivo> -o <arquivo> -i v0\n\n";
}

int read(string fileName, string outputFileName, int v0)
{
    ifstream file;
    try
    {
        file.open(fileName);
        if (!file.good())
            throw "Arquivo não encontrado!";
    }
    catch (const char *msg)
    {
        cerr << "\e[31mErro: " << msg << "\e[0m" << endl;
        return -1;
    }

    string linha;
    getline(file, linha);

    if (linha == "")
    {
        cout << "\e[31mErro: Arquivo vazio!\e[0m" << endl;
        return -1;
    }

    int vertices, arestas;

    istringstream iss(linha);

    iss >> vertices >> arestas;

    if (v0 < 1 || v0 > vertices)
    {
        cout << "\e[31mErro: Vértice inicial inválido!\e[0m" << endl;
        return -1;
    }

    Grafo g(vertices + 1); // +1 pois o grafo começa do vertice 1

    for (int i = 0; i < arestas; i++)
    {
        getline(file, linha);
        int v1, v2, peso;
        istringstream iss(linha);
        iss >> v1 >> v2 >> peso;
        g.adicionar(v1, v2, peso);
        g.adicionar(v2, v1, peso); // para grafos não direcionados
    }

    file.close();

    if (outputFileName != "")
    {
        ofstream outFile;
        outFile.open(outputFileName);

        vector<int> resultado = g.dijkstra(v0);

        for (int i = 1; i < resultado.size(); i++)
        {
            if (resultado[i] == inf)
                resultado[i] = -1;
            outFile << i << ":" << resultado[i] << " ";
        }

        outFile.close();
    }
    else
    {
        vector<int> resultado = g.dijkstra(v0);

        for (int i = 1; i < resultado.size(); i++)
        {
            if (resultado[i] == inf)
                resultado[i] = -1;
            cout << i << ":" << resultado[i] << " ";
        }

        cout << endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    try
    {
        bool fFlag = false, hFlag = false;
        string outputFileName = "", inputFileName = "";
        int v0 = 1;

        if (argc - 1 == 0)
            throw "Nenhum argumento foi mandado!";

        for (int i = 1; i < argc; i++)
        {
            if (!strcmp(argv[i], "-h"))
            {
                help();
                hFlag = true;
                break;
            }
            else if ((!strcmp(argv[i], "-o") || !strcmp(argv[i], "-f") || !strcmp(argv[i], "-i")) && argv[i + 1] == NULL)
            {
                throw "Especifique o caminho do arquivo (ou o vértice inicial)! (Veja o help: ./dijkstra.bin -h)";
                break;
            }
            else if (!strcmp(argv[i], "-o"))
            {
                outputFileName = argv[i + 1];
                i++;
            }
            else if (!strcmp(argv[i], "-f"))
            {
                fFlag = true;
                inputFileName = argv[i + 1];
                i++;
            }
            else if (!strcmp(argv[i], "-i"))
            {
                v0 = stoi(argv[i + 1]);
                i++;
            }
            else
            {
                throw "Argumento inválido!";
                break;
            }
        }
        if (fFlag)
            read(inputFileName, outputFileName, v0);
        else if (!hFlag)
            throw "Nenhum arquivo de entrada foi especificado! (Veja o help: ./dijkstra.bin -h)";
    }
    catch (const char *msg)
    {
        cerr << "\e[31mErro: " << msg << "\e[0m" << endl;
    }
}