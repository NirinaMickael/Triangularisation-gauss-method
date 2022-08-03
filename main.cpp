#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    float a=0,b=0,x=0;
    int n =0;
    b = 4095.09999;
    a=b+1;
    x=1;
    for(n=1; n<10;n++){
        x= a*x-b;
        cout << "x= " << setw(20) <<setprecision(16) << x << endl;
    }
    return 0;
}