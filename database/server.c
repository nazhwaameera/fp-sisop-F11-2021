#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#define PORT 8080


int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char id[1024] = {0};
    char pass[1024] = {0};
    char pilihan1[1024] = {0};
    char input_akun[1024] = {0};

    char *path = "/home/rayhan12/cmpt/soal1fix/soal1";
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    FILE *fakun, *ffiles, *fptr1, *fptr2;

    //ambil pilihan register atau login dari client
    valread = read( new_socket , pilihan1, 1024);
    //ambil id dan pass
    valread = read( new_socket , input_akun, 1024);
    if(pilihan1[0]=='r'){
        fakun= fopen("akun.txt","a");

        //input id dan pass akun baru
        fputs(input_akun, fakun);
        fputs("\n", fakun);
        fflush(fakun);
        fclose(fakun);
    }
    else{
        char line[1024];
        int ada=0;

        //cek id dan pass sama 
        FILE* srcFile = fopen("akun.txt", "r");
        while (fgets(line , sizeof(line) , srcFile )!= NULL)
        {   
            if (strstr(line , input_akun) != NULL)
                ada=1;
        }

        if(ada)
            send(new_socket , "berhasil", 8 , 0 );
        else{
            send(new_socket , "gagal", 5 , 0 );
            return 0;
        }
            
    }

    while(1){
        char pilihan[1024] = {0};
    
        if(pilihan[0]=='e')
            break;
    }
    return 0;
}