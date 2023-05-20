#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include <list>
#include <queue>
#include <algorithm> // sort
#include <string.h>  // memset

using namespace std;

struct Aresta
{
    int v1, v2, peso;
};

class Grafo
{
private:   // os membro de uma classe são privados
    int v; // numero de vertices

    // ponteiro para um array contendo as listas de adjacencias
    list<pair<int, int>> *adj; // pair para indicar qual vertice liga a qual vertice com custo x

public:
    // construtor
    Grafo(int v)
    {
        this->v = v; // atribuindo o numero de vertices
        adj = new list<pair<int, int>>[v];
    }

    // adiciona uma aresta ao grafo de v1 a v2
    void adicionar(int v1, int v2, int custo)
    {
        adj[v1].push_back(make_pair(v2, custo)); // tem um vertice saindo de v1 ate v2 com um custo x
    }
    // compara o peso da aresta para ordenar depois
    static bool comparacaoAresta(const Aresta &v1, const Aresta &v2)
    {
        return v1.peso < v2.peso;
    }

    int Find(vector<int> pai, int i)
    {
        if (pai[i] != i)
        {
            return Find(pai, pai[i]);
        }
        else
        {
            return pai[i];
        }
    }

    void Union(vector<int> &pai, vector<int> &rank, int v1, int v2)
    {
        if (rank[v1] >= rank[v2])
        {
            pai[v2] = v1;
            if (rank[v1] == rank[v2])
            {
                rank[v1]++;
            }
            return;
        }
        pai[v1] = v2;
    }

    vector<Aresta> kruskal()
    {
        vector<Aresta> agm;     // para guarda todos os vetores que fazem parte da arvore geradora minima
        vector<int> pai(v);     // Vetor para armazenar os pais dos subconjuntos
        vector<int> rank(v, 0); // inicializando rank com v pos e 0 em todas

        // Criando array com arestas ordenadas
        vector<Aresta> arestas_ord;
        for (int i = 0; i < v; i++)
        {
            for (auto it = adj[i].begin(); it != adj[i].end(); it++)
            {
                int dest = it->first;
                int peso = it->second;
                if (i < dest)
                { // Adicionar apenas uma cópia da aresta para evitar duplicações
                    Aresta arestas;
                    arestas.v1 = i;
                    arestas.v2 = dest;
                    arestas.peso = peso;
                    arestas_ord.push_back(arestas);
                }
            }
        }
        // ordenar as arestas pelo menor peso
        sort(arestas_ord.begin(), arestas_ord.end(), comparacaoAresta);

        // make set so para o pai pois ja to fazendo na declarção o do rank
        for (int i = 0; i < v; i++)
        {
            pai[i] = i;
        }

        // Iterar por todas as arestas
        for (int i = 0; i < arestas_ord.size(); i++)
        {
            int inicio = arestas_ord[i].v1;
            int destino = arestas_ord[i].v2;
            int inicio_pai = Find(pai, inicio);
            int destino_pai = Find(pai, destino);

            if (inicio_pai != destino_pai)
            {
                agm.push_back(arestas_ord[i]);
                Union(pai, rank, inicio_pai, destino_pai);
            }
        }

        return agm;
    }
};

void help()
{
    cout << "☆ Algoritmo de Kruskal ☆ <https://pt.wikipedia.org/wiki/Algoritmo_de_Kruskal>\n\n"
            "-h           : mostra o help\n"
            "-o <arquivo> : redireciona a saida para o \"arquivo\"\n"
            "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada\n"
            "-s           : mostra a solução (em ordem crescente)\n\n"
            "Para calcular o custo da AGM, use:\n./kruskal.bin -f <arquivo>\n\n"
            "Para imprimir a árvore geradora mínima, use: \n./kruskal.bin -f <arquivo> -s\n\n"
            "Para salvar o resultado em um arquivo, use: \n./kruskal.bin -f <arquivo> -o <arquivo>\n\n";
}

int read(string fileName, string outputFileName, bool agm)
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

    vector<Aresta> resultado = g.kruskal();
    int custo = 0;

    if (outputFileName != "")
    {
        ofstream outFile;
        outFile.open(outputFileName);

        if (agm)
        {
            sort(resultado.begin(), resultado.end(), [](Aresta a, Aresta b)
                 { return a.v1 < b.v1 || (a.v1 == b.v1 && a.v2 < b.v2); });

            for (int i = 0; i < resultado.size(); i++)
            {
                if (resultado[i].v1 < resultado[i].v2)
                    outFile << "(" << resultado[i].v1 << "," << resultado[i].v2 << ") ";
                else
                    outFile << "(" << resultado[i].v2 << "," << resultado[i].v1 << ") ";
            }
        }
        else
        {
            for (int i = 0; i < resultado.size(); i++)
                custo += resultado[i].peso;

            outFile << custo;
        }

        outFile.close();
    }
    else
    {
        if (agm)
        {
            sort(resultado.begin(), resultado.end(), [](Aresta a, Aresta b)
                 { return a.v1 < b.v1 || (a.v1 == b.v1 && a.v2 < b.v2); });

            for (int i = 0; i < resultado.size(); i++)
            {
                if (resultado[i].v1 < resultado[i].v2)
                    cout << "(" << resultado[i].v1 << "," << resultado[i].v2 << ") ";
                else
                    cout << "(" << resultado[i].v2 << "," << resultado[i].v1 << ") ";
            }
        }
        else
        {
            for (int i = 0; i < resultado.size(); i++)
                custo += resultado[i].peso;

            cout << custo;
        }

        cout << endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    try
    {
        bool fFlag = false, hFlag = false, ordemCrescente = false;
        string outputFileName = "", inputFileName = "";

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
            else if ((!strcmp(argv[i], "-o") || !strcmp(argv[i], "-f")) && argv[i + 1] == NULL)
            {
                throw "Especifique o caminho do arquivo! (Veja o help: ./kruskal.bin -h)";
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
            else
            {
                throw "Argumento inválido!";
                break;
            }
        }
        if (fFlag)
            read(inputFileName, outputFileName, ordemCrescente);
        else if (!hFlag)
            throw "Nenhum arquivo de entrada foi especificado! (Veja o help: ./kruskal.bin -h)";
    }
    catch (const char *msg)
    {
        cerr << "\e[31mErro: " << msg << "\e[0m" << endl;
    }
}