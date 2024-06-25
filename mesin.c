/*Saya Julian Dwi Satrio dengan NIM 2300484 mengerjakan evaluasi Tugas Masa Depan 
dalam mata kuliah Algoritma dan Pemrograman II untuk keberkahanNya maka saya 
tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.*/

#include "header.h"
#include <time.h> // include time.h untuk prosedur waktu
#include <stdlib.h> // include stdlib untuk system cls

#define RED         "\x1b[31m" // define warna merah
#define GREEN       "\x1b[32m" // define warna hijau
#define CYAN        "\x1b[36m" // define warna cyan
#define YELLOW      "\x1b[33m" // define warna kuning
#define COLORRESET  "\x1b[0m" // define reset warna kembali hitam

int idx; // idx untuk pindah huruf
int wlen; // panjang dari cw
char cw[256]; // penampung kata yang sedang dicek (current word)

char table[256]; // untuk menampung nama tabel
int target = 0; // untuk menampung target atau posisi id yang dicari
int jmldonatur = 0; // counter data donatur
int jmlpanti = 0; // counter data panti
int jmljoin = 0; // counter data join


t_biasa donatur[300]; // variabel global struct donatur
t_biasa panti[300]; // variabel global struct panti
t_join join[300]; // variabel global struct join

// prosedur animasi tunggu
void wait(float x){
    time_t start; // ambil fungsi dari time.h sebagai waktu mulai
    time_t current; // ambil waktu saat ini
    time(&start); // mulai waktu
    do{
        time(&current);
    }while(difftime(current,start) < x); // mendelay waktu selama kurang dari satu x selisih waktunya
}

// prosedur header atau tampilan awal dbms
void startdbms(){
    system("cls"); // clear dulu layar biar rapih
    /*print pola dengan pattern
       print pola
       delay 1 detik
       dst..*/

    wait(1);    
    printf("              +~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~            \n");
    wait(1);
    printf("        +~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+       \n");
    wait(1);
    printf("    --------------------------------------------------    \n");
    wait(1);
    printf("    :   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  :    \n");
    wait(1);
    printf("    :  ^  Selamat Datang di DBMS sederhana [joel] ^  :    \n");
    wait(1);
    printf("    :  ^     Query Dapat diakhiri dengan ';'      ^  :    \n");
    wait(1);
    printf("    :  ^      Copyright (C) 2024 juliandwii       ^  :    \n");
    wait(1);
    printf("    :  ^               Version 1.1                ^  :    \n");
    wait(1);
    printf("    :   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   :    \n");
    wait(1);
    printf("    --------------------------------------------------    \n");
    wait(1);
    printf("        +~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+       \n");
    wait(1);
    printf("              +~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~            \n");
    wait(1);
}

// nyalakan mesin
void start(char pita[]){
    // set index dan panjang kata menjadi 0
    idx = 0;
    wlen = 0;

    while (pita[idx] == ' '){ // ignore blank
        idx++;
    }

    // ambil kata masukkan dalam current word
    while ((pita[idx] != ' ') && (eop(pita) == 0)){
        cw[wlen] = pita[idx];
        wlen++;
        idx++;
    }
    cw[wlen] = '\0'; // akhiri dengan null terminator
}

// reset current word
void reset(){
    wlen = 0; // kembalikan panjang kata menjadi 0
    cw[wlen] = '\0'; // set current word menjadi null (siap diisi)
}

// cek eop
int eop(char pita[]){
    if(pita[idx] == ';'){ // jika ';' return 1
        return 1;
    }
    else{
        return 0; // jika bukan ';' kembalikan 0
    }
}

// prosedur untuk error handling
int carieop(char pita[]){
    // tujuannya adalah untuk memastikan di input pita query terdapat EOP / ';'
    idx = 0; // set idx jadi 0
    int found = 0; // marking founf
    while(pita[idx] != '\0'){ // looping sampai ujung (null terminator)
        if(pita[idx] == ';'){ // jika paling ujung menemukan ';' 
            found = 1; // maka nilai found berubah
        }
        idx++;
    }
    // kembalikan nilai found
    return found;
}

// pindah next kata
void inc(char pita[]){
    wlen = 0; // set panjang kata jadi 0 (memastikan)

    while (pita[idx] == ' '){ // ignore blank
        idx++;
    }

    // masukkan kata baru
    while ((pita[idx] != ' ') && (eop(pita) == 0)){
        cw[wlen] = pita[idx];
        wlen++;
        idx++;
    }
    cw[wlen] = '\0'; // akhiri lagi
}

// mengembalikan current word
char* getcw(){
    return cw;
}

// mengembalikan panjang current word
int getlen(){
    return wlen;
}

// prosedur mencari primary key
int BinarySearch(int n, char dicari[], t_biasa source[]){
    // gunakan binary search
    int i = 0, j = n - 1, mid;
    int found = 0;

    while(found == 0 && i <= j){
        mid = (i + j) / 2;
        if (strcmp(source[mid].id, dicari) == 0){ // cari primary key sesuai param
            found = 1; // jika ketemu found menjadi 1
            target = mid; // lalu variabel global target akan berubah menjadi idx data yang ditemukan
        }
        else{
            if (strcmp(source[mid].id, dicari) > 0){
                j = mid - 1;
            }
            else{
                i = mid + 1;
            }
        }
    }
    
    return found; // kembalikan nilai found
}

// prosedur cek foreign key (sedang tertaut apa tidak)
int cekforeignkey(int n, char dicari[], t_biasa source[]){
    int i = 0, j = n - 1, mid;
    int found = 0;

    while(found == 0 && i <= j){
        mid = (i + j) / 2;
        if (strcmp(source[mid].att3, dicari) == 0){ // sama seperti diatas namun att 3 yang dibandingkan
            found = 1; // cari apakah ketemu apa tidak saja
        }
        else{
            if (strcmp(source[mid].att3, dicari) > 0){
                j = mid - 1;
            }
            else{
                i = mid + 1;
            }
        }   
    }
    
    return found; // kembalikan nilai found
}

// proses sorting data (agar bisa menggunakan binary search)
void sorting(int n, t_biasa source[]){
    // gunakan selection sort
    int i, j, min;
    t_biasa temp;
    for(i=0; i<n-1; i++){
        min = i;
        for(j= (i+1); j<n; j++){
            if(strcmp(source[min].id, source[j].id) > 0){ // sorting berdasarkan id atau primary key 
                min = j;
            }
        }

        temp = source[i];
        source[i] = source[min];
        source[min] = temp;
    }
}

void readfile(char filename[], t_biasa source[]){
    int n = 0; // counter jumlah data

    FILE *fData; // koneksi untuk file yang akan dibuka
    fData = fopen(filename, "r"); // buka file dengan mode read
    
    // scan baris pertama data
    int returnVal = fscanf(fData, "%s %s %s %s", source[n].id, source[n].att1, source[n].att2, source[n].att3);

    // cek apakah baris pertama EOF
    if (strcmp(source[n].id, "####") == 0 || returnVal == EOF){
        // jika iya maka merupakan file kosong
        printf("File Kosong\n");
    }
    else{
        // jika bukan EOF maka akan langsung proses read data
        while (strcmp(source[n].id, "####") != 0){
            n++; // maju ke data berikutnya
            fscanf(fData, "%s %s %s %s", source[n].id, source[n].att1, source[n].att2, source[n].att3);
        }
    }

    // melakukan penyesuaian jumlah data nya pindahkan ke variabel jml
    if (strcmp(filename, "tdonatur.txt") == 0){ // jika tabel adalah tabel donatur
        jmldonatur = n;
    }
    else if (strcmp(filename, "tpantiasuhan.txt") == 0){ // jika tabel adalah tabel panti asuhan
        jmlpanti = n;
    }
    // tutup kembali file
    fclose(fData);
}

void writeFile(int n, t_biasa source[], char filename[]){
    FILE *fTemp; // buka koneksi pointer ke file 
    fTemp = fopen(filename, "w"); // buka file dengan mode write
   
    // tulis data ke file
    for (int i = 0; i < n; i++){
        fprintf(fTemp, "%s %s %s %s\n", source[i].id, source[i].att1, source[i].att2, source[i].att3);
    }

    // beri dummy/EOF dipaling akhir
    fprintf(fTemp, "%s %s %s %s\n", "####", "####", "####", "####");

    // tutup file kembali
    fclose(fTemp);
}

// prosedur untuk print error handling
void displayerror(int n){ // menggunakan parameter angka yang tinggal diisi
    printf(RED); // ubah dulu warna menjadi merah
    if(n == 1101){ // kondisi atribut query tidak lengkap
        printf("Error: Nilai atribut tidak lengkap. Silakan lengkapi semua nilai atribut yang diperlukan! (Error Code: 1101)\n");
    }
    else if(n == 1102){ // kondisi data tidak ditemukan dalam tabel (error input primary key saat update atau delete)
        printf("Error: ID '%s' tidak ditemukan dalam tabel '%s'. Pastikan ID yang dimasukkan benar! (Error Code: 1102)\n", getcw(), table);
    }
    else if(n == 1103){ // kondisi atribut yang diberikan terlalu banyak dalam inputan
        printf("Error: Nilai yang dimasukkan melebihi batas spesifikasi tabel. Periksa kembali nilai yang diinput! (Error Code: 1103)\n");
    }
    else if(n == 1104){ // kondisi ketika input primary key yang sudah ada
        printf("Error: ID '%s' sudah ada di dalam tabel '%s'. Gunakan ID yang berbeda! (Error Code: 1104)\n", getcw(), table);
    }
    else if(n == 1105){ // kondisi menginput nama tabel yang tidak ada
        printf("Error: Tabel tidak ditemukan. Pastikan nama tabel yang dimasukkan benar! (Error Code: 1105)\n");
    }
    else if(n == 1106){ // kondisi nilai yang dimasukkan melebihi batas spesifikasi perintah misal : DELETE [tabel] [id] [nama] (cukup id saja)
        printf("Error: Nilai yang dimasukkan melebihi batas spesifikasi perintah. Periksa kembali nilai yang diinput! (Error Code: 1106)\n");
    }
    else if(n == 1107){ // kondisi gagal menghapus karena sedang menjadi foreign key di tabel lain
        printf("Error: Gagal menghapus. ID '%s' sedang tertaut di tabel lain. Hapus keterkaitan sebelum mencoba lagi! (Error Code: 1107)\n", getcw());
    }
    else if(n == 1108){ // kondisi perintah join tidak benar
        printf("Error: Tidak dapat melakukan join. Periksa nama tabel dan pastikan keduanya benar! (Error Code: 1108)\n");
    }
    else if(n == 1109){ // kondisi memasukkan foreign key yang tidak ada primary key nya di tabel lain
        printf("Error: ID '%s' tidak ditemukan dalam tabel 'tpantiasuhan'. Pastikan Foreign Key yang dimasukkan benar! (Error Code: 1109)\n", getcw());
    }
    else if(n == 1110){ // kondisi query yang dimasukkan salah misal : INSERT seharusnya INPUT
        printf("Error: Query yang dimasukkan salah. Silakan masukkan query dengan benar! (Error Code: 1110)\n");
    }
    else if(n == 1111){ // kondisi error tidak ada EOP pada pita inputan
        printf("Error: Harap tambahkan tanda titik koma (;) di akhir Inputan Anda! (Error Code: 1111)\n");
    }
    printf(COLORRESET); // reset kembali warna nya
}

void goodbyemessage(){
    printf(CYAN); // Ubah warna teks menjadi cyan agar lebih menarik
    
    // Deklarasikan array string yang akan diprint, sebanyak 8 string
    char kumpulanString[8][100] ={
        "Barca Taun Depan Tsunami Thropy!!!",
        "TMD ALPRO 2 sangat menyenangkan!!",
        "Bismillah Calon Asprak Dasprog 2024",
        "Jangan Lupa Bersyukur Hari Ini~",
        "Terimakasih Bu Rosa 2 Semester Nyaaa!",
        "See u di semester 3 mentemenn!",
        "Selamat Berliburrrr",
        "Winrate Alpro 2 Ku 100% Alprotulation!!"
    };

    // Hitung jumlah string dalam array kumpulanString
    int jumlahString = sizeof(kumpulanString) / sizeof(kumpulanString[0]);

    // Inisialisasi seed untuk fungsi rand() menggunakan waktu saat ini
    srand(time(NULL));
    
    // Pilih indeks acak dari array kumpulanString
    int indeksAcak = rand() % jumlahString;
    
    // Print string yang dipilih secara acak dari array
    printf("%s\n", kumpulanString[indeksAcak]);
    
    // Kembalikan warna teks ke warna default
    printf(COLORRESET);
}

// Prosedur untuk mencetak tabel biasa
void printtable(int tab, t_biasa source[], int n){
    char id[50], coll1[50], coll2[50], coll3[50];

    // Tentukan header kolom berdasarkan nilai tab
    if(tab == 1){
        strcpy(id, "Id Donatur");
        strcpy(coll1, "Nama Donatur");
        strcpy(coll2, "Pekerjaan");
        strcpy(coll3, "Id Panti");
    }
    else if(tab == 2){
        strcpy(id, "Id Panti");
        strcpy(coll1, "Nama Panti Asuhan");
        strcpy(coll2, "Lokasi");
        strcpy(coll3, "No Telp");
    }

    // Hitung panjang maksimum setiap kolom header
    int lenid = strlen(id);
    int lencoll1 = strlen(coll1);
    int lencoll2 = strlen(coll2);
    int lencoll3 = strlen(coll3);

    // Periksa setiap data untuk menemukan panjang maksimum dari setiap kolom
    for(int i = 0; i < n; i++){
        if(strlen(source[i].id) > lenid){
            lenid = strlen(source[i].id);
        }
        if(strlen(source[i].att1) > lencoll1){
            lencoll1 = strlen(source[i].att1);
        }
        if(strlen(source[i].att2) > lencoll2){
            lencoll2 = strlen(source[i].att2);
        }
        if(strlen(source[i].att3) > lencoll3){
            lencoll3 = strlen(source[i].att3);
        }
    }

    // Cetak garis horizontal untuk header tabel
    printf("~");
    for(int i = 0; i < lenid + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll1 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll2 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll3 + 4; i++){
        printf("~");
    }
    printf("~\n");

    // Cetak header kolom tabel
    printf("| %s ", id);
    for(int i = strlen(id); i < lenid + 2; i++){
        printf(" ");
    }
    printf("| %s ", coll1);
    for(int i = strlen(coll1); i < lencoll1 + 2; i++){
        printf(" ");
    }
    printf("| %s ", coll2);
    for(int i = strlen(coll2); i < lencoll2 + 2; i++){
        printf(" ");
    }
    printf("| %s ", coll3);
    for(int i = strlen(coll3); i < lencoll3 + 2; i++){
        printf(" ");
    }
    printf("|\n");

    // Cetak garis horizontal di bawah header tabel
    printf("~");
    for(int i = 0; i < lenid + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll1 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll2 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll3 + 4; i++){
        printf("~");
    }
    printf("~\n");

    // Cetak setiap baris data tabel
    for(int i = 0; i < n; i++){
        printf("| %s ", source[i].id);
        for(int j = strlen(source[i].id); j < lenid + 2; j++){
            printf(" ");
        }
        printf("| %s ", source[i].att1);
        for(int j = strlen(source[i].att1); j < lencoll1 + 2; j++){
            printf(" ");
        }
        printf("| %s ", source[i].att2);
        for(int j = strlen(source[i].att2); j < lencoll2 + 2; j++){
            printf(" ");
        }
        printf("| %s ", source[i].att3);
        for(int j = strlen(source[i].att3); j < lencoll3 + 2; j++){
            printf(" ");
        }
        printf("|\n");
    }

    // Cetak garis horizontal di bawah tabel
    printf("~");
    for(int i = 0; i < lenid + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll1 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll2 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll3 + 4; i++){
        printf("~");
    }
    printf("~\n");
}

// proses insert data
void insertdata(char pita[]){
    t_biasa temp; // buat struct t_biasa sebagai temp
    strcpy(temp.id, getcw()); // copy id (posisi current word)
    inc(pita); // increment kata
    if(eop(pita) == 1){ // jika eop maka
        displayerror(1101); // print error atribut kurang
    }
    else{ // jika bukan
        strcpy(temp.att1, getcw()); // copy kata selanjutnya kedalam atribut 1
        inc(pita); // increment kata lagi
        if(eop(pita) == 1){ // jika eop 
            displayerror(1101); // error atribut kurang
        }
        else{ // jika bukan
            strcpy(temp.att2, getcw()); // copy kata selanjutnya ke atribut 2
            inc(pita); // increment lagi
            if(eop(pita) == 1){ // jika sudah di eop (ujung query)
                if(strcmp(table, "tdonatur") == 0){ // kondisi input data ke tabel donatur
                    int found = BinarySearch(jmlpanti, getcw(), panti); // cari apakah foreign key nya yang dimasukkan ada pada tabel lain
                    if(found == 1){ // jika ada
                        strcpy(temp.att3, getcw()); // copy kata ke atribut 3
                        // kondisi struct terisi semua

                        donatur[jmldonatur] = temp; // masukkan temp ke idx baru di tabel donatur
                        jmldonatur++; // jumlah donatur bertambah

                        printf(GREEN "Query OK!\n" COLORRESET); // print hasil query ok
                        printf(GREEN "Berhasil menambahkan record '%s' kedalam tabel '%s'\n\n" COLORRESET, temp.id, table); // print berhasil memasukkan data

                        printf(YELLOW "Menampilkan '%d' Record\n" COLORRESET, jmldonatur);
                        printtable(1, donatur, jmldonatur); // tampilkan table
                    }
                    else{ // error
                        displayerror(1109); // jika  foerign key tidak ketemu maka print error
                    }
                }
                else{
                    // kondisi tabel yang diisi adalah tabel panti asuhan
                    strcpy(temp.att3, getcw()); // copy kata ke atribut 3

                    panti[jmlpanti] = temp; // masukkan temp ke idx baru tabel panti
                    jmlpanti++; // jumlah panti bertambah

                    printf(GREEN "Query OK!\n" COLORRESET); // print query ok
                    printf(GREEN "Berhasil menambahkan record '%s' kedalam tabel '%s'\n\n" COLORRESET, temp.id, table); // print berhasil menambahkan data

                    printf(YELLOW "Menampilkan %d Record\n" COLORRESET, jmlpanti);
                    printtable(2, panti, jmlpanti); // tampilkan table
                }
            }
            else{ // jika bukan eop 
                displayerror(1103); // maka print error melebihi spesifikasi tabel
            }
        }
    }
}

// proses membaca query INPUT
void controllerinsert(char pita[]){
    inc(pita); // increment kata naik ke tabel 
    if(strcmp(getcw(), "tdonatur") == 0 || strcmp(getcw(), "tpantiasuhan") == 0){ // jika tabel diantara tdonatur / tpantiasuhan
        strcpy(table, getcw()); // copy current word kedalam variabel global tabel (mengamankan tabel)
        if(eop(pita) == 1){ // jika sudah eop maka error
            displayerror(1101); // error nilai atribut kurang
        }
        else{ // jika bukan maka
            inc(pita); // increment kata lagi naik ke value berikutnya
            if(eop(pita) == 1){ // jika eop
                displayerror(1101); // error nilai atribut kurang
            }
            else{ // jika bukan
                // proses memasukkan data
                if(strcmp(table, "tdonatur") == 0){ // kondisi tabel sebelumnya adalah tdonatur
                    int ketemu = BinarySearch(jmldonatur, getcw(), donatur); // cari primary key (current word) di tabel donatur
                    if(ketemu == 0){ // jika tidak ditemukan
                        insertdata(pita); // masukkan data
                    }
                    else{
                        displayerror(1104); // jika sudah ditemukan print error
                    }
                }
                else{ // kondisi lainnya adalah tabel panti asuhan
                    int ketemu = BinarySearch(jmlpanti, getcw(), panti); // cari juga primary key di tabel panti
                    if(ketemu == 0){ // jika tidak ditemukan
                        insertdata(pita); // lakukan insert data
                    }
                    else{
                        displayerror(1104); // jika ditemukan maka print error 
                    }
                }
            }
        }
    }
    else{
        displayerror(1105); // kondisi error tabel tidak ditemukan
    }
}

// proses update data
void updatedata(char pita[]){
    int idxupdate = target; // menyimpan indeks yang akan diupdate
    t_biasa temp; // struct sementara untuk menyimpan data yang diupdate
    strcpy(temp.id, getcw()); // mengcopy kata saat ini ke dalam temp
    inc(pita); // pindah ke kata berikutnya
    if(eop(pita) == 1){ // jika sudah akhir pita, error
        displayerror(1101); // tampilkan error atribut kurang
    }
    else{
        strcpy(temp.att1, getcw()); // copy kata saat ini ke atribut 1
        inc(pita); // pindah ke kata berikutnya
        if(eop(pita) == 1){ // jika sudah akhir pita, error
            displayerror(1101); // tampilkan error atribut kurang
        }
        else{
            strcpy(temp.att2, getcw()); // copy kata saat ini ke atribut 2
            inc(pita); // pindah ke kata berikutnya
            if(eop(pita) == 1){
                if(strcmp(table, "tdonatur") == 0){ // jika tabel adalah tdonatur
                    int found = BinarySearch(jmlpanti, getcw(), panti); // cari foreign key di tabel panti
                    if(found == 1){ // jika ditemukan
                        strcpy(temp.att3, getcw()); // copy kata saat ini ke atribut 3

                        donatur[idxupdate] = temp; // update data di indeks yang ditentukan
                        printf(GREEN "Query OK!\n" COLORRESET); // tampilkan pesan sukses
                        printf(GREEN "Berhasil mengupdate record '%s' di dalam tabel '%s'\n\n" COLORRESET, temp.id, table);

                        printf(YELLOW "Menampilkan '%d; Record\n" COLORRESET, jmldonatur);
                        printtable(1, donatur, jmldonatur); // tampilkan tabel donatur
                    }
                    else{ // jika foreign key tidak ditemukan, error
                        displayerror(1109);
                    }
                }
                else{ // jika tabel adalah tpantiasuhan
                    printf("%s\n", getcw());
                    strcpy(temp.att3, getcw()); // copy kata saat ini ke atribut 3

                    panti[idxupdate] = temp; // update data di indeks yang ditentukan
                    printf(GREEN "Query OK!\n" COLORRESET); // tampilkan pesan sukses
                    printf(GREEN "Berhasil mengupdate record '%s' di dalam tabel '%s'\n" COLORRESET, temp.id, table);

                    printf(YELLOW "Menampilkan '%d' Record\n" COLORRESET, jmlpanti);
                    printtable(2, panti, jmlpanti); //tampilkan tabel panti
                }
            }
            else{ // jika kata melebihi spesifikasi tabel, error
                displayerror(1103);
            }
        }
    }
}

// proses membaca query UPDATE
void controllerupdate(char pita[]){
    inc(pita); // pindah ke nama tabel
    if(strcmp(getcw(), "tdonatur") == 0 || strcmp(getcw(), "tpantiasuhan") == 0){ // cek apakah tabel merupakan tdonatur atau tpantiasuhan
        strcpy(table, getcw()); // simpan nama tabel ke variabel global
        if(eop(pita) == 1){ // jika sudah akhir pita, error
            displayerror(1101); // tampilkan error atribut kurang
        }
        else{
            inc(pita); // pindah ke ID
            if(eop(pita) == 1){ // jika sudah akhir pita, error
                displayerror(1101); // tampilkan error atribut kurang
            }
            else{
                if(strcmp(table, "tdonatur") == 0){ // jika tabel adalah tdonatur
                    int ketemu = BinarySearch(jmldonatur, getcw(), donatur); // cari primary key di tabel donatur
                    if(ketemu == 1){ // jika ditemukan
                        updatedata(pita); // lakukan update data
                    }
                    else{ // jika tidak ditemukan, error
                        displayerror(1102);
                    }
                }
                else{ // jika tabel adalah tpantiasuhan
                    int ketemu = BinarySearch(jmlpanti, getcw(), panti); // cari primary key di tabel panti
                    if(ketemu == 1){ // jika ditemukan
                        updatedata(pita); // lakukan update data
                    }
                    else{ // jika tidak ditemukan, error
                        displayerror(1102);
                    }
                }
            }
        }
    }
    else{ // jika tabel tidak ditemukan, error
        displayerror(1105);
    }
}

// proses hapus data
void deletedata(char pita[], int n, t_biasa source[]){
    int idxdelete = target; // menyimpan indeks yang akan dihapus
    for(int i=idxdelete; i<n; i++){ // memindahkan data dari indeks selanjutnya (menimpa data di idxdelete)
        source[i] = source[i+1];
    }

    if(strcmp(table, "tdonatur") == 0){ // jika tabel adalah tdonatur
        jmldonatur--; // kurangi jumlah donatur
    }
    else{ // jika tabel adalah tpantiasuhan
        jmlpanti--; // kurangi jumlah panti
    }
    printf(GREEN "Query OK!\n" COLORRESET); // tampilkan pesan sukses
    printf(GREEN "Berhasil menghapus record '%s' di dalam tabel '%s'\n\n" COLORRESET, getcw(), table); // tampilkan pesan berhasil menghapus data

    // jika table adalah tdonatur
    if(strcmp(table, "tdonatur") == 0){ // tampilkan tabel donatur setelah dihapus
        printf(YELLOW "Menampilkan '%d' Record\n" COLORRESET, jmldonatur);
        printtable(1, donatur, jmldonatur);
    }
    // jika table adalah tpantiasuhan
    else{ // tampilkan tabel panti setelah dihapus
        printf(YELLOW "Menampilkan '%d; Record\n" COLORRESET, jmlpanti);
        printtable(2, panti, jmlpanti);
    }
}

// proses membaca query DELETE
void controllerdelete(char pita[]){
    inc(pita); // Pindah ke nama tabel
    if(strcmp(getcw(), "tdonatur") == 0 || strcmp(getcw(), "tpantiasuhan") == 0){ // Cek apakah tabel valid
        strcpy(table, getcw()); // Simpan nama tabel ke variabel global
        if(eop(pita) == 1){ // Jika sudah akhir pita, error
            displayerror(1101); // Tampilkan error atribut kurang
        }
        else{
            inc(pita); // Pindah ke ID
            if(eop(pita) == 0){ // Jika tidak akhir pita, error
                displayerror(1106); // Tampilkan error format query salah
            }
            else{
                if(strcmp(table, "tdonatur") == 0){ // Jika tabel adalah tdonatur
                    int ketemu = BinarySearch(jmldonatur, getcw(), donatur); // Cari primary key di tabel donatur
                    if(ketemu == 1){ // Jika ditemukan
                        deletedata(pita, jmldonatur, donatur); // Hapus data
                    }
                    else{ // Jika tidak ditemukan, error
                        displayerror(1102);
                    }
                }
                else{ // Jika tabel adalah tpantiasuhan
                    int ketemu = BinarySearch(jmlpanti, getcw(), panti); // Cari primary key di tabel panti
                    if(ketemu == 1){ // Jika ditemukan
                        int fk = cekforeignkey(jmldonatur, getcw(), donatur); // Cek foreign key di tabel donatur
                        if(fk == 1){ // Jika foreign key ditemukan, error
                            displayerror(1107);
                        }
                        else{ // Jika tidak, hapus data
                            deletedata(pita, jmlpanti, panti);
                        }
                    }
                    else{ // Jika tidak ditemukan, error
                        displayerror(1102);
                    }
                }
            }
        }
    }
    else{ // Jika tabel tidak ditemukan, error
        displayerror(1105);
    }
}

// proses jointabel
void jointable(){
    jmljoin = 0; // deklarasi jumlah join menjadi 0 terlebih dahulu
    // perulangan sampai jumlah data donatur
    for(int i=0; i<jmldonatur; i++){
        // copy atribut dalam tabel donatur
        strcpy(join[i].id, donatur[i].id); // copy id
        strcpy(join[i].nama, donatur[i].att1); // copy nama
        strcpy(join[i].pekerjaan, donatur[i].att2); // copy pekerjaan
        int found = BinarySearch(jmlpanti, donatur[i].att3, panti); // cari foreign key pada att 3 di tabel panti
        if(found == 1){ // jika ketemu data nya 
            strcpy(join[i].kodejoin, panti[target].att1); // copy indx data yang ditemukan (nama panti ke atribut selanjutnya)
            strcpy(join[i].lokasi, panti[target].att2); // copy lokasi 
            strcpy(join[i].notelp, panti[target].att3); // copy no telp
            jmljoin++; // jumlah join bertambah
        }
        else{ // jika tidak ditemukan
            // atribut selanjutnya saya set NULL semua
            strcpy(join[i].kodejoin, "NULL");
            strcpy(join[i].lokasi, "NULL");
            strcpy(join[i].notelp, "NULL");
            jmljoin++;
        }
    }
}

// Prosedur untuk mencetak tabel join
void printjoin(t_join source[], int n){
    // Mendefinisikan panjang awal header kolom
    int lenid = strlen("Id Donatur");
    int lencoll1 = strlen("Nama Donatur");
    int lencoll2 = strlen("Pekerjaan");
    int lencoll3 = strlen("Nama Panti Asuhan");
    int lencoll4 = strlen("Lokasi");
    int lencoll5 = strlen("No Telp");

    // Memeriksa setiap data untuk menemukan panjang maksimum dari setiap kolom
    for(int i = 0; i < n; i++){
        if(strlen(source[i].id) > lenid){
            lenid = strlen(source[i].id);
        }
        if(strlen(source[i].nama) > lencoll1){
            lencoll1 = strlen(source[i].nama);
        }
        if(strlen(source[i].pekerjaan) > lencoll2){
            lencoll2 = strlen(source[i].pekerjaan);
        }
        if(strlen(source[i].kodejoin) > lencoll3){
            lencoll3 = strlen(source[i].kodejoin);
        }
        if(strlen(source[i].lokasi) > lencoll4){
            lencoll4 = strlen(source[i].lokasi);
        }
        if(strlen(source[i].notelp) > lencoll5){
            lencoll5 = strlen(source[i].notelp);
        }
    }

    // Cetak garis horizontal untuk header tabel
    printf("~");
    for(int i = 0; i < lenid + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll1 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll2 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll3 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll4 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll5 + 4; i++){
        printf("~");
    }
    printf("~\n");

    // Cetak header kolom tabel
    printf("| Id Donatur ");
    for(int i = strlen("Id Donatur"); i < lenid + 2; i++){
        printf(" ");
    }
    printf("| Nama Donatur ");
    for(int i = strlen("Nama Donatur"); i < lencoll1 + 2; i++){
        printf(" ");
    }
    printf("| Pekerjaan ");
    for(int i = strlen("Pekerjaan"); i < lencoll2 + 2; i++){
        printf(" ");
    }
    printf("| Nama Panti Asuhan ");
    for(int i = strlen("Nama Panti Asuhan"); i < lencoll3 + 2; i++){
        printf(" ");
    }
    printf("| Lokasi ");
    for(int i = strlen("Lokasi"); i < lencoll4 + 2; i++){
        printf(" ");
    }
    printf("| No Telp ");
    for(int i = strlen("No Telp"); i < lencoll5 + 2; i++){
        printf(" ");
    }
    printf("|\n");

    // Cetak garis horizontal di bawah header tabel
    printf("~");
    for(int i = 0; i < lenid + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll1 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll2 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll3 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll4 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll5 + 4; i++){
        printf("~");
    }
    printf("~\n");

    // Cetak setiap baris data tabel
    for(int i = 0; i < n; i++){
        printf("| %s ", source[i].id);
        for(int j = strlen(source[i].id); j < lenid + 2; j++){
            printf(" ");
        }
        printf("| %s ", source[i].nama);
        for(int j = strlen(source[i].nama); j < lencoll1 + 2; j++){
            printf(" ");
        }
        printf("| %s ", source[i].pekerjaan);
        for(int j = strlen(source[i].pekerjaan); j < lencoll2 + 2; j++){
            printf(" ");
        }
        printf("| %s ", source[i].kodejoin);
        for(int j = strlen(source[i].kodejoin); j < lencoll3 + 2; j++){
            printf(" ");
        }
        printf("| %s ", source[i].lokasi);
        for(int j = strlen(source[i].lokasi); j < lencoll4 + 2; j++){
            printf(" ");
        }
        printf("| %s ", source[i].notelp);
        for(int j = strlen(source[i].notelp); j < lencoll5 + 2; j++){
            printf(" ");
        }
        printf("|\n");
    }

    // Cetak garis horizontal di bawah tabel
    printf("~");
    for(int i = 0; i < lenid + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll1 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll2 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll3 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll4 + 4; i++){
        printf("~");
    }
    printf("~");
    for(int i = 0; i < lencoll5 + 4; i++){
        printf("~");
    }
    printf("~\n");
}

// proses membaca query SHOW
void controllertampil(char pita[]){
    inc(pita); // pindah kata selanjutnya
    if(strcmp(getcw(), "tdonatur") == 0 || strcmp(getcw(), "tpantiasuhan") == 0){ // cek apakah kata selanjutnya termasuk tdonatur atau tpantiasuhan
        strcpy(table, getcw()); // copy kata sekarang ke tabel
        if(eop(pita) == 1){ // jika sudah eop (maka hanya menampilkan satu table)
            printf(GREEN "Query OK!\n" COLORRESET);
            printf(GREEN "Berhasil Menampilkan Data!\n\n" COLORRESET);
            if(strcmp(table, "tdonatur") == 0){ // jika tabel merupakan tabel donatur
                printf(YELLOW "Menampilkan '%d' Record\n" COLORRESET, jmldonatur);
                printtable(1, donatur, jmldonatur); // panggil print table donatur
            }
            else if(strcmp(table, "tpantiasuhan") == 0){ // jika merupakan panti asuhan
                printf(YELLOW "Menampilkan '%d' Record\n" COLORRESET, jmlpanti);
                printtable(2, panti, jmlpanti); // print tabel panti
            }
        }
        else{ // jika bukan eop (anggapannya join data)
            inc(pita); // increment dulu kata
            if(strcmp(getcw(), "tdonatur") == 0 || strcmp(getcw(), "tpantiasuhan") == 0){ // jika next kata termasuk tdonatur atau tpantiasuhan
                // cek apabila tdonatur yang diinput sebelumnya maka yang kedua harus tpantiasuhan, jika tpantiasuhan sebelumnya maka harus tdonatur
                if((strcmp(getcw(), "tdonatur") == 0 && strcmp(table, "tpantiasuhan") == 0) || (strcmp(getcw(), "tpantiasuhan") == 0 && strcmp(table, "tdonatur") == 0)){
                    if(eop(pita) == 1){ // jika sudah eop maka query berhasil
                        jointable(); // lakukan proses join table terlebih dahulu
                        printf(GREEN "Query OK!\n" COLORRESET); // print query oke
                        printf(GREEN "Hasil Join, MANTAPPP!\n\n" COLORRESET);
                        printjoin(join, jmljoin); // lalu print tabel hasil join
                    } // jika bukan eop maka error
                    else{
                        displayerror(1106); // error melebihi batas perintah
                    }
                }
                else{
                    displayerror(1108); // error tidak bisa join (gagal join)
                }
            }
            else{
                displayerror(1108); // error tidak bisa join atau gagal join
            }
        }
    }
    else{
        displayerror(1105); // error tabel tidak ada
    }
}

// proses membaca query awal (command)
void readquery(char pita[]){
    // read terlebih dahulu file donatur
    readfile("tdonatur.txt", donatur);
    // read juga file panti asuhan
    readfile("tpantiasuhan.txt", panti);

    // karena dalam pemrosesan query diperlukan searching urutkan dulu kedua data
    sorting(jmldonatur, donatur);
    sorting(jmlpanti, panti);

    // mulai mesin kata (cw = kata pertama)
    start(pita);
    if(eop(pita) == 0){ // jika belum eop
        if(strcmp(getcw(), "INPUT") == 0 || strcmp(getcw(), "Input") == 0 || strcmp(getcw(), "input") == 0){ // cek kata pertama apakan command nya input
            controllerinsert(pita); // panggil controller untuk insert data
        }
        else if(strcmp(getcw(), "UPDATE") == 0 || strcmp(getcw(), "Update") == 0 || strcmp(getcw(), "update") == 0){ // jika command adalah update
            controllerupdate(pita); // panggil controller update
        }
        else if(strcmp(getcw(), "DELETE") == 0 || strcmp(getcw(), "Delete") == 0 || strcmp(getcw(), "delete") == 0){ // jika command adalah delete
            controllerdelete(pita); // panggil controller delete
        }
        else if(strcmp(getcw(), "SHOW") == 0 || strcmp(getcw(), "Show") == 0 || strcmp(getcw(), "show") == 0){ // jika command nya show
            controllertampil(pita); // panggil controller untuk menampilkan
        }
        else{
            displayerror(1110); // selain itu maka query atau command tidak valid
        }
    }
    else{
        displayerror(1101); // jika langsung eop maka nilai atribut kurang
    }

    // sehabis pemrosesan write kembali kedua file (flush file)
    writeFile(jmldonatur, donatur, "tdonatur.txt");
    writeFile(jmlpanti, panti, "tpantiasuhan.txt");
}