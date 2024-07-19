//
// Created by 29396 on 24-7-13.
//

#include "User.h"

void borrow_copy(borrow& to, borrow& from){
    to.id = from.id;
    to.date = from.date;
}

void User_copy(User& to, User& from){
    to.ID = from.ID;
    strcpy(to.name, from.name);
    strcpy(to.password, from.password);
    for (int i=0;i<5;i++)
        borrow_copy(to.Borrow[i], from.Borrow[i]);

    to.power = from.power;
}

int get_user_num(){
    int user_num = 0;
    //这里是所有者可读可写, 本组和其他组只可以读
    int fd = open(USER_FILE_NAME, O_RDONLY | O_CREAT, 0644);

    ssize_t n_bytes_read;
    n_bytes_read = read(fd, &user_num, sizeof user_num);

    if (n_bytes_read == -1) return 0;
    return user_num;
}

int append_user(User* added_user){

    int user_num = get_user_num();
    user_num++;

    ssize_t bytes_written;

    //以追加写入方式打开图书文件
    int fd_add_num = open(USER_FILE_NAME, O_WRONLY | O_CREAT, 0644);

    //写入用户数量
    bytes_written = write(fd_add_num, &user_num, sizeof user_num);
    if (bytes_written == -1) return -1;
    close(fd_add_num);

    int fd_add = open(USER_FILE_NAME, O_WRONLY | O_CREAT | O_APPEND, 0644);
    //写入用户数据
    bytes_written = write(fd_add, added_user, sizeof (struct User));
    close(fd_add);

    //错误校验
    if (bytes_written == -1) return -1;

    return 0;
}

int del_user(ull del_ID){

    int user_num = 0;

    //打开源文件和缓存文件
    int fd1 = open(USER_FILE_NAME, O_RDONLY);
    if (fd1 == -1) return -1;
//    printf("open fd1\n");

    int fd2 = open(USER_FILE_NAME_RE, O_WRONLY|O_CREAT|O_APPEND, 0644);
    if (fd2 == -1)return -1;
//    printf("open fd2\n");

    struct User* user = new User;
    ssize_t bytes_read, bytes_written;

    //写入
    bytes_read = read(fd1, &user_num, sizeof user_num);
    if (bytes_read == -1) return -1;
//    printf("write user_num\n");

    user_num--;

    bytes_written = write(fd2, &user_num, sizeof user_num);
    if (bytes_written == -1) return -1;

//    printf("on write user_info\n\n");


    for (int i = 0; i < user_num+1; i++) {
        bytes_read = read(fd1, user, sizeof (struct User));

        if (bytes_read == -1) return -1;
        if (user->ID == del_ID){
            continue;
        }

        bytes_written = write(fd2, user, sizeof (struct User));

        if (bytes_written == -1) return -1;
    }

    close(fd1);
    close(fd2);


    rename(USER_FILE_NAME_RE, USER_FILE_NAME);

    return 0;
}

int pwd_comparison(ull ID, char* pwd){
    int fd = open(USER_FILE_NAME, O_RDONLY);
    if (fd == -1) return -1;

    User* user = new User;
    ssize_t bytes_read;
    int User_num = 0;

    bytes_read = read(fd, &User_num, sizeof User_num);
    if (bytes_read == -1) return -1;

    while ((bytes_read = read(fd, user, sizeof(struct User))) > 0) {
        if (bytes_read == -1) return -1;
        if (user->ID == ID){

            printf("\n");
            if (strcmp(user->password, pwd)==0) return 0;
            else return 1;
        }
    }
    return 2;
}

User* get_user(int ID){
    int fd = open(USER_FILE_NAME, O_RDONLY);
    if (fd == -1) return NULL;
    User* user = new User;
    ssize_t bytes_read;

    int User_num = 0;
    bytes_read = read(fd, &User_num, sizeof User_num);
    if (bytes_read == -1) return NULL;

    while (1) {
        if ((bytes_read = read(fd, user, sizeof (struct User)) <= 0))break;
        if (bytes_read == -1) break;
        if (user->ID == ID) return user;
    }
    close(fd);
    return nullptr;
}

int user_update(User* update_user){
    int fd1 = open(USER_FILE_NAME, O_RDONLY);
    if (fd1 == -1) return -1;


    int fd2 = open(USER_FILE_NAME_RE, O_WRONLY|O_CREAT, 0644);
    if (fd2 == -1) return -1;

    int User_num = 0;
    ssize_t bytes_read, bytes_written;

    bytes_read = read(fd1, &User_num, sizeof User_num);
    if (bytes_read == -1) return -1;
//
    bytes_written = write(fd2, &User_num, sizeof User_num);
    if (bytes_written == -1) return -1;

    User* user = new User;
    while ((bytes_read = read(fd1, user, sizeof(struct User))) > 0) {
        if (bytes_read == -1) return -1;


        if (user->ID == update_user->ID) bytes_written = write(fd2, update_user, sizeof(struct User));
        else bytes_written = write(fd2, user, sizeof(struct User));

        if (bytes_written == -1) return -1;
    }
    close(fd1);
    close(fd2);

    rename(USER_FILE_NAME_RE, USER_FILE_NAME);
    return 0;
}

User* list_user(int page){
    User* user_list = new User[USER_PAGE_NUM];

    int fd = open(USER_FILE_NAME, O_RDONLY);
    if (fd == -1) return NULL;

    User* user = new User;
    ssize_t bytes_read;

    int User_num = 0;
    bytes_read = read(fd, &User_num, sizeof User_num);
    if (bytes_read == -1) return NULL;

    int index = 0, array_index = 0;
    while (1) {
        if ((bytes_read = read(fd, user, sizeof (struct User)) <= 0))break;
        if (index++ < USER_PAGE_NUM*page) continue;
        if (bytes_read == -1) return NULL;
        User_copy(user_list[array_index++], *user);
        if (array_index == USER_PAGE_NUM) break;
    }

    return user_list;
}