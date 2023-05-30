/**
 * @file Trabalho2Bim.cpp
 * @date 2023-05-25
 * @brief Organizar dados do arquivo iris_petalas.csv, onde flores similares serão agrupadas
 *      em k grupos definidos pelo usuario.
 * @author Carlos Sérgio Fernandes Júnior - 2157633 <carlos_fernandes.1@hotmail.com>
 * @author Matheus Paulino Ribeiro - 2143432 <mathpaulinor@gmail.com>
 * @author Nicolas Fagundes Scarpa - 2093087 <bkscarpa@gmail.com>
 * @copyright Copyright (c) 2023
 */

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

typedef struct {
    long double comprimento;
    long double largura;
    std::string variedade;
} Flor;

typedef struct {
    std::string numero;
    long double comprimento;
    long double largura;
    Flor *flores;
    int tamanhoVetor;
} Grupo;

int calculaTamanhoArquivo(const std::string nomeArquivo); /// Calcula a quantidade de linhas do arquivo de texto.
void imprimeCabecalho(); /// Imprime o cabecalho do programa na saida padrao.
int leNaturalNaoNulo(std::string mensagem); /// Realiza a leitura de um numero natural diferente de zero.
int leNumeroDeGrupos(std::string mensagem, const int tamanhoArquivo); /// Realiza a leitura de um numero natural menor que a quantidade de registros no arquivo.
Grupo* inicializaGruposComRepresentantes(const int numeroDeGrupos, const std::string nomeArquivo, const int tamanhoArquivo); /// Aloca o vetor dos grupos e o inicializa com as informacoes das flores escolhidas como representantes.
Flor* buscaRepresentantes(const int numeroRepresentantes, const std::string nomeArquivo, const int tamanhoArquivo); /// Encontra dentro do arquivo os representantes sorteados.
int* sorteiaIndicesRepresentantes(const int numeroRepresentantes, const int tamanhoArquivo); /// Sorteia as flores que servirao como representantes iniciais para os grupos.
bool elementoEstaEmLista(int elemento, int* lista, const int tamanho); /// Verifica se um dado elemento esta no vetor.
void classificaFlores(Grupo* grupos, const int numeroDeGrupos, const std::string nomeArquivo, const int numeroDeExecucoes); /// Classifica as flores em quantos grupos o usuario desejar. A operacao e repetida quantas vezes o usuario desejar tambem para maior refinamento.
int encontraGrupoIdeal(Grupo* grupos, const int numeroDeGrupos, const long double comprimentoFlor, const long double larguraFlor); /// Encontra o grupo ideal para alocar a flor.
long double calculaDistanciaEuclidiana(long double comprimentoRepresentante, long double comprimentoFlor, long double larguraRepresentante, long double larguraFlor); /// Calcula a distancia euclidiana entre os representantes dos grupos e as flores do arquivo.
int encontraIndiceComMenorValor(long double* vetor, const int tamanho); /// Encontra o menor valor em um vetor.
void alocaFlorNoGrupoIdeal(Flor flor, Grupo* grupos, const int indiceIdeal); /// Aloca uma flor no grupo que possui o indice ideal.
Flor* realocaVetor(Flor* vet, int* t); /// Redimensiona o vetor, incrementando o tamanho de um a um.
void atualizaRepresentantes(Grupo* grupos, const int numeroDeGrupos); /// Atualiza os valores dos representantes dos grupos de flores.
void desalocaVetorDeFlores(Grupo* grupos, const int numeroDeGrupos); /// Desaloca os vetores que armazenam flores.
void persisteResultado(Grupo *grupos, const int numeroDeGrupos, const std::string nomeArquivo); ///Cria um novo arquivo e armazena os resultados.
std::string formataLinhaDeFlores(Flor flor, std::string numeroGrupo); /// Formata as informações de uma flor.
void desalocaVetorDeGrupos(Grupo* grupos, const int numeroDeGrupos); /// Desaloca o vetor que armazena os grupos.
template <typename T> void checaAlocacao(T* aloc); /// Checa se a alocação foi bem sucedida, e em caso de falha encerra o programa.

int main(int argc, char *argv[]) {

    // Nome do arquivo recuperado atraves do vetor de parametros da funcao main
    const std::string NOME_ARQUIVO = argv[1];
    const int TAMANHO_ARQUIVO = calculaTamanhoArquivo(NOME_ARQUIVO);
    
    // Imprimindo cabeçalho inicial
    imprimeCabecalho();

    // Lendo informacoes do usuario
    const int NUMERO_DE_GRUPOS = leNumeroDeGrupos("Digite a quantidade de grupos que deseja organizar: ", TAMANHO_ARQUIVO);
    const int NUMERO_DE_EXECUCOES = leNaturalNaoNulo("Digite a quantidade de vezes que a organizacao se repetira: ");
    
    // Inicializando os grupos com seus representantes
    Grupo *grupos = inicializaGruposComRepresentantes(NUMERO_DE_GRUPOS, NOME_ARQUIVO, TAMANHO_ARQUIVO);

    // Classificando as flores
    std::cout << "\nClassificando as flores...\n";
    classificaFlores(grupos, NUMERO_DE_GRUPOS, NOME_ARQUIVO, NUMERO_DE_EXECUCOES);
    std::cout << "Classificacao concluida.\n"; 
    
    // Armazenando resultados em um outro arquivo
    std::cout << "Armazenando resultado no arquivo classificacao_" << NOME_ARQUIVO << "...\n";
    persisteResultado(grupos, NUMERO_DE_GRUPOS,NOME_ARQUIVO);

    // Desalocando vetor de grupos
    desalocaVetorDeGrupos(grupos, NUMERO_DE_GRUPOS);
    
    std::cout << "\nEncerrando o programa...\n\n";

    return 0;
}

/**
 * @brief Calcula a quantidade de linhas do arquivo de texto.
 * 
 * @param nomeArquivo Nome do arquivo.
 * @return O tamanho do arquivo em quantidade de linhas.
 */
int calculaTamanhoArquivo(const std::string nomeArquivo) {
    std::ifstream arquivo(nomeArquivo, std::ios::in);
    int tamanho = 0;
    std::string linha = "";
    while(getline(arquivo, linha))
        tamanho++;
    arquivo.close();
    return tamanho;
}
 /**
  * @brief Imprime o cabecalho do programa na saida padrao.
  * 
  */
void imprimeCabecalho() {
    std::cout << "\nInicializando o programa...\n";
    std::cout << std::endl <<
        "=======================================" << std::endl <<
        "   Organizacao de Especies de Flores" << std::endl <<
        "=======================================" << std::endl << std::endl;
}

/**
 * @brief Realiza a leitura de um numero natural diferente de zero.
 * 
 * @param message Mensagem de a ser exibida na solicitacao de entrada de um numero.
 * @return O numero natural nao nulo.
 */
int leNaturalNaoNulo(std::string mensagem) {
    int numero;
    std::string mensagemDeErro = "Entrada invalida. Tente novamente.\n";
    bool numeroValidado = false;
    std::cout << mensagem;
    while(!numeroValidado) {
       std::cin >> numero;
        
        if(std::cin.fail()) { // Verifica se houve erro na leitura do numreo
            std::cout << mensagemDeErro << mensagem;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer do comeco ate o limite da sua capacidade
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(std::cin.gcount() > 1) { // Verifica se ha caracteres nao numericos na leitura
            std::cout << mensagemDeErro << mensagem;
            continue;
        }

        if(numero <= 0) {
            std::cout << mensagemDeErro << mensagem;
            continue;
        }

        numeroValidado = true;
    }
    return numero;
}

/**
 * @brief Realiza a leitura de um numero natural menor que a quantidade de registros no arquivo.
 * 
 * @param mensagem Mensagem de a ser exibida na solicitacao de entrada de um numero.
 * @param tamanhoArquivo Quantidade de linhas do arquivo.
 * @return Um numero natural menor ou igual a quantidade de registros presentes no arquivo.
 */
int leNumeroDeGrupos(std::string mensagem, const int tamanhoArquivo) {
    int numero;
    bool numeroValidado = false;
    while (!numeroValidado) {
        numero = leNaturalNaoNulo(mensagem);
        if(numero < tamanhoArquivo) numeroValidado = true;
        else std::cout << "Entrada invalida. Quantidade maxima permitida: " << tamanhoArquivo - 1 << ". Tente novamente.\n";
    }
    return numero;
}

/**
 * @brief Aloca o vetor de grupos e o inicializa com as informacoes das flores 
 *      escolhidas como representantes. 
 * 
 * @param numeroDeGrupos Numero total de grupos.
 * @param nomeArquivo Nome do arquivo.
 * @param tamanhoArquivo Quantidade de linhas do arquivo.
 * @return O vetor de grupos inicializado.
 */
Grupo* inicializaGruposComRepresentantes(const int numeroDeGrupos, const std::string nomeArquivo, const int tamanhoArquivo) {
    Grupo *grupos = new Grupo[numeroDeGrupos];
    checaAlocacao(grupos);
    Flor *flores = buscaRepresentantes(numeroDeGrupos, nomeArquivo, tamanhoArquivo);
    for (int i = 0; i < numeroDeGrupos; i++) {
        grupos[i].numero = std::to_string(i+1);
        grupos[i].comprimento = flores[i].comprimento;
        grupos[i].largura = flores[i].largura;
    }
    delete[] flores;
    return grupos;
}

/**
 * @brief Encontra dentro do arquivo os representantes sorteados.
 * 
 * @param numeroRepresentantes Quantidade de representantes.
 * @param nomeArquivo Nome do arquivo.
 * @param tamanhoArquivo Quantidade de linhas do arquivo.
 * @return Vetor que contem as flores representantes.
 */
Flor* buscaRepresentantes(const int numeroRepresentantes, const std::string nomeArquivo, const int tamanhoArquivo) {
    std::ifstream arquivo(nomeArquivo, std::ios::in);

    if(!arquivo)
        throw std::ifstream::failure("Erro ao abrir o arquivo.");

    // Descartando o cabecalho do arquivo e garantindo que esta string nao pode mais ser utilizada
    {
        std::string cabecalho = "";
        getline(arquivo, cabecalho, '\n');
    }

    // Encontrando as flores representantes
    Flor *flores = new Flor[numeroRepresentantes];
    checaAlocacao(flores);
    int *indicesRepresentantes = sorteiaIndicesRepresentantes(numeroRepresentantes, tamanhoArquivo);
    int indiceLeitura = 0;
    int indiceFlor = 0;
    std::string linha = "";
    
    // Adiciona ao vetor as flores representantes
    while(getline(arquivo, linha)) {
        if(elementoEstaEmLista(++indiceLeitura, indicesRepresentantes, numeroRepresentantes)) {
            replace(linha.begin(), linha.end(), ',', ' ');
            std::stringstream linhaStream(linha); 
            Flor flor;
            linhaStream >> flor.comprimento >> flor.largura >> flor.variedade;
            flores[indiceFlor] = flor;
            indiceFlor++;
        }
    }

    arquivo.close();
    free(indicesRepresentantes);
    
    return flores;
}

/**
 * @brief Sorteia as flores que servirao como representantes iniciais para os grupos. 
 * 
 * @param numeroRepresentantes Quantidade de representantes.
 * @param tamanhoArquivo Quantidade de linhas do arquivo.
 * @return O vetor que contem os indices sorteados.
 */
int* sorteiaIndicesRepresentantes(const int numeroRepresentantes, const int tamanhoArquivo) {
    srand(time(0));
    int quantidadeMaxima = tamanhoArquivo - 1; // Desconsiderando linha de cabecalho
    int *indices = (int*) calloc(numeroRepresentantes, sizeof(int));
    checaAlocacao(indices);
    int contador = 0;
    while (contador < numeroRepresentantes) {
        int indice = rand() % quantidadeMaxima + 1;
        if(!elementoEstaEmLista(indice, indices, numeroRepresentantes)) {
            indices[contador] = indice;
            contador++;
        }
    }
    return indices;
}

/**
 * @brief Verifica se um dado elementa esta no vetor.
 * 
 * @param elemento Elemento a ser buscado.
 * @param lista Vetor onde sera feita a busca.
 * @param tamanho Tamanho do vetor.
 * @return true Se o elemento for encontrado.
 * @return false Se o elemento não for encontrado.
 */
bool elementoEstaEmLista(int elemento, int* lista, const int tamanho) {
    for (int i = 0; i < tamanho; i++)
        if(elemento == lista[i])
            return true;
    return false;
}

/**
 * @brief Classifica as flores em quantos grupos o usuario desejar. A operacao
 *      e repetida quantas vezes o usuario desejar para maior refinamento.
 * 
 * @param grupos Vetor que armazena os grupos.
 * @param numeroDeGrupos Numero de grupos.
 * @param nomeArquivo Nome do arquivo.
 * @param numeroDeExecucoes Numero de vezes que a classificacao ocorrera.
 */
void classificaFlores(Grupo* grupos, const int numeroDeGrupos, const std::string nomeArquivo, const int numeroDeExecucoes) {
    for (int execucao = 0; execucao < numeroDeExecucoes; execucao++) {
        std::ifstream arquivo(nomeArquivo, std::ios::in);
        if(!arquivo)
            throw std::ifstream::failure("Falha na leitura do arquivo.");

        // Descartar o cabeçalho do arquivo
        {
            std::string linhaTemp = "";
            getline(arquivo, linhaTemp);
        }

        // "Zerar" informacoes do vetor de flores
        for (int indice = 0; indice < numeroDeGrupos; indice++) {
            grupos[indice].flores = new Flor[1];
            checaAlocacao(grupos[indice].flores);
            grupos[indice].tamanhoVetor = 0;
        }
        
        std::string linha = "";
        while (getline(arquivo, linha)) {
            
            // Atribuindo os valores da linha a flor
            replace(linha.begin(), linha.end(), ',', ' '); // Substituir as vírgulas por espaços para separar os valores da linha
            std::stringstream linhaStream(linha);
            Flor flor;
            linhaStream >> flor.comprimento >> flor.largura >> flor.variedade;

            int indiceIdeal = encontraGrupoIdeal(grupos, numeroDeGrupos, flor.comprimento, flor.largura);
            alocaFlorNoGrupoIdeal(flor, grupos, indiceIdeal);
        }
        arquivo.close();

        atualizaRepresentantes(grupos, numeroDeGrupos);
        if(execucao < numeroDeExecucoes - 1) // Desaloca vetores de flores para todas as execucoes com excecao da ultima
            desalocaVetorDeFlores(grupos, numeroDeGrupos);
    }
}

/**
 * @brief Encontra o grupo ideal para alocar a flor.
 * 
 * @param grupos Vetor de grupos.
 * @param numeroDeGrupos Numero de grupos.
 * @param comprimentoFlor Comprimento da flor.
 * @param larguraFlor Largura da flor.
 * @return O grupo ideal para que a flor seja alocada.
 */
int encontraGrupoIdeal(Grupo* grupos, const int numeroDeGrupos, const long double comprimentoFlor, const long double larguraFlor) {
    long double *distanciasEuclidianas = new long double[numeroDeGrupos];
    checaAlocacao(distanciasEuclidianas);
    for (int i = 0; i < numeroDeGrupos; i++) // Calcular a distância euclidiana entre a flor e cada grupo
        distanciasEuclidianas[i] = calculaDistanciaEuclidiana(grupos[i].comprimento, comprimentoFlor, grupos[i].largura, larguraFlor);
    int indiceIdeal = encontraIndiceComMenorValor(distanciasEuclidianas, numeroDeGrupos);
    delete[] distanciasEuclidianas;
    return indiceIdeal;
}

/**
 * @brief Calcula a distância euclidiana entre os representantes dos grupos e as flores do arquivo.
 * 
 * @param comprimentoRepresentante Comprimento do representante.
 * @param comprimentoFlor Comprimento da flor.
 * @param larguraRepresentante Largura do representante.
 * @param larguraFlor Largura da flor.
 * @return Distancia Euclidiana entre os pontos fornecidos.
 */
long double calculaDistanciaEuclidiana(long double comprimentoRepresentante, long double comprimentoFlor, long double larguraRepresentante, long double larguraFlor) {
    return sqrt(pow(comprimentoRepresentante - comprimentoFlor, 2) + pow(larguraRepresentante - larguraFlor, 2));
}

/**
 * @brief Encontra o menor valor em um vetor.
 * 
 * @param vetor Vetor que armazena as distancias euclidianas.
 * @param tamanho Tamanho do vetor fornecido.
 * @return Menor valor do vetor fornecido.
 */
int encontraIndiceComMenorValor(long double* vetor, const int tamanho) {
    int indiceRetorno = 0;
    long double menorValor = vetor[0];
    for (int i = 0; i < tamanho; i++) {
        if(vetor[i] < menorValor) {
            menorValor = vetor[i];
            indiceRetorno = i;
        }
    }
    return indiceRetorno;
}

/**
 * @brief Aloca uma flor no grupo que possui o indice ideal.
 * 
 * @param flor Flor que sera alocada.
 * @param grupos Vetor que armazena os grupos.
 * @param indiceIdeal O indice do vetor que possui a menor distancia euclidiana em relacao a flor que esta sendo alocada.
 */
void alocaFlorNoGrupoIdeal(Flor flor, Grupo* grupos, const int indiceIdeal) {
    grupos[indiceIdeal].flores = realocaVetor(grupos[indiceIdeal].flores, &grupos[indiceIdeal].tamanhoVetor);
    int ultimoIndiceDeFlores = grupos[indiceIdeal].tamanhoVetor - 1;
    grupos[indiceIdeal].flores[ultimoIndiceDeFlores] = flor;
}

/**
 * @brief Redimenciona o vetor, incrementando o tamanho de um a um.
 * 
 * @param vet Vetor que sera redimencionado.
 * @param t Ponteiro para a variavel que guarda o tamanho atual do vetor
 * @return O novo vetor redimensionado.
 */
Flor* realocaVetor(Flor* vet, int* t) {
    Flor* newvet = new Flor[*t+1];
    checaAlocacao(newvet);
    for(int i = 0; i < *t; i++)
        newvet[i] = vet[i];
    (*t)++;
    delete[] vet;
    return newvet;
}

/**
 * @brief Atualiza os valores dos representantes dos grupos de flores.
 * 
 * @param grupos Vetor que armazena os grupos.
 * @param numeroDeGrupos Numero de grupos.
 */
void atualizaRepresentantes(Grupo* grupos, const int numeroDeGrupos) {
    for (int i = 0; i < numeroDeGrupos; i++) {
        int quantidadeDeFlores = grupos[i].tamanhoVetor;
        long double somaComprimentos = 0;
        long double somaLarguras = 0;
        for (int j = 0; j < quantidadeDeFlores; j++) {
            somaComprimentos += grupos[i].flores[j].comprimento;
            somaLarguras += grupos[i].flores[j].largura;
        }
        grupos[i].comprimento = somaComprimentos / quantidadeDeFlores;
        grupos[i].largura = somaLarguras / quantidadeDeFlores;
    }
}

/**
 * @brief Desaloca os vetores que armazenam flores.
 * 
 * @param grupos Vetor que armazena os grupos.
 * @param numeroDeGrupos Numero de grupos.
 */
void desalocaVetorDeFlores(Grupo* grupos, const int numeroDeGrupos) {
    for(int i = 0; i < numeroDeGrupos; i++)
        delete[] grupos[i].flores;
}

/**
 * @brief Cria um novo arquivo e armazena os resultados da classificacao.
 * 
 * @param grupos  Vetor que armazena os grupos.
 * @param numeroDeGrupos Numero de grupos.
 * @param nomeArquivo Nome do arquivo que sera gerado.
 */
void persisteResultado(Grupo *grupos, const int numeroDeGrupos, const std::string nomeArquivo) {
    std::string nomeArquivoClassificacao = "classificacao_";
    nomeArquivoClassificacao.append(nomeArquivo);
    
    std::ofstream novoArquivo(nomeArquivoClassificacao, std::ios::out);
    novoArquivo << "comprimento,largura,variedade,grupo" << std::endl;

    for(int i = 0; i < numeroDeGrupos; i++){
        std::string numeroGrupo = grupos[i].numero;
        for(int j = 0; j < grupos[i].tamanhoVetor; j++)
            novoArquivo << formataLinhaDeFlores(grupos[i].flores[j], numeroGrupo);
    }

    novoArquivo.close();
}

/**
 * @brief Formata as informações de uma flor.
 * 
 * @param flor Flor que tera as informacoes formatadas.
 * @param numeroGrupo Numero do grupo que atualmente armazena a flor que sera formatada.
 * @return Linha formatada com as informações da flor.
 */
std::string formataLinhaDeFlores(Flor flor, std::string numeroGrupo){
    std::stringstream linha;
    linha << std::fixed << std::setprecision(1) << flor.comprimento << "," << 
            flor.largura << "," << flor.variedade << "," << numeroGrupo << std::endl;
    return linha.str();
}

/**
 * @brief Desaloca o vetor que armazena os grupos
 * 
 * @param grupos vetor de grupos que será desalocado 
 * @param numeroDeGrupos Numero de grupos
 */
void desalocaVetorDeGrupos(Grupo* grupos, const int numeroDeGrupos) {
    for(int i = 0; i < numeroDeGrupos; i++)
        delete[] grupos[i].flores;
    delete[] grupos;
}

/**
 * @brief Checa se a alocação foi bem sucedida e, em caso de falha, encerra o programa.
 * 
 * @tparam T Tipo de dado do ponteiro.
 * @param aloc Ponteiro que tera a alocacao checada.
 */
template <typename T>
void checaAlocacao(T* aloc) {
    if(aloc == NULL) {
        std::cout << "\nFalha de alocacao!\nPrograma encerrado.\n\n";
        exit(EXIT_FAILURE);
    }
}