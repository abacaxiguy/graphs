#include <iostream>
#include <string.h>
using namespace std;

void help()
{
    cout << "☆ Algoritmo de ? ☆ <https://pt.wikipedia.org/wiki/?>\n\n"
            "-h           : mostra o help\n"
            "-o <arquivo> : redireciona a saida para o \"arquivo\"\n"
            "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada\n"
            "-i v0        : vértice inicial \"v0\" \n\n"
            "Para saber a distância mínima do vértice v0 para todos os demais, use: \n./? -f <arquivo> -i v0\n"
            "Para salvar a distância mínima em um arquivo, use: \n./? -f <arquivo> -o <arquivo> -i v0\n";
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc - 1 == 0)
            throw "Nenhum argumento foi mandado!";

        for (int i = 1; i < argc; i++)
        {
            if (!strcmp(argv[i], "-h"))
                help();
            else if ((!strcmp(argv[i], "-o") || !strcmp(argv[i], "-f") || !strcmp(argv[i], "-i")) && argv[i + 1] == NULL)
            {
                throw "Especifique o caminho do arquivo como mostrado no help (./prim -h)";
                break;
            }
            else if (!strcmp(argv[i], "-o"))
            {
                printf("OUTPUT, SEU ARQUIVO É: %s\n", argv[i + 1]);
                i++;
            }
            else if (!strcmp(argv[i], "-f"))
            {
                printf("FILE, SEU ARQUIVO É: %s\n", argv[i + 1]);
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
    }
    catch (const char *msg)
    {
        cerr << "Erro: " << msg << endl;
    }
}