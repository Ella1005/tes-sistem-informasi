#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>

using namespace std;

struct Transaksi {
    string jenis;
    double jumlah;
    string tanggal;
    string deskripsi;
    string kategori;
};

double saldo = 0.0;
vector<Transaksi> transaksi;
map<string, vector<Transaksi>> transaksiBerkategori;

void PemisahTampilan() {
    cout << "============================" << endl;
}

char PilihJenisTransaksi() {
    char jenisTransaksi;
    cout << "Pilih jenis transaksi (a: pemasukan, b: pengeluaran): ";
    cin >> jenisTransaksi;
    return tolower(jenisTransaksi); // Mengonversi ke huruf kecil
}

void TambahTransaksi() {
    Transaksi transaksiBaru;
    char jenisTransaksi = PilihJenisTransaksi();

    if (jenisTransaksi == 'a') {
        transaksiBaru.jenis = "pemasukan";
    } else if (jenisTransaksi == 'b') {
        transaksiBaru.jenis = "pengeluaran";
    } else {
        cout << "Jenis transaksi tidak valid. Harap pilih 'a' (pemasukan) atau 'b' (pengeluaran)." << endl;
        return;
    }

    cout << "Jumlah transaksi: ";
    cin >> transaksiBaru.jumlah;
    cout << "Tanggal transaksi (YYYY-MM-DD): ";
    cin >> transaksiBaru.tanggal;
    cin.ignore();
    cout << "Deskripsi transaksi: ";
    getline(cin, transaksiBaru.deskripsi);
    cout << "Kategori transaksi: ";
    getline(cin, transaksiBaru.kategori);
    transaksiBaru.kategori[0] = tolower(transaksiBaru.kategori[0]);

    if (transaksiBaru.jenis == "pengeluaran" && transaksiBaru.jumlah > saldo) {
        cout << "Saldo tidak mencukupi untuk transaksi pengeluaran." << endl;
        return;
    }

    transaksi.push_back(transaksiBaru);
    saldo += (transaksiBaru.jenis == "pemasukan") ? transaksiBaru.jumlah : -transaksiBaru.jumlah;
    transaksiBerkategori[transaksiBaru.kategori].push_back(transaksiBaru);

    cout << "Transaksi berhasil ditambahkan." << endl;
}

void LihatSaldo() {
    cout << "Saldo saat ini: " << ((transaksi.empty()) ? 0 : saldo) << endl;
}

void LihatTransaksiPerKategori() {
    cout << "Transaksi per kategori:" << endl;

    if (transaksiBerkategori.empty()) {
        cout << "Tidak ada kategori transaksi yang tersedia." << endl;
    } else {
        for (const auto& pasangan : transaksiBerkategori) {
            cout << "Kategori: " << pasangan.first << endl;

            if (pasangan.second.empty()) {
                cout << "  Tidak ada riwayat transaksi untuk kategori ini." << endl;
            } else {
                for (const Transaksi& transaksi : pasangan.second) {
                    cout << "  Jenis: " << transaksi.jenis << ", Tanggal: " << transaksi.tanggal << ", Jumlah: " << transaksi.jumlah << endl;
                }
            }
        }
    }
}

void TampilkanLaporanKeuangan() {
    while (true) {
        int pilihan;

        cout << "Pilih tipe laporan:\n";
        cout << "1. Laporan berdasarkan tanggal\n";
        cout << "2. Laporan berdasarkan kategori\n";
        cout << "3. Laporan berdasarkan jenis transaksi\n";
        cout << "4. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string tanggalCari;
                cout << "Masukkan tanggal (YYYY-MM-DD): ";
                cin >> tanggalCari;

                cout << "Laporan berdasarkan tanggal " << tanggalCari << ":\n";
                for (const Transaksi& transaksi : transaksi) {
                    if (transaksi.tanggal == tanggalCari) {
                        cout << "  Jenis: " << transaksi.jenis << ", Kategori: " << transaksi.kategori << ", Jumlah: " << transaksi.jumlah << endl;
                    }
                }
                break;
            }
            case 2: {
                string kategoriCari;
                cout << "Masukkan kategori yang ingin dicari: ";
                cin.ignore();
                getline(cin, kategoriCari);

                cout << "Laporan berdasarkan kategori " << kategoriCari << ":\n";
                for (const Transaksi& transaksi : transaksiBerkategori[kategoriCari]) {
                    cout << "  Jenis: " << transaksi.jenis << ", Tanggal: " << transaksi.tanggal << ", Jumlah: " << transaksi.jumlah << endl;
                }
                break;
            }
            case 3: {
                char jenisTransaksi = PilihJenisTransaksi();
                string jenisCari;

                if (jenisTransaksi == 'a') {
                    jenisCari = "pemasukan";
                } else if (jenisTransaksi == 'b') {
                    jenisCari = "pengeluaran";
                } else {
                    cout << "Jenis transaksi tidak valid. Harap pilih 'a' (pemasukan) atau 'b' (pengeluaran)." << endl;
                    continue;
                }

                cout << "Laporan berdasarkan jenis transaksi " << jenisCari << ":\n";
                for (const Transaksi& transaksi : transaksi) {
                    if (transaksi.jenis == jenisCari) {
                        cout << "  Kategori: " << transaksi.kategori << ", Tanggal: " << transaksi.tanggal << ", Jumlah: " << transaksi.jumlah << endl;
                    }
                }
                break;
            }
            case 4:
                return;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

int main() {
    while (true) {
        int pilihan;

        PemisahTampilan();
        cout << "Aplikasi Catatan Keuangan\n";
        PemisahTampilan();
        cout << "Menu:\n";
        cout << "1. Tambah Transaksi\n";
        cout << "2. Lihat Saldo\n";
        cout << "3. Lihat Transaksi per Kategori\n";
        cout << "4. Tampilkan Laporan Keuangan\n";
        cout << "5. Keluar\n";
        cout << "Pilih tindakan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                TambahTransaksi();
                break;
            case 2:
                LihatSaldo();
                break;
            case 3:
                LihatTransaksiPerKategori();
                break;
            case 4:
                TampilkanLaporanKeuangan();
                break;
            case 5:
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}