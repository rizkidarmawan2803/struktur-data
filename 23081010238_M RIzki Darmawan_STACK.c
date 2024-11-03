#include <stdio.h>
#include <stdlib.h>

// Struktur node untuk stack
struct node {
    int data;
    struct node *next;
};
typedef struct node node;

// Struktur stack yang memiliki pointer top dan penghitung jumlah elemen
struct stack {
    node *top;
    int count;
};
typedef struct stack Stack;

// Fungsi inisialisasi stack
void createStack(Stack *s) {
    s->top = NULL;
    s->count = 0;
}

// Mengecek apakah stack kosong
int isEmpty(Stack *s) {
    return s->count == 0;
}

// Mendapatkan jumlah elemen dalam stack
int stackCount(Stack *s) {
    return s->count;
}

// Menambahkan elemen ke dalam stack (push)
int push(Stack *s, int data) {
    node *pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal\n");
        return 0;
    }
    pNew->data = data;
    pNew->next = s->top;
    s->top = pNew;
    s->count++;
    return 1;
}

// Menghapus elemen dari stack (pop)
int pop(Stack *s, int *dataOut) {
    if (isEmpty(s)) {
        printf("Stack kosong!\n");
        return 0;
    }
    node *pDel = s->top;
    *dataOut = pDel->data;
    s->top = s->top->next;
    free(pDel);
    s->count--;
    return 1;
}

// Mengambil nilai teratas stack tanpa menghapusnya
int top(Stack *s, int *dataOut) {
    if (isEmpty(s)) {
        printf("Stack kosong!\n");
        return 0;
    }
    *dataOut = s->top->data;
    return 1;
}

// Menghitung total penjumlahan data dalam stack
int totalData(Stack *s) {
    int total = 0;
    node *pCur = s->top;
    while (pCur != NULL) {
        total += pCur->data;
        pCur = pCur->next;
    }
    return total;
}

// Menghancurkan stack dan membebaskan memori
void destroyStack(Stack *s) {
    while (!isEmpty(s)) {
        int temp;
        pop(s, &temp); // Menghapus elemen dari stack hingga kosong
    }
}

// Mencari data dalam stack
void cariData(Stack *s, int bil) {
    node *pCur = s->top;
    int found = 0;
    while (pCur != NULL) {
        if (pCur->data == bil) {
            printf("Data %d ditemukan dalam stack.\n", bil);
            found = 1;
            break;
        }
        pCur = pCur->next;
    }
    if (!found) {
        printf("Data %d tidak ditemukan dalam stack.\n", bil);
    }
}

// Menampilkan isi stack (untuk debugging)
void displayStack(Stack *s) {
    node *pWalker = s->top;
    printf("Isi stack: ");
    while (pWalker != NULL) {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    }
    printf("NULL\n");
}

// Fungsi utama dengan menu
int main() {
    Stack s;
    createStack(&s);
    char pilih;
    int bil, dataOut;

    do {
        system("cls");
        printf("masukkan pilihan\n");
        printf("0. Push data ke stack\n");
        printf("1. Push data di posisi tertentu\n");
        printf("2. Push data di akhir stack\n");
        printf("3. Tampilkan isi stack\n");
        printf("4. Pop data dari awal stack\n");
        printf("5. Pop data di tengah stack\n");
        printf("6. Pop data dari akhir stack\n");
        printf("7. Cari data dalam stack\n");
        printf("8. Tampilkan jumlah data\n");
        printf("9. Tampilkan total penjumlahan data\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf(" %c", &pilih);

        switch (pilih) {
            case '0':  // Push data ke stack
                printf("Masukkan data yang ingin di-push: ");
                scanf("%d", &bil);
                if (push(&s, bil))
                    printf("Data %d berhasil di-push ke stack.\n", bil);
                else
                    printf("Push gagal.\n");
                break;

            case '1':  // Push data di posisi tertentu (tidak digunakan di stack, opsi tetap disertakan)
                printf("Operasi ini tidak didukung untuk stack.\n");
                break;

            case '2':  // Push data di akhir stack
                printf("Masukkan data yang ingin di-push ke akhir: ");
                scanf("%d", &bil);
                if (push(&s, bil))
                    printf("Data %d berhasil di-push ke akhir stack.\n", bil);
                else
                    printf("Push gagal.\n");
                break;

            case '3':  // Tampilkan isi stack
                displayStack(&s);
                break;

            case '4':  // Pop data dari awal (teratas)
                if (pop(&s, &dataOut))
                    printf("Data %d berhasil di-pop dari stack.\n", dataOut);
                else
                    printf("Pop gagal.\n");
                break;

            case '5':  // Pop data di tengah stack (tidak digunakan di stack, opsi tetap disertakan)
                printf("Operasi ini tidak didukung untuk stack.\n");
                break;

            case '6':  // Pop data di akhir stack
                if (pop(&s, &dataOut))
                    printf("Data %d berhasil di-pop dari akhir stack.\n", dataOut);
                else
                    printf("Pop gagal.\n");
                break;

            case '7':  // Cari data dalam stack
                printf("Masukkan data yang ingin dicari: ");
                scanf("%d", &bil);
                cariData(&s, bil);
                break;

            case '8':  // Tampilkan jumlah data
                printf("Jumlah data dalam stack: %d\n", stackCount(&s));
                break;

            case '9':  // Tampilkan total penjumlahan data
                printf("Total penjumlahan data dalam stack: %d\n", totalData(&s));
                break;

            default:
                if (pilih != 'q')
                    printf("Pilihan tidak valid.\n");
                break;
        }
        printf("Tekan sembarang tombol untuk melanjutkan...");
        getchar();  // Menunggu input untuk melanjutkan
        getchar();

    } while (pilih != 'q');

    destroyStack(&s);
    printf("Program selesai.\n");
    return 0;
}
