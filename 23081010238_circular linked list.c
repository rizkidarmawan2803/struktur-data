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
        printf("Masukkan pilihan\n");
        printf("0. Tambah data di awal\n");
        printf("1. Tambah data di tengah list\n");
        printf("2. Tambah data di akhir list\n");
        printf("3. Cetak isi list\n");
        printf("4. Hapus data di awal\n");
        printf("5. Hapus data di tengah\n");
        printf("6. Hapus data di akhir\n");
        printf("7. Cari data\n");
        printf("8. Tampilkan jumlah data\n");
        printf("9. Tampilkan total penjumlahan data\n");
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
    node *pNew, *pCur;

    printf("Masukkan bilangan: ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;

        if (*head == NULL) {
            pNew->next = pNew; 
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pNew->next = *head; 
            pCur->next = pNew;  
            *head = pNew;       
        }
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
    printf("\nPosisi penyisipan setelah data bernilai: ");
    scanf("%d", &pos);
    printf("\nBilangan: ");
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
        if (pCur == *head) break; 
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == *head && (*head == NULL || pCur->data != pos)) {
        printf("\nNode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
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

    printf("Masukkan bilangan: ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;

        if (*head == NULL) {
            pNew->next = pNew; 
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pCur->next = pNew;  
            pNew->next = *head; 
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tranverse(node *head) {
    node *pWalker;

    if (head == NULL) {
        printf("List kosong!\n");
        return;
    }

    pWalker = head;
    do {
        printf("%d\t -> ", pWalker->data);
        pWalker = pWalker->next;
    } while (pWalker != head);  
    printf("%d\n", head->data);
}

//========================================================

void hapusAwal(node **head) {
    node *pDel, *pCur;

    if (*head == NULL) {
        printf("List kosong!\n");
        return;
    }

    pDel = *head;

    if ((*head)->next == *head) {
        *head = NULL;
        free(pDel);
    } else {
        pCur = *head;
        while (pCur->next != *head) {
            pCur = pCur->next;
        }
        *head = (*head)->next;  
        pCur->next = *head;     
        free(pDel);
    }
    printf("Data di awal berhasil dihapus!\n");
}

//========================================================

void hapusTengah(node **head, int bil) {
    node *pCur, *pPrev;

    if (*head == NULL) {
        printf("List kosong!\n");
        return;
    }

    pCur = *head;
    pPrev = NULL;

    do {
        if (pCur->data == bil) break;
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head); 

    if (pCur == *head) {
        hapusAwal(head); 
    } else if (pCur->next == *head) {
        hapusAkhir(head); 
    } else {
        pPrev->next = pCur->next;
        free(pCur);
        printf("Data %d berhasil dihapus!\n", bil);
    }
}

//========================================================

void hapusAkhir(node **head) {
    node *pCur, *pPrev;

    if (*head == NULL) {
        printf("List kosong!\n");
        return;
    }

    pCur = *head;

    if ((*head)->next == *head) {
        *head = NULL;
        free(pCur);
    } else {
        pPrev = NULL;
        while (pCur->next != *head) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = *head; 
        free(pCur);
    }
    printf("Data di akhir berhasil dihapus!\n");
}

//========================================================

void cariData(node *head, int bil) {
    node *pCur = head;
    int found = 0;

    if (head == NULL) {
        printf("List kosong!\n");
        return;
    }

    do {
        if (pCur->data == bil) {
            printf("Data %d ditemukan!\n", bil);
            found = 1;
            break;
        }
        pCur = pCur->next;
    } while (pCur != head);  

    if (!found) {
        printf("Data %d tidak ditemukan!\n", bil);
    }
}

//========================================================

int jumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    if (head == NULL) return 0;

    do {
        count++;
        pCur = pCur->next;
    } while (pCur != head);  

    return count;
}

//========================================================

int totalData(node *head) {
    int total = 0;
    node *pCur = head;

    if (head == NULL) return 0;

    do {
        total += pCur->data;
        pCur = pCur->next;
    } while (pCur != head);  

    return total;
}
