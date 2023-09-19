/*Programa para cadastro de clientes. Nesse cadastro é possivel cadastrar emprestimos, parcelas pagas e gerenciar os dados 
do cliente.
@Autor: Nicolas Scarpa
Data: 20/03/2023
*/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Struct do endereço
typedef struct{
    
    string rua;
    int numero = 0;
    string bairro;
    string cidade;

}Endereco;

// Struct do emprestimo
typedef struct{

    double valorEmprestimo = 0;
    string dataEmprestimo;
    int qtdParcelas = 0;
    // Vetor para armazenar as parcelas
    // Iniciando com 0 todos os elementos do vetor para não ter lixo de memoria
    double parcelas[12] = {0};

}Emprestimo;

// Struct do cliente
typedef struct{
    
    string nome;
    string cpf;
    Endereco endereco;
    string dataNascimento;
    Emprestimo emprestimo;

}Cliente;

// Escopo das funções
int menu(); // Função para exibir o menu
void chamarDados(Cliente cliente[], int n); // Função para exibir chamar as funções
void cadastrarCliente(Cliente cliente[], int n); // Função para cadastrar cliente
void exibirDadosCliente(Cliente cliente[], int n); // Função para exibir os dados do cliente
void alterarDados(Cliente cliente[], int n); // Função para alterar os dados do cliente
void parcelasPagas(Cliente cliente[], int n); // Função para cadastrar a parcela paga
void cadastrarEmprestimo(Cliente cliente[], int n); // Função para cadastrar o emprestimo
void excluirCliente(Cliente cliente[], int n); // Função para excluir o cliente
bool validaCPF(Cliente cliente[], int i); // Função para validar o CPF
bool verificaParcelas(Cliente cliente[], int n); // Função para verificar a quantidade de parcelas
bool validaDataNascimento(Cliente cliente[], int i); // Função para validar a data de nascimento
bool validaDataEmprestimo(Cliente cliente[], int i); // Função para validar a data do emprestimo
void exibeCPF(Cliente cliente[], int i); // Função para exibir o CPF com pontos e traço
void dataNascimento(Cliente cliente[], int i); // Função para exibir a data de nascimento com barras
void dataEmprestimo(Cliente cliente[], int i); // Função para exibir a data do emprestimo com barras

// Função principal do programa
int main(){  

    int n = 0; // Variavel para armazenar a quantidade de clientes iniciando com 0 para não ter lixo de memoria
    
    cout << "Bem vindo ao programa!" << endl;
    cout << "----------------------" << endl;
    cout << "Informe a quantidade de clientes: " << endl;
    cin >> n;
    cout << endl;

    Cliente cliente[n]; // Vetor de struct do tipo cliente recebendo a quantidade de clientes

    chamarDados(cliente, n); // Chama a função para chamar as funções

    return 0;
}

// Função menu
int menu(){
    
    // Variavel para armazenar a opção do usuario iniciando com 0 para não ter lixo de memoria
    int opcao = 0;

    // exibe o menu
    cout << "\t[1] Cadastrar cliente" << endl;
    cout << "\t[2] Vizualizar as informações de um cliente" << endl;
    cout << "\t[3] Editar as informacoes de um cliente" << endl;
    cout << "\t[4] Cadastrar parcela paga" << endl;
    cout << "\t[5] Cadastrar emprestismo" << endl;
    cout << "\t[6] Excluir cliente" << endl;
    cout << "\t[7] Sair" << endl;
    
    cin >> opcao; // lê a opção do usuário

    // retorna a opção escolhida pelo usuario para a função chamarDados para usar como condição no switch case
    return opcao; 
}

// Função para chamar as funções
void chamarDados(Cliente cliente[], int n){
      
    int opcao = 0;

    while(opcao != 7){ // Enquanto a opção for diferente de 7 o programa continua rodando
        // armazenando a opção escolhida pelo usuario na variavel opcao
        opcao = menu();
            switch(opcao){ // Switch case para chamar as funções
                // Caso a opção seja 1 chama a função cadastrarCliente
                case 1:
                    cadastrarCliente(cliente, n);
                    break;
                // Caso a opção seja 2 chama a função exibirDadosCliente
                case 2:
                    exibirDadosCliente(cliente, n);
                    break;
                // Caso a opção seja 3 chama a função alterarDados
                case 3:
                    alterarDados(cliente, n);
                    break;
                // Caso a opção seja 4 chama a função parcelasPagas
                case 4:
                   parcelasPagas(cliente, n);
                    break;
                // Caso a opção seja 5 chama a função cadastrarEmprestimo
                case 5:
                    cadastrarEmprestimo(cliente, n);
                    break;
                // Caso a opção seja 6 chama a função excluirCliente
                case 6:
                    excluirCliente(cliente, n);
                    break;
                // Caso a opção seja 7 exibe a mensagem de saida
                case 7:
                    cout << "Saindo..." << endl;
                    break;
                // Caso a opção seja invalidade exibe a mensagem de opção invalida
                default:
                    cout << "Opcao invalida!" << endl;
                    break;
        }
   }
}

// Função para cadastrar cliente
void cadastrarCliente(Cliente cliente[], int n){

    cout << "********************" << endl;
    cout << "Cadastro de cliente" << endl;
    cout << "********************" << endl;
    

    for(int i = 0; i < n; i++){
        cout << "Dados do cliente " << i + 1 << endl;  
        cout << "-------------------" << endl;   
        cout << "Informe o CPF do cliente: " << endl;
        cin.ignore();
        getline(cin, cliente[i].cpf);
        cout << "-------------------" << endl;
        
        // Se o CPF for valido o cadastro continua até a verificação da data de nascimento
        while(validaCPF(cliente, i) == false){
            cout << "CPF invalido!" << endl;
            cout << "Informe o CPF do cliente novamente: " << endl;
            getline(cin, cliente[i].cpf);
            cout << "-------------------" << endl;
        }
        cout << "Nome do cliente: " << endl;
        getline(cin, cliente[i].nome);
        cout << "-------------------" << endl;

        // Verifica se a data de nascimento é valida, se for valida o cadastro continua até a verificação da data do emprestimo
        cout << "Informe a data de nascimento com 8 caracteres: " << endl;
        getline(cin, cliente[i].dataNascimento);
        cout << "-------------------" << endl;

        // Se a data de nascimento não for valida o cadastro entra em um loop até que a data seja valida
        while(validaDataNascimento(cliente, i) == false){
            cout << "Data invalida!" << endl;
            cout << "Por favor, insira novamente a data com 8 caracteres: " << endl;
            getline(cin, cliente[i].dataNascimento);
            cout << "-------------------" << endl;
        }
        cout << "Rua do cliente: " << endl;
        getline(cin, cliente[i].endereco.rua);
        cout << "-------------------" << endl;
        cout << "Numero da residencia: " << endl;
        cin >> cliente[i].endereco.numero;
        cout << "-------------------" << endl;
        cout << "Bairro: " << endl;
        cin.ignore();
        getline(cin, cliente[i].endereco.bairro);
        cout << "-------------------" << endl;
        cout << "Cidade: " << endl;
        getline(cin, cliente[i].endereco.cidade);
        cout << "-------------------" << endl;
        
            cout << "Valor do emprestimo: " << endl;
            cin >> cliente[i].emprestimo.valorEmprestimo;
            cout << "-------------------" << endl;

        // Se o valor do emprestimo for maior que 0 o cadastro continua normalmente
        // Se for igual a 0 o cadastro é finalizado e o cliente não tem emprestimo nem parcelas
        if(cliente[i].emprestimo.valorEmprestimo > 0){
            // Verifica se a data do emprestimo é valida, se for valida o cadastro continua até a verificação da quantidade de parcelas
            cout << "Informe a data do emprestimo com 8 caracteres: " << endl;
            getline(cin, cliente[i].emprestimo.dataEmprestimo);
            cout << "-------------------" << endl;
        
            // Se a data do emprestimo não for valida o cadastro entra em um loop até que a data seja valida
            while(validaDataEmprestimo(cliente, i) == false){
                cout << "Data invalida!" << endl;
                cout << "Por favor, insira novamente a data com 8 caracteres: " << endl;
                getline(cin, cliente[i].emprestimo.dataEmprestimo);
                cout << "-------------------" << endl;
            }

            cout << "Quantidade de parcelas: " << endl;
            cin >> cliente[i].emprestimo.qtdParcelas;
            cout << "-------------------" << endl;
            
            // Se a quantidade de parcelas for valida o cadastro continua normalmente
            // Se for invalida o cadastro entra em um loop até que a quantidade de parcelas seja valida
            while(verificaParcelas(cliente, i) == false){
                cout << "Quantidade de parcelas invalida!" << endl;
                cout << "Por favor, insira novamente a quantidade de parcelas: " << endl;
                cin >> cliente[i].emprestimo.qtdParcelas;
                cout << "-------------------" << endl;
            }
        
            // Calcula o valor de cada parcela 
            for(int j = 0; j < cliente[i].emprestimo.qtdParcelas; j++){
                // Dividindo o valor do emprestimo pela quantidade de parcelas e armazenando o valor em cada parcela no vetor
                cliente[i].emprestimo.parcelas[j] = cliente[i].emprestimo.valorEmprestimo / cliente[i].emprestimo.qtdParcelas;
            }

            cout << endl;
            cout << "*************************************" << endl;
            cout << "Cliente cadastrado com sucesso!" << endl;
            cout << "*************************************" << endl;

        }else{
            cliente[i].emprestimo.qtdParcelas = 0;
            cout << endl;
            cout << "*************************************" << endl;
            cout << "Cliente cadastrado com sucesso!" << endl;
            cout << "*************************************" << endl; 
        }

    }
}

// Função para exibir dados do cliente
void exibirDadosCliente(Cliente cliente[], int n){
      
    string cpf;
     
    cout << "********************************" << endl;
    cout << "Visualizacao de dados do cliente" << endl;
    cout << "********************************" << endl;
     
    // Solicitando ao usuario o cpf do cliente para verificar se o cliente existe na base de dados
    cout << "Informe o CPF do cliente: " << endl;
    cin.ignore();
    getline(cin, cpf);
    cout << "-----------------------------" << endl;
    
    // Percore o vetor de clientes para verificar se o cpf informado pelo usuario existe na base de dados
    for(int i = 0; i < n; i++){
        // Se o cpf informado pelo usuario for igual ao cpf do cliente, exibe os dados do cliente
        if(cliente[i].cpf == cpf){
            cout << "--------------------------------" << endl;
            cout << "Nome: " << cliente[i].nome << endl;
            cout << "CPF: ";
            exibeCPF(cliente, i);
            cout << endl;
            cout << "Data de nascimento: ";
            dataNascimento(cliente, i);
            cout << endl;
            cout << "Endereco: " << cliente[i].endereco.rua << ", " << cliente[i].endereco.numero << " - " << cliente[i].endereco.bairro << endl;  
            cout << "Cidade: " << cliente[i].endereco.cidade << endl;
            
            // Verificando se a quantidade de parcelas é maior que 0
            // Se for maior que 0, exibe a quantidade de parcelas e o valor de cada parcela
            if(cliente[i].emprestimo.qtdParcelas > 0 && cliente[i].emprestimo.valorEmprestimo > 0){
                cout << fixed << setprecision(2);
                cout << "Valor do emprestimo: " << cliente[i].emprestimo.valorEmprestimo << endl;
                cout << "Data do emprestimo: ";
                dataEmprestimo(cliente, i);
                cout << endl;
                cout << "Quantidade de parcelas: " << cliente[i].emprestimo.qtdParcelas << endl;
                cout << "Parcelas: " << endl;
            
                // Percorrendo o vetor de parcelas para verificar qual está paga
                for(int j = 0; j < cliente[i].emprestimo.qtdParcelas; j++){
                    // Se a parcela estiver paga, exibe a mensagem "Paga"
                    if(cliente[i].emprestimo.parcelas[j] == true){
                        cout << "Parcela " << j + 1 << ": " << "Paga" << endl;
                    }
                    // Se a parcela não estiver paga, exibe o valor da parcela
                    if(cliente[i].emprestimo.parcelas[j] != true){
                        cout << "Parcela " << j + 1 << ": " << cliente[i].emprestimo.parcelas[j] << endl;
                }
            }
            cout << "--------------------------------" << endl;
            }else{
                cout << "--------------------------------" << endl;
            }
        }else{
            // Se o cliente não existir na base de dados exibe a mensagem "Cliente nao encontrado!"
            cout << "Cliente nao encontrado!" << endl;
        }
    }
}

// Função para alterar dados do cliente
void alterarDados(Cliente cliente[], int n){
    
    string cpf;
    int opcao = 0;

    cout << "********************************" << endl;
    cout << "Alteracao de dados do cliente" << endl;
    cout << "********************************" << endl;

    // Solicita o CPF do cliente que deseja-se alterar
    cout << "Informe o CPF do cliente: " << endl;
    cin.ignore();
    getline(cin, cpf);
    
    // Se o cliente existir na base de dados, solicita o dado que deseja alterar
    for(int i = 0; i < n; i++){
        if(cliente[i].cpf == cpf){
            cout << "--------------------------------" << endl;
            cout << "O que deseja alterar?" << endl;
            cout << "\t[1] Nome" << endl;
            cout << "\t[2] Data de nascimento" << endl;
            cout << "\t[3] Endereco" << endl;
            cout << "\t[4] Sair" << endl;
            cin >> opcao;

            // Realiza a acao correspondente a opcao escolhida
            switch(opcao){
                // Opção 1: Altera o nome do cliente
                case 1:
                   
                    cout << "Informe o nome: " << endl;
                    cin.ignore();
                    getline(cin, cliente[i].nome);
                    break;

                // Opção 2: Altera a data de nascimento do cliente
                case 2:

                    cout << "Informe a data de nascimento: " << endl;
                    cin.ignore();
                    getline(cin, cliente[i].dataNascimento);
                    break;

                // Opção 3: Altera o endereco do cliente
                case 3:

                    cout << "Informe a rua: " << endl;
                    cin.ignore();
                    getline(cin, cliente[i].endereco.rua);
                    cout << "Informe o numero: " << endl;
                    cin >> cliente[i].endereco.numero;
                    cout << "Informe o bairro: " << endl;
                    cin.ignore();
                    getline(cin, cliente[i].endereco.bairro);
                    cout << "Informe a cidade: " << endl;
                    getline(cin, cliente[i].endereco.cidade);
                    break;

                // Opção 4: Sair
                case 4:
                    cout << "Saindo..." << endl;
                    break;

                    // Default é a opção caso o usuario digite uma opção invalida
                default:
                    cout << "Opcao invalida!" << endl;
                    break;    
            }
        }
    }
}

// Função para cadastrar parcelas pagas
void parcelasPagas(Cliente cliente[], int n){

    int parcela = 0;
    string cpf;

    cout << "********************************" << endl;
    cout << "Cadastro de parcelas pagas" << endl;
    cout << "********************************" << endl;
    
    // Solicita o CPF do cliente que deseja-se cadastrar as parcelas pagas
    cout << "Informe o CPF do cliente: " << endl;
    cin.ignore();
    getline(cin, cpf);
    
    // Percorre o vetor de clientes para verificar se o cliente existe na base de dados
    for(int i = 0; i < n; i++){
        // Se o cliente existir na base de dados, solicita o numero da parcela paga
        if(cliente[i].cpf == cpf){
            
            cout << "Informe o numero da parcela paga: " << endl;
            // Armazena o numero da parcela paga 
            cin >> parcela;
            
            // Após o usuario informar a parcela, dimunui 1 do valor para ser igual a posição da parcela no vetor
            // Ex: se o usuario informar a parcela 1, o valor da parcela no vetor será a posição 0 e assim por diante
            // Essa posição é marcada como true, indicando que a parcela foi paga
            cliente[i].emprestimo.parcelas[parcela - 1] = true;
            
            cout << "Parcela paga com sucesso!" << endl;
         }
    }
}   

// Função para cadastrar emprestimo
void cadastrarEmprestimo(Cliente cliente[], int n){

    string cpf;

    cout << "********************************" << endl;
    cout << "Cadastro de emprestimo" << endl;
    cout << "********************************" << endl;

    // Solicita o CPF do cliente que deseja-se cadastrar o emprestimo
    cout << "Informe o CPF do cliente: " << endl;
    cin.ignore();
    getline(cin, cpf);

    // Percorre o vetor de clientes
    for(int i = 0; i < n; i++){
        // Verifica se o cliente atual tem o CPF informado pelo usuário
        if(cliente[i].cpf == cpf){
            // Verifica se o cliente já possui um empréstimo
            if(cliente[i].emprestimo.valorEmprestimo != 0){
                cout << "Cliente ja possui emprestimo!" << endl;
                // Se o cliente não possuir um empréstimo, solicita os dados do empréstimo para cadastrar
            }else{
            // Solicita os dados do empréstimo
                cout << "Informe o valor do emprestimo: " << endl;
                cin >> cliente[i].emprestimo.valorEmprestimo;
                cout << "Informe a data do emprestimo: " << endl;
                cin.ignore();
                getline(cin, cliente[i].emprestimo.dataEmprestimo);
                cout << "Informe a quantidade de parcelas: " << endl;
                cin >> cliente[i].emprestimo.qtdParcelas;
                
                // Calcula o valor de cada parcela dividindo o valor do emprestimo pela quantidade de parcelas e armazena no vetor parcelas
                for(int j = 0; j < cliente[i].emprestimo.qtdParcelas; j++){
                cliente[i].emprestimo.parcelas[j] = cliente[i].emprestimo.valorEmprestimo / cliente[i].emprestimo.qtdParcelas;
            }
                cout << "Emprestimo cadastrado com sucesso!" << endl;
            }
        }
    }
    cout << "Cliente nao encontrado!" << endl;
}

// Função para excluir cliente
void excluirCliente(Cliente cliente[], int n){
    
    string cpf;

    cout << "********************************" << endl;
    cout << "Exclusao de dados do cliente" << endl;
    cout << "********************************" << endl;

    // Solicita o CPF do cliente que deseja-se excluir
    cout << "Informe o CPF do cliente: " << endl;
    cin.ignore();
    getline(cin, cpf);
    
    // Percorre o vetor de clientes para achar o cliente com o CPF informado
    for(int i = 0; i < n; i++){
        // Verifica se o cliente atual tem o CPF informado pelo usuário
        if(cliente[i].cpf == cpf){
            // se o cliente existir na base de dados, exclui o cpf que apoonta para o cliente
          cliente[i].cpf = "";
            }
        }

     // Exibe mensagem de sucesso   
    cout << "Cliente excluido com sucesso!" << endl;
}

// Função para validar CPF
bool validaCPF(Cliente cliente[], int i){

    // Verificando se todos os caracteres são dígitos numéricos
    for(int cont = 0; cont < 11; cont++){
        if (!isdigit(cliente[i].cpf[cont])) // Utilizando a função isdigit() para verificar se o caractere é um dígito numérico
            // Se não for retorna false
            return false;
    }
    
    if(cliente[i].cpf.length() != 11){
        // Se não tiver 11 dígitos retorna false
        return false;
    }
        // Se todos os caracteres forem digitos e tiver 11 dígitos retorna true
        return true; 
}
   
// Função para validar a quantidade de parcelas
bool verificaParcelas(Cliente cliente[], int i){
    
    int quantidadeParcelas = 12;
    
    // Verificando se a quantidade de parcelas é maior que 12
    if(cliente[i].emprestimo.qtdParcelas > quantidadeParcelas)
        // Se for maior retorna false
        return false;
    
    // Se for menor ou igual a 12 retorna true
    return true;
}

// Função para validar data de nascimento
bool validaDataNascimento(Cliente cliente[], int i){

    // Verificando se todos os caracteres são dígitos numéricos
    for(int cont = 0; cont < 8; cont++){
        if(!isdigit(cliente[i].dataNascimento[cont])) 
        // Se não for retorna false
            return false;
    }

    // Verificando se a data de nascimento tem 8 dígitos
    if(cliente[i].dataNascimento.length() != 8) 
        // Se não tiver 8 dígitos retorna false
        return false;
    
    // Se todos os caracteres forem digitos numericos e tiverem 8 dígitos retorna true
    return true;
}

// Função para validar a data do emprestimo
bool validaDataEmprestimo(Cliente cliente[], int i){

    // Verificando se todos os caracteres são dígitos numéricos
    for(int cont = 0; cont < 8; cont++){
        if(!isdigit(cliente[i].emprestimo.dataEmprestimo[cont]))
        // Se não for retorna false
            return false;
    }

    // Verificando se a data do emprestimo tem 8 dígitos
    if(cliente[i].emprestimo.dataEmprestimo.length() != 8) 
        // Se não tiver 8 dígitos retorna false
        return false;
    
    // Se todos os caracteres forem digitos numericos e tiverem 8 dígitos retorna true
    return true; 
}

// Funçã para colocar ponto no CPF
void exibeCPF(Cliente cliente[], int i){
    
    for(int cont = 0; cont < 11; cont++){
        if(cont == 3 || cont == 6){
            // Imprimindo um ponto na tela
            cout << "."; 
        }
        if(cont == 9){
            // Imprimindo um hífen na tela
            cout << "-"; 
        }
        // Imprimindo o caractere na posição cont
        cout << cliente[i].cpf[cont]; 
    }
}

// Função para colocar barra na data de nascimento
void dataNascimento(Cliente cliente[], int i){
    for(int cont = 0; cont < 8; cont++){
        if(cont == 2 || cont == 4){
            cout << "/"; // Imprimindo uma barra na tela
        }
        // Imprimindo o caractere na posição cont
        cout << cliente[i].dataNascimento[cont];
    }
}

// Função para colocar barra na data do emprestimo
void dataEmprestimo(Cliente cliente[], int i){
    for(int cont = 0; cont < 8; cont++){
        if(cont == 2 || cont == 4){
            // Imprimindo uma barra na tela
            cout << "/"; 
        }
        // Imprimindo o caractere na posição cont
        cout << cliente[i].emprestimo.dataEmprestimo[cont]; 
    }
}
