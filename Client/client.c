#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    char buffer[1024] = {0};
    char login_status[1024] = {0};

    char pilihan[100];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char id[20], pass[20], input_akun[100];
    
    printf("Register atau Login? ");
    scanf("%s", pilihan);

    //kirim perintah register atau login ke server
    send(sock , pilihan , strlen(pilihan) , 0 );

    //masukkan id dan pass lalu kirim ke server
    printf("Masukkan id : ");
    scanf("%s", id);
    printf("Masukkan pass : ");
    scanf("%s", pass);
    strcpy(input_akun, id);
    strcat(input_akun, ":");
    strcat(input_akun, pass);
    input_akun[strlen(input_akun)] = '\0';
    send(sock , input_akun , strlen(input_akun) , 0 );

    if(pilihan[0]=='r'){
       printf("Register berhasil\n");
    }
    else if(pilihan[0]=='l'){
        valread = read( sock , login_status, 1024);
        if(login_status[0]=='b'){
            printf("Login berhasil\n");
        }
        else{
            printf("Login gagal!!\n");
            return 0;
        }   
    }

    while(1){
        printf("\nMasukkan perintah : ");
        scanf("%s", pilihan);
        // kirim comand ke
        send(sock , pilihan, strlen(pilihan) , 0 );

        
        
        if(pilihan[0]=='e')
            break;
    }
    return 0;
}