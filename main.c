/*Saya Julian Dwi Satrio dengan NIM 2300484 mengerjakan evaluasi Tugas Masa Depan 
dalam mata kuliah Algoritma dan Pemrograman II untuk keberkahanNya maka saya 
tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.*/

#include "header.h"

int main() {
    char pita[501]; // variabel pita inputan
    int stop = 0; // variabel looping

    startdbms(); // jalankan animasi start dbms
    // lakukan looping untuk input dan pembacaan query
    while(stop == 0){ // gunakan variabel looping tado
        printf("dbms [joule.io] on %s >> ", __TIME__); // print biar keren pake realtime
        scanf(" %500[^\n]s", pita); // scan input
        
        // kondisi command exit dari database
        if(strcmp(pita, "jangan lupa bahagia hari ini;") == 0 || strcmp(pita, "keluar;") == 0){
            goodbyemessage(); // tampilkan message goodbye
            printf("Byee~~\n"); // print byeeeee
            stop = 1; // stop menjadi 1
        }
        // kondisi terdapat ';' dalam inputan
        else if(carieop(pita) == 1){ // jika terdapat ';' maka jalankan proses read query
            readquery(pita);
        }
        // kondisi tidak terdapat eop (;)
        else{
            displayerror(1111); // tampilkan error tentang ';'
        }
    }

    return 0;
}