//
// Created by 29396 on 24-7-13.
//

#ifndef LMS_USER_H
#define LMS_USER_H

#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

//每一页加载的用户数量
#define USER_PAGE_NUM 16

//文件路径
#define USER_FILE_NAME "./data/User"
#define USER_FILE_NAME_RE "./data/users_BUFFER.txt"
typedef int ull;


typedef struct borrow {
    ull id;             //书籍ID
    ull date;           //书籍到期时间
} borrow;


void borrow_copy(borrow& to, borrow& from);


typedef struct User {
    ull ID;             //用户ID
    char name[52];      //昵称
    char password[52];  //密码
    borrow Borrow[5];   //借的书籍
    bool power;         //0为读者，1为管理员
} User;

//拷贝函数
void User_copy(User& to, User& from);

//返回用户数量 0
int get_user_num();

//添加用户 0
int append_user(User* add_user);

//删除用户 0
int del_user(ull del_ID);

//给定 ID和密码进行比对,匹配成功返回0,失败返回1,没有该用户返回2,出现错误返回-1 0
int pwd_comparison(ull ID, char* pwd);

//给定ID,获得对应用户结构体 0
User* get_user(int ID);

//给定更新的用户结构体, 更新成功返回0; 0
int user_update(User* update_user);

//返回用户的数组指针,page表示加载到第几页 0
User* list_user(int page);


#endif //LMS_USER_H
