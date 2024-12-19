#include <iostream>
#include "MLL.h"

void createListParent(ListPenulis &LP){
    firstPe(LP) = NULL;
    lastPe(LP) = NULL;
}
void createListChild(ListPaper &LC){
    firstPa(LC) = NULL;
}
void createListRelasi(ListRelasi &LR){
    firstRe(LR) = NULL;
}

adrPenulis createElementPenulis(Penulis x){
    adrPenulis P = new elmPenulis;
    infoPe(P) = x;
    nextPe(P) = NULL;
    prevPe(P) = NULL;
    return P;
}

adrPaper createElementPaper(Paper x){
    adrPaper P = new elmPaper;
    infoPa(P) = x;
    nextPa(P) = NULL;
    return P;
}

void insertFirstParent(ListPenulis &LP, adrPenulis PP){
    if (firstPe(LP) == NULL && lastPe(LP)== NULL) {
        firstPe(LP) = PP;
        lastPe(LP)  = PP;
    } else {
        nextPe(PP) = firstPe(LP);
        prevPe(firstPe(LP)) = PP;
        firstPe(LP) = PP;
    }
}

adrPenulis searchParentNama(ListPenulis LP, string Nama){
    if (firstPe(LP)== NULL){
        return nullptr;
    } else {
        adrPenulis P = firstPe(LP);
        while (P!= NULL && infoPe(P).Nama != Nama){
            P = nextPe(P);
        }
        return P;
    }
}

void showParent(ListPenulis LP){
    if (firstPe(LP) == nullptr) {
        cout << "List Penulis Kosong." << endl;
    } else{
        adrPenulis p = firstPe(LP);
        cout << "==============Daftar Penulis===============" << endl;
        while (p!=NULL){
                cout << "Nama           : " << infoPe(p).Nama << endl;
                cout << "Tempat Lahir   : " << infoPe(p).TempatLahir << endl;
                cout << "Tanggal Lahir  : " << infoPe(p).TanggalLahir << endl;
                cout << "-------------------------------------------" << endl;
                p = nextPe(p);
        }
        cout << "===========================================" << endl;
    }
}


void printChild(ListPaper LC) {
    if (firstPa(LC) == nullptr) {
        cout << "List Paper Kosong." << endl;
    } else{
        adrPaper currentPaper = firstPa(LC);
        cout << "========================Daftar Paper========================" << endl;
        while (currentPaper != nullptr) {
            Paper paperInfo = infoPa(currentPaper);
            cout << "Judul Paper     : " << paperInfo.Judul << endl;
            cout << "Tahun Terbit    : " << paperInfo.TahunTerbit << endl;
            cout << "Jumlah Sitasi   : " << paperInfo.JumlahSitasi << endl;
            cout << "Jumlah Penulis  : " << paperInfo.JumlahPenulis << endl;
            cout << "Nama Penulis    : ";
            for (int i = 0; i < paperInfo.JumlahPenulis; i++) {
                cout << paperInfo.NamaPenulis[i];
                if (i < paperInfo.JumlahPenulis - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
            cout << "------------------------------------------------------" << endl;
            currentPaper = nextPa(currentPaper);
        }
        cout << "==========================================================" << endl;
    }
}


void toDeleteParent(ListPenulis &LP, adrPenulis parent){
    if (parent == firstPe(LP)) {
        firstPe(LP) = nextPe(parent);
        if (firstPe(LP) != nullptr) {
            prevPe(firstPe(LP)) = nullptr;
        }
    }
    else if (parent == lastPe(LP)) {
        lastPe(LP) = prevPe(parent);
        nextPe(prevPe(parent)) = nullptr;
    }
    else {
        nextPe(prevPe(parent)) = nextPe(parent);
        prevPe(nextPe(parent)) = prevPe(parent);
    }

    delete parent;
}

void toDeleteChild(ListPaper &LC, adrPaper targetPaper){
    if (targetPaper == firstPa(LC)) {
        firstPa(LC) = nextPa(targetPaper);
    }
    else {
        adrPaper temp = firstPa(LC);
        while (nextPa(temp) != targetPaper) {
            temp = nextPa(temp);
        }
        nextPa(temp) = nextPa(targetPaper);
    }

    delete targetPaper;
}

void toDeleteRelation(ListRelasi &LR, adrRelasi targetRelasi){
    if (targetRelasi == firstRe(LR)) {
        firstRe(LR) = nextRe(targetRelasi);
    }
    else {
        adrRelasi temp = firstRe(LR);
        while (nextRe(temp) != targetRelasi) {
            temp = nextRe(temp);
        }
        nextRe(temp) = nextRe(targetRelasi);
    }

    delete targetRelasi;
}

void deleteParentAndItsChild(ListPenulis &LP, ListPaper &LC, ListRelasi &LR, string Nama){
    adrPenulis targetPenulis = searchParentNama(LP, Nama);
    if (targetPenulis == nullptr) {
        cout << "Penulis Tidak Ditemukan!!" << endl;
    } else {
        adrRelasi currRelasi = firstRe(LR);
        while (currRelasi != nullptr) {
            if (currRelasi->HubPenulis == targetPenulis) {
                adrPaper targetPaper = currRelasi->HubPaper;

                adrRelasi tempRelasi = firstRe(LR);
                bool isShared = false;
                while (tempRelasi != nullptr) {
                    if (tempRelasi->HubPaper == targetPaper && tempRelasi->HubPenulis != targetPenulis) {
                        isShared = true;
                        break;
                    }
                    tempRelasi = nextRe(tempRelasi);
                }
                if (!isShared) {
                    toDeleteChild(LC, targetPaper);
                }
                adrRelasi toDeleteRelasi = currRelasi;
                currRelasi = nextRe(currRelasi);
                toDeleteRelation(LR, toDeleteRelasi);
            } else {
                currRelasi = nextRe(currRelasi);
            }
        }
        toDeleteParent(LP, targetPenulis);
        cout << "Penulis dan Papernya berhasil dihapus!!!" << endl;
    }
}

void editDataParent(ListPenulis &LP, string Nama){
    adrPenulis targetPenulis = searchParentNama(LP, Nama);
    if (targetPenulis == nullptr) {
        cout << "Penulis dengan nama '" << Nama << "' tidak ditemukan!" << endl;
    } else {
        cout << "Data Penulis:" << endl;
        cout << "Nama          : " << infoPe(targetPenulis).Nama << endl;
        cout << "Tanggal Lahir : " << infoPe(targetPenulis).TanggalLahir << endl;
        cout << "Tempat Lahir  : " << infoPe(targetPenulis).TempatLahir << endl;

        cout << "\nMasukkan Data Penulis Baru:" << endl;

        string newNama, newTanggalLahir, newTempatLahir;
        cout << "Nama          : " << infoPe(targetPenulis).Nama << endl;
        cout << "Tanggal Lahir Baru : ";
        getline(cin, newTanggalLahir);
        cout << "Tempat Lahir Baru  : ";
        getline(cin, newTempatLahir);

        infoPe(targetPenulis).TanggalLahir = newTanggalLahir;
        infoPe(targetPenulis).TempatLahir = newTempatLahir;
        cout << "Data Penulis Berhasil di Edit" << endl;
    }
}

adrRelasi createElementRelasi(adrPaper PC, adrPenulis PP){
    adrRelasi newRelasi = new elmRelasi;
    newRelasi->HubPenulis = PP;
    newRelasi->HubPaper = PC;
    newRelasi->nextRelasi = nullptr;
}

void insertRelasi(ListRelasi &LR, adrRelasi PR){
    if (firstRe(LR) == nullptr) {
            firstRe(LR) = PR;
        } else {
            adrRelasi tempRelasi = firstRe(LR);
            while (nextRe(tempRelasi) != nullptr) {
                tempRelasi = nextRe(tempRelasi);
            }
            nextRe(tempRelasi) = PR;
        }
}

void insertChild(ListPaper &LC, ListPenulis &LP, ListRelasi &LR, Paper x) {
    adrPaper newPaper = createElementPaper(x);

    if (firstPa(LC) == nullptr) {
        firstPa(LC) = newPaper;
    } else {
        adrPaper temp = firstPa(LC);
        while (nextPa(temp) != nullptr) {
            temp = nextPa(temp);
        }
        nextPa(temp) = newPaper;
    }

    for (int i = 0; i < x.JumlahPenulis; i++) {
        string namaPenulis = x.NamaPenulis[i];

        adrPenulis parent = searchParentNama(LP, namaPenulis);

        if (parent == nullptr){
            Penulis newPenulis;
            newPenulis.Nama = namaPenulis;
            cout << "---------------------------------------------------------------------------------" << endl;
            cout << newPenulis.Nama << " Tidak Ditemukan dalam Daftar Penulis, Mohon Tambahkan Data Penulis" << endl;
            cout << "---------------------------------------------------------------------------------" << endl;
            cout << "Nama Penulis : " << newPenulis.Nama << endl;
            cout << "Tanggal Lahir Penulis : ";
            getline(cin,newPenulis.TanggalLahir);
            cout << "Tempat Lahir Penulis : ";
            getline(cin,newPenulis.TempatLahir);
            cout << endl;
            adrPenulis newParent = createElementPenulis(newPenulis);
            insertFirstParent(LP, newParent);
            cout << "Penulis Berhasil Ditambahkan" << endl;
            parent = newParent;
        }

        adrRelasi newRelasi = createElementRelasi(newPaper, parent);
        insertRelasi(LR, newRelasi);
    }
}

adrPaper searchChildJudul(ListPaper LP, string JudulPaper){
    adrPaper targetPaper = firstPa(LP);
    while (targetPaper != nullptr && infoPa(targetPaper).Judul != JudulPaper) {
        targetPaper = nextPa(targetPaper);
    }
    return targetPaper;
}

void editDataChild(ListPaper &LP, string JudulPaper){
    adrPaper targetPaper = searchChildJudul(LP, JudulPaper);
    if (targetPaper == nullptr) {
        cout << "Paper dengan judul \"" << JudulPaper << "\" tidak ditemukan!" << endl;
    } else {
        cout << "Paper ditemukan! Silakan masukkan data baru:" << endl;
        cout << "Judul baru: ";
        getline(cin, infoPa(targetPaper).Judul);
        cout << "Tahun Terbit: ";
        cin >> infoPa(targetPaper).TahunTerbit;
        cout << "Jumlah Sitasi: ";
        cin >> infoPa(targetPaper).JumlahSitasi;
        cout << "Data Paper Berhasil di Edit" << endl;
    }
}

void printAllParentAndItsChild(ListPenulis LP, ListRelasi LR, ListPaper LC) {
    adrPenulis currPenulis = firstPe(LP);
    if (currPenulis == nullptr) {
        cout << "Tidak ada data penulis!" << endl;
    } else {
        cout << "================Daftar Penulis dan Papernya==================" << endl;
        while (currPenulis != nullptr) {
            cout << "Penulis: " << infoPe(currPenulis).Nama << endl;
            cout << "Tanggal Lahir: " << infoPe(currPenulis).TanggalLahir << endl;
            cout << "Tempat Lahir: " << infoPe(currPenulis).TempatLahir << endl;

            bool hasPaper = false;
            cout << endl;
            cout << "Daftar Paper: " << endl;
            adrRelasi currRelasi = firstRe(LR);
            while (currRelasi != nullptr) {
                if (currRelasi->HubPenulis == currPenulis) {
                    hasPaper = true;

                    adrPaper relatedPaper = currRelasi->HubPaper;
                    cout << "Judul Paper: " << infoPa(relatedPaper).Judul << endl;
                    cout << "Tahun Terbit: " << infoPa(relatedPaper).TahunTerbit << endl;
                    cout << "Jumlah Sitasi: " << infoPa(relatedPaper).JumlahSitasi << endl;
                    cout << endl;
                }
                currRelasi = nextRe(currRelasi);
            }

            if (!hasPaper) {
                cout << "  (Tidak ada paper terkait)" << endl;
            }

            cout << "----------------------------------------" << endl;
            currPenulis = nextPe(currPenulis);
        }
        cout << "============================================================" << endl;
    }
}

void searchChildFromParent(ListPenulis LP, ListRelasi LR, ListPaper LC, string NamaParent, string JudulPaper) {
    adrPenulis parent = searchParentNama(LP, NamaParent);
    if (parent == nullptr) {
        cout << "Penulis dengan nama \"" << NamaParent << "\" tidak ditemukan." << endl;
    } else {
        adrRelasi currRelasi = firstRe(LR);
        bool found = false;
        while (currRelasi != nullptr) {
            if (currRelasi->HubPenulis == parent) {
                adrPaper paper = currRelasi->HubPaper;
                if (infoPa(paper).Judul == JudulPaper) {
                    cout << "Paper ditemukan!" << endl;
                    cout << "Judul: " << infoPa(paper).Judul << endl;
                    cout << "Tahun Terbit: " << infoPa(paper).TahunTerbit << endl;
                    cout << "Jumlah Sitasi: " << infoPa(paper).JumlahSitasi << endl;

                    found = true;
                    break;
                }
            }
            currRelasi = nextRe(currRelasi);
        }
        if (!found) {
            cout << "Paper dengan judul \"" << JudulPaper << "\" tidak ditemukan untuk penulis \"" << NamaParent << "\"." << endl;
        }
    }
}

void deleteChildFromParent(ListPenulis &LP, ListPaper &LC, ListRelasi &LR, string NamaParent, string JudulPaper) {
    adrPenulis parent = searchParentNama(LP, NamaParent);
    if (parent == nullptr) {
        cout << "Penulis dengan nama \"" << NamaParent << "\" tidak ditemukan." << endl;
    } else {

        adrRelasi currRelasi = firstRe(LR);
        adrRelasi targetRelasi = nullptr;
        adrPaper targetPaper = nullptr;

        while (currRelasi != nullptr) {
            if (currRelasi->HubPenulis == parent && infoPa(currRelasi->HubPaper).Judul == JudulPaper) {
                targetRelasi = currRelasi;
                targetPaper = currRelasi->HubPaper;
                break;
            }
            currRelasi = nextRe(currRelasi);
        }

        if (targetRelasi == nullptr) {
            cout << "Paper dengan judul \"" << JudulPaper << "\" tidak ditemukan untuk penulis \"" << NamaParent << "\"." << endl;
        } else {

            toDeleteRelation(LR, targetRelasi);

            bool isShared = false;
            currRelasi = firstRe(LR);
            while (currRelasi != nullptr) {
                if (currRelasi->HubPaper == targetPaper) {
                    isShared = true;
                    break;
                }
                currRelasi = nextRe(currRelasi);
            }

            if (!isShared) {
                toDeleteChild(LC, targetPaper);
            }
        }
        cout << "Paper dengan judul \"" << JudulPaper << "\" berhasil dihapus dari penulis \"" << NamaParent << "\"." << endl;
    }
}

int countTotalSitasiPenulis(ListRelasi LR, ListPenulis LP, string NamaPenulis) {

    adrPenulis targetPenulis = searchParentNama(LP, NamaPenulis);
    if (targetPenulis == nullptr) {
        cout << "Penulis dengan nama \"" << NamaPenulis << "\" tidak ditemukan." << endl;
        return 0;
    } else {
        int totalSitasi = 0;
        adrRelasi currRelasi = firstRe(LR);
        while (currRelasi != nullptr) {
            if (currRelasi->HubPenulis == targetPenulis) {
                totalSitasi += currRelasi->HubPaper->infoPaper.JumlahSitasi;
            }
            currRelasi = nextRe(currRelasi);
        }
        return totalSitasi;
    }
}

void printAndCountPaperbyYear(ListPaper LP, int tahunTerbit) {
    adrPaper currPaper = firstPa(LP);
    int countpaper = 0;

    cout << "Daftar Paper yang Terbit pada Tahun " << tahunTerbit << ":\n";
    cout << "===========================================\n";

    while (currPaper != nullptr) {
        if (infoPa(currPaper).TahunTerbit == tahunTerbit) {
            cout << "Judul: " << infoPa(currPaper).Judul << endl;
            cout << "Jumlah Sitasi: " << infoPa(currPaper).JumlahSitasi << endl;
            cout << "-------------------------------------------\n";
            countpaper++;
        }
        currPaper = nextPa(currPaper);
    }

    cout << "Total Paper yang Terbit pada Tahun " << tahunTerbit << " : " << countpaper << endl;
}

void inputTest(ListPenulis &LP, ListPaper &LC, ListRelasi &LR) {
    Penulis penulis1 = {"Ahmad Pratama", "1990-05-12", "Jakarta"};
    Penulis penulis2 = {"Rini Kusuma", "1987-08-25", "Bandung"};
    Penulis penulis3 = {"Bayu Wijaya", "1993-11-03", "Surabaya"};

    adrPenulis p1 = createElementPenulis(penulis1);
    adrPenulis p2 = createElementPenulis(penulis2);
    adrPenulis p3 = createElementPenulis(penulis3);

    insertFirstParent(LP, p1);
    insertFirstParent(LP, p2);
    insertFirstParent(LP, p3);

    Paper paper1 = {"Pengaruh Teknologi AI di Indonesia", 1, {"Ahmad Pratama"}, 2020, 15};
    Paper paper2 = {"Peningkatan Pendidikan Digital", 2, {"Rini Kusuma", "Bayu Wijaya"}, 2021, 20};
    Paper paper3 = {"Inovasi Pertanian Modern", 1, {"Bayu Wijaya"}, 2022, 10};

    insertChild(LC, LP, LR, paper1);
    insertChild(LC, LP, LR, paper2);
    insertChild(LC, LP, LR, paper3);

    cout << "Data Test Telah Ditamabahkan.\n";
}












