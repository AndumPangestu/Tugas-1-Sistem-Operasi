#include "header.h"

/* Inisialisasi queue. */

// Prosedur untuk membuat queue.
void createqueue(queue *Q)
{
    // Inisialisasi posisi top dari queue ke NULL.
    (*Q).first = NULL;
    (*Q).last = NULL;
}

/* Modifikasi queue. */

// Prosedur untuk menambahkan elemen ke queue.
void add(int data, queue *Q)
{
    // Menyiapkan data dan alamatnya yang akan ditambahkan.
    element *new;
    new = (element*) malloc(sizeof(element));
    new->value = data; new->next = NULL;

    // Jika queue masih kosong...
    if((*Q).first == NULL)
    {
        // "Arahkan" pointer elemen pertama ke elemen baru.
        (*Q).first = new;
    }
    // Jika elemen sudah ada...
    else
    {
        // "Arahkan" pointer next elemen terakhir ke elemen baru.
        (*Q).last->next = new;
    }

    // Jadikan data baru ini data terakhir.
    (*Q).last = new;
    new = NULL;
}

// Prosedur untuk menghapus data dari queue.
void del(queue *Q)
{
    // Jika ada elemen pada queue... 
    if((*Q).first != NULL)
    {
        // Menentukan pointer yang akan dihapus.
        element *del;
        del = (*Q).first;

        // Jika elemen ini merupakan terakhir...
        if(countelement(*Q) == 1)
        {
            // Set first dan last menjadi NULL.
            (*Q).first = NULL;
            (*Q).last = NULL;
        }
        // Jika elemen masih banyak...
        else
        {
            // Set first ke data setelahnya.
            (*Q).first = (*Q).first->next;
        }

        // Membersihkan memori dari elemen yang dihapus.
        del->next = NULL;
        free(del);
    }
}

// Fungsi untuk memeriksa apakah queue kosong.
int isempty(queue Q)
{
    int result = 0;
    if(Q.first == NULL)
    {
        result = 1;
    }

    return result;
}

// Fungsi untuk menghitung banyaknya elemen.
int countelement(queue Q)
{
    // Deklarasi nilai total.
    int total = 0;

    // Menghitung data di queue secara berurutan.
    if(Q.first != NULL)
    {
        element *current;
        current = Q.first;

        while(current != NULL)
        {
            total++;
            current = current->next;
        }
    }

    // Mengembalikan nilai total.
    return total;
}

int countbuffer(queue Q)
{
    int total = 0;

    // Menghitung data di queue secara berurutan.
    if(Q.first != NULL)
    {
        element *current;
        current = Q.first;

        while(current != NULL)
        {
            total += current->value;
            current = current->next;
        }
    }

    // Mengembalikan nilai total.
    return total;
}