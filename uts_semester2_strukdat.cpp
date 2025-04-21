#include <iostream>
#include <string>
#include <map> 
using namespace std;

namespace operation_Q {
    typedef struct {
        int ID;
        string nama;
        int prioritas;
    } Pelanggan;

    typedef struct elm* alamatelm;
    typedef struct elm {
        Pelanggan kontainer;
        alamatelm next;
    } elemen;

    typedef struct {
        elemen* first;
        elemen* last;
    } Queue;

    void createEmpty(Queue* Q) {
        (*Q).first = nullptr;
        (*Q).last = nullptr;
    }

    bool isEmpty(Queue* Q) {
        return (Q->first == nullptr);
    }

    int countElement(Queue Q) {
        int hasil = 0;
        if (Q.first != nullptr) {
            elemen* bantu = Q.first;
            while (bantu != nullptr) {
                hasil++;
                bantu = bantu->next;
            }
        }
        return hasil;
    }

    void add(int id, string nama, int prioritas, Queue* Q) {
        elemen* baru = new elemen;
        baru->kontainer.ID = id;
        baru->kontainer.nama = nama;
        baru->kontainer.prioritas = prioritas;
        baru->next = nullptr;

        if ((*Q).first == nullptr) {
            (*Q).first = baru;
            (*Q).last = baru;
        }
        else {
            elemen* prev = nullptr;
            elemen* curr = (*Q).first;
            while (curr != nullptr && curr->kontainer.prioritas <= prioritas) {
                prev = curr;
                curr = curr->next;
            }
            if (prev == nullptr) {
                baru->next = (*Q).first;
                (*Q).first = baru;
            }
            else {
                prev->next = baru;
                baru->next = curr;
            }

            if (baru->next == nullptr) {
                (*Q).last = baru;
            }
        }
    }

    void del(Queue* Q) {
        if ((*Q).first != nullptr) {
            elemen* hapus = (*Q).first;
            if (countElement(*Q) == 1) {
                (*Q).first = nullptr;
                (*Q).last = nullptr;
            }
            else {
                (*Q).first = (*Q).first->next;
                hapus->next = nullptr;
            }

            delete hapus;
        }
    }

    void printQueue(Queue Q) {
        if (Q.first != nullptr) {
            cout << "======= ANTREAN LAYANAN =======\n\n";
            elemen* bantu = Q.first;
            int i = 1;
            while (bantu != nullptr) {
                cout << "------------------------------\n";
                cout << "Antrean ke-" << i << endl;
                cout << "ID : " << bantu->kontainer.ID << endl;
                cout << "Nama : " << bantu->kontainer.nama << endl;
                cout << "Level Prioritas : " << bantu->kontainer.prioritas << endl;
                bantu = bantu->next;
                i++;
            }
            cout << "------------------------------\n";
        }
        else {
            cout << "Antrean kosong!\n";
        }
    }

    void cariPelanggan(int id, Queue Q) {
        elemen* bantu = Q.first;
        bool ditemukan = false;
        while (bantu != nullptr) {
            if (bantu->kontainer.ID == id) {
                cout << "Pelanggan ditemukan!\n";
                cout << "ID : " << bantu->kontainer.ID << endl;
                cout << "Nama : " << bantu->kontainer.nama << endl;
                cout << "Level Prioritas : " << bantu->kontainer.prioritas << endl;
                ditemukan = true;
                break;
            }
            bantu = bantu->next;
        }
        if (!ditemukan) {
            cout << "Pelanggan dengan ID " << id << " tidak ditemukan\n";
        }
    }

    bool login(string role) {
        string pass;
        int percobaan = 3;
        string passwordBenar = (role == "admin") ? "admin123" : "teknisi123";

        while (percobaan > 0) {
            cout << "Masukkan password " << role << " : ";
            cin >> pass;
            if (pass == passwordBenar) {
                cout << "Login berhasil!\n";
                return true;
            }
            else {
                percobaan--;
                cout << "Password salah. Sisa percobaan: " << percobaan << endl;
            }
        }
        return false;
    }

}

namespace operation_S {
    struct Node {
        string pengirim;
        string pesan;
        Node* next;
    };

    class chatstack {
    private:
        Node* top;

    public:
        chatstack() {
            top = nullptr;
        }

        void push(string nama, string message) {
            Node* newNode = new Node;
            newNode->pengirim = nama;
            newNode->pesan = message;
            newNode->next = top;
            top = newNode;
        }

        void pop() {
            if (top == nullptr) {
                cout << "Tidak ada pesan yang bisa dihapus.\n";
                return;
            }
            Node* temp = top;
            top = top->next;
            delete temp;
        }

        void display() {
            if (top == nullptr) {
                cout << "Belum ada percakapan\n";
                return;
            }
            Node* current = top;
            cout << "\n--- RIWAYAT PERCAKAPAN TERBARU ---\n";
            while (current != nullptr) {
                cout << current->pengirim << " : " << current->pesan << endl;
                current = current->next;
            }
        }

        ~chatstack() {
            while (top != nullptr) {
                pop();
            }
        }
    };

    int chat_interaktif() {
        int chat;
        cout << "\n======= CHAT INTERAKTIF =======\n";
        cout << "1) Kirim Pesan\n";
        cout << "2) Hapus Pesan Terakhir\n";
        cout << "3) Tampilkan Riwayat Percakapan\n";
        cout << "4) Keluar\n";
        cout << "==================================\n";
        cout << "Pilih Chat (1/2/3/4) : ";
        cin >> chat;

        if (chat < 1 || chat > 4) {
            cout << "Invalid input. Please enter a valid option\n";
        }
        return chat;
    }
}

namespace Menu {
    int Menu_Utama() {
        int menu;
        do {
            cout << "\n============= MENU UTAMA ============\n";
            cout << "1) Administrator\n";
            cout << "2) Teknisi\n";
            cout << "3) Registrasi\n";
            cout << "4) Keluar Program\n";
            cout << "=======================================\n";
            cout << "Pilih Menu (1/2/3/4) : ";
            cin >> menu;

            if (menu < 1 || menu > 4) {
                cout << "Invalid input. Please enter a valid option\n";
            }
        } while (menu < 1 || menu > 4);

        return menu;
    }

    int Menu_Admin() {
        int menuadmin;
        do {
            cout << "\n====== MENU ADMIN =======\n";
            cout << "1) Lihat Antrean\n";
            cout << "2) Lihat Riwayat Interaksi\n";
            cout << "3) Cari Pelanggan\n";
            cout << "4) Keluar Program\n";
            cout << "===========================\n";
            cout << "Pilih Menu (1/2/3/4) : ";
            cin >> menuadmin;

            if (menuadmin < 1 || menuadmin > 4) {
                cout << "Invalid input. Please enter a valid option\n";
            }
        } while (menuadmin < 1 || menuadmin > 4);

        return menuadmin;
    }

    int Menu_teknisi() {
        int menuteknis;
        do {
            cout << "\n====== MENU TEKNISI ======\n";
            cout << "1) Layanan Pelanggan\n";
            cout << "2) Keluar program\n";
            cout << "============================\n";
            cout << "Pilih Menu (1/2) : ";
            cin >> menuteknis;

            if (menuteknis < 1 || menuteknis > 2) {
                cout << "Invalid input. Please enter a valid option\n";
            }
        } while (menuteknis < 1 || menuteknis > 2);

        return menuteknis;
    }

    int Menu_Registrasi() {
        int menuregis;
        do {
            cout << "\n======= MENU REGISTRASI =======\n";
            cout << "1) Masuk Antrean\n";
            cout << "2) Keluar Program\n";
            cout << "=================================\n";
            cout << "Pilih Menu (1/2) : ";
            cin >> menuregis;

            if (menuregis < 1 || menuregis > 2) {
                cout << "Invalid input. Please enter a valid option\n";
            }
        } while (menuregis < 1 || menuregis > 2);
        return menuregis;
    }
}

namespace greetings {
    inline void sapa() {
        cout << "\n======= LAYANAN PELANGGAN ESHER =======\n";
        cout << "Selamat datang di Layanan Pelanggan Esher\n";
        cout << "Harap isi menu dibawah ini\n";
    }

    inline void terimakasih() {
        cout << "Terima kasih telah menggunakan jasa layanan kami\n";
        cout << "Tim kami akan segera memproses permintaan Anda\n";
    }
}

using namespace greetings;
using namespace Menu;
using namespace operation_Q;
using namespace operation_S;

int main() {
    Queue Q;
    createEmpty(&Q);
    string nama1 = "Teknisi";
    string nama2 = "User";
    string pesan;
    bool giliranUser1 = true;

    // MAP untuk simpan chat dari ID pelanggan
    map<int, chatstack> daftarChat;

    int masuk;
    do {
        sapa();
        masuk = Menu_Utama();

        switch (masuk) {
        case 1:
            if (login("admin")) {
                int pilihadmin;
                do {
                    pilihadmin = Menu_Admin();
                    switch (pilihadmin) {
                    case 1:
                        printQueue(Q);
                        break;
                    case 2: {
                        int idChat;
                        cout << "Masukkan ID pelanggan untuk melihat riwayat chat: ";
                        cin >> idChat;
                        if (daftarChat.find(idChat) != daftarChat.end()) {
                            daftarChat[idChat].display();
                        }
                        else {
                            cout << "Tidak ada riwayat chat untuk ID tersebut.\n";
                        }
                        break;
                    }
                    case 3: {
                        int idcari;
                        cout << "Masukkan ID pelanggan : ";
                        cin >> idcari;
                        cariPelanggan(idcari, Q);
                        break;
                    }
                    }
                } while (pilihadmin != 4);
            }
            break;

        case 2:
            if (login("teknisi")) {
                int pilihtek;
                do {
                    pilihtek = Menu_teknisi();
                    switch (pilihtek) {
                    case 1: {
                        if (!isEmpty(&Q)) {
                            int currentID = Q.first->kontainer.ID;
                            cout << "Sedang melayani pelanggan dengan ID: " << currentID << endl;
                            int pilihanchat;
                            do {
                                pilihanchat = chat_interaktif();
                                switch (pilihanchat) {
                                case 1: {
                                    cout << "\n--- Mode Percakapan ---\n";
                                    cout << "Note : ketik '/keluar' untuk keluar dari mode percakapan\n\n";
                                    cin.ignore();
                                    while (true) {
                                        if (giliranUser1)
                                            cout << nama1 << ": ";
                                        else
                                            cout << nama2 << ": ";

                                        getline(cin, pesan);
                                        if (pesan == "/keluar") {
                                            cout << "Keluar dari mode percakapan.\n";
                                            break;
                                        }

                                        daftarChat[currentID].push(giliranUser1 ? nama1 : nama2, pesan);
                                        giliranUser1 = !giliranUser1;
                                    }
                                    break;
                                }
                                case 2:
                                    daftarChat[currentID].pop();
                                    break;
                                case 3:
                                    daftarChat[currentID].display();
                                    break;
                                case 4:
                                    cout << "Percakapan Selesai\n";
                                    break;
                                }
                            } while (pilihanchat != 4);
                            del(&Q);
                            cout << "Pelanggan telah dilayani\n";
                        }
                        else {
                            cout << "Tidak ada pelanggan dalam antrean.\n";
                        }
                        break;
                    }
                    case 2:
                        cout << "Keluar dari menu teknisi.\n";
                        break;
                    }
                } while (pilihtek != 2);
            }
            break;

        case 3: {
            int regis;
            do {
                regis = Menu_Registrasi();
                switch (regis) {
                case 1: {
                    int id, prioritas;
                    string nama;
                    cout << "Masukkan ID: ";
                    cin >> id;
                    cin.ignore();
                    cout << "Masukkan Nama: ";
                    getline(cin, nama);
                    cout << "Masukkan Prioritas (1=tinggi, 2=sedang, 3=rendah): ";
                    cin >> prioritas;
                    add(id, nama, prioritas, &Q);
                    cout << "Pelanggan berhasil masuk antrean!\n";
                    break;
                }
                case 2:
                    cout << "Keluar dari menu registrasi.\n";
                    break;
                }
            } while (regis != 2);
            break;
        }

        case 4:
            cout << "\nAnda memilih keluar dari program.\n";
            terimakasih();
            break;
        }
    } while (masuk != 4);

    return 0;
}