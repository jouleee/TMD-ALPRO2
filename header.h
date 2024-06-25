/*Saya Julian Dwi Satrio dengan NIM 2300484 mengerjakan evaluasi Tugas Masa Depan 
dalam mata kuliah Algoritma dan Pemrograman II untuk keberkahanNya maka saya 
tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.*/

#include <stdio.h>
#include <string.h>

// struct untuk menyimpan tabel biasa berisi 1 coll id dan 3 coll att
typedef struct{
    char id[256];
    char att1[256], att2[256], att3[256];
}t_biasa;

// struct untuk menyimpan data join berisi 1 coll id dan 5 coll att
typedef struct{
    char id[256];
    char nama[256], pekerjaan[256], kodejoin[256], lokasi[256], notelp[256];
}t_join;

// variabel global mesin kata
extern int idx; // idx huruf
extern int wlen; // panjang kata (word length)
extern char cw[256]; // current word

// variabel global modify dbms
extern char table[256]; // nama tabel yang di eksekusi 
extern int target; // id tujuan yang dicari (jika ditemukan)
extern int jmldonatur; // counter jumlah data donatur
extern int jmlpanti; // counter jumlah data panti
extern int jmljoin; // counter jumlah data yang di join

// variabel global dbms
extern t_biasa donatur[300]; // struct donatur
extern t_biasa panti[300]; // struct panti
extern t_join join[300]; // struct join
 
// prosedur animasi awal
void wait(float x); // prosedur menunggu waktu selama 1 detik (delay)
void startdbms(); // prosedur animasi start dbms (UI)

// prosedur mesin kata
void start(char pita[]); // prosedur memulai mesin kata
void reset(); // prosedur reset current word
void inc(char pita[]); // prosedur increment kata (pindah kata ke selanjutnya)
int eop(char pita[]); // prosedur cek sudah sampai eop atau belum
char* getcw(); // mereturn current word
int getlen(); // mereturn panjang kata (word length)
int carieop(char pita[]); // mencari apakah dalam pita terdapat eop

// prosedur preparing data
void sorting(int n, t_biasa source[]); // prosedur sorting data berdasarkan id
int BinarySearch(int n, char dicari[], t_biasa source[]); // proses search primary key dari tiap tabel
int cekforeignkey(int n, char dicari[], t_biasa source[]); // proses cek foreign key yang bertaut

// prosedur reading and write file
void readfile(char filename[], t_biasa source[]); // read file
void writefile(int n, t_biasa skincare[], char namafile[]); // write file

// prosedur print message
void displayerror(int n); // prosedur print error handling / error message
void goodbyemessage(); // prosedur untuk print random goodbye message

// proses modify data
void insertdata(char pita[]); // proses inserting data
void controllerinsert(char pita[]); // controller utk insert data (error handling)

void updatedata(char pita[]); // proses update data
void controllerupdate(char pita[]); // controller update data

void deletedata(char pita[], int n, t_biasa source[]); // prosedur delete data
void controllerdelete(char pita[]); // controller delete data

void controllertampil(char pita[]); // controller menampilkan data

void printtable(int tab, t_biasa source[], int n); // proses print tabel
void jointable(); // proses join data
void printjoin(t_join source[], int n); // print tabel join

// prosedur read input pita (query)
void readquery(char pita[]); // prosedur reading query