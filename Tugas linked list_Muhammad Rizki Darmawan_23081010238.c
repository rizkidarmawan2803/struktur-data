#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

// Fungsi utama
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void tranverse(node *head);
void hapusAwal(node **head);
void hapusTengah(node **head, int bil);
void hapusAkhir(node **head);
void cariData(node *head, int bil);
int jumlahData(node *head);
int totalData(node *head);



//========================================================

int main() {
    node *head = NULL;
    char pilih;
    int bil;

    do {
        system("cls");
        printf("masukkan pilihan\n");
        printf("0. tambah data di awal\n");
        printf("1. tambah data di tengah list\n");
        printf("2. tambah data di akhir list\n");
        printf("3. cetak isi list\n");
        printf("4. hapus data di awal\n");
        printf("5. hapus data di tengah\n");
        printf("6. hapus data di akhir\n");
        printf("7. cari data\n");
        printf("8. tampilkan jumlah data\n");
        printf("9. tampilkan total penjumlahan data\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);

        switch (pilih) {
            case '0':
                tambahAwal(&head);
                break;
            case '1':
                tambahData(&head);
                break;
            case '2':
                tambahAkhir(&head);
                break;
            case '3':
                tranverse(head);
                getch();
                break;
            case '4':
                hapusAwal(&head);
                getch();
                break;
            case '5':
                printf("Masukkan nilai data yang ingin dihapus: ");
                scanf("%d", &bil);
                hapusTengah(&head, bil);
                getch();
                break;
            case '6':
                hapusAkhir(&head);
                getch();
                break;
            case '7':
                printf("Masukkan nilai yang ingin dicari: ");
                scanf("%d", &bil);
                cariData(head, bil);
                getch();
                break;
            case '8':
                printf("Jumlah data: %d\n", jumlahData(head));
                getch();
                break;
            case '9':
                printf("Total penjumlahan data: %d\n", totalData(head));
                getch();
                break;
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    printf("masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    scanf("%d", &pos);
    printf("\nbilangan : ");
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nnode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nalokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    printf("masukkan bilangan : ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tranverse(node *head) {
    node *pWalker = head;

    while (pWalker != NULL) {
        printf("%d\t", pWalker->data);
        pWalker = pWalker->next;
        printf(" -> ");
    }
    printf("NULL\n");
}

//========================================================

void hapusAwal(node **head) {
    node *pDel;

    if (*head == NULL) {
        printf("List kosong!\n");
    } else {
        pDel = *head;
        *head = (*head)->next;
        free(pDel);
        printf("Data di awal berhasil dihapus!\n");
    }
}

//========================================================

void hapusTengah(node **head, int bil) {
    node *pCur, *pPrev;

    if (*head == NULL) {
        printf("List kosong!\n");
    } else {
        pCur = *head;
        pPrev = NULL;

        while (pCur != NULL && pCur->data != bil) {
            pPrev = pCur;
            pCur = pCur->next;
        }

        if (pCur == NULL) {
            printf("Data tidak ditemukan!\n");
        } else {
            if (pPrev == NULL) {
                *head = pCur->next;
            } else {
                pPrev->next = pCur->next;
            }
            free(pCur);
            printf("Data %d berhasil dihapus!\n", bil);
        }
    }
}

//========================================================

void hapusAkhir(node **head) {
    node *pCur, *pPrev;

    if (*head == NULL) {
        printf("List kosong!\n");
    } else {
        pCur = *head;
        pPrev = NULL;

        while (pCur->next != NULL) {
            pPrev = pCur;
            pCur = pCur->next;
        }

        if (pPrev == NULL) {
            *head = NULL;
        } else {
            pPrev->next = NULL;
        }

        free(pCur);
        printf("Data di akhir berhasil dihapus!\n");
    }
}

//========================================================

void cariData(node *head, int bil) {
    node *pCur = head;
    int found = 0;

    while (pCur != NULL) {
        if (pCur->data == bil) {
            printf("Data %d ditemukan!\n", bil);
            found = 1;
            break;
        }
        pCur = pCur->next;
    }

    if (!found) {
        printf("Data %d tidak ditemukan!\n", bil);
    }
}

//========================================================

int jumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }

    return count;
}

//========================================================

int totalData(node *head) {
    int total = 0;
    node *pCur = head;

    while (pCur != NULL) {
        total += pCur->data;
        pCur = pCur->next;
    }

    return total;
}

//========================================================
