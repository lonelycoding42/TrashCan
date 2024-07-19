#ifndef LMS_BOOK_H
#define LMS_BOOK_H

#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>

#define BOOK_FILE_NAME "./data/Book"
#define BOOK_FILE_NAME_RE "./data/books_BUFFER"

//每一页加载的图书数量
#define BOOK_PAGE_NUM 16
typedef int ull;

//记录图书存放位置
typedef struct where {
    int floor;          //楼层
    char zone;          //区域
    int shelf;          //书架
    int number;         //编号
} where;

//where的拷贝函数
void where_copy(where &to, where &from);

typedef struct Book {
    ull id;             //书籍ID
    char ISBN[15];      //ISBN码
    char Title[52];     //标题
    char tag[11];        //标签
    where Where;        //书籍位置
    bool visual;        //对普通读者是否可见
    ull status;         //在馆内为0，借出记录为用户ID
} Book;

//book的拷贝函数
void book_copy(Book &to, Book &from);

// 返回图书数量 0
int get_book_num();

//added_book 被添加的图书指针, 返回操作状态码。 0
int add_book(Book *added_book);

//del_id 被删除书籍的id, 返回操作状态码 0
int del_book(ull del_id);

//sk_id 查询书籍的id, 返回id匹配的书籍 0
Book* seek_book_by_id(int sk_id);

Book* seek_book_by_Title(char *Title);

//update_book 被更新书籍的指针, 返回操作状态码 0
int update_book(Book *update_book);

//返回书籍列表指针 0
Book* list_books(int  page);

//book_list需要排序的book, array_len是数组长度
int Sort_books(Book* book_list, int ary_len,int mode);

#endif //LMS_BOOK_H