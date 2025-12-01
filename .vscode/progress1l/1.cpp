#include <iostream>
#include <iomanip>

using namespace std;

double hitungTHI(double temp, double rh);
string statusTHI(double thi) ;
string statusCO2(double c) ;
int hitungAQI(double pm) ;
string statusAQI(int aqi);
string rekomendasiHarian(double rataAQI, double rataCO2, double rataTHI);

int main (){
	string hari, ruangan;
	
	double pm25[6], co2[6],suhu[6],rh[6];
	int aqi[6];
	double thi[6];
	string periode [6] = {"00.00-04.00", "04.00-08.00", "08.00-12.00", "12.00-16.00", "16.00-20.00", "20.00=24.00"};
	double totalPM = 0, totalco2 = 0, totalsuhu = 0, totalrh = 0;
	string statusaqi[6], statusco2[6],statusthi[6];
	double rataPM=0, ratasuhu=0, rataco2=0, rataRH=0;
	cout<< "Hari : ";
	cin>> hari;
	cout<<"Ruangan :";
	cin >>ruangan;
	cout<< endl;
	cout<<endl;
	for (int i=0; i<6; i++){
		cout << "Pengukuran PM2.5 pada (mikro g/m^3) pada "<< periode[i]<<" : ";
		cin >> pm25[i];
		totalPM += pm25[i];
		double rataPM = totalPM/6;
		
		cout << "Pengukuran Co2 pada (ppm) pada "<< periode[i]<<" : ";
		cin >> co2[i];
		totalco2 += co2[i];
		double rataco2 = totalco2/6;
		
		cout << "Pengukuran Suhu pada (derajat C) pada "<< periode[i]<<" : ";
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
		statusaqi [j]=statusAQI(aqi[j]);
		statusco2 [j]= statusCO2 (co2[j]);
		statusthi [j]= statusTHI(thi[j]);
	}
	double rataTHI = (thi[0]+thi[1]+thi[2]+thi[3]+thi[4]+thi[5])/6;
	double rataAQI = (aqi[0]+aqi[1]+aqi[2]+aqi[3]+aqi[4]+aqi[5])/6;
	    cout << "=========================================== Laporan Kualitas Udara Harian Ruang "<<ruangan<<" pada Hari " <<hari<<" ==========================================="<<endl;
    cout << left << setw(15) << "Waktu Pengukuran"
         << setw(12) << "PM2.5"
         << setw(8)  << "AQI"
         << setw(28) << "Status AQI"
         << setw(12) << "CO2"
         << setw(28) << "Status CO2"
         << setw(8)  << "Suhu"
         << setw(8)  << "RH"
         << setw(10) << "THI"
         << setw(28) << "Status THI"
         << endl;

    cout << "------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

    for (int i = 0; i < 6; i++) {
        cout << left << setw(15) << periode[i]
             << setw(12) << pm25[i]
             << setw(8)  << aqi[i]
             << setw(28) << statusaqi[i]
             << setw(12) << co2[i]
             << setw(28) << statusco2[i]
             << setw(8)  << suhu[i]
             << setw(8)  << rh[i]
             << setw(10) << fixed << setprecision(1) << thi[i]
             << setw(28) << statusthi[i]
             << endl;
    }

    cout << "================================================================================================================================================"<<endl;
	cout <<endl;
	cout <<endl;
	cout << "==================================== DATA STATISIK RATA-RATA HARIAN ===================================="<<endl;
	cout <<endl;
	cout<<endl;
	cout << "Rata-rata partikel udara 2,5 mikrometer (PM2.5)	 			: "<<rataPM<<" mikro g/m^3 "<<endl;
	cout << "Rata-rata Indeks Kualitas Udara (AQI)					: "<<rataAQI<<" ("<<statusAQI(rataAQI)<<")"<<endl;
	cout << "Rata-rata konsentrasi karbondioksida (Co2)				: "<<rataco2<<" ppm"<<endl;
	cout << "Rata-rata suhu								: "<<ratasuhu<<" derajat Celcius"<<endl;
	cout << "Rata-rata kelembapan relatih (RH)					: "<<rataRH<<" %"<<endl;
	cout << "Rata-rata tingkat kenyamanan panas (THI)				: "<<rataTHI<<" ("<<statusTHI(rataTHI)<<")"<<endl;
	cout << "---------------------------------------------------------------------------------------------------------"<<endl;
	cout <<endl;
	cout <<endl;
	cout << "==================================== !!!!!!!!!! REKOMENDASI !!!!!!!!!! ===================================="<<endl;
	string hasil = rekomendasiHarian(rataAQI, rataco2, rataTHI);
	cout << hasil;

	
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
string rekomendasiHarian(double rataAQI, double rataCO2, double rataTHI) {
    string rec = "";
    if (rataAQI <= 50) {
        rec += "- Udara sangat baik. Aktivitas luar ruangan aman.\n";
        rec += "- Ventilasi alami sudah optimal.\n";
    }
    else if (rataAQI <= 100) {
        rec += "- Udara cukup baik namun sensitif mungkin sedikit terpengaruh.\n";
        rec += "- Kurangi aktivitas fisik berat di luar.\n";
    }
    else if (rataAQI <= 150) {
        rec += "- Kualitas udara kurang sehat.\n";
        rec += "- Disarankan memakai masker terutama bagi lansia & anak kecil.\n";
        rec += "- Hindari olahraga berat di luar ruangan.\n";
    }
    else if (rataAQI <= 200) {
        rec += "- Udara tidak sehat.\n";
        rec += "- Gunakan masker saat di luar.\n";
        rec += "- Perbanyak kegiatan di dalam ruangan.\n";
    }
    else {
        rec += "- Udara sangat berbahaya.\n";
        rec += "- Hindari keluar rumah.\n";
        rec += "- Gunakan air purifier jika ada.\n";
    }

    
    if (rataCO2 <= 800) {
        rec += "- Kadar CO2 baik, ventilasi memadai.\n";
        rec += "- Ruangan nyaman untuk belajar/kerja.\n";
    }
    else if (rataCO2 <= 1200) {
        rec += "- Ventilasi perlu ditambah.\n";
        rec += "- Disarankan buka pintu/jendela.\n";
    }
    else if (rataCO2 <= 2000) {
        rec += "- CO2 tinggi! Ruangan pengap.\n";
        rec += "- Buka jendela dan hidupkan kipas.\n";
        rec += "- Kurangi jumlah orang dalam ruangan.\n";
    }
    else {
        rec += "- CO2 sangat tinggi (berbahaya).\n";
        rec += "- Wajib tingkatkan ventilasi.\n";
        rec += "- Segera kosongkan ruangan jika perlu.\n";
    }

    
    if (rataTHI < 27) {
        rec += "- Kondisi suhu nyaman.\n";
        rec += "- Tidak perlu perlakuan khusus.\n";
    }
    else if (rataTHI < 29) {
        rec += "- Agak panas.\n";
        rec += "- Gunakan kipas atau ventilasi silang.\n";
    }
    else if (rataTHI < 32) {
        rec += "- Panas tidak nyaman.\n";
        rec += "- Minum air cukup.\n";
        rec += "- Hindari aktivitas berat.\n";
    }
    else if (rataTHI < 35) {
        rec += "- Panas ekstrem.\n";
        rec += "- Risiko heat stress meningkat.\n";
        rec += "- Gunakan AC atau pendingin.\n";
    }
    else {
        rec += "- Sangat berbahaya! Heat stroke mungkin terjadi.\n";
        rec += "- Segera cari ruangan dingin / ber-AC.\n";
        rec += "- Minum air & hindari panas matahari.\n";
    }

    return rec;
}
