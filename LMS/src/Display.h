//
// Created by lilon on 24-7-10.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include "cursor.h"
#include "Book.h"
#include "User.h"
#include "Tag.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class Display {
public:
    void LogRes();  //登录&注册
    int mainpage(); //主界面

    int check();    //查看所有书籍

    int manage();   //书籍管理

    int search();   //查询&排序
    void seekID_paint(bool if_show);
    void seekTitle_paint(bool if_show);
    void seekID();
    void seekTitle();

    int usrman();   //用户管理
    int lbook();    //借还书
    int modify();   //查询&修改个人信息
    void loading(); //载入界面

protected:
    Book book{};
    User user{};
    //页面栈(开发中)
    /*int head=0,tail=0;
    int page[10]={0};*/

private:
};



#endif //DISPLAY_H