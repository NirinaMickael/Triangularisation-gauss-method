/*
    TODISOA Nirina Mickael
    L3 MISA
    Devoir Elimibat
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>
#include<cassert>
#include<algorithm>
#include<cctype>
using namespace std;
void affiche_matrix(vector<vector<double>> matrix){
    for (int i = 0; i < (int)matrix.size(); i++){
        for (int j = 0; j < (int)matrix[i].size(); j++){
            if (j != 0){
                cout << setw(7) << setprecision(6) << matrix[i][j] << " ";
            }
            else{
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
};
void affiche_colonne(vector<double> colonne){
    for (int i = 0; i < (int)colonne.size(); i++){
        cout <<"X"<<i+1<<" -> "<<colonne[i] << endl;
    }
};
vector<double> String_to_Vector(string str){
    vector<double> result;
    string r = "";
    for (int i = 0; i < (int)str.size(); i++){
        // non espace
        bool test = str[i] == ' ';
        if (!test){
            r += str[i];
        }
        else{
            result.push_back(stod(r));
            r = "";
        }
    }
    result.push_back(stod(r));
    return result;
};
vector<double> getMaxPivot(vector<vector<double>> matrix, int pos_colonne){

    int taille = (int)matrix.size();
    vector<double> stock_vect_colonne;
    double temp_max = matrix[pos_colonne][pos_colonne];
    int temp_Ipov = pos_colonne;
    vector<double> Max;
    for (int i = pos_colonne + 1; i < taille; i++){
        if (fabs(matrix[i][pos_colonne]) > temp_max){
            temp_max = fabs(matrix[i][pos_colonne]);
            temp_Ipov = i;
        }
    }
    Max.push_back(temp_max);
    Max.push_back(temp_Ipov);
    return Max;
};

vector<vector<double>> permute_Matrix(vector<vector<double>> matrix, int _lpiv, int pos_pivot_init, vector<double> &vector){
    int taille = (int)matrix.size();
    int temp = 0;
    for (int i = 0; i < taille && _lpiv != pos_pivot_init; i++){
        temp = matrix[_lpiv][i];
        matrix[_lpiv][i] = matrix[pos_pivot_init][i];
        matrix[pos_pivot_init][i] = temp;
    }
    if (_lpiv != pos_pivot_init){
        swap(vector[_lpiv], vector[pos_pivot_init]);
    }
    return matrix;
};
vector<vector<double>> triangularisation(vector<vector<double>> matrix, int k, vector<double> &vect_colonne){
    // affiche_matrix(matrix);
    int taille = (int)matrix.size();
    for (int i = k + 1; i < taille; i++){
        for (int j = k + 1; j < taille; j++){
            matrix[i][j] -= (matrix[i][k] * matrix[k][j]) / matrix[k][k];
        }
        vect_colonne[i] -= (matrix[i][k] * vect_colonne[k]) / matrix[k][k];
        matrix[i][k] = 0;
    }
    return matrix;
}

vector<double>solution(vector<vector<double>> matrix, vector<double> vect_colonne){
    int taille = (int)matrix.size();
    vector<double> resultat{0,0,0,0};
    double x = vect_colonne[taille-1]/matrix[taille-1][taille-1];
    resultat[3]=x;
    for (int i = 1; i <taille; i++){
        double ele_vect_colonne = vect_colonne[taille-(i+1)];
        double pivot  = matrix[taille-i-1][taille-i-1];
         double sum_x=0;
        for (int k = taille-i; k < taille; k++){
            sum_x += matrix[taille-(i+1)][k]*resultat[k];
        }
        x= (ele_vect_colonne-sum_x)/pivot;
        resultat[taille-i-1]=x;
    }
    return resultat;
}
int main(){
    // Notre Matrice
    vector<vector<double>> M;
    ifstream data{"data.txt"}; // variable temporaire pour stocker le flux d'entré depuis le fichier
    string temp = ""; // taille de la matrice
    double taille = 0;// vecteur colonne
    vector<double> vect_coloun;// c'est une sorte d'indication
    int pos = 0;
    while (getline(data, temp)){
        vector<double> temporary;
        bool test_input = any_of(temp.begin(), temp.end(), [](auto i){return isalpha(i);});;
        if(test_input){
            cout << "Erreur: Verifier vos fichier ,peut etre que vous avez saisir des valeur on numeric"<< endl;
            return(-1);
        }
        if (pos == 0){
            taille = stod(temp);
        }
        else if (pos >= 1 && pos <= taille){
            temporary = String_to_Vector(temp);
            M.push_back(temporary);
        }
        else{
            vect_coloun = String_to_Vector(temp);
        }
        pos++;
    }
    for (int k = 0; k < taille - 1; k++)
    {
        vector<double> Max_pivot{getMaxPivot(M, k)};// permuttons la matrice à chaque itération
        M = permute_Matrix(M, Max_pivot[1], k, vect_coloun);
        M = triangularisation(M, k, vect_coloun);
    }
    cout << "Matrice triangularisé " << endl;
    affiche_matrix(M);
    cout << "Vecteur colonne modifié " << endl;
    affiche_colonne(vect_coloun);
    cout << "Solution " << endl;
    affiche_colonne(solution(M,vect_coloun));
}