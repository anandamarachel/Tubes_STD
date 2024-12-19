#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include <iostream>

#define firstPe(L) L.firstPenulis
#define lastPe(L) L.lastPenulis
#define firstPa(L) L.firstPaper
#define firstRe(L) L.firstRelasi
#define nextPe(L) L->nextPenulis
#define prevPe(L) L->prevPenulis
#define nextPa(L) L->nextPaper
#define nextRe(L) L->nextRelasi
#define infoPe(L) L->infoPenulis
#define infoPa(L) L->infoPaper

using namespace std;
const int NMAXPenulis = 6;

typedef struct elmPenulis *adrPenulis;
typedef struct elmPaper *adrPaper;
typedef struct elmRelasi *adrRelasi;

struct Penulis {
    string Nama;
    string TanggalLahir;
    string TempatLahir;
};

struct Paper {
    string Judul;
    int JumlahPenulis;
    string NamaPenulis[NMAXPenulis];
    int TahunTerbit;
    int JumlahSitasi;
};

struct elmPenulis{
    Penulis infoPenulis;
    adrPenulis nextPenulis;
    adrPenulis prevPenulis;
};

struct elmPaper{
    Paper infoPaper;
    adrPaper nextPaper;
};

struct elmRelasi {
    adrPenulis HubPenulis;
    adrPaper HubPaper;
    adrRelasi nextRelasi;
};

struct ListPenulis {
    adrPenulis firstPenulis;
    adrPenulis lastPenulis;
};

struct ListPaper {
    adrPaper firstPaper;
};

struct ListRelasi {
    adrRelasi firstRelasi;
};

void createListParent(ListPenulis &LP);
void createListChild(ListPaper &LC);
void createListRelasi(ListRelasi &LR);
adrPenulis createElementPenulis(Penulis x);
adrPaper createElementPaper(Paper x);
void insertFirstParent(ListPenulis &LP, adrPenulis PP);
adrPenulis searchParentNama(ListPenulis LP, string Nama);
void showParent(ListPenulis LP);
void printChild(ListPaper LC);
void toDeleteParent(ListPenulis &LP, adrPenulis parent);
void toDeleteChild(ListPaper &LC, adrPaper targetPaper);
void toDeleteRelation(ListPenulis &LR, adrRelasi targetRelasi);
void deleteParentAndItsChild(ListPenulis &LP, ListPaper &LC, ListRelasi &LR, string Nama);
void editDataParent(ListPenulis &LP, string Nama);
adrRelasi createElementRelasi(adrPaper PC, adrPenulis PP);
void insertRelasi(ListRelasi &LR, adrRelasi PR);
void insertChild(ListPaper &LC, ListPenulis &LP, ListRelasi &LR, Paper x);
adrPaper searchChildJudul(ListPaper LP, string JudulPaper);
void editDataChild(ListPaper &LP, string JudulPaper);
void printAllParentAndItsChild(ListPenulis LP, ListRelasi LR, ListPaper LC);
void searchChildFromParent(ListPenulis LP, ListRelasi LR, ListPaper LC, string NamaParent, string JudulPaper);
void deleteChildFromParent(ListPenulis &LP, ListPaper &LC, ListRelasi &LR, string NamaParent, string JudulPaper);
int countTotalSitasiPenulis(ListRelasi LR, ListPenulis LP, string NamaPenulis);
void printAndCountPaperbyYear(ListPaper LP, int tahunTerbit);
void inputTest(ListPenulis &LP, ListPaper &LC, ListRelasi &LR);
#endif // MLL_H_INCLUDED
