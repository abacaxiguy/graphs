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
    // contrutor
    Grafo(int v)
    {
        this->v = v; // atribuindo o numero de vertices
        /* cria as lista on de cada lista é uma lista de pairs onde cada pair é formado pelo vertice de destino e o custo*/
        adj = new list<pair<int, int>>[v]; // eu tenho v listas de adjacencias
    }

    // adiciona uma aresta ao grafo de v1 a v2
    void adicionar(int v1, int v2, int custo)
    {
        adj[v1].push_back(make_pair(v2, custo)); // tem um vertice saindo de v1 ate v2 com um custo x
    }

    // algoritmo de Dijkstra
    int dijkstra(int orig, int dest)
    {
        // vetor de distancia
        int dist[v];

        // vetor de visistados para n repetir vertecie
        int visitados[v];

        // heap minima c++
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap_min; // aparti de vector é alteração que precisa ser feita para torna a heap minima

        // inicia o vetor de distancia e visitados
        for (int i = 0; i < v; i++)
        {
            dist[i] = inf;
            visitados[i] = false;
        }
        // distancia de origem para origem é 0
        dist[orig] = 0;

        // insere na heap
        heap_min.push(make_pair(dist[orig], orig));

        // loop do algoritmo
        while (!heap_min.empty())
        {
            pair<int, int> p = heap_min.top(); // extrair o pair do topo
            int u = p.second;                  // obtendo o vertice que é o secundo elemonto do pear o primeiro é a distancia
            heap_min.pop();                    // removendo da fila

            // verifica se o vertice foi visitado
            if (visitados[u] == false)
            {
                // marca como visitado
                visitados[u] = true;

                list<pair<int, int>>::iterator it; // percorre a lista dos vizinhos atraves do iterator

                // percorre os vertices v vizinhos de u
                for (it = adj[u].begin(); it != adj[u].end(); it++)
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
        return dist[dest];
    }
};

void help()
{
    cout << "☆ Algoritmo de Dijkstra ☆ <https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra>\n\n"
            "-h           : mostra o help\n"
            "-o <arquivo> : redireciona a saida para o \"arquivo\"\n"
            "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada\n"
            "-i v0        : vértice inicial \"v0\" \n\n"
            "Para saber a distância mínima do vértice v0 para todos os demais, use: \n./dijkstra -f <arquivo> -i v0\n"
            "Para salvar a distância mínima em um arquivo, use: \n./dijkstra -f <arquivo> -o <arquivo> -i v0\n";
}

int read(string fileName, int modoDeOutput, string outputFileName)
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
        cerr << "Erro: " << msg << endl;
        return -1;
    }

    int vertices, arestas;
    string linha;
    getline(file, linha);

    istringstream iss(linha);

    iss >> vertices >> arestas;

    // cout << "Vértices: " << vertices << endl;
    // cout << "Arestas: " << arestas << endl;

    Grafo g(vertices);

    for (int i = 0; i < arestas; i++)
    {
        getline(file, linha);
        int v1, v2, peso;
        istringstream iss(linha);
        iss >> v1 >> v2 >> peso;
        // cout << v1 << " " << v2 << " " << peso << endl;
        g.adicionar(v1, v2, peso);
    }

    file.close();
    // cout << "Fechou o arquivo" << endl;
    if (modoDeOutput == 1)
    {
        ofstream outFile;
        outFile.open(outputFileName);

        for (int i = 1; i <= vertices; i++)
        {
            outFile << i << ":";
            outFile << g.dijkstra(1, i) << " ";
        }

        outFile.close();
    }
    else
    {
        for (int i = 1; i <= vertices; i++)
        {
            {
                cout << i << ":";
                cout << g.dijkstra(1, i);
            }
        }

        cout << endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    try
    {
        int modoDeOutput = 0; // 0: terminal, 1: arquivo
        int fRun = 0;
        string outputFileName = "", inputFileName = "";

        if (argc - 1 == 0)
            throw "Nenhum argumento foi mandado!";

        for (int i = 1; i < argc; i++)
        {
            if (!strcmp(argv[i], "-h"))
            {
                help();
                break;
            }
            else if ((!strcmp(argv[i], "-o") || !strcmp(argv[i], "-f") || !strcmp(argv[i], "-i")) && argv[i + 1] == NULL)
            {
                throw "Especifique o caminho do arquivo como mostrado no help (./dijkstra -h)";
                break;
            }
            else if (!strcmp(argv[i], "-o"))
            {
                modoDeOutput = 1;
                outputFileName = argv[i + 1];
                i++;
            }
            else if (!strcmp(argv[i], "-f"))
            {
                fRun = 1;
                inputFileName = argv[i + 1];
                i++;
            }
            else if (!strcmp(argv[i], "-i"))
            {
                printf("VERTICE INICIAL: %d\n", atoi(argv[i + 1]));
                i++;
            }
            else
            {
                throw "Argumento inválido!";
                break;
            }
        }
        if (fRun)
            read(inputFileName, modoDeOutput, outputFileName);
    }
    catch (const char *msg)
    {
        cerr << "Erro: " << msg << endl;
    }
}