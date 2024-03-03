#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ban_DLinkedln();
    void signIn_admin();
        void dash_admin();
                void add_lowongan();
                void delate_lowongan();
                void list_lowongan();
                    void bubblesort_list_lowongan();
                    void view_bubblesort_list_lowongan();

                void dash_akun();
                    void akun_prem();
                        void bubblesort_list_prem();
                        void view_bubblesort_list_prem();
                    void akun_norm();
                        void bubblesort_list_norm();
                        void view_bubblesort_list_norm();
            
    void dash_user();
            void signIn_user();
            void signUp_user();
                void  view_profile();
                    void edit_profile();
                void search_user();
                void search_lowongan(); // disini bisa langsung daftar pekerjaan
                void list_lowongan();
                void upgrade_akun_prem();

FILE *DataLowongan;
FILE *DataPrem;
FILE *DataNorm;

struct User{
    // biodata profile
    char Nama[20], username[20], email[20], pass[20], kontak[10], alamat[20], pekerjaan[20], aboutMe[50], pengalaman[30], pendidikan[30];

    // lowongan kerja
    char perusahaan[20], posisi[20], peryaratan[100], gaji[20], open[20], tutup[20]; 
}usernya[1000];

struct User temp;
struct User user;

void ban_DLinkedln() {
    printf("---------------------------------------------------\n");
    printf("||              Welcome to D'Linkedln             ||\n");
    printf("---------------------------------------------------\n");
    printf("||     Your Gateway to Professional Networking    ||\n");
    printf("----------------------------------------------------\n");
}

void signIn_admin(int percobaan){
    char username[30], pass[30];
    ban_DLinkedln();

    printf("|| Username:    "); gets(username);
    printf("|| Password:    "); gets(pass);

    if(strcmp(username, "ALLdaskom")==0 & strcmp(pass, "000")==0){
        printf("\n");
        printf("Anda berhasil login!! \n");
        system("pause"); system("cls");
        dash_admin();

    }else{
        printf("\n");
        printf("Gagal login, username atau password tidak sesuai!! \n");
        if(percobaan <3){
            system("pause"); system("cls");
            signIn_admin(percobaan+1);
        } else{
            printf("\n");
            printf("Aktivitas anda telah di banned oleh Google\n");
            printf("Silahkan hubungi Staf IT!!\n");
            system("pause"); system("cls");
            main();
        }
    }
}
