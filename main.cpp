#include <iostream>
#include "MLL.h"

using namespace std;

int main() {
    ListPenulis LP;
    ListPaper LC;
    ListRelasi LR;

    createListParent(LP);
    createListChild(LC);
    createListRelasi(LR);

    int choice;
    do {
        cout << "=== Main Menu ===" << endl;
        cout << "1. Tambah Data" << endl;
        cout << "2. Edit Data" << endl;
        cout << "3. Hapus Data" << endl;
        cout << "4. Show Data" << endl;
        cout << "5. Search Data" << endl;
        cout << "6. Extra Function" << endl;
        cout << "7. Test Input" << endl;
        cout << "8. Exit" << endl;
        cout << "================="<< endl;
        cout << "Pilih menu: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                int subChoice;
                do {
                    cout << "=== Tambah Data ===" << endl;
                    cout << "1. Tambah Penulis" << endl;
                    cout << "2. Tambah Paper" << endl;
                    cout << "3. Return to Main Menu" << endl;
                    cout << "===================" <<endl;
                    cout << "Pilih menu: ";
                    cin >> subChoice;
                    cout << endl;

                    if (subChoice == 1) {
                        Penulis p;
                        cout << "Masukkan Nama Penulis: ";
                        cin.ignore();
                        getline(cin, p.Nama);
                        cout << "Masukkan Tanggal Lahir: ";
                        getline(cin, p.TanggalLahir);
                        cout << "Masukkan Tempat Lahir: ";
                        getline(cin, p.TempatLahir);

                        adrPenulis newPenulis = createElementPenulis(p);
                        insertFirstParent(LP, newPenulis);
                        cout << "Penulis Berhasil di Tambahkan" << endl;
                        cout << endl;

                    } else if (subChoice == 2) {
                        Paper p;
                        cout << "Masukkan Judul Paper: ";
                        cin.ignore();
                        getline(cin, p.Judul);
                        cout << "Masukkan Tahun Terbit: ";
                        cin >> p.TahunTerbit;
                        cout << "Masukkan Jumlah Sitasi: ";
                        cin >> p.JumlahSitasi;
                        cout << "Masukkan Jumlah Penulis: ";
                        cin >> p.JumlahPenulis;
                        cin.ignore();

                        for (int i = 0; i < p.JumlahPenulis; i++) {
                            cout << "Nama Penulis ke-" << i + 1 << ": ";
                            getline(cin, p.NamaPenulis[i]);
                        }

                        adrPaper newPaper = createElementPaper(p);
                        insertChild(LC, LP, LR, p);
                        cout << "Paper Berhasil Ditambahkan" << endl;
                        cout << endl;
                    }
                } while (subChoice != 3);
                break;
            }
            case 2: {
                int subChoice;
                do {
                    cout << "=== Edit Data ===" << endl;
                    cout << "1. Edit Penulis" << endl;
                    cout << "2. Edit Paper" << endl;
                    cout << "3. Return to Main Menu" << endl;
                    cout << "=================" <<endl;
                    cout << "Pilih menu: ";
                    cin >> subChoice;
                    cout << endl;

                    if (subChoice == 1) {
                        string nama;
                        cout << "Masukkan Nama Penulis yang ingin diubah: ";
                        cin.ignore();
                        getline(cin, nama);
                        editDataParent(LP, nama);
                        cout << endl;

                    } else if (subChoice == 2) {
                        string judul;
                        cout << "Masukkan Judul Paper yang ingin diubah: ";
                        cin.ignore();
                        getline(cin, judul);
                        editDataChild(LC, judul);
                        cout << endl;
                    }
                } while (subChoice != 3);
                break;
            }
            case 3: {
                int subChoice;
                do {
                    cout << "=== Hapus Data ===" << endl;
                    cout << "1. Hapus Penulis dan Semua Papernya" << endl;
                    cout << "2. Hapus Paper dari Penulis" << endl;
                    cout << "3. Return to Main Menu" << endl;
                    cout << "==================" <<endl;
                    cout << "Pilih menu: ";
                    cin >> subChoice;
                    cout << endl;

                    if (subChoice == 1) {
                        string nama;
                        cout << "Masukkan Nama Penulis yang ingin dihapus: ";
                        cin.ignore();
                        getline(cin, nama);
                        deleteParentAndItsChild(LP, LC, LR, nama);
                        cout << endl;

                    } else if (subChoice == 2) {
                        string nama, judul;
                        cout << "Masukkan Nama Penulis: ";
                        cin.ignore();
                        getline(cin, nama);
                        cout << "Masukkan Judul Paper yang ingin dihapus: ";
                        getline(cin, judul);
                        deleteChildFromParent(LP, LC, LR, nama, judul);
                        cout << endl;
                    }
                    cout << endl;
                } while (subChoice != 3);
                break;
            }
            case 4: {
                int subChoice;
                do {
                    cout << "=== Show Data ===" << endl;
                    cout << "1. Show data Penulis" << endl;
                    cout << "2. Show data Paper" << endl;
                    cout << "3. Show Daftar Penulis dan Papernya" << endl;
                    cout << "4. Return to Main Menu" << endl;
                    cout << "=================" <<endl;
                    cout << "Pilih menu: ";
                    cin >> subChoice;
                    cout << endl;

                    if (subChoice == 1) {
                        showParent(LP);
                    } else if (subChoice == 2) {
                        printChild(LC);
                    } else if (subChoice == 3) {
                        printAllParentAndItsChild(LP, LR, LC);
                    }
                    cout << endl;
                } while (subChoice != 4);
                break;
            }
            case 5: {
                int subChoice;
                do {
                    cout << "=== Search Data ===" << endl;
                    cout << "1. Search Penulis" << endl;
                    cout << "2. Search Paper" << endl;
                    cout << "3. Search Paper dari Penulis" << endl;
                    cout << "4. Return to Main Menu" << endl;
                    cout << "===================" <<endl;
                    cout << "Pilih menu: ";
                    cin >> subChoice;
                    cout << endl;

                    if (subChoice == 1) {
                        string nama;
                        cout << "Masukkan Nama Penulis: ";
                        cin.ignore();
                        getline(cin, nama);
                        adrPenulis result = searchParentNama(LP, nama);
                        if (result != nullptr) {
                            cout << "Penulis ditemukan!! " << endl;
                            cout << "Nama           : " << infoPe(result).Nama << endl;
                            cout << "Tempat Lahir   : " << infoPe(result).TempatLahir << endl;
                            cout << "Tanggal Lahir  : " << infoPe(result).TanggalLahir << endl;
                        } else {
                            cout << "Penulis tidak ditemukan." << endl;
                        }
                        cout << endl;

                    } else if (subChoice == 2) {
                        string judul;
                        cout << "Masukkan Judul Paper: ";
                        cin.ignore();
                        getline(cin, judul);
                        adrPaper result = searchChildJudul(LC, judul);
                        if (result != nullptr) {
                            cout << "Paper ditemukan!!!" << endl;
                            cout << "Judul Paper     : " << infoPa(result).Judul << endl;
                            cout << "Tahun Terbit    : " << infoPa(result).TahunTerbit << endl;
                            cout << "Jumlah Sitasi   : " << infoPa(result).JumlahSitasi << endl;
                            cout << "Jumlah Penulis  : " << infoPa(result).JumlahPenulis << endl;
                            cout << "Nama Penulis    : ";
                            for (int i = 0; i < infoPa(result).JumlahPenulis; i++) {
                                cout << infoPa(result).NamaPenulis[i];
                                if (i < infoPa(result).JumlahPenulis - 1) {
                                    cout << ", ";
                                }
                            }
                            cout << endl;
                        } else {
                            cout << "Paper tidak ditemukan." << endl;
                        }
                        cout << endl;

                    } else if (subChoice == 3) {
                        string nama, judul;
                        cout << "Masukkan Nama Penulis: ";
                        cin.ignore();
                        getline(cin, nama);
                        cout << "Masukkan Judul Paper: ";
                        getline(cin, judul);
                        searchChildFromParent(LP, LR, LC, nama, judul);
                        cout << endl;
                    }
                } while (subChoice != 4);
                break;
            }
            case 6: {
                int subChoice;
                do {
                    cout << "=== Extra Function ===" << endl;
                    cout << "1. Total Sitasi dari Penulis" << endl;
                    cout << "2. Total Paper yang terbit di Tahun X" << endl;
                    cout << "3. Return to Main Menu" << endl;
                    cout << "======================" <<endl;
                    cout << "Pilih menu: ";
                    cin >> subChoice;
                    cout << endl;

                    if (subChoice == 1) {
                        string nama;
                        cout << "Masukkan Nama Penulis: ";
                        cin.ignore();
                        getline(cin, nama);
                        int totalSitasi = countTotalSitasiPenulis(LR, LP, nama);
                        if (totalSitasi != 0){
                        cout << "Total Sitasi dari Penulis " << nama << " adalah: " << totalSitasi << endl;
                        }
                        cout << endl;

                    } else if (subChoice == 2) {
                        int tahun;
                        cout << "Masukkan Tahun Terbit: ";
                        cin >> tahun;
                        printAndCountPaperbyYear(LC, tahun);
                        cout << endl;
                    }
                } while (subChoice != 3);
                break;
            }
            case 7 :{
                inputTest(LP, LC, LR);
                cout << endl;
                break;
            }

            case 8: {
                cout << "Terimaksih sudah Menggunakan Aplikasi Kami!!!, Exiting..." << endl;
                break;
            }
            default:{
                cout << "Pilihan tidak valid. Coba lagi." << endl;
            }
        }
    } while (choice != 8);

    return 0;
}
