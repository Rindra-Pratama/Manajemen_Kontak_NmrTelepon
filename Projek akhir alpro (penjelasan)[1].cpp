#include <iostream>
#include <string>

using namespace std;

// Kelas Kontak untuk menyimpan informasi kontak
class Kontak {
public:
    string nama, nomor_telepon, email;
    
    // Konstruktor dengan nilai default
    Kontak(string nama = "", string nomor_telepon = "", string email = "")
    : nama(nama), nomor_telepon(nomor_telepon), email(email) {}
    
    // Metode untuk menampilkan informasi kontak
    void display() {
        cout << "Nama         : " << nama << endl;
        cout << "Nomor Telepon: " << nomor_telepon << endl;
        cout << "Email        : " << email << endl;
    }
};

// Kelas ManajemenKontak untuk mengelola daftar kontak
class ManajemenKontak {
private:
    Kontak* daftar_kontak; // Array dinamis untuk menyimpan kontak
    int jumlah_kontak, kapasitas;
    
    // Metode untuk mengubah ukuran array ketika penuh
    void resize() {
        kapasitas *= 2; // Menggandakan kapasitas
        Kontak* temp = new Kontak[kapasitas];
        for (int i = 0; i < jumlah_kontak; i++) {
            temp[i] = daftar_kontak[i];
        }
    }
    // Metode statis untuk menukar dua kontak
    static void swap(Kontak& a, Kontak& b) {
        Kontak temp = a;
        a = b;
        b = temp;
    }

public:
    // Konstruktor untuk menginisialisasi manajemen kontak
    ManajemenKontak() : jumlah_kontak(0), kapasitas(10) {
        daftar_kontak = new Kontak[kapasitas];
    }
    
    // untuk menambah kontak baru
    void tambahKontak(string nama, string nomor_telepon, string email) {
        if (jumlah_kontak == kapasitas) {
            resize();
        }
        daftar_kontak[jumlah_kontak++] = Kontak(nama, nomor_telepon, email);
    }
    
    // Metode untuk mencari kontak berdasarkan kata kunci
    void cariKontak(string kata_kunci) {
        for (int i = 0; i < jumlah_kontak; ++i) {
            if (daftar_kontak[i].nama.find(kata_kunci) < daftar_kontak[i].nama.size() ||
                daftar_kontak[i].nomor_telepon.find(kata_kunci) < daftar_kontak[i].nomor_telepon.size() ||
                daftar_kontak[i].email.find(kata_kunci) < daftar_kontak[i].email.size()) {
                daftar_kontak[i].display();
            }
        }
    }

    // Metode untuk mengurutkan kontak berdasarkan nama
    void urutkanKontak() {
        for (int i = 0; i < jumlah_kontak - 1; ++i) {
            for (int j = 0; j < jumlah_kontak - i - 1; ++j) {
                if (daftar_kontak[j].nama > daftar_kontak[j + 1].nama) {
                    swap(daftar_kontak[j], daftar_kontak[j + 1]); // SWAP DI UBAH MENJADI TEMPORARY
                }
            }
        }
    }

    // Metode untuk menampilkan semua kontak
    void displaySemuaKontak() {
        for (int i = 0; i < jumlah_kontak; ++i) {
            daftar_kontak[i].display();
        }
    }

    // Metode untuk mengedit kontak berdasarkan nama
    void editKontak(string nama) {
        for (int i = 0; i < jumlah_kontak; ++i) {
            if (daftar_kontak[i].nama == nama) {
                cout << "Masukkan Nama baru         : ";
                getline(cin, daftar_kontak[i].nama);
                cout << "Masukkan Nomor Telepon baru: ";
                getline(cin, daftar_kontak[i].nomor_telepon);
                cout << "Masukkan Email baru        : ";
                getline(cin, daftar_kontak[i].email);
                cout << "Kontak berhasil diperbarui.\n";
                return;
            }
        }
        cout << "Kontak dengan nama " << nama << " tidak ditemukan.\n";
    }
};

int main() {
    ManajemenKontak manajemen_kontak; // Objek untuk mengelola kontak
    string nama, nomor_telepon, email;
    int pilihan;

    do {
        // Menampilkan menu
        cout << "Menu: \n1. Tambah Kontak \n2. Cari Kontak \n3. Urutkan Kontak \n4. Tampilkan Semua Kontak \n5. Edit Kontak \n6. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        cin.ignore(); // Membersihkan newline character setelah cin

        switch (pilihan) {
            case 1:
                // Menambah kontak baru
                cout << "Masukkan Nama: ";
                getline(cin, nama);
                cout << "Masukkan Nomor Telepon: ";
                getline(cin, nomor_telepon);
                cout << "Masukkan Email: ";
                getline(cin, email);
                manajemen_kontak.tambahKontak(nama, nomor_telepon, email);
                break;
            case 2:
                // Mencari kontak berdasarkan kata kunci
                cout << "Masukkan Nama, Nomor Telepon, atau Email untuk mencari : ";
                getline(cin, nama); // Menggunakan variabel nama sebagai kata kunci
                manajemen_kontak.cariKontak(nama);
                break;
            case 3:
                // Mengurutkan kontak berdasarkan nama
                manajemen_kontak.urutkanKontak();
                cout << "Kontak telah diurutkan berdasarkan nama.\n";
                break;
            case 4:
                // Menampilkan semua kontak
                cout << "Daftar Semua Kontak:\n";
                manajemen_kontak.displaySemuaKontak();
                break;
            case 5:
                // Mengedit kontak berdasarkan nama
                cout << "Masukkan Nama kontak yang ingin diedit: ";
                getline(cin, nama);
                manajemen_kontak.editKontak(nama);
                break;
            case 6:
                // Keluar dari program
                cout << "Keluar.\n";
                break;
            default:
                // Pilihan tidak valid
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 6);

    return 0;
}

