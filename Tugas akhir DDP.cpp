#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct Menu {
    string nama;
    int harga;
};

void tampilkanMenu(Menu daftarMenu[], int jumlahMenu) {
    cout << "\nMenu:\n";
    for (int i = 0; i < jumlahMenu; i++) {
        cout << i + 1 << ". " << daftarMenu[i].nama << " - Rp" << daftarMenu[i].harga << endl;
    }
}

int hitungTotalHarga(Menu daftarMenu[], int jumlahPesanan[], int jumlahMenu) {
    int total = 0;
    for (int i = 0; i < jumlahMenu; i++) {
        total += jumlahPesanan[i] * daftarMenu[i].harga;
    }
    return total;
}

void cetakStruk(string namaPemesan, Menu daftarMenu[], int jumlahPesanan[], int jumlahMenu, int totalHarga, int bayar, int kembalian) {
    ofstream file("struk.txt");

    file << "\n------------------------------------------------------------\n";
    file << "Pesanan atas nama: " << namaPemesan << endl;
    file << "------------------------------------------------------------\n";
    file << "| NO | Nama Menu   | Jumlah | Harga   | Total Harga       |\n";
    file << "------------------------------------------------------------\n";

    for (int i = 0; i < jumlahMenu; i++) {
        if (jumlahPesanan[i] > 0) {
            int totalPerItem = jumlahPesanan[i] * daftarMenu[i].harga;
            file << "| " << setw(2) << i + 1 << " | " << setw(10) << daftarMenu[i].nama
                 << " | " << setw(6) << jumlahPesanan[i] << " | " << setw(7) << daftarMenu[i].harga
                 << " | " << setw(15) << totalPerItem << " |\n";
        }
    }

    file << "------------------------------------------------------------\n";
    file << "| TOTAL                                      | " << setw(15) << totalHarga << " |\n";
    file << "------------------------------------------------------------\n";
    file << "Bayar: " << bayar << endl;
    file << "Kembalian: " << kembalian << endl;
    file << "------------------------------------------------------------\n";

    file.close();

    cout << "\nStruk telah dicetak ke file struk.txt\n";
}

int main() {
    Menu daftarMenu[] = {
        {"rendang", 10000},
        {"nasi", 4000},
        {"es jeruk", 3500},
        {"ayam goreng", 12000},
        {"soto ayam", 8000},
        {"teh manis", 3000},
        {"kopi", 5000}
    };

    const int jumlahMenu = sizeof(daftarMenu) / sizeof(daftarMenu[0]);
    int jumlahPesanan[jumlahMenu] = {0};
    string namaPemesan;

    cout << "==================================="<<endl;
    cout << "  SELAMAT DATANG DI WARTEQ PADANG  "<<endl;
    cout << "==================================="<<endl;

    cout << "Pesanan atas nama: ";
    cin >> namaPemesan;

    char tambahLagi;
    do {
        tampilkanMenu(daftarMenu, jumlahMenu);

        int pilihan, jumlah;
        cout << "Pilih menu (1-" << jumlahMenu << "): ";
        cin >> pilihan;
        cout << "Jumlah: ";
        cin >> jumlah;

        if (pilihan >= 1 && pilihan <= jumlahMenu) {
            jumlahPesanan[pilihan - 1] += jumlah;
        } else {
            cout << "Pilihan tidak valid!\n";
        }

        cout << "Ada tambahan lagi [Y/T]: ";
        cin >> tambahLagi;
    } while (tambahLagi == 'Y' || tambahLagi == 'y');

    int totalHarga = hitungTotalHarga(daftarMenu, jumlahPesanan, jumlahMenu);

    int bayar, kembalian;
    cout << "Bayar: ";
    cin >> bayar;
    kembalian = bayar - totalHarga;

    cetakStruk(namaPemesan, daftarMenu, jumlahPesanan, jumlahMenu, totalHarga, bayar, kembalian);

    return 0;
}

