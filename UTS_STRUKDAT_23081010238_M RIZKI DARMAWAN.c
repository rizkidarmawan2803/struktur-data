#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Peserta {
    char nama[50];
    char jenis_kelamin;
    struct Peserta* next;
};

struct Peserta* buatPesertaBaru(char nama[], char jenis_kelamin) {
    struct Peserta* pesertaBaru = (struct Peserta*)malloc(sizeof(struct Peserta));
    strcpy(pesertaBaru->nama, nama);
    pesertaBaru->jenis_kelamin = jenis_kelamin;
    pesertaBaru->next = NULL;
    return pesertaBaru;
}

void tambahPeserta(struct Peserta** head, char nama[], char jenis_kelamin) {
    struct Peserta* pesertaBaru = buatPesertaBaru(nama, jenis_kelamin);
    
    if (*head == NULL) {
        *head = pesertaBaru;
    } else {
        struct Peserta* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = pesertaBaru;
    }
    
    printf("Peserta %s ditambahkan ke lingkaran.\n", nama);
}

void hapusPeserta(struct Peserta** head, char nama[]) {
    struct Peserta* temp = *head;
    struct Peserta* prev = NULL;

    if (temp != NULL && strcmp(temp->nama, nama) == 0) {
        *head = temp->next;
        free(temp);
        printf("%s keluar dari lingkaran.\n", nama);
        return;
    }

    while (temp != NULL && strcmp(temp->nama, nama) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Peserta dengan nama %s tidak ditemukan.\n", nama);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("%s keluar dari lingkaran.\n", nama);
}

void tampilkanKegiatan(struct Peserta* lingkaranMahasiswa, struct Peserta* lingkaranMahasiswi) {
    printf("\nKegiatan di acara api unggun:\n");

    if (lingkaranMahasiswa != NULL) {
        printf("\nKegiatan untuk mahasiswa (Laki-laki):\n");
        struct Peserta* temp = lingkaranMahasiswa;
        while (temp != NULL) {
            printf("Peserta: %s\n", temp->nama);
            temp = temp->next;
        }
        printf("Kegiatan: bergandengan tangan dengan mahasiswa lainnya, berputar mengitari api unggun, dan mendirikan tenda.\n");
    }

    if (lingkaranMahasiswi != NULL) {
        printf("\nKegiatan untuk mahasiswi (Perempuan):\n");
        struct Peserta* temp = lingkaranMahasiswi;
        while (temp != NULL) {
            printf("Peserta: %s\n", temp->nama);
            temp = temp->next;
        }
        printf("Kegiatan: bergandengan tangan dengan mahasiswi lainnya, berputar mengitari api unggun, dan memasak di dapur.\n");
    }
}

void pisahkanDanTampilkan(struct Peserta* lingkaran, struct Peserta** lingkaranMahasiswa, struct Peserta** lingkaranMahasiswi) {
    struct Peserta* temp = lingkaran;
    
    while (temp != NULL) {
        if (temp->jenis_kelamin == 'L') {
            tambahPeserta(lingkaranMahasiswa, temp->nama, temp->jenis_kelamin);
        } else if (temp->jenis_kelamin == 'P') {
            tambahPeserta(lingkaranMahasiswi, temp->nama, temp->jenis_kelamin);
        }
        temp = temp->next;
    }

    tampilkanKegiatan(*lingkaranMahasiswa, *lingkaranMahasiswi);
}

int main() {
    struct Peserta* lingkaran = NULL;
    struct Peserta* lingkaranMahasiswa = NULL;
    struct Peserta* lingkaranMahasiswi = NULL;

    int pilihan;
    char nama[50];
    char jenis_kelamin;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Tambah peserta ke lingkaran\n");
        printf("2. Hapus peserta dari lingkaran\n");
        printf("3. Pisahkan dan tampilkan kegiatan di lingkaran\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            printf("\nMasukkan nama peserta: ");
            scanf("%s", nama);
            printf("Masukkan jenis kelamin (L/P): ");
            scanf(" %c", &jenis_kelamin);

            tambahPeserta(&lingkaran, nama, jenis_kelamin);
        } else if (pilihan == 2) {
            printf("\nMasukkan nama peserta yang ingin keluar: ");
            scanf("%s", nama);
            hapusPeserta(&lingkaran, nama);
        } else if (pilihan == 3) {
            lingkaranMahasiswa = NULL;
            lingkaranMahasiswi = NULL;
            
            pisahkanDanTampilkan(lingkaran, &lingkaranMahasiswa, &lingkaranMahasiswi);
        } else if (pilihan == 4) {
            break;
        } else {
            printf("Pilihan tidak valid. Coba lagi.\n");
        }
    }

    return 0;
}
