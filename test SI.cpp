#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>

using namespace std;

struct Uang {
    string jenis;
    double jumlah;
    string kategori;
    string tanggal;
    string deskripsi;
};


std::vector<Uang> catatan;


double saldo = 0.0;
vector<Uang> Keuangan;
vector<Uang> transaksib;
map<string, vector<Uang>> transaksiberkategori;


char Pilihjenist() {
    char Jenist;
    cout << "Pilih jenis transaksi ((+): pemasukan, (-): pengeluaran): ";
    cin >> Jenist;
    return tolower(Jenist);
}


void TamTransaksi() {
    Uang transaksib;
    char Jenist = Pilihjenist();
    if (Jenist == '+') {
        transaksib.jenis = "Pemasukan";
    } else if (Jenist == '-') {
        transaksib.jenis = "Pengeluaran";
    } else {
        cout << "Jenis transaksi tidak valid. Harap pilih '+' (Pemasukan) atau '-' (Pengeluaran)." << endl;
        return;
    }

    cout << "Jumlah: ";
    cin >> transaksib.jumlah;
    cout << "Kategori: ";
    getline(cin, transaksib.deskripsi);
    cin >> transaksib.kategori;
    cout << "Tanggal (dd/mm/yyyy): ";
    cin >> transaksib.tanggal;
    cin.ignore();
    transaksib.kategori[0] = tolower(transaksib.kategori[0]);

    if (transaksib.jenis == "pengeluaran" && transaksib.jumlah > saldo) {
        cout << "Saldo tidak mencukupi untuk transaksi pengeluaran. :(" << endl;
        return;
    }

    Keuangan.push_back(transaksib);
    saldo += (transaksib.jenis == "pemasukan") ? transaksib.jumlah : -transaksib.jumlah;
    transaksiberkategori[transaksib.kategori].push_back(transaksib);

    cout << "TransaksiiD \b: berhasil ditambahkan. :D" << endl;

}


void Ceksaldo() {
    cout << "Saldo saat ini: " << ((Keuangan.empty()) ? 0 : saldo) << endl;
}


void Pesan(void Ceksaldo()) {
    if (saldo < 0) {
        cout << "Peringatan: Saldo akun telah habis!" << endl;
    }
}


void Cekhistroriperkategori() {
    cout << "Transaksi per kategori:" << endl;

    if (transaksiberkategori.empty()) {
        cout << "Tidak ada kategori transaksi yang tersedia." << endl;
    } else {
        for (const auto& pair : transaksiberkategori) {
            cout << "Kategori: " << pair.first << endl;

            if (pair.second.empty()) {
                cout << "  Tidak ada riwayat transaksi untuk kategori ini." << endl;
            } else {
                for (const Uang& Keuangan : pair.second) {
                    cout << "  Jenis: " << Keuangan.jenis << ", Tanggal: " << Keuangan.tanggal << ", Jumlah: " << Keuangan.jumlah << endl;
                }
            }
        }
    }
}

void laporankeuangan() {
    while (true) {
        int pilihan;

        cout << "\nPilih tipe laporan:\n";
        cout << "1. Laporan berdasarkan tanggal\n";
        cout << "2. Laporan berdasarkan kategori\n";
        cout << "3. Laporan berdasarkan jenis transaksi\n";
        cout << "4. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string tancari;
                cout << "Masukkan tanggal (dd/mm/yyyy): ";
                cin >> tancari;

                cout << "Laporan berdasarkan tanggal " << tancari << ":\n";
                for (const Uang& Keuangan : Keuangan) {
                    if (Keuangan.tanggal == tancari) {
                        cout << "  Jenis: " << Keuangan.jenis << ", Kategori: " << Keuangan.kategori << ", Jumlah: " << Keuangan.jumlah << endl;
                    }
                }
                break;
            }
            case 2: {
                string katcari;
                cout << "Masukkan kategori yang ingin dicari: ";
                cin.ignore();
                getline(cin, katcari);

                cout << "Laporan berdasarkan kategori " << katcari << ":\n";
                for (const Uang& Kuangan : transaksiberkategori[katcari]) {
                    cout << "  Jenis: " << Kuangan.jenis << ", Tanggal: " << Kuangan.tanggal << ", Jumlah: " << Kuangan.jumlah << endl;
                }
                break;
            }
            case 3: {
                char Jenist = Pilihjenist();
                string jenisCari;

                if (Jenist == '+') {
                    jenisCari = "pemasukan";
                } else if (Jenist == '-') {
                    jenisCari = "pengeluaran";
                } else {
                    cout << "Jenis transaksi tidak valid. Harap pilih 'a' (pemasukan) atau 'b' (pengeluaran)." << endl;
                    continue;
                }

                cout << "Laporan berdasarkan jenis transaksi " << jenisCari << ":\n";
                for (const Uang &Keuangan: Keuangan) {
                    if (Keuangan.jenis == jenisCari) {
                        cout << "  Kategori: " << Keuangan.kategori << ", Tanggal: " << Keuangan.tanggal << ", Jumlah: "
                             << Keuangan.jumlah << endl;
                    }
                }
                break;
            }
                case 4:
                    return;
                default:
                    cout << "Pilihan tidak valid. Mohon pilih lagi :(" << endl;
            }
        }
    }


int main() {
    int pilihan;

    while (true) {

        cout << "\n";
        cout << "PROGRAM PENCATATAN KEUANGAN" << endl;
        cout << "\n";
        cout << "\nMenu:\n";
        cout << "1. Pendataan Transaksi\n";
        cout << "2. Cek Saldo\n";
        cout << "3. Lihat Laporan Keuangan\n";
        cout << "4. Lihat Transaksi Perkategori\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                TamTransaksi();
                break;
            case 2:
                Ceksaldo();
                Pesan(Ceksaldo);
                break;
            case 3:
                laporankeuangan();
                break;
            case 4: {
                Cekhistroriperkategori();
            }
                break;
            case 5: {
                return 0;
                }
            default: {
                cout << "Pilihan tidak valid. Mohon pilih lagi :(" << endl;
            }
        }
     }
 }
