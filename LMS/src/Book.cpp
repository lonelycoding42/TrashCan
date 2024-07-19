#include "Book.h"

//缓存区最大大小
#define MAX_BUFFER_SIZE 1024

void where_copy(where &to, where &from){
    to.floor = from.floor;
    to.number = from.number;
    to.shelf = from.shelf;
    to.zone = from.zone;

}

void book_copy(Book &to, Book &from){
    to.id = from.id;
    strcpy(to.ISBN, from.ISBN);;
    strcpy(to.Title, from.Title);
    strcpy(to.tag, from.tag);
    where_copy(to.Where, from.Where);
    to.visual = from.visual;
    to.status = from.status;

}

int get_book_num(){
    int book_num = 0;
    //这里是所有者可读可写, 本组和其他组只可以读
    int fd = open(BOOK_FILE_NAME, O_RDONLY | O_CREAT, 0644);

    ssize_t n_bytes_read;
    n_bytes_read = read(fd, &book_num, sizeof book_num);

    if (n_bytes_read == -1) return 0;
    return book_num;
}


//添加书籍的函数
int add_book(Book *added_book) {
    //S_IRWXU00700	权限, 代表该文件所有者具有可读、可写及可执行的权限
    //S_IRUSR	或S_IREAD, 00400 权限, 代表该文件所有者具有可读取的权限
    //S_IWUSR	或S_IWRITE, 00200 权限, 代表该文件所有者具有可写入的权限
    //S_IXUSR	或S_IEXEC, 00100 权限, 代表该文件所有者具有可执行的权限
    //       S_IRWXG	00070 权限, 代表该文件用户组具有可读、可写及可执行的权限
    //       S_IRGRP	00040 权限, 代表该文件用户组具有可读的权限
    //       S_IWGRP	00020 权限, 代表该文件用户组具有可写入的权限
    //       S_IXGRP	00010 权限, 代表该文件用户组具有可执行的权限
    //       S_IRWXO	00007 权限, 代表其他用户具有可读、可写及可执行的权限
    //       S_IROTH	00004 权限, 代表其他用户具有可读的权限
    //       S_IWOTH	00002 权限, 代表其他用户具有可写入的权限
    //       S_IXOTH	00001 权限, 代表其他用户具有可执行的权限

    //获取图书数量
    int book_num = get_book_num();
    book_num++;

    ssize_t bytes_written;

    //打开图书文件
    int fd_add_num = open(BOOK_FILE_NAME, O_WRONLY | O_CREAT, 0644);

    //写入图书数量
    bytes_written = write(fd_add_num, &book_num, sizeof book_num);
    if (bytes_written == -1) return -1;
    close(fd_add_num);

    //以追加写入方式打开图书文件
    int fd_add = open(BOOK_FILE_NAME, O_WRONLY | O_CREAT | O_APPEND, 0644);
    //写入图书数据
    bytes_written = write(fd_add, added_book, sizeof(struct Book));
    close(fd_add);

    //错误校验
    if (bytes_written == -1) return -1;

    return 0;
}


int del_book(ull del_id){
    int book_num = 0;

    //得到书籍id
    int fd1 = open(BOOK_FILE_NAME, O_RDONLY);
    if (fd1 == -1) return -1;

    int fd2 = open(BOOK_FILE_NAME_RE, O_WRONLY|O_CREAT|O_APPEND, 0644);
    if (fd2 == -1)return -1;

    struct Book book;
    ssize_t bytes_read, bytes_written;
    bytes_read = read(fd1, &book_num, sizeof book_num);
    if (bytes_read == -1) return -1;

    bytes_written = write(fd2, &book_num, sizeof book_num);
    if (bytes_written == -1) return -1;

    while ((bytes_read = read(fd1, &book, sizeof book)) > 0) {
        if (bytes_read == -1) return -1;
        if (book.id == del_id) continue;
        bytes_written = write(fd2, &book, sizeof(struct Book));
        if (bytes_written == -1) return -1;
    }

    close(fd1);
    close(fd2);


    rename(BOOK_FILE_NAME_RE, BOOK_FILE_NAME);
    return 0;

}

Book* seek_book_by_id(ull seek_id){
    int fd = open(BOOK_FILE_NAME, O_RDONLY);
    if (fd == -1) return nullptr;

    Book* book = new Book;
    ssize_t bytes_read;
    int  book_num;

    bytes_read = read(fd, &book_num, sizeof book_num);
    if (bytes_read == -1) return nullptr;

    while ((bytes_read = read(fd, book, sizeof (struct Book))) > 0) {

        if (bytes_read == -1) {
            return NULL;
        }
        if (book->id==seek_id){
            return book;
        }
    }

    return NULL;
}

Book* seek_book_by_Title(char *Title){
    int fd = open(BOOK_FILE_NAME, O_RDONLY);
    if (fd == -1) return nullptr;

    Book book;
    Book* book_list= new Book[1000];
    memset(book_list,0,sizeof(book_list));
    ssize_t bytes_read;
    int book_num, num=0;

    bytes_read = read(fd, &book_num, sizeof book_num);
    if (bytes_read == -1) return nullptr;

    while ((bytes_read = read(fd, &book, sizeof (struct Book))) > 0) {

        if (bytes_read == -1) {
            delete []book_list;
            return nullptr;
        }
        if (strncmp(Title, book.Title, strlen(Title)) == 0){
            book_list[num]=book; num++;
        }
    }

    if(num==0) {
        delete []book_list;
        return nullptr;
    }
    return book_list;
}

int update_book(Book *update_book){
    int book_num = 0;

    int fd1 = open(BOOK_FILE_NAME, O_RDONLY);
    if (fd1 == -1) return -1;


    int fd2 = open(BOOK_FILE_NAME_RE, O_WRONLY|O_CREAT|O_APPEND, 0644);
    if (fd2 == -1) return -1;

    Book* book = new Book;
    ssize_t bytes_read, bytes_written;
    bytes_read = read(fd1, &book_num, sizeof book_num);
    if (bytes_read == -1) return -1;

    bytes_written = write(fd2, &book_num, sizeof book_num);
    if (bytes_written == -1) return -1;

    while ((bytes_read = read(fd1, book, sizeof (struct Book))) > 0) {
        if (bytes_read == -1) return -1;


        if (book->id == update_book->id) bytes_written = write(fd2, update_book, sizeof(struct Book));
        else bytes_written = write(fd2, book, sizeof(struct Book));

        if (bytes_written == -1) return -1;
    }
    close(fd1);
    close(fd2);

    rename(BOOK_FILE_NAME_RE, BOOK_FILE_NAME);

    return 0;
}

Book* list_books(int page) {

    Book* book_list = new Book[1000];

    int fd = open(BOOK_FILE_NAME, O_RDONLY);
    if (fd == -1) return nullptr;

    Book book;
    ssize_t bytes_read;
    int  book_num = 0, index = 0, array_index = 0;

    bytes_read = read(fd, &book_num, sizeof book_num);
    if (bytes_read == -1) return nullptr;

    while ((bytes_read = read(fd, &book, sizeof book)) > 0) {
        if (index++<page*BOOK_PAGE_NUM) continue;
        if (bytes_read == -1) return nullptr;
        book_copy(book_list[array_index++], book);
        if (array_index == BOOK_PAGE_NUM) break;
    }

    return book_list;
}

//按照ID排序
int cmp_by_ID(Book book1, Book book2){
    return (book1.id > book2.id);
}

int cmp_by_ID_reverse(Book book1, Book book2){
    return (book1.id < book2.id);
}

//按照字典序排序
int cmp_by_lexicographical_order(Book book1, Book book2){
    return (strcmp(book1.Title, book2.Title)>0);
}

int cmp_by_lexicographical_order_reverse(Book book1, Book book2){
    return (strcmp(book1.Title, book2.Title)>0);
}

int Sort_books(Book* book_list, int ary_len, int mode){
    switch (mode) {
        case 1:
            std::sort(book_list,book_list+ary_len, cmp_by_ID);
            break;
        case 2:
            std::sort(book_list,book_list+ary_len, cmp_by_ID_reverse);
            break;
        case 3:
            std::sort(book_list,book_list+ary_len, cmp_by_lexicographical_order);
            break;
        case 4:
            std::sort(book_list,book_list+ary_len, cmp_by_lexicographical_order_reverse);
            break;
    }
    return 0;
}