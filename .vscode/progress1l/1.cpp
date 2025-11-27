#include <iostream>
#include <iomanip>
using namespace std;

double hitungTHI(double temp, double rh);
string statusTHI(double thi) ;
string statusCO2(double c) ;
int hitungAQI(double pm) ;
string statusAQI(int aqi);


int main (){
	string hari, ruangan;
	
	double pm25[6], co2[6],suhu[6],rh[6];
	int aqi[6];
	double thi[6];
	string periode [6] = {"00.00-04.00", "04.00-08.00", "08.00-12.00", "12.00-16.00", "16.00-20.00", "20.00=24.00"};
	double totalPM = 0, totalco2 = 0, totalsuhu = 0, totalrh = 0;
	for (int i=0; i<6; i++){
		cout << "Pengukuran PM2.5 pada (mikro g/m^3)"<< periode[i]<<" : ";
		cin >> pm25[i];
		totalPM += pm25[i];
		double rataPM = totalPM/6;
		
		cout << "Pengukuran Co2 pada (ppm)"<< periode[i]<<" : ";
		cin >> co2[i];
		totalco2 += co2[i];
		double rataco2 = totalco2/6;
		
		cout << "Pengukuran Suhu pada (derajat C)"<< periode[i]<<" : ";
		cin >> suhu[i];
		totalsuhu += suhu[i];
		double ratasuhu = totalsuhu/6;
		
		cout << "Pengukuran RH (%) pada "<< periode[i]<<" : ";
		cin >> rh[i];
		totalrh+= rh[i];
		double rataRH = totalrh/6;
		
		cout << endl;
	}
	for (int j=0; j<6; j++){
		thi [j]= hitungTHI(suhu[j], rh[j]);
		aqi [j]= hitungAQI(pm25 [j]);
	}
	
}
double hitungTHI(double temp, double rh) {
    return 0.8 * temp + (rh / 100.0) * (temp - 14.4) + 46.4;
}

string statusTHI(double thi) {
    if (thi < 27) return "Nyaman";
    else if (thi < 29) return "Agak Tidak Nyaman";
    else if (thi < 32) return "Tidak Nyaman";
    else return "Bahaya Heat Stress";
}
string statusCO2(double c) {
    if (c <= 800) return "Baik";
    else if (c <= 1200) return "Sedang";
    else return "Buruk (Ventilasi Kurang)";
}
int hitungAQI(double pm) {
    double Clow, Chigh, Ilow, Ihigh;

    if (pm <= 12.0) { Clow = 0; Chigh = 12; Ilow = 0; Ihigh = 50; }
    else if (pm <= 35.4) { Clow = 12.1; Chigh = 35.4; Ilow = 51; Ihigh = 100; }
    else if (pm <= 55.4) { Clow = 35.5; Chigh = 55.4; Ilow = 101; Ihigh = 150; }
    else if (pm <= 150.4) { Clow = 55.5; Chigh = 150.4; Ilow = 151; Ihigh = 200; }
    else if (pm <= 250.4) { Clow = 150.5; Chigh = 250.4; Ilow = 201; Ihigh = 300; }
    else { Clow = 250.5; Chigh = 500; Ilow = 301; Ihigh = 500; }

    return Ilow + ((pm - Clow) / (Chigh - Clow)) * (Ihigh - Ilow);
}
string statusAQI(int aqi) {
    if (aqi <= 50) return "Baik";
    else if (aqi <= 100) return "Sedang";
    else if (aqi <= 150) return "Tidak Sehat (Sensitif)";
    else if (aqi <= 200) return "Tidak Sehat";
    else return "Sangat Tidak Sehat";
}
