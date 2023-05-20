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

    // adiciona uma aresta ao grafo de v1 a v2
    void adicionar(int v1, int v2, int custo)
    {
        adj[v1].push_back(make_pair(v2, custo)); // tem um vertice saindo de v1 ate v2 com um custo x
    }

    void prim(int orig, string outputFileName, bool agm)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> h;
        vector<int> custo(v, inf);
        vector<int> prev(v, -1);
        vector<bool> visitado(v, false);

        custo[orig] = 0;
        h.push(make_pair(custo[orig], orig));

        while (!h.empty())
        {
            int u = h.top().second;
            h.pop();

            visitado[u] = true;

            for (auto it = adj[u].begin(); it != adj[u].end(); it++)
            {
                int v = it->first;
                int custo_aresta = it->second;

                if (visitado[v] == false && custo[v] > custo_aresta)
                {
                    custo[v] = custo_aresta;
                    prev[v] = u;
                    h.push(make_pair(custo[v], v));
                }
            }
        }

        if (outputFileName != "")
        {
            ofstream outFile;
            outFile.open(outputFileName);

            if (agm)
            {
                for (int i = 1; i < prev.size(); i++)
                {
                    if (prev[i] == -1)
                        continue;
                    outFile << "(" << prev[i] << "," << i << ") ";
                }
            }
            else
            {
                int total = 0;
                for (int i = 1; i < v; i++)
                    total += custo[i];
                outFile << total;
            }

            outFile.close();
        }
        else
        {
            if (agm)
            {
                for (int i = 1; i < prev.size(); i++)
                {
                    if (prev[i] == -1)
                        continue;
                    cout << "(" << prev[i] << "," << i << ") ";
                }
            }
            else
            {
                int total = 0;
                for (int i = 1; i < v; i++)
                    total += custo[i];
                cout << total;
            }

            cout << endl;
        }
    }
};

int read(string fileName, string outputFileName, int v0, bool agm)
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

    g.prim(v0, outputFileName, agm);

    return 0;
}

void help()
{
    cout << "☆ Algoritmo de Prim ☆ <https://pt.wikipedia.org/wiki/Algoritmo_de_Prim>\n\n"
            "-h           : mostra o help\n"
            "-o <arquivo> : redireciona a saida para o \"arquivo\"\n"
            "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada\n"
            "-s           : mostra a solução (em ordem crescente)\n"
            "-i v0        : vértice inicial \"v0\" (se não for enviado, v0 será 1)\n\n"
            "Para calcular o custo da AGM, use:\n./prim -f <arquivo> -i v0\n\n"
            "Para imprimir a árvore geradora mínima, use: \n./prim -f <arquivo> -i v0 -s\n\n"
            "Para salvar o resultado em um arquivo, use: \n./prim -f <arquivo> -o <arquivo> -i v0\n\n";
}

int main(int argc, char *argv[])
{
    try
    {
        bool fFlag = false, hFlag = false, ordemCrescente = false;
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
            else if (!strcmp(argv[i], "-s"))
                ordemCrescente = true;
            else if ((!strcmp(argv[i], "-o") || !strcmp(argv[i], "-f") || !strcmp(argv[i], "-i")) && argv[i + 1] == NULL)
            {
                throw "Especifique o caminho do arquivo (ou o vértice inicial)! (Veja o help: ./prim -h)";
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
                v0 = atoi(argv[i + 1]);
                i++;
            }
            else
            {
                throw "Argumento inválido!";
                break;
            }
        }
        if (fFlag)
            read(inputFileName, outputFileName, v0, ordemCrescente);
        else if (!hFlag)
            throw "Nenhum arquivo de entrada foi especificado! (Veja o help: ./prim -h)";
    }
    catch (const char *msg)
    {
        cerr << "\e[31mErro: " << msg << "\e[0m" << endl;
    }
}