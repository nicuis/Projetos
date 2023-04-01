/* Programa para calcular o seno e o cosseno de um angulo usando 3 termos e 40 termos e exibir o erro absoluto e relativo comparando
com as funções pronta sin() e cos() da biblioteca cmath.

@Autor: Nicolas Scarpa
Data: 11/03/2023
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#define PI 3.1415 // Definindo o valor de PI

// Informando ao compilador que as funcoes existem
int entradaDados(); // Funcao para armazenar o angulo informado pelo usuario
void exibirDados(float angulo); // Funcao para exibir os dados
long double Radiano(float angulo); // Funcao para converter o angulo para radiano
long double Fatorial(int n); // Funcao para calcular o fatorial do numero
long double Seno(float angulo, int n); // Funcao para calcular o seno usando a formula de Taylor
long double Cosseno(float angulo, int n); // Funcao para calcular o cosseno usando a formula de Taylor
long double Seno2(float angulo); // Funcao para calcular o seno utilizando a funcao sin() da lib cmath
long double Cosseno2(float angulo); // Funcao para calcular o cosseno utilizando a funcao cos() da lib cmath
long double calculoErroAbsoluto(long double sen3, long double real); // Funcao para calcular o erro absoluto
long double calculoErroRelativo(long double sen3, long double real); // Funcao para calcular o erro relativo

int main(){

    exibirDados(entradaDados()); // Chamada da funcao para exibir os dados

    return 0;
}

// Função para armezar o angulo informado pelo usuario
int entradaDados(){

    float angulo = 0;

    cout << "Informe o angulo: " << endl;
    cin >> angulo;
    
    return angulo;

}

// Funcao para exibir os dados
void exibirDados(float angulo){

    cout << fixed << setprecision(6); // Definindo 5 casa decimais para exibir os numeros
    
    cout << "Seno usando 3 termos: " << Seno(angulo, 3)<< endl;
    cout << "Seno usando 40 termos: " << Seno(angulo, 40) << endl;
    cout << "Seno utilizando a funcao sin: " << Seno2(angulo) << endl;
    cout << "Erro absoluto do seno: " << calculoErroAbsoluto(Seno(angulo, 3), Seno2(angulo)) << endl;
    cout << "Erro relativo do seno em porcentagem: " << calculoErroRelativo(Seno(angulo, 3), Seno2(angulo)) << "%" << endl;

    cout << "" << endl;
    cout << "--------------------------------------------" << endl;

    cout << "Cosseno usando 3 termos: " << Cosseno(angulo, 3) << endl;
    cout << "Cosseno usando 40 termos: " << Cosseno(angulo, 40) << endl;
    cout << "Cosseno utilizando a funcao cos: " << Cosseno2(angulo) << endl;
    cout << "Erro absoluto do cosseno: " << calculoErroAbsoluto(Cosseno(angulo, 3), Cosseno2(angulo)) << endl;
    cout << "Erro relativo do cosseno em porcentagem: " << calculoErroRelativo(Cosseno(angulo, 3), Cosseno2(angulo)) << "%" << endl;
    
    cout << "" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Obrigado por usar o programa!!" << endl;

}

// Funcao para converter o angulo para radiano
long double Radiano(float angulo){

    return (angulo * PI) / 180; //  Retornando o valor do angulo em radiano
     
}

// Funcao para calcular o fatorial do numero usando recursividade
long double Fatorial(int n){

    if(n == 0){ 
        return 1;
    }else{
        return n*Fatorial(n - 1); // Chamada recursiva da funcao para calcular o fatorial
    }

}

// Funcao para calcular o seno usando a formula de Taylor
long double Seno(float angulo, int n){
    
    double result = 0;
    
    // loop para percorrer os termos
    for(int i = 0; i < n; i++){ 
        // o resultado é igual a ele mesmo mais a potencia de -1 elevado ao i
        // vezes a potencia do angulo em radiano elevado ao 2 vezes i mais 1 dividido pelo fatorial de 2 vezes i mais 1
        result += pow(-1, i) * pow(Radiano(angulo), 2*i + 1)/Fatorial(2*i + 1); // Calculo do seno
    }

    return result; // Retornando o resultado

}

// Funcao para calcular o cosseno usando a formula de Taylor
long double Cosseno(float angulo, int n){
    
    double result = 0;
    
    // loop para percorrer os termos
    for(int i = 0; i < n; i++){
        // o resultado é igual a ele mesmo mais a potencia de -1 elevado ao i 
        // vezes a potencia do angulo em radiano elevado ao 2 vezes i dividido pelo fatorial de 2 vezes i
        result += pow(-1, i) * pow(Radiano(angulo), 2*i)/Fatorial(2*i); // Calculo do cosseno
    }

    return result; // Retornando o resultado

}

// Funcao para calcular o seno utilizando a função sin() da lib cmath
long double Seno2(float angulo){ 
    
   return sin(Radiano(angulo)); // Retornando o resultado da função sin

}

// Funcao para calcular o cosseno utilizando a funcao cos() da lib cmath
long double Cosseno2(float angulo){ 
   
   return cos(Radiano(angulo)); // Retornando o resultado da função cos

}

// Funcao para calcular o erro absoluto
long double calculoErroAbsoluto(long double sen3, long double valorReal){
    
    return abs(sen3 - valorReal); // Retornando o valor absoluto da subtracao do valor calculado com o valor real usando a função abs para retornar o modulo do valor

}

// Funcao para calcular o erro relativo
long double calculoErroRelativo(long double sen3, long double valorReal){

    return abs((sen3 - valorReal) / valorReal) * 100; // Retornando o valor relativo em porcentagem

}
