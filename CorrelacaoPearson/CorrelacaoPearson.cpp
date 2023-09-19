/* Algoritmo para calculo da correlação linear de Pearson e para achar a equação da reta interpoladora.
Feito para estudantes universitarios que precisam corrigir exercicios.
@autor: Nicolas Scarpa
Data: 12/05/2022
*******************************************************************************************************
Algorithm to calculate Pearson's linear correlation and to find the equation of the interpolating line.
Made for college students who need to correct exercises.
@author: Nicolas Scarpa
Date: 05/12/2022
*/
# include <iostream>
# include <cmath>
# include <iomanip>
using namespace std;

float r(float xIyI, float somaXi, float somaYi, float somaXi2, float somaYi2, int num);
float A(float XIYI, float Somaxi, float Somayi, float Somaxi2, float num2);
float B(float somayi, float a1, float somaxi, float num3);
void Exibir(float r, float a, float b);

int main(){

   // Declarando as variaveis. | Declaring the variables.
  int n;
  float XiYi = 0, SomaXi = 0, SomaYi = 0, SomaXi2 = 0, SomaYi2 = 0, a, pearson, b;
   
  cout << "Escreva a quantidade de numeros do Xi e do Yi: ";
  cin >> n;

  float Xi[n];
  float Yi[n];
   
   // Loop para receber os valores de Xi e Yi e efetuar os calculos. | Loop to receive the values ​​of Xi and Yi and perform the calculations.
   for(int i = 0; i < n; i++){
     cout << "Digite o valor " << i + 1 << " de Xi: "; 
     cin >> Xi[i];
     cout << "Digite o valor " << i + 1 << " de Yi: ";
     cin >> Yi[i];
     
     // Efetuando os calculos das variaveis. | Carrying out the variable calculations.
     SomaXi = SomaXi + Xi[i];
     SomaYi = SomaYi + Yi[i];
     XiYi = XiYi + (Xi[i] * Yi[i]);
     SomaXi2 = SomaXi2 + (pow(Xi[i], 2));
     SomaYi2 = SomaYi2 + (pow(Yi[i], 2));
   }
   
   // Chamando as funções e armazenando nas variaveis. | Calling functions and storing them in variables.
   r = r(XiYi,SomaXi,SomaYi,SomaXi2,SomaYi2,n);
   a = A(XiYi,SomaXi,SomaYi,SomaXi2,n);
   b = B(SomaYi,a,SomaXi,n);

   // Exibindo os resultados. | Displaying the results.
      exibir(r,a,b);

   return 0;
}

float r(float xIyI, float somaXi, float somaYi, float somaXi2, float somaYi2, int num){
    
    float p;

    p = (xIyI - (somaXi * somaYi) / num ) / sqrt((somaXi2 - (pow(somaXi, 2) / num)) * (somaYi2 - (pow(somaYi, 2) / num))); // Calculo do coeficiente de correlação | Calculation of the correlation coefficient.

    cout << fixed << setprecision(4); // Limitando as casas decimais em duas casas. | Limiting decimal places to two places.

    if (p == 1){
      cout << "Correlacao perfeita positiva" << endl;
    }else if (p == -1){
      cout << "Correlacao perfeita negativa" << endl;
    }else if (p >= 0 && p <= 0.3){
      cout << "Correlacao nula" << endl;
    }else if (p > 0.3 && p <= 0.6){
      cout << "Correlacao fraca" << endl;
    }else if (p > 0.6 && p < 1){
      cout  << "Correlacao forte" << endl;
    }else{
      cout << "Inexistente" << endl;
    }
    
    return p;
}

float A(float XIYI, float Somaxi, float Somayi, float Somaxi2, float num2){
   
   cout << fixed << setprecision(4); 
   float a;
  
   a = (XIYI - (Somaxi * Somayi) / num2) / (Somaxi2 - (pow(Somaxi, 2) / num2)); // Calculo do a | Calculation of the a.

   return a;

}

float B(float somayi, float a1, float somaxi, float num3){

    float b;

    cout << fixed << setprecision(4);

    b = (somayi / num3) - ((a1 * somaxi) / num3); // Calculo do b | Calculation of the b

    return b;
}

void Exibir(float r, float a, float b){
    
    cout << "************************" << endl;
    cout << "r = " << r << endl;
    cout << "************************" << endl;
    cout << "a = " << a << endl;
    cout << "************************" << endl;
    cout << "b = " << b << endl;
    cout << "************************" << endl;
   
   cout << "A equacao da reta interpoladora eh: |y = " << a << "x - (" << b << ")" << "|"; 
    
}