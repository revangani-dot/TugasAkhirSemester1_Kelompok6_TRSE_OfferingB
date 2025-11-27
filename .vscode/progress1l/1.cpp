#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

void haripercobaan (string hari, string ruangan){
	cout << "Nama Ruangan: "<<ruangan<<endl;
	cout << "Hari : "<<hari<<endl;
}
void hitungTHI (double temp, int RH, double &HTI){
	HTI = (0.8*temp)+ (RH/100)*(temp-14.4)+46,4;
}
double ratarata (double total, double &rata){
	rata = total/6;
}