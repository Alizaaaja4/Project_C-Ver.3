#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
        void warning();
            void signIn_user_norm();
            void signUp_user_norm();

            void signIn_user_prem();
            void signUp_user_prem();

                void  view_profile();
                    void edit_profile();
                    void search_user();
                    void search_lowongan(); // disini bisa langsung daftar pekerjaan
                    void list_lowongan();
                    void upgrade_akun_prem();

FILE *DataLowongan;
FILE *DataLowongan_backup;
FILE *DataPrem;
FILE *DataNorm;

struct User{
    // biodata profile
    char Nama[20], username[20], email[20], pass[20], kontak[10], alamat[20], pekerjaan[20], aboutMe[50], pengalaman1[300], pengalaman2[300], pengalaman3[300], pendidikan[30];

    // klasifikasi jenis akun
    char jenis_akun[100];

    // lowongan kerja
    char perusahaan[20], posisi[20], peryaratan1[1000], peryaratan2[1000], peryaratan3[1000], gaji[20], open[20], tutup[20]; 
}usernya[1000];

struct User temp;
struct User user;
char IdUser[50];


void ban_DLinkedln() {
    printf("---------------------------------------------------\n");
    printf("||              Welcome to D'Linkedln             ||\n");
    printf("---------------------------------------------------\n");
    printf("||     Your Gateway to Professional Networking    ||\n");
    printf("----------------------------------------------------\n");
}

void add_lowongan(){
    int i, j, k;

    DataLowongan = fopen("Daftar Lowongan Pekerjaan.dat", "ab");
    ban_DLinkedln();

    printf("|| Perusahaan: "); gets(user.perusahaan);
    printf("|| Posisi: "); gets(user.posisi);
    printf("|| Gaji: "); gets(user.gaji);
    printf("----------------------------------------------------\n");
    printf("|| Buka Pendaftaraan: "); gets(user.open);
    printf("|| Tutup Pendaftaran: "); gets(user.tutup);
    printf("----------------------------------------------------\n");
    printf("|| Input Persyaratan: \n");
    
    for(i=0; i<1; i++){
        printf("|| %d. ", i+1); gets(user.peryaratan1);
        for(j=1; j<2; j++){
            printf("|| %d. ", j+1); gets(user.peryaratan2);
            for(k=2; k<3; k++){
                printf("|| %d. ", k+1); gets(user.peryaratan3);
        }
        }
    }

    fwrite(&user, sizeof(struct User), 1, DataLowongan);
    fclose(DataLowongan);

    printf("\n");
    printf("Loading....\n"); sleep(2);
    printf("Lowongan baru telah ditambahkan!! \n");

    system("pause"); system("cls");

    dash_admin();
}

// sorting berdasarkan open lowongan kerja
void bubblesort_list_lowongan(int banyaklowongan, struct User usernya[]){
    int i, j;

    for(i=0; i<banyaklowongan; i++){
        for(j=0; j<banyaklowongan -i -1; j++){
            if(strcmp(usernya[j].open, usernya[j+1].open)>0){
                temp = usernya[j];
                usernya[j] = usernya[j+1];
                usernya[j+1] = temp;
            }
        }
    }
}   

void view_bubblesort_list_lowongan(int banyaklowongan, struct User usernya[]){
    int i, j, k, l;

    for(i=0; i<banyaklowongan; i++){
        printf("%d. Perusahaan: %s\n", i+1, usernya[i].perusahaan);
        printf("Posisi: %s\n", usernya[i].posisi);
        printf("Gaji: %s\n", usernya[i].gaji);
        printf("----------------------------------------------------\n");
        printf("Buka Pendaftaran: %s\n", usernya[i].open);
        printf("Tutup Pendaftaan: %s\n", usernya[i].tutup);
        printf("----------------------------------------------------\n");
        printf("Persyaratan:\n");

        // Menampilkan setiap persyaratan dalam array perusahaan
        for(j = 0; j < 1; j++){
            printf("%d. %s\n", j+1, usernya[i].peryaratan1);
                for(k = 1; k < 2; k++){
                printf("%d. %s\n", k+1, usernya[i].peryaratan2);
                    for(l = 2; l < 3; l++){
                    printf("%d. %s\n", l+1, usernya[i].peryaratan3);
                }
            }
        }

        printf("\n");
    }
}

void delate_lowongan(){
    char hapusperusahaan[100], posisipekerjaan[100], open[100], close[100];
    int ditemukan =0, banyaklowongan;

    ban_DLinkedln();

    DataLowongan = fopen("Daftar Lowongan Pekerjaan.dat", "rb");
    DataLowongan_backup = fopen("Daftar Lowongan Pekerjaan backup.dat", "wb");

    printf("\n");
    printf("|| System: Masukan Nama Perusahaan: \n");
    printf("|| /> "); gets(hapusperusahaan);
    printf("|| System: Masukan Posisi Pekerjaan: \n");
    printf("|| /> "); gets (posisipekerjaan);
    printf("|| System: Masukan Tanggal Dibuka: \n"); 
    printf("|| /> "); gets(open);
    printf("|| System: Masukan Tanggal Ditutup: \n");
    printf("|| /> "); gets (close);

    while(fread(&user, sizeof(struct User), 1, DataLowongan)==1){
        if(strcmp(user.perusahaan, hapusperusahaan) != 0 && strcmp(user.posisi, posisipekerjaan)!= 0 && strcmp(user.open, open)!= 0 && strcmp(user.tutup, close)!= 0){
            fwrite(&user, sizeof(struct User), 1, DataLowongan_backup);
        } else{
            ditemukan = 1;
        }
    }

    fclose(DataLowongan);
    fclose(DataLowongan_backup);

    remove("Daftar Lowongan Pekerjaan.dat");
    rename("Daftar Lowongan Pekerjaan backup.dat", "Daftar Lowongan Pekerjaan.dat");

    if(ditemukan ==1){
        printf("\n");
        printf("Loading....\n"); sleep(2);
        printf("Lowongan Pekerjaan di %s dengan posisi %s berhasil di tutup!!\n", hapusperusahaan, posisipekerjaan);
    }else{
        printf("\n");
        printf("Loading....\n"); sleep(2);
        printf("Lowongan Pekerjaan di %s dengan posisi %s tidak ditemukan\n!!", hapusperusahaan, posisipekerjaan);
    }

    system("pause"); system("cls");
    dash_admin();
}

void list_lowongan(){
    int banyaklowongan = 0;

    DataLowongan = fopen("Daftar Lowongan Pekerjaan.dat", "rb");
    
    if (DataLowongan == NULL){
        printf("Tidak ada lowongan pekerjaan terbaru!!\n");
        system("pause"); system("cls");

        dash_admin();
    }

    while(fread(&usernya[banyaklowongan],sizeof(struct User), 1, DataLowongan)==1){
        banyaklowongan++;
    }

    fclose(DataLowongan);

    bubblesort_list_lowongan(banyaklowongan, usernya);
    printf("          ---- Daftar Lowongan Pekerjaan ----       \n");
    printf("----------------------------------------------------\n");
    view_bubblesort_list_lowongan(banyaklowongan, usernya);

    system("pause"); system("cls");
    dash_admin();
}

void bubblesort_list_prem(int banyakakunprem, struct User usernya[]){
    int i, j;

    for(i=0; i<banyakakunprem; i++){
        for(j=0; j<banyakakunprem -i -1; j++){
            if(strcmp(usernya[j].Nama, usernya[j+1].Nama)>0){
                temp = usernya[j];
                usernya[j] = usernya[j+1];
                usernya[j+1] = temp;
            }
        }
    }
}

void view_bubblesort_list_prem(int banyakakunprem, struct User usernya[]){
    int i;

    for(i=0; i<banyakakunprem; i++){
        printf("%d. Nama Lengkap: %s\n", i+1, usernya[i].Nama);
        printf("---------------------------------------------\n");
        printf("Pekerjaan       : %s\n", usernya[i].pekerjaan);
        printf("---------------------------------------------\n");
        printf("Email           : %s\n", usernya[i].email);
        printf("Kontak          : %s\n", usernya[i].kontak);
        printf("Alamat          : %s\n", usernya[i].alamat);
        printf("---------------------------------------------\n");
        printf("\n");
    }
}

void dash_akun(){
    int menu;
    ban_DLinkedln();

    printf("|| [1]. Daftar Akun Premium                      ||\n");
    printf("|| [2]. Daftar Akun Normal                       ||\n");
    printf("|| [3]. Kembali                                  ||\n");
    printf("----------------------------------------------------\n");
    printf("Option /> "); scanf("%d", &menu); getchar();
    
    switch(menu){
        case 1: system("cls");
                akun_prem();
                break;
        
        case 2: system("cls");
                akun_norm();
                break;
        
        case 3: system("cls");
                dash_admin();
                break;
        
        default: printf("Option tidak tersedia, silahkan coba kembali");
                system("pause"); system("cls");
                dash_akun();
                break; 
    }
} 

void signIn_admin(int percobaan){
    char username[30], pass[30];
    ban_DLinkedln();

    printf("|| Username:    "); gets(username);
    printf("|| Password:    "); gets(pass);

    if(strcmp(username, "ALLdaskom")==0 & strcmp(pass, "000")==0){
        printf("\n");
        printf("Proses verfikasi...."); sleep(2);
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

void warning(){
    char pilih;

    printf("                 SILAHKAN PILIH JENIS AKUN                \n");
    printf("----------------------------------------------------------\n");
    printf("[A]. Akun Premium                                         \n");
    printf("-----------------------------------------------------------\n");
    printf("| +> Melakukan pencarian pengguna LinkedIn.               |\n");
    printf("| +> Melakukan pencarian lowongan kerja.                  |\n");
    printf("| +> Melakukan pendaftaran pada lowongan kerja.           |\n");
    printf("| +> Menampilkan daftar lowongan yang sudah didaftarkan.  |\n");
    printf("----------------------------------------------------------\n");
    printf("[B]. Akun Silver                                          \n");
    printf("-----------------------------------------------------------\n");
    printf("| +> Melakukan pencarian pengguna LinkedIn.               |\n");
    printf("| +> Melakukan pencarian lowongan kerja.                  |\n");
    printf("| o> Anda dapat melakukan upgrade akun ke premium         |\n");
    printf("----------------------------------------------------------\n");
    printf("\n");
    printf("|| (A or B)/> "); scanf("%c", &pilih); getchar();

    switch(pilih){
        case 'A':
        case 'a': system("cls"); printf("Loading....\n"); sleep(2); signUp_user_norm(); break;

        case 'B':
        case 'b': system("cls"); printf("Loading....\n"); sleep(2); signUp_user_prem(); break;

        default: printf("Option tidak tersedia, silahkan coba kembali");
                system("pause"); system("cls");
                warning();
                break; 
    }
}

void signUp_user_prem(){
     int i, j, k;
    DataPrem = fopen("Daftar Akun Premium.dat", "ab");

    fflush(stdin);
    printf("\n");
    printf("||               Registrasi Biodata                \n");
    printf("---------------------------------------------------\n");
    printf("|| Nama Lengkap     : "); gets(user.Nama);
    printf("|| Email            : "); gets(user.email);
    printf("|| Kontak           : "); gets(user.kontak);
    printf("|| Alamat           : "); gets(user.alamat);
    printf("---------------------------------------------------\n");
    printf("|| Username         : "); gets(user.username);
    printf("|| Password         : "); gets(user.pass);
    printf("---------------------------------------------------\n");
    printf("|| Pekerjaan        : "); gets(user.pekerjaan);
    printf("|| Deksripsi        : "); gets(user.aboutMe);
    printf("---------------------------------------------------\n");
    printf("|| Pendidikan       : "); gets(user.pendidikan);
    printf("|| Input Pengalaman : \n");
     
    for(i=0; i<1; i++){
        printf("|| %d. ", i+1); gets(user.pengalaman1);
        for(j=1; j<2; j++){
            printf("|| %d. ", j+1); gets(user.pengalaman2);
            for(k=2; k<3; k++){
                printf("|| %d. ", k+1); gets(user.pengalaman3);
            }
        }
    }

    fwrite(&user, sizeof(struct User), 1, DataPrem);
    fclose(DataPrem);

    printf("\n");
    printf("Akun sedang dibuat....\n"); sleep(2);
    printf("Berhasil registrasi!!\n");

    system("pause"); system("cls");
    signIn_user_prem(1);

}

void signIn_user_prem(int percobaan){
    int banyakuser = 0, berhasil =0, i;
    char unamep[50], passp[50], emailp[50];

    DataPrem = fopen("Daftar Akun Premium.dat", "rb");

    if(DataPrem == NULL){
        printf("Loading....\n"); sleep(2);
        printf("Akun anda tidak dapat ditemukan!!\n");
        system("pause");
    }

    printf("||                Login D'Linkedln                 \n");
    printf("---------------------------------------------------\n");
    printf("|| Email    : "); gets(emailp);
    printf("|| Username : "); gets(unamep);
    printf("|| Password : "); gets(passp);
    printf("---------------------------------------------------\n");
    
    while(fread(&usernya[banyakuser], sizeof(struct User), 1, DataPrem)==1){
        banyakuser++;
    }

    for(i=0; i< banyakuser; i++){
        if(strcmp(usernya[i].email, emailp)==0 && strcmp(usernya[i].username, unamep)==0 && strcmp(usernya[i].pass, passp)==0){
            strcpy(IdUser, unamep);
            berhasil =1;
        }
    }

    fclose(DataPrem);

    if(berhasil ==1){
        printf("\n");
        printf("Verifikasi akun....\n"); sleep(2);
        printf("Berhasil login!!\n");

        system("pause"); system("cls");
        view_profile();

    } else{
        printf("\n");
        printf("Verifikasi akun....\n"); sleep(2);
        printf("Gagal login!!, sisa kesempatan %d lagi!!\n\n", 3-percobaan);

        if(percobaan < 3){
            system("pause"); system("cls");
            signIn_user_prem(percobaan+1);
        }else{
            printf("Loading....\n"); sleep(2);
            printf("Verifikasi melewati limit!!\n");
            system("pause"); system("cls");
            dash_user();
        }
    }
}

void signUp_user_norm(){
    int i, j, k;
    DataNorm = fopen("Daftar Akun Normal.dat", "ab");

    fflush(stdin);
    printf("\n");
    printf("||               Registrasi Biodata                \n");
    printf("---------------------------------------------------\n");
    printf("|| Nama Lengkap     : "); gets(user.Nama);
    printf("|| Email            : "); gets(user.email);
    printf("|| Kontak           : "); gets(user.kontak);
    printf("|| Alamat           : "); gets(user.alamat);
    printf("---------------------------------------------------\n");
    printf("|| Username         : "); gets(user.username);
    printf("|| Password         : "); gets(user.pass);
    printf("---------------------------------------------------\n");
    printf("|| Pekerjaan        : "); gets(user.pekerjaan);
    printf("|| Deksripsi        : "); gets(user.aboutMe);
    printf("---------------------------------------------------\n");
    printf("|| Pendidikan       : "); gets(user.pendidikan);
    printf("|| Input Pengalaman : \n");
     
    for(i=0; i<1; i++){
        printf("|| %d. ", i+1); gets(user.pengalaman1);
        for(j=1; j<2; j++){
            printf("|| %d. ", j+1); gets(user.pengalaman2);
            for(k=2; k<3; k++){
                printf("|| %d. ", k+1); gets(user.pengalaman3);
            }
        }
    }

    fwrite(&user, sizeof(struct User), 1, DataNorm);
    fclose(DataNorm);

    printf("\n");
    printf("Akun sedang dibuat....\n"); sleep(2);
    printf("Berhasil registrasi!!\n");

    system("pause"); system("cls");
    signIn_user_norm(1);
}

void signIn_user_norm(int percobaan){
    int banyakuser = 0, berhasil =0, i;
    char unamep[50], passp[50], emailp[50];

    DataNorm = fopen("Daftar Akun Normal.dat", "rb");

    if(DataNorm == NULL){
        printf("Loading....\n"); sleep(2);
        printf("Akun anda tidak dapat ditemukan!!\n");
        system("pause");
    }

    printf("||                Login D'Linkedln                 \n");
    printf("---------------------------------------------------\n");
    printf("|| Email    : "); gets(emailp);
    printf("|| Username : "); gets(unamep);
    printf("|| Password : "); gets(passp);
    printf("---------------------------------------------------\n");
    
    while(fread(&usernya[banyakuser], sizeof(struct User), 1, DataNorm)==1){
        banyakuser++;
    }

    for(i=0; i< banyakuser; i++){
        if(strcmp(usernya[i].email, emailp)==0 && strcmp(usernya[i].username, unamep)==0 && strcmp(usernya[i].pass, passp)==0){
            strcpy(IdUser, unamep);
            berhasil =1;
        }
    }

    fclose(DataNorm);

    if(berhasil ==1){
        printf("\n");
        printf("Verifikasi akun....\n"); sleep(2);
        printf("Berhasil login!!\n");

        system("pause"); system("cls");
        view_profile();

    } else{
        printf("\n");
        printf("Verifikasi akun....\n"); sleep(2);
        printf("Gagal login!!, sisa kesempatan %d lagi!!\n\n", 3-percobaan);

        if(percobaan < 3){
            system("pause"); system("cls");
            signIn_user_norm(percobaan+1);
        }else{
            printf("Loading....\n"); sleep(2);
            printf("Verifikasi melewati limit!!\n");
            system("pause"); system("cls");
            dash_user();
        }
    }
}
