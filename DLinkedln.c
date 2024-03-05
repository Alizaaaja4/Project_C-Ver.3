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
                    void bubblesort_list_lowongan(); //proses sorting secara ascending
                    void view_bubblesort_list_lowongan();

                void dash_akun();
                    void akun_prem();
                        void bubblesort_list_prem(); //proses sorting secara ascending
                        void view_bubblesort_list_prem();

                    void akun_norm();
                        void bubblesort_list_norm(); //proses sorting secara descending
                        void view_bubblesort_list_norm();
            
    void dash_user();
        void warning();
            void signIn_user_norm();
            void signUp_user_norm();

            void signIn_user_prem();
            void signUp_user_prem();
                
                void view_profile();
                void cariPremiumakun(); // id 1010xxxxx
                void cariNormalakun(); // id 2020xxxx
                    void view_profile_prem();
                        void edit_password();
                        void edit_idakun();
                        void search_user();
                        void search_lowongan(); // disini bisa langsung daftar pekerjaan
                        void notifikasi();
                    
                    void view_profile_norm();
                        void search_user();
                        void search_lowongan();
                        void upgrade_akun_prem();

FILE *DataLowongan;
FILE *DataLowongan_backup;
FILE *DataPrem;
FILE *DataNorm;

struct User{
    // biodata profile
    char Nama[50], username[20], email[50], pass[20], kontak[10], alamat[20], pekerjaan[20], aboutMe[50], pengalaman1[300], pengalaman2[300], pengalaman3[300], pendidikan[30];

    // klasifikasi jenis akun
    char jenis_akun[50]; // 0101 akun normal dan 1010 akun premium

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

void akun_prem(){
   int banyakakunprem = 0;

   DataPrem = fopen("Daftar Akun Premium.dat", "rb");

   if (DataPrem == NULL){
    printf("Sedang Mencari data.... \n"); sleep(2);
    printf("Saat ini tidak user yang mendaftar akun premium!!\n");
    system("pause"); system("cls");
    dash_akun();
   }
   while(fread(&usernya[banyakakunprem], sizeof(struct User), 1, DataPrem)==1){
        banyakakunprem++;
   }

   fclose(DataPrem);

   bubblesort_list_prem(banyakakunprem, usernya);
   printf("             ---- Daftar Akun Premium ----          \n");
   printf("----------------------------------------------------\n");
   view_bubblesort_list_prem(banyakakunprem, usernya);

    system("pause"); system("cls");

    dash_akun();

}

void bubblesort_list_norm(int banyakakunnorm, struct User usernya[]){
    int i, j;

    for(i=0; i<banyakakunnorm; i++){
        for(j=0; j<banyakakunnorm -i -1; j++){
            if(strcmp(usernya[j].Nama, usernya[j+1].Nama)>0){
                temp = usernya[j];
                usernya[j] = usernya[j+1];
                usernya[j+1] = temp;
            }
        }
    }
}

void view_bubblesort_list_norm(int banyakakunnorm, struct User usernya[]){
    int i;

    for(i=0; i<banyakakunnorm; i++){
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

void akun_norm(){
    int banyakakunnorm = 0;

   DataNorm = fopen("Daftar Akun Normal.dat", "rb");

   if (DataNorm == NULL){
    printf("Sedang Mencari data.... \n"); sleep(2);
    printf("Saat ini tidak user yang mendaftar akun premium!!\n");
    system("pause"); system("cls");
    dash_akun();
   }
   while(fread(&usernya[banyakakunnorm], sizeof(struct User), 1, DataNorm)==1){
        banyakakunnorm++;
   }

   fclose(DataNorm);

   bubblesort_list_norm(banyakakunnorm, usernya);
   printf("             ---- Daftar Akun Silver ----           \n");
   printf("----------------------------------------------------\n");
   view_bubblesort_list_norm(banyakakunnorm, usernya);

    system("pause"); system("cls");

    dash_akun();
}

void dash_akun(){
    int menu;
    ban_DLinkedln();

    printf("|| [1]. Daftar Akun Premium                      ||\n");
    printf("|| [2]. Daftar Akun Silver                       ||\n");
    printf("|| [3]. Kembali                                  ||\n");
    printf("----------------------------------------------------\n");
    printf("Option /> "); scanf("%d", &menu); getchar();
    
    switch(menu){
        case 1: system("cls"); akun_prem(); break;
        case 2: system("cls"); akun_norm(); break;
        case 3: system("cls"); dash_admin(); break;
        default: printf("Option tidak tersedia, silahkan coba kembali");
                system("pause"); system("cls");
                dash_akun();
                break; 
    }
}   

void dash_admin(){
    int menu;
    ban_DLinkedln();

    printf("|| [1]. Buka Lowongan Kerja                      ||\n");
    printf("|| [2]. Tutup Lowongan Kerja                     ||\n");
    printf("|| [3]. Daftar Lowongan Pekerjaan                ||\n");
    printf("|| [4]. Daftar Akun Linkedln                     ||\n");
    printf("|| [5]. Logout                                   ||\n");
    printf("----------------------------------------------------\n");
    printf("Option /> "); scanf("%d", &menu); getchar();
    switch(menu){
        case 1: system("cls"); add_lowongan(); break;
        case 2: system("cls"); delate_lowongan(); break;
        case 3: system("cls"); list_lowongan(); break;
        case 4: system("cls"); dash_akun(); break;
        case 5: system("cls"); main(); break;
        default: printf("Option tidak tersedia, silahkan coba kembali");
                system("pause"); system("cls");
                dash_admin();
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
        printf("Proses verfikasi....\n"); sleep(2);
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
        case 'a': system("cls"); printf("Loading....\n"); sleep(2); signUp_user_prem(); break;

        case 'B':
        case 'b': system("cls"); printf("Loading....\n"); sleep(2); signUp_user_norm(); break;

        default: printf("Option tidak tersedia, silahkan coba kembali\n");
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
    printf("||             Registrasi Akun Premium             \n");
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

    printf("\n");
    printf("Buat ID Akun (ex: 1010xxxx): "); gets(user.jenis_akun);

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

    printf("||            Login D'Linkedln (Premium)           \n");
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
        view_profile_prem();

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
    printf("||            Registrasi Akun Silver               \n");
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

    printf("\n");
    printf("Buat ID Akun (ex: 2020xxxx): "); gets(user.jenis_akun);

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

    printf("||            Login D'Linkedln (Silver)            \n");
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
        view_profile_norm();

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

void cariPremiumakun(char idakun[]){
    int banyakakun =0, berhasil =0, i;

    DataPrem = fopen("Daftar Akun Premium.dat", "rb");

    if(DataPrem == NULL){
        printf("\n");
        printf("Proses Autentikasi....\n"); sleep(2);
        printf("Akun Premium dengan ID %s tidak ditemukan.\n", idakun);
        system("pause");
    }

    while(fread(&usernya[banyakakun], sizeof(struct User), 1, DataPrem)==1){
        banyakakun++;
    }

    for(i=0; i< banyakakun; i++){
        if(strcmp(usernya[i].jenis_akun, idakun)==0){
            strcpy(IdUser, idakun);
            berhasil =1;
        }
    }

    fclose(DataPrem);

    if(berhasil == 1){
        printf("\n");
        printf("Proses Autentikasi....\n"); sleep(2);
        printf("Berhasil!!\n");

        system("pause"); system("cls");
        signIn_user_prem(1);

    } else{
        printf("\n");
        printf("Proses Autentikasi....\n"); sleep(2);
        printf("Gagal!!\n");

        system("pause"); system("cls");
        view_profile();
    }
}

void cariNormalakun(char idakun[]){
    int banyakakun =0, berhasil =0, i;

    DataNorm = fopen("Daftar Akun Normal.dat", "rb");

    if(DataNorm == NULL){
        printf("\n");
        printf("Proses Autentikasi....\n"); sleep(2);
        printf("Akun Silver dengan ID %s tidak ditemukan.\n", idakun);
        system("pause");
    }

    while(fread(&usernya[banyakakun], sizeof(struct User), 1, DataNorm)==1){
        banyakakun++;
    }

    for(i=0; i< banyakakun; i++){
        if(strcmp(usernya[i].jenis_akun, idakun)==0){
            strcpy(IdUser, idakun);
            berhasil =1;
        }
    }

    fclose(DataNorm);

    if(berhasil == 1){
        printf("\n");
        printf("Proses Autentikasi....\n"); sleep(2);
        printf("Berhasil!!\n");

        system("pause"); system("cls");
        signIn_user_norm(1);

    } else{
        printf("\n");
        printf("Proses Autentikasi....\n"); sleep(2);
        printf("Gagal!!\n");

        system("pause"); system("cls");
        view_profile();
    }
}

void view_profile(){
    char idakun[30], pilih;

    fflush(stdin);
    printf("||         ---- Klasifikasi ID Akun ----         ||\n");
    printf("---------------------------------------------------\n");
    printf("|| Jenis akun anda premium? (y / n): "); scanf("%c", &pilih); getchar();

    if(pilih == 'Y' || pilih =='y'){
        system("cls"); printf("Loading....\n\n"); sleep(2);
        printf("||           ---- Masukan ID Akun ----           ||\n");
        printf("---------------------------------------------------\n");
        printf("              ID Akun Anda: "); gets(idakun);

        cariPremiumakun(idakun);

    } else if(pilih == 'N' || pilih == 'n'){
        system("cls"); printf("Loading....\n\n"); sleep(2);
        printf("||           ---- Masukan ID Akun ----           ||\n");
        printf("---------------------------------------------------\n");
        printf("              ID Akun Anda: "); gets(idakun);

        cariNormalakun(idakun);

    } else{
        printf("Option tidak tersedia, silahkan coba kembali\n");
        system("pause"); system("cls");
        view_profile();
    }
}

void edit_password(){
    DataPrem = fopen("Daftar Akun Premium.dat", "rb+");

    char cariakun[50], cariemail[50], passbaru[50];
    int ditemukan = 0;

    printf("System: masukan username: \n"); printf("/> "); gets(cariakun);
    printf("System: masukan email   : \n"); printf("/> "); gets(cariemail);

    printf("\n\n");

    while(fread(&user, sizeof(struct User), 1, DataPrem)==1){
        if(strcmp(user.username, cariakun)==0 && strcmp(user.email, cariemail)==0){
            ditemukan = 1;
            printf("||        --- Masukan Password ---        ||\n");
            printf("--------------------------------------------\n");
            printf("| Nama           : %s\n", user.Nama);
            printf("| Username       : %s\n", user.username);
            printf("--------------------------------------------\n");
            printf("| Password (old) : %s\n", user.pass);
            printf("| Password (new) : "); gets(passbaru);

            fseek(DataPrem, -(long long)sizeof(struct User), SEEK_CUR);
            strcpy(user.pass, passbaru);
            fwrite(&user, sizeof(struct User), 1, DataPrem);

            printf("--------------------------------------------\n");
            break;
        }
    }

    fclose(DataPrem);
    if (ditemukan ==1){
        printf("Loading.....\n"); sleep(2);
        printf("Akun User %s berhasil diubah!!\n", cariakun);
    } else{
        printf("Loading.....\n"); sleep(2);
        printf("Akun User %s tidak ditemukan dalam database!!\n", cariakun);
    }
    printf("\n"); system("pause"); system("cls"); view_profile_prem();
}

void edit_idakun(){
    DataPrem = fopen("Daftar Akun Premium.dat", "rb+");

    char cariakun[50], cariemail[50], idbaru[50];
    int ditemukan = 0;

    printf("System: masukan username: \n"); printf("/> "); gets(cariakun);
    printf("System: masukan email   : \n"); printf("/> "); gets(cariemail);

    printf("\n\n");

    while(fread(&user, sizeof(struct User), 1, DataPrem)==1){
        if(strcmp(user.username, cariakun)==0 && strcmp(user.email, cariemail)==0){
            ditemukan = 1;
            printf("||           ----- Masukan ID Akun -----           ||\n");
            printf("-----------------------------------------------------\n");
            printf("| Nama                    : %s\n", user.Nama);
            printf("| Username                : %s\n", user.username);
            printf("-----------------------------------------------------\n");
            printf("| ID Akun (old)           : %s\n", user.jenis_akun);
            printf("| ID Akun (new: 1010xxxx) : "); gets(idbaru);

            fseek(DataPrem, -(long long)sizeof(struct User), SEEK_CUR);
            strcpy(user.jenis_akun, idbaru);
            fwrite(&user, sizeof(struct User), 1, DataPrem);

            printf("----------------------------------------------------\n");
            break;
        }
    }

    fclose(DataPrem);
    if (ditemukan ==1){
        printf("Loading.....\n"); sleep(2);
        printf("ID Akun User %s berhasil diubah!!\n", cariakun);
    } else{
        printf("Loading.....\n"); sleep(2);
        printf("ID Akun User %s tidak ditemukan dalam database!!\n", cariakun);
    }
    printf("\n"); system("pause"); system("cls"); view_profile_prem();
}

void view_profile_prem(){
    int menu;
    fflush(stdin);

    printf("\n");
    printf("=-=-=-=-=-=-=-=-=-= D'Linkedln Premium =-=-=-=-=-=-=-=-=\n");
    printf("|| [1]. Edit Password     | [2]. Edit ID Akun         ||\n");
    printf("|| [3]. Cari User         | [4]. Cari Lowongan Kerja  ||\n");
    printf("|| [5]. Notifikasi        | [6]. Logout               ||\n");
    printf("---------------------------------------------------------\n");
    printf("/> "); scanf("%d", &menu); getchar();

    switch(menu){
        case 1: system("cls"); edit_password(); break;
        case 2: system("cls"); edit_idakun(); break;
        // case 3: system("cls"); search_user(); break;
        // case 4: system("cls"); search_lowongan(); break;
        // case 5: system("cls"); notifikasi(); break;
        case 6: system("cls"); dash_user(); break;
        default: printf("Option tidak tersedia, silahkan coba kembali\n");
                system("pause"); system("cls");
                view_profile_prem();
                break;
    }   
}

void view_profile_norm(){
    printf("ini berhasil silver");
}

void dash_user(){
    int menu;
    ban_DLinkedln();

    printf("|| [1]. Sign In                                   ||\n");
    printf("|| [2]. Sign Up                                   ||\n");
    printf("|| [3]. Kembali                                   ||\n");
    printf("---------------------------------------------------\n");
    printf("Option /> "); scanf("%d", &menu); getchar();
    switch(menu){
        case 1: system("cls"); view_profile(); break;
        case 2: system("cls"); warning(); break;
        case 3: system("cls"); main(); break;
        default: printf("Option tidak tersedia, silahkan coba kembali\n");
                system("pause"); system("cls");
                dash_user();
                break;
    }
}

int main (){
    int menu;
    ban_DLinkedln();
    printf("|| [1]. Administrator                             ||\n");
    printf("|| [2]. User                                      ||\n");
    printf("---------------------------------------------------\n");
    printf("Option /> "); scanf("%d", &menu); getchar();
    switch (menu){
        case 1: system("cls"); signIn_admin(1); break;
        case 2: system("cls"); dash_user(); break;
        default: printf("Option tidak tersedia, silahkan coba kembali\n");
                system("pause"); system("cls");
                main();
                break;
    }
}
