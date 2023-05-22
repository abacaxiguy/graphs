#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm> // sort

#define inf 9999999

using namespace std;

struct Arco
{
    int v, fluxo, capacidade;

    Arco(int _v, int _capacidade) : v(_v), capacidade(_capacidade), fluxo(0) {}
};

class Grafo
{
private:   // os menbro de uma classe são privados
    int v; // numero de vertices

    unordered_map<int, vector<Arco>> adj; // lista de adjacencia

public:
    // construtor
    Grafo(int v)
    {
        this->v = v; // atribuindo o numero de vertices
    }

    // adiciona uma aresta ao grafo de v1 a v2
    void adicionar(int v1, int v2, int capacidade)
    {
        Arco arco(v2, capacidade);
        adj[v1].push_back(arco);
    }

    bool bfs(int source, int sink, vector<int> &parent, vector<vector<int>> &residuo)
    {
        vector<bool> visited(v, false);
        queue<int> q;

        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (const auto &arco : adj[u])
            {
                int v = arco.v;

                if (visited[v] == false && residuo[u][v] > 0)
                {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        return visited[sink];
    }

    void edmonds_karp(int source, int sink, string outputFileName, bool path, bool totalPath)
    {
        if (sink == 0)
            sink = v - 1;

        vector<vector<int>> residuo(v, vector<int>(v, 0));

        for (int u = 0; u < v; u++)
        {
            for (const auto &arco : adj[u])
            {
                residuo[u][arco.v] = arco.capacidade;
            }
        }

        unordered_map<int, vector<Arco>> fluxoMaximoGrafo(adj);

        int fluxoMaximo = 0;
        vector<int> parent(v);

        while (bfs(source, sink, parent, residuo))
        {
            int fluxoCaminho = inf;

            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                fluxoCaminho = min(fluxoCaminho, residuo[u][v]);
            }

            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                residuo[u][v] -= fluxoCaminho;
                residuo[v][u] += fluxoCaminho;

                for (auto &arco : fluxoMaximoGrafo[u])
                {
                    if (arco.v == v)
                    {
                        arco.fluxo += fluxoCaminho;
                        break;
                    }
                }
            }
            fluxoMaximo += fluxoCaminho;
        }

        if (path)
        {
            // print first the path from source to sink, then print the rest of the edges
            vector<pair<int, Arco>> caminho;
            if (outputFileName != "")
            {
                ofstream outputFile;
                outputFile.open(outputFileName);

                outputFile << source << " -> " << sink << endl;

                for (int u = 1; u < v; u++)
                {
                    for (const auto &arco : fluxoMaximoGrafo[u])
                    {
                        if (arco.fluxo > 0)
                        {
                            outputFile << "(" << u << "," << arco.v << ") - " << arco.fluxo << "/" << arco.capacidade << endl;
                        }
                    }
                }

                if (totalPath)
                {
                    for (int u = 1; u < v; u++)
                    {
                        for (const auto &arco : fluxoMaximoGrafo[u])
                        {
                            if (arco.fluxo == 0)
                            {
                                outputFile << "(" << u << "," << arco.v << ") - " << arco.fluxo << "/" << arco.capacidade << endl;
                            }
                        }
                    }
                }

                outputFile.close();
            }
            else
            {

                cout << source << " -> " << sink << endl;

                for (int u = 1; u < v; u++)
                {
                    for (const auto &arco : fluxoMaximoGrafo[u])
                    {
                        if (arco.fluxo > 0)
                        {
                            cout << "(" << u << "," << arco.v << ") - " << arco.fluxo << "/" << arco.capacidade << endl;
                        }
                    }
                }
                if (totalPath)
                {
                    for (int u = 1; u < v; u++)
                    {
                        for (const auto &arco : fluxoMaximoGrafo[u])
                        {
                            if (arco.fluxo == 0)
                            {
                                cout << "(" << u << "," << arco.v << ") - " << arco.fluxo << "/" << arco.capacidade << endl;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (outputFileName != "")
            {
                ofstream outputFile;
                outputFile.open(outputFileName);

                outputFile << fluxoMaximo << endl;

                outputFile.close();
            }
            else
                cout << fluxoMaximo << endl;
        }
    }
};

void read(string fileName, string outputFileName, int v0, int vi, bool path, bool totalPath)
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
        return;
    }

    string linha;
    getline(file, linha);

    if (linha == "")
    {
        cout << "\e[31mErro: Arquivo vazio!\e[0m" << endl;
        return;
    }

    int vertices, arestas;

    istringstream iss(linha);

    iss >> vertices >> arestas;

    Grafo g(vertices + 1); // +1 pois o grafo começa do vertice 1

    for (int i = 0; i < arestas; i++)
    {
        getline(file, linha);
        istringstream iss(linha);

        int v1, v2, capacidade;

        iss >> v1 >> v2 >> capacidade;

        g.adicionar(v1, v2, capacidade); // grafo direcionado
    }

    file.close();

    g.edmonds_karp(v0, vi, outputFileName, path, totalPath);

    return;
}

void help()
{
    cout << "☆ Algoritmo de Edmonds-Karp ☆ <https://pt.wikipedia.org/wiki/Algoritmo_de_Edmonds-Karp>\n\n"
            "-h           : mostra o help\n"
            "-o <arquivo> : redireciona a saida para o \"arquivo\"\n"
            "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada\n"
            "-i v0        : vértice inicial/source \"v0\" (se não for enviado, v0 será 1) \n"
            "-d vi        : vértice final/sink \"vi\" (se não for enviado, vi será o último vértice) \n"
            "-c           : mostra o fluxo máximo/corte mínimo de arestas com fluxo maior que 0\n"
            "-ct          : mostra o fluxo máximo/corte mínimo de todas as arestas (recomendado para grafos com poucas arestas)\n\n"
            "Para saber o fluxo máximo do vértice v0 para vi, use: \n./edmonds-karp.bin -f <arquivo> -i v0 -d vi\n\n"
            "Para saber o caminho percorrido, use: \n./edmonds-karp.bin -f <arquivo> -i v0 -d vi -c\n\n"
            "Para salvar o resultado em um arquivo, use: \n./edmonds-karp.bin -f <arquivo> -o <arquivo> -i v0 -d vi\n\n";
}

int main(int argc, char *argv[])
{
    try
    {
        bool fFlag = false, hFlag = false, path = false, totalPath = false;
        string outputFileName = "", inputFileName = "";
        int v0 = 1, vi = 0;

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
            else if ((!strcmp(argv[i], "-o") || !strcmp(argv[i], "-f") || !strcmp(argv[i], "-i") || !strcmp(argv[i], "-d")) && argv[i + 1] == NULL)
            {
                throw "Especifique o caminho do arquivo (ou o vértice inicial/final)! (Veja o help: ./edmonds-karp.bin -h)";
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
            else if (!strcmp(argv[i], "-d"))
            {
                vi = stoi(argv[i + 1]);
                i++;
            }
            else if (!strcmp(argv[i], "-c"))
            {
                path = true;
            }
            else if (!strcmp(argv[i], "-ct"))
            {
                path = true;
                totalPath = true;
            }
            else
            {
                throw "Argumento inválido!";
                break;
            }
        }
        if (fFlag)
            read(inputFileName, outputFileName, v0, vi, path, totalPath);
        else if (!hFlag)
            throw "Nenhum arquivo de entrada foi especificado! (Veja o help: ./edmonds-karp.bin -h)";
    }
    catch (const char *msg)
    {
        cerr << "\e[31mErro: " << msg << "\e[0m" << endl;
    }
}