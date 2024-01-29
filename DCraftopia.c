// library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// all function
    // function for administrator mode
    void login_admin();
        void menu_admin();
            // for Craftsmen
            void view_Account_Craftsmen();
                void bubblesort_AC();
                void view_bubblesort_AC();
            void delate_Account_Craftsmen();

            // for Customer
            void view_Account_Buyer();
                void bubblesort_AB();
                void view_bubblesort_AB();
            void delate_Account_Buyer();
            void view_feedback_Buyer();

    // function for Craftsmen
    void dashboard_Craftsmen();
        void signUp_Craftsmen();
        void signIn_Craftsmen();
            void menu_Craftsmen();
                void add_product();
                void delate_product();
                void view_product();
                    void bubblesort_product();
                    void view_bubblesort_product();
                void view_orders();
                void chat_box();

    // function for Buyer
    void dasbord_Buyer();
        void signUp_Buyer();
        void signIn_Buyer();
            void menu_Buyer();
                void view_profile();
                void search_product();
                    void order_product();
                void pays_product();
                void send_message_product();
                void send_feedback_Craftsmen();

    // header biar keren aja sih
    void header_welcome();

// all file handling :)
    // file for Craftsmen
    FILE *Account_Craftsmen;
    FILE *Account_Craftsmen_backup;

    FILE *Products;
    FILE *Products_backup;

    FILE *Orders;
    FILE *ChatBox;

    // file for Buyer
    FILE *Account_Buyer;
    FILE *Account_Buyer_backup;

    FILE *Feedback_Buyer;
