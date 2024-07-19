//
// Created by lilon on 24-7-10.
//

#include "Display.h"

void show_book(Book bk, int x, int y,  bool if_chs){
    //    int x = 3+(index/4)*7, y = 0+(index%4)*30;
    moveto(x, y);
    unhigh_light();

    if (if_chs){
        high_light();
    }

    for (int i = 0; i < 7; i++) {
        moveto(x+i, y);
        printf("                              ");
    }

    moveto(x, y);
    printf("------------------------------");
    moveto(x+1, y);
    printf("|ID        :%d", bk.id);
    moveto(x+2, y);
    printf("|ISBN      :%s", bk.ISBN);
    moveto(x+3, y);
    printf("|Title     :%s", bk.Title);
    moveto(x+4, y);
    printf("|IF_in_lib :%s", (bk.status==0)?"IN":"OUT");
    moveto(x+5, y);
    printf("|POS       :%d-%c-%d-%d",
           bk.Where.floor, bk.Where.zone,
           bk.Where.shelf, bk.Where.number);
    moveto(x+6, y);
    printf("|Visibility:%s", bk.visual?"Visible":"Invisible");

    unhigh_light();

}

void painter(){
    moveto(8,50);
    printf("                                 ");
    moveto(9,50);
    printf("                                 ");
    moveto(14,70);
    cout<<"                  ";
    SET_FRONT_COLOR(FRONT_WHITE);
    for (int i = 0; i < 18; ++i) {
        moveto(8+i, 60);
        printf("|");
    }
}

void Display::LogRes() {
    loading();
    clear();
    hide_cursor();
    reset_cursor();
    user.power=false;
    for(int i=0;i<5;i++) {
        user.Borrow[i].id=0;
    }
    cout<<"Use Tab to switch options!"<<endl;
    moveto(12,56);
    SET_FRONT_COLOR(FRONT_BLUE);
    cout<<"Welcome!"<<endl;
    moveto(14,51);
    SET_FRONT_COLOR(FRONT_WHITE);
    cout<<"ID   ";
    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
    for(int i=1;i<=12;i++) cout<<" ";
    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
    moveto(15,48);
    cout<<"Password";
    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
    for(int i=1;i<=12;i++) cout<<" ";
    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
    moveto(16,57);
    cout<<"[Login]"<<endl;
    moveto(17,55);
    cout<<"[Register]"<<endl;
    moveto(18,57);
    cout<<"[Exit]"<<endl;
    int p=0,p_id=0,p_passwd=0;                  //选中界面、id指针、密码指针
    int id[20]={0};                             //id
    char passwd[52]={0};                        //密码
    while(true) {
        if(p==0) {
            moveto(14,56);
            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
            high_light();
            for(int i=1;i<=12;i++) cout<<" ";
            moveto(14,56);
            char ch=getch();
            while(ch!=9) {
                if(ch==127) {
                    if(p_id!=0) {
                        moveto(14,p_id+55);
                        cout<<" ";
                        moveto(14,p_id+55);
                        id[p_id-1]=0;
                        p_id--;
                    }
                    ch=getch();
                    continue;
                }
                if(ch<'0'||ch>'9') {
                    ch=getch();
                    continue;
                }
                cout<<ch;
                id[p_id++]=ch-'0';
                ch=getch();
            }
            unhigh_light();
            moveto(14,56);
            for(int i=0;i<12;i++) {
                if(i<p_id) {
                    cout<<id[i];
                }
                else cout<<" ";
            }
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            p++;
        }
        if(p==1) {
            moveto(15,56);
            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
            high_light();
            for(int i=1;i<=12;i++) cout<<" ";
            moveto(15,56);
            char ch=getch();
            while(ch!=9) {
                if(ch==127) {
                    if(p_passwd!=0) {
                        moveto(15,p_passwd+55);
                        cout<<" ";
                        moveto(15,p_passwd+55);
                        passwd[p_passwd-1]=0;
                        p_passwd--;
                    }
                    ch=getch();
                    continue;
                }
                if(ch<20||ch>126) {
                    ch=getch();
                    continue;
                }
                if(p_passwd<=11) cout<<"*";
                passwd[p_passwd++]=ch;
                ch=getch();
            }
            unhigh_light();
            moveto(15,56);
            for(int i=0;i<12;i++) {
                if(i<p_passwd) {
                    cout<<"*";
                }
                else cout<<" ";
            }
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            p++;
        }
        if(p==2) {
            hide_cursor();
            moveto(16,57);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Login]"<<endl;
            char ch=getch();
            while (ch!=9) {
                if(ch==10) {
                    unhigh_light();
                    if(p_id==0||p_passwd==0) {
                        clear();
                        p_id=p_passwd=0;
                        memset(id,0,sizeof(id));
                        memset(passwd,0,sizeof(passwd));
                        SET_FRONT_COLOR(FRONT_RED);
                        moveto(13,0);
                        cout<<"Error"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<endl<<"ID/Password Block"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<endl<<":( Please Retry"<<endl;
                        cout<<"Press Any Key To Continue";
                        SET_FRONT_COLOR(FRONT_WHITE);
                        ch=getch();
                        clear();
                        hide_cursor();
                        reset_cursor();
                        cout<<"Use Tab to switch options!"<<endl;
                        moveto(12,56);
                        SET_FRONT_COLOR(FRONT_BLUE);
                        cout<<"Welcome!"<<endl;
                        moveto(14,51);
                        SET_FRONT_COLOR(FRONT_WHITE);
                        cout<<"ID   ";
                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                        for(int i=1;i<=12;i++) cout<<" ";
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        moveto(15,48);
                        cout<<"Password";
                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                        for(int i=1;i<=12;i++) cout<<" ";
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        moveto(16,57);
                        cout<<"[Login]"<<endl;
                        moveto(17,55);
                        cout<<"[Register]"<<endl;
                        moveto(18,57);
                        cout<<"[Exit]"<<endl;
                        p--;
                        goto SKIP;
                    }
                    for(int i=0;i<p_id;i++) {
                        this->user.ID=this->user.ID*10+id[i];
                    }
                    strcpy(this->user.password,passwd);
                    int chk=pwd_comparison(this->user.ID,this->user.password);
                    if(chk==0) {
                        this->user=*get_user(this->user.ID);
                        return;
                    }
                    else if(chk==1) {
                        clear();
                        user.ID=0;
                        p_id=p_passwd=0;
                        memset(id,0,sizeof(id));
                        memset(passwd,0,sizeof(passwd));
                        SET_FRONT_COLOR(FRONT_RED);
                        moveto(13,0);
                        cout<<"Error"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<endl<<"Wrong Password"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<endl<<":( Please Retry"<<endl;
                        cout<<"Press Any Key To Continue";
                        SET_FRONT_COLOR(FRONT_WHITE);
                        ch=getch();
                        clear();
                        hide_cursor();
                        reset_cursor();
                        cout<<"Use Tab to switch options!"<<endl;
                        moveto(12,56);
                        SET_FRONT_COLOR(FRONT_BLUE);
                        cout<<"Welcome!"<<endl;
                        moveto(14,51);
                        SET_FRONT_COLOR(FRONT_WHITE);
                        cout<<"ID   ";
                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                        for(int i=1;i<=12;i++) cout<<" ";
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        moveto(15,48);
                        cout<<"Password";
                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                        for(int i=1;i<=12;i++) cout<<" ";
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        moveto(16,57);
                        cout<<"[Login]"<<endl;
                        moveto(17,55);
                        cout<<"[Register]"<<endl;
                        moveto(18,57);
                        cout<<"[Exit]"<<endl;
                    }
                    else if(chk==2) {
                        clear();
                        user.ID=0;
                        p_id=p_passwd=0;
                        memset(id,0,sizeof(id));
                        memset(passwd,0,sizeof(passwd));
                        SET_FRONT_COLOR(FRONT_RED);
                        moveto(13,0);
                        cout<<"Error"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<endl<<"User Not Exist"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<endl<<":( Please Retry"<<endl;
                        cout<<"Press Any Key To Continue";
                        SET_FRONT_COLOR(FRONT_WHITE);
                        ch=getch();
                        clear();
                        hide_cursor();
                        reset_cursor();
                        cout<<"Use Tab to switch options!"<<endl;
                        moveto(12,56);
                        SET_FRONT_COLOR(FRONT_BLUE);
                        cout<<"Welcome!"<<endl;
                        moveto(14,51);
                        SET_FRONT_COLOR(FRONT_WHITE);
                        cout<<"ID   ";
                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                        for(int i=1;i<=12;i++) cout<<" ";
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        moveto(15,48);
                        cout<<"Password";
                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                        for(int i=1;i<=12;i++) cout<<" ";
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        moveto(16,57);
                        cout<<"[Login]"<<endl;
                        moveto(17,55);
                        cout<<"[Register]"<<endl;
                        moveto(18,57);
                        cout<<"[Exit]"<<endl;
                    }
                    else if(chk==-1) {
                        clear();
                        SET_FRONT_COLOR(FRONT_RED);
                        reset_cursor();
                        cout<<"Error With Document,Please check"<<endl;
                        exit(1);
                    }
                    p--;
                }
                ch=getch();
            }
            SKIP:
            unhigh_light();
            moveto(16,57);
            cout<<"[Login]"<<endl;
            p++;
        }
        if(p==3) {
            Back:
            moveto(17,55);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Register]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    //注册用户
                    loading();
                    clear();
                    unhigh_light();
                    reset_cursor();
                    int old=p; p=0;
                    cout<<"Use Tab to switch options!"<<endl;
                    moveto(14,50);
                    cout<<"Name  ";
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(15,48);
                    cout<<"Password";
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(16,49);
                    cout<<"Again  ";
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(18,55);
                    cout<<"[Register]"<<endl;
                    moveto(19,57);
                    cout<<"[Back]"<<endl;
                    memset(passwd,0,sizeof(passwd));
                    char name[52]={0},again[52]={0};
                    int p_name=0,p_again=0; p_passwd=0;
                    while(true) {
                        //Name
                        if(p==0) {
                            moveto(14,56);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(14,56);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_name!=0) {
                                        moveto(14,p_name+55);
                                        cout<<" ";
                                        moveto(14,p_name+55);
                                        p_name--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<20||ch>126) {
                                    ch=getch();
                                    continue;
                                }
                                cout<<ch;
                                name[p_name++]=ch;
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(14,56);
                            for(int i=0;i<12;i++) {
                                if(i<p_name) {
                                    cout<<name[i];
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        //Passwd
                        if(p==1) {
                            moveto(15,56);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(15,56);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_passwd!=0) {
                                        moveto(15,p_passwd+55);
                                        cout<<" ";
                                        moveto(15,p_passwd+55);
                                        p_passwd--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<20||ch>126) {
                                    ch=getch();
                                    continue;
                                }
                                if(p_passwd<=11) cout<<"*";
                                passwd[p_passwd++]=ch;
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(15,56);
                            for(int i=0;i<12;i++) {
                                if(i<p_passwd) {
                                    cout<<"*";
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        //Again
                        if(p==2) {
                            moveto(16,56);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(16,56);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_again!=0) {
                                        moveto(16,p_again+55);
                                        cout<<" ";
                                        moveto(16,p_again+55);
                                        p_again--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<20||ch>126) {
                                    ch=getch();
                                    continue;
                                }
                                if(p_again<=11) cout<<"*";
                                again[p_again++]=ch;
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(16,56);
                            for(int i=0;i<12;i++) {
                                if(i<p_again) {
                                    cout<<"*";
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        //注册
                        if(p==3) {
                            hide_cursor();
                            moveto(18,55);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Register]"<<endl;
                            ch=getch();
                            while (ch!=9) {
                                if(ch==10) {
                                    unhigh_light();
                                    if(strcmp(passwd,again)!=0) {
                                        unhigh_light();
                                        clear();
                                        p_name=p_passwd=0;
                                        memset(passwd,0,sizeof(passwd));
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"The two inputs are inconsistent"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<":( Please Retry"<<endl;
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        clear();
                                        hide_cursor();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(14,50);
                                        cout<<"Name  ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(15,48);
                                        cout<<"Password";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(16,49);
                                        cout<<"Again  ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(18,55);
                                        cout<<"[Register]"<<endl;
                                        moveto(19,57);
                                        cout<<"[Back]"<<endl;
                                        high_light();
                                        p--;
                                        goto SKIP1;
                                    }
                                    if(p_name==0||p_passwd==0) {
                                        clear();
                                        p_name=p_passwd=0;
                                        memset(passwd,0,sizeof(passwd));
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"Name/Password Block"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<":( Please Retry"<<endl;
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        clear();
                                        hide_cursor();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(14,50);
                                        cout<<"Name  ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(15,48);
                                        cout<<"Password";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(16,49);
                                        cout<<"Again  ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(18,55);
                                        cout<<"[Register]"<<endl;
                                        moveto(19,57);
                                        cout<<"[Back]"<<endl;
                                        }
                                    strcpy(this->user.name,name);
                                    strcpy(this->user.password,passwd);
                                    this->user.ID=get_user_num();
                                    int tmp=append_user(&this->user);
                                    if(tmp==0) {
                                        clear();
                                        memset(passwd,0,sizeof(passwd));
                                        SET_FRONT_COLOR(FRONT_GREEN);
                                        moveto(13,0);
                                        cout<<"Success"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"Your ID is "<<user.ID<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<":) Please Remember it"<<endl;
                                        cout<<"Press Any Key To Continue";
                                        ch=getch();
                                        loading();
                                        user.ID=0;
                                        memset(passwd,0,sizeof(passwd));
                                        memset(id,0,sizeof(id));
                                        p_passwd=0; p_id=0; p=old;
                                        unhigh_light();
                                        clear();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(12,56);
                                        SET_FRONT_COLOR(FRONT_BLUE);
                                        cout<<"Welcome!"<<endl;
                                        moveto(14,51);
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        cout<<"ID   ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(15,48);
                                        cout<<"Password";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(16,57);
                                        cout<<"[Login]"<<endl;
                                        moveto(17,55);
                                        cout<<"[Register]"<<endl;
                                        moveto(18,57);
                                        cout<<"[Exit]"<<endl;
                                        goto Back;
                                    }
                                    else {
                                        clear();
                                        SET_FRONT_COLOR(FRONT_RED);
                                        reset_cursor();
                                        cout<<"Error With Document,Please check"<<endl;
                                        exit(1);
                                    }
                                }
                                ch=getch();
                            }
                            SKIP1:
                            unhigh_light();
                            moveto(18,55);
                            cout<<"[Register]"<<endl;
                            p++;
                        }
                        if(p==4) {
                            hide_cursor();
                            moveto(19,57);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Back]"<<endl;
                            ch=getch();
                            while (ch!=9) {
                                if(ch==10) {
                                    memset(passwd,0,sizeof(passwd));
                                    memset(id,0,sizeof(id));
                                    p_passwd=0; p_id=0; p=old;
                                    unhigh_light();
                                    clear();
                                    reset_cursor();
                                    cout<<"Use Tab to switch options!"<<endl;
                                    moveto(12,56);
                                    SET_FRONT_COLOR(FRONT_BLUE);
                                    cout<<"Welcome!"<<endl;
                                    moveto(14,51);
                                    SET_FRONT_COLOR(FRONT_WHITE);
                                    cout<<"ID   ";
                                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                    for(int i=1;i<=12;i++) cout<<" ";
                                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                    moveto(15,48);
                                    cout<<"Password";
                                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                    for(int i=1;i<=12;i++) cout<<" ";
                                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                    moveto(16,57);
                                    cout<<"[Login]"<<endl;
                                    moveto(17,55);
                                    cout<<"[Register]"<<endl;
                                    moveto(18,57);
                                    cout<<"[Exit]"<<endl;
                                    goto Back;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(19,57);
                            cout<<"[Back]"<<endl;
                            p=0;
                        }
                    }
                }
                ch=getch();
            }
            unhigh_light();
            moveto(17,55);
            cout<<"[Register]"<<endl;
            p++;
        }
        if(p==4) {
            moveto(18,57);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Exit]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    // 我是来结束这个程序的
                    clear();
                    exit(0);
                }
                ch=getch();
            }
            unhigh_light();
            moveto(18,57);
            cout<<"[Exit]"<<endl;
            reset_cursor();
            show_cursor();
            p=0;
        }
    }
}

int Display::mainpage() {
    loading();
    clear(); int p=0;
    for(int i=0;i<30;i++) {
           moveto(i,20);
           cout<<"|";
    }
    reset_cursor();
    hide_cursor();
    //管理员
    if(user.power) {
        cout<<"[Book Check]"<<endl<<endl;       //1
        cout<<"[Book Management]"<<endl<<endl;  //2
        cout<<"[Search]"<<endl<<endl;           //3
        cout<<"[User Management]"<<endl<<endl;  //4
        cout<<"[Mine]"<<endl<<endl;             //5
        cout<<"[Logout]"<<endl<<endl;           //0
        cout<<"[Exit]"<<endl<<endl;
        while(true) {
            if(p==0) {
                moveto(1,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Book Check]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        unhigh_light();
                        return 1;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(1,0);
                cout<<"[Book Check]"<<endl;
                p++;
            }
            if(p==1) {
                moveto(3,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Book Management]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        unhigh_light();
                        return 2;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(3,0);
                cout<<"[Book Management]"<<endl;
                p++;
            }
            if(p==2) {
                moveto(5,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Search]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        unhigh_light();
                        return 3;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(5,0);
                cout<<"[Search]"<<endl;
                p++;
            }
            if(p==3) {
                moveto(7,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[User Management]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        unhigh_light();
                        return 4;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(7,0);
                cout<<"[User Management]"<<endl;
                p++;
            }
            if(p==4) {
                moveto(9,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Mine]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        unhigh_light();
                        return 5;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(9,0);
                cout<<"[Mine]"<<endl;
                p++;
            }
            if(p==5) {
                moveto(11,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Logout]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        user.ID=0;
                        unhigh_light();
                        return 0;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(11,0);
                cout<<"[Logout]"<<endl;
                p++;
            }
            if(p==6) {
                moveto(13,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Exit]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        //我是来结束这个程序的
                        clear();
                        exit(0);
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(13,0);
                cout<<"[Exit]"<<endl;
                p=0;
            }
        }
    }
    else {
        cout<<"[Book Check]"<<endl<<endl;   //1
        cout<<"[Search]"<<endl<<endl;       //3
        cout<<"[Bor&Ret]"<<endl<<endl;      //6
        cout<<"[Mine]"<<endl<<endl;         //5
        cout<<"[Logout]"<<endl<<endl;       //0
        cout<<"[Exit]"<<endl<<endl;
        while(true) {
            if(p==0) {
                moveto(1,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Book Check]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        unhigh_light();
                        return 1;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(1,0);
                cout<<"[Book Check]"<<endl;
                p++;
            }
            if(p==1) {
                moveto(3,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Search]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        unhigh_light();
                        return 3;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(3,0);
                cout<<"[Search]"<<endl;
                p++;
            }
            if(p==2) {
                moveto(5,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Bor&Ret]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        unhigh_light();
                        return 6;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(5,0);
                cout<<"[Bor&Ret]"<<endl;
                p++;
            }
            if(p==3) {
                moveto(7,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Mine]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        unhigh_light();
                        return 5;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(7,0);
                cout<<"[Mine]"<<endl;
                p++;
            }
            if(p==4) {
                moveto(9,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Logout]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        user.ID=0;
                        unhigh_light();
                        return 0;
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(9,0);
                cout<<"[Logout]"<<endl;
                p++;
            }
            if(p==5) {
                moveto(11,0);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                high_light();
                cout<<"[Exit]"<<endl;
                char ch=getch();
                while(ch!=9) {
                    if(ch==10) {
                        //我是来结束这个程序的
                        clear();
                        exit(0);
                    }
                    ch=getch();
                }
                unhigh_light();
                moveto(11,0);
                cout<<"[Exit]"<<endl;
                p=0;
            }
        }
    }
    char ch=getch();
    return 0;
}

int Display::check() {
    int Book_ref = 0, page = 0, book_num = get_book_num() - page*BOOK_PAGE_NUM;
    if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;

    loading();

    clear();
    hide_cursor();
    reset_cursor();

    moveto(1, 0);
    printf("Q->Left");
    moveto(1, 15);
    printf("E->Right");
    moveto(2, 0);
    printf("J->Back");
    moveto(2, 15);
    printf("K->Exit");


    Book* book_list = list_books(page);
    for (int i = 0; i < 16; i++) {
        show_book(book_list[i], 3+(i/4)*7, 0+(i%4)*30, false    );
    }

    show_book(book_list[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);

    while (true){
        char ch=getch();
        if(ch=='q'||ch=='e'||ch=='j'||ch=='k') {
            ch=ch-'a'+'A';
        }
        switch (ch) {
            case 9:
                if (Book_ref<15){
                    show_book(book_list[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, false);
                    show_book(book_list[Book_ref+1], 3+((Book_ref+1)/4)*7, 0+((Book_ref+1)%4)*30, true);
                } else{
                    show_book(book_list[book_num-1], 3+((book_num-1)/4)*7, 0+((book_num-1)%4)*30, false);
                    show_book(book_list[0], 3, 0,true);
                }
                Book_ref++;
                if (Book_ref==book_num) Book_ref = 0;
                break;
            case 'Q':

                if (page == 0) break;

                page--;

                book_list = list_books(page);
                for (int i = 0; i < 16; i++) {
                    show_book(book_list[i], 3+(i/4)*7, 0+(i%4)*30, false);
                }

                show_book(book_list[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                break;
            case 'E':
                if (page*BOOK_PAGE_NUM+book_num==get_book_num()) break;
                page++;
                book_num = get_book_num() - page*BOOK_PAGE_NUM;
                if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;

                book_list = list_books(page);
                for (int i = 0; i < 16; i++) {
                    show_book(book_list[i], 3+(i/4)*7, 0+(i%4)*30, false);
                }

                show_book(book_list[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                break;

            case 'K':
                clear();
                exit(0);
            case 'J':
                return 0;
        }
    }
    return 0;
}

void modify_book(int mode, Book bk){
    int tab_ref = 0;
    switch (mode) {
        case 0:
            SET_FRONT_COLOR(FRONT_RED);
            moveto(20, 70);
            printf("[Modify_Visibility]");
            SET_FRONT_COLOR(FRONT_WHITE);

            moveto(20, 22);
            printf("                  ");
            break;
        case 1:
            SET_FRONT_COLOR(FRONT_RED);
            moveto(16, 70);
            printf("[Modify_ISBN]");
            SET_FRONT_COLOR(FRONT_WHITE);
            moveto(16, 22);
            printf("                  ");
            break;
        case 2:
            SET_FRONT_COLOR(FRONT_RED);
            moveto(17, 70);
            printf("[Modify_Title]");
            SET_FRONT_COLOR(FRONT_WHITE);
            moveto(17, 22);
            printf("                  ");
            break;
        case 3:
            SET_FRONT_COLOR(FRONT_RED);
            moveto(19, 70);
            printf("[Modify_Pos]");
            SET_FRONT_COLOR(FRONT_WHITE);
            moveto(19, 22);
            printf("                  ");
            break;
    }

    SET_FRONT_COLOR(FRONT_RED);
    moveto(22, 70);
    printf("[Modify]");
    SET_FRONT_COLOR(FRONT_WHITE);

    SET_FRONT_COLOR(FRONT_RED);
    moveto(23, 70);
    printf("[Back]");
    SET_FRONT_COLOR(FRONT_WHITE);

    char info[52] = {0};
    while (true){
        int  p = 0;


        char ch = getch();
        switch (ch) {
            case 9:
                if (tab_ref == 1){
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(23, 70);
                    printf("[Back]");
                    SET_FRONT_COLOR(FRONT_WHITE);

                    SET_BACKGROUND_COLOR(BACKGROUND_RED);
                    SET_FRONT_COLOR(FRONT_BLACK);
                    moveto(22, 70);
                    printf("[Modify]");
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    tab_ref++;
                } else if(tab_ref == 2){
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(22, 70);
                    printf("[Modify]");
                    SET_FRONT_COLOR(FRONT_WHITE);

                    SET_BACKGROUND_COLOR(BACKGROUND_RED);
                    SET_FRONT_COLOR(FRONT_BLACK);
                    moveto(23, 70);
                    printf("[Back]");
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    tab_ref = 0;
                } else if(tab_ref == 0){
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(23, 70);
                    printf("[Back]");
                    SET_FRONT_COLOR(FRONT_WHITE);

                    switch (mode) {
                        case 0:
                            moveto(20,22);
                            high_light();
                            printf("          ");
                            show_cursor();
                            moveto(20,22);
                            break;
                        case 1:
                            moveto(16,22);
                            high_light();
                            printf("          ");
                            show_cursor();
                            moveto(16,22);
                            break;
                        case 2:
                            moveto(17,22);
                            high_light();
                            printf("          ");
                            show_cursor();
                            moveto(17,22);
                            break;
                        case 3:
                            moveto(19,22);
                            high_light();
                            printf("          ");
                            show_cursor();
                            moveto(19,22);
                            break;
                    }

                    ch=getch();
                    while(ch!=9) {
                        if(ch==127) {
                            if(p!=0) {
                                switch (mode) {
                                    case 0:
                                        moveto(20,p+21);
                                        cout<<" ";
                                        moveto(20,p+21);
                                        p--;
                                        break;
                                    case 1:
                                        moveto(16,p+21);
                                        cout<<" ";
                                        moveto(16,p+21);
                                        p--;
                                        break;
                                    case 2:
                                        moveto(17,p+21);
                                        cout<<" ";
                                        moveto(17,p+21);
                                        p--;
                                        break;
                                    case 3:
                                        moveto(19,p+21);
                                        cout<<" ";
                                        moveto(19,p+21);
                                        p--;
                                        break;
                                }

                            }
                            ch=getch();
                            continue;
                        }
                        if(ch<20||ch>120) {
                            ch=getch();
                            continue;
                        }
                        cout<<ch;
                        info[p++]=ch;
                        ch=getch();
                    }
                    hide_cursor();
                    unhigh_light();

                    tab_ref++;
                }
                break;
            case 10:
                if (tab_ref == 2){
                    Book new_book;
                    book_copy(new_book, bk);

                    switch (mode) {
                        case 1:
                            strcpy(new_book.ISBN, info);
                            break;
                        case 2:
                            strcpy(bk.Title, info);
                            break;
                    }
                    int  status = update_book(&new_book);
                    moveto(0,0);
                    printf("%d", status);
                    Book* book = seek_book_by_id(bk.id);
                    if (book == nullptr) printf("NULL");
                    show_book(*book, 14, 10, true);
                    memset(info,0,sizeof(info));

                } else if (tab_ref == 0){
                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(22, 70);
                    printf("           ");
                    SET_FRONT_COLOR(FRONT_WHITE);

                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(23, 70);
                    printf("         ");
                    SET_FRONT_COLOR(FRONT_WHITE);


                    return;
                }
                break;
        }
    }
}
void manage_book(Book bk){
    clear();
    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
    show_book(bk, 14, 10, true);
    for (int i = 0; i < 18; ++i) {
        moveto(8+i, 60);
        printf("|");
    }

    moveto(16, 70);
    printf("[Modify_ISBN]");

    moveto(17, 70);
    printf("[Modify_Title]");

    moveto(19, 70);
    printf("[Modify_Pos]");

    moveto(20, 70);
    printf("[Modify_Visibility]");

    int tab_ref = 0;
    while (true){
        bk = *seek_book_by_id(bk.id);
        show_book(bk, 14, 10, true);

        char ch = getch();
        switch (ch) {
            case 9:
                if (tab_ref == 0){
                    high_light();
                    moveto(20, 10);
                    printf("                              ");
                    moveto(20, 10);
                    printf("|Visibility:%s", bk.visual?"Visible":"Invisible");
                    unhigh_light();

                    moveto(20, 70);
                    printf("[Modify_Visibility]");

                    high_light();
                    moveto(16, 70);
                    printf("[Modify_ISBN]");
                    unhigh_light();

                    moveto(16, 10);
                    printf("                              ");
                    moveto(16, 10);
                    printf("|ISBN      :%s", bk.ISBN);


                    tab_ref++;
                }
                else if (tab_ref == 1){
                    moveto(16, 10);
                    high_light();
                    printf("                              ");
                    moveto(16, 10);
                    printf("|ISBN      :%s", bk.ISBN);
                    unhigh_light();

                    moveto(16, 70);
                    printf("[Modify_ISBN]");

                    high_light();
                    moveto(17, 70);
                    printf("[Modify_Title]");
                    unhigh_light();

                    moveto(17, 10);
                    printf("                              ");
                    moveto(17, 10);
                    printf("|Title     :%s", bk.Title);

                    tab_ref++;
                } else if (tab_ref == 2){
                    moveto(17, 10);
                    high_light();
                    printf("                              ");
                    moveto(17, 10);
                    printf("|Title     :%s", bk.Title);
                    unhigh_light();

                    moveto(17, 70);
                    printf("[Modify_Title]");

                    high_light();
                    moveto(19, 70);
                    printf("[Modify_Pos]");
                    unhigh_light();

                    moveto(19, 10);
                    printf("                              ");
                    moveto(19, 10);
                    printf("|POS       :%d-%c-%d-%d",
                           bk.Where.floor, bk.Where.zone,
                           bk.Where.shelf, bk.Where.number);

                    tab_ref++;
                } else if (tab_ref == 3){
                    high_light();
                    moveto(19, 10);
                    printf("                              ");
                    moveto(19, 10);
                    printf("|POS       :%d-%c-%d-%d",
                           bk.Where.floor, bk.Where.zone,
                           bk.Where.shelf, bk.Where.number);
                    unhigh_light();

                    moveto(19, 70);
                    printf("[Modify_Pos]");

                    high_light();
                    moveto(20, 70);
                    printf("[Modify_Visibility]");
                    unhigh_light();

                    moveto(20, 10);
                    printf("                              ");
                    moveto(20, 10);
                    printf("|Visibility:%s", bk.visual?"Visible":"Invisible");

                    tab_ref = 0;
                }
                break;
            case 10:
                modify_book(tab_ref, bk);
                break;
            case 'K':
                exit(0);
            case 'J':
                return;
        }
    }
}
int Display::manage() {
    int Book_ref = 0, page = 0, book_num = get_book_num() - page*BOOK_PAGE_NUM;
    if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;

    loading();

    clear();
    hide_cursor();
    reset_cursor();
    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);

    moveto(1, 0);
    printf("Q->Left");
    moveto(1, 15);
    printf("E->Right");
    moveto(2, 0);
    printf("J->Back");
    moveto(2, 15);
    printf("K->Exit");


    Book* book_list = list_books(page);
    for (int i = 0; i < 16; i++) {
        show_book(book_list[i], 3+(i/4)*7, 0+(i%4)*30, false);
    }

    show_book(book_list[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);

    while (true){
        char ch=getch();
        switch (ch) {
            case 9:
                if (Book_ref<15){
                    show_book(book_list[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, false);
                    show_book(book_list[Book_ref+1], 3+((Book_ref+1)/4)*7, 0+((Book_ref+1)%4)*30, true);
                } else{
                    show_book(book_list[book_num-1], 3+((book_num-1)/4)*7, 0+((book_num-1)%4)*30, false);
                    show_book(book_list[0], 3, 0,true);
                }
                Book_ref++;
                if (Book_ref==book_num) Book_ref = 0;
                break;

            case 10:
                manage_book(book_list[Book_ref]);
                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);

                moveto(1, 0);
                printf("Q->Left");
                moveto(1, 15);
                printf("E->Right");
                moveto(2, 0);
                printf("J->Back");
                moveto(2, 15);
                printf("K->Exit");


                book_list = list_books(page);
                for (int i = 0; i < 16; i++) {
                    show_book(book_list[i], 3+(i/4)*7, 0+(i%4)*30, false);
                }

                show_book(book_list[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);

                break;
            case 'Q':

                if (page == 0) break;

                page--;

                book_list = list_books(page);
                for (int i = 0; i < 16; i++) {
                    show_book(book_list[i], 3+(i/4)*7, 0+(i%4)*30, false);
                }

                show_book(book_list[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                break;
            case 'E':
                if (page*BOOK_PAGE_NUM+book_num==get_book_num()) break;
                page++;
                book_num = get_book_num() - page*BOOK_PAGE_NUM;
                if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;

                book_list = list_books(page);
                for (int i = 0; i < 16; i++) {
                    show_book(book_list[i], 3+(i/4)*7, 0+(i%4)*30, false);
                }

                show_book(book_list[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                break;

            case 'K':
                clear();
                exit(0);
            case 'J':
                return 0;
        }
    }
    return 0;
}

int Display::search() {
    int mode_ref = 0;
    loading();
    clear();

    moveto(8,50);
    SET_FRONT_COLOR(FRONT_BLUE);
    cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
    moveto(9,50);
    cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

    moveto(14,30);
    SET_FRONT_COLOR(FRONT_WHITE);
    cout<<"SEEK BY BOOK-ID";

    moveto(14,70);
    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
    cout<<"SEEK BY BOOK-TITLE";

    while (true){
        char ch=getch();
        if(ch=='q'||ch=='e'||ch=='j'||ch=='k') {
            ch=ch-'a'+'A';
        }

        switch (ch) {
            case 9:
                //ID
                if (mode_ref){
                    mode_ref = 0;

                    SET_FRONT_COLOR(FRONT_WHITE);
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(14,70);
                    cout<<"SEEK BY BOOK-TITLE";
                    seekTitle_paint(false);

                    high_light();
                    moveto(14,30);
                    SET_FRONT_COLOR(FRONT_RED);
                    cout<<"SEEK BY BOOK-ID";
                    SET_FRONT_COLOR(FRONT_WHITE);
                    unhigh_light();
                    seekID_paint(true);

                } else{
                    mode_ref = 1;

                    SET_FRONT_COLOR(FRONT_WHITE);
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(14,30);
                    cout<<"SEEK BY BOOK-ID";
                    seekID_paint(false);

                    high_light();
                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(14,70);
                    cout<<"SEEK BY BOOK-TITLE";
                    SET_FRONT_COLOR(FRONT_WHITE);
                    unhigh_light();
                    seekTitle_paint(true);

                }
                break;
            case 10:
                if (mode_ref)
                    seekTitle();
                else
                    seekID();
                break;
            case 'J':
                return 0;
            case 'K':
                exit(0);
        }
    }
    return 0;
}
void Display::seekID_paint(bool if_show){
    if (if_show){
        SET_FRONT_COLOR(FRONT_RED);
        moveto(18,30);
        printf("BOOK-ID:");
        SET_BACKGROUND_COLOR(BACKGROUND_RED);
        printf("          ");
        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
        moveto(22,34);
        printf("[Search]");
        moveto(23,35);
        printf("[Back]");
        SET_FRONT_COLOR(FRONT_WHITE);
    } else{
        moveto(18, 25);
        printf("                       ");
        moveto(22, 34);
        printf("                       ");
        moveto(23, 34);
        printf("                       ");

    }
}
void Display::seekTitle_paint(bool if_show){
    if (if_show){
        SET_FRONT_COLOR(FRONT_RED);
        moveto(18,70);
        printf("BOOK-Title:");
        SET_BACKGROUND_COLOR(BACKGROUND_RED);
        printf("          ");
        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
        moveto(22,74);
        printf("[Search]");
        moveto(23,75);
        printf("[Back]");
        SET_FRONT_COLOR(FRONT_WHITE);
    } else {
        moveto(18, 70);
        printf("                       ");
        moveto(22, 74);
        printf("                       ");
        moveto(23, 74);
        printf("                       ");

    }
}
void Display::seekID(){
    moveto(14,70);
    cout<<"                  ";
    painter();
    int id[20]={0};
    int tab_ref = 0,p_id=0;

    while (true){
        char ch = getch();
        switch (ch) {
            case 9:
                //Search
                if (tab_ref == 1){
                    SET_BACKGROUND_COLOR(BACKGROUND_RED);
                    SET_FRONT_COLOR(FRONT_BLACK);
                    moveto(18,38);
                    for(int i=0;i<10;i++) {
                        if(i<p_id) {
                            cout<<id[i];
                        }
                        else cout<<" ";
                    }

                    SET_BACKGROUND_COLOR(BACKGROUND_RED);
                    SET_FRONT_COLOR(FRONT_BLACK);
                    moveto(22,34);
                    printf("[Search]");
                    tab_ref = 0;
                }
                //Back
                else if(tab_ref==0) {
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(22,34);
                    printf("[Search]");

                    SET_BACKGROUND_COLOR(BACKGROUND_RED);
                    SET_FRONT_COLOR(FRONT_BLACK);
                    moveto(23,35);
                    printf("[Back]");
                    tab_ref = 2;
                }
                //输入栏
                else {
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(23,35);
                    printf("[Back]");

                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    SET_FRONT_COLOR(FRONT_RED);
                    show_cursor();
                    moveto(18,38);
                    printf("          ");
                    moveto(18,38);
                    tab_ref = 1;

                    ch=getch();
                    while(ch!=9) {
                        if(ch==127) {
                            if(p_id!=0) {
                                moveto(18,p_id+37);
                                cout<<" ";
                                moveto(18,p_id+37);
                                p_id--;
                            }
                            ch=getch();
                            continue;
                        }
                        if(ch<'0'||ch>'9') {
                            ch=getch();
                            continue;
                        }
                        cout<<ch;
                        id[p_id++]=ch-'0';
                        ch=getch();
                    }
                    hide_cursor();
                }
                break;
            case 10:
                if (tab_ref == 0){
                    int ID=0;
                    for(int i=0;i<p_id;i++) {
                        ID=ID*10+id[i];
                    }
                    Book* BK = seek_book_by_id(ID);
                    p_id=0; memset(id,0,sizeof(id));
                    if(BK==nullptr) {
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        clear();
                        SET_FRONT_COLOR(FRONT_RED);
                        moveto(13,0);
                        cout<<"Error"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<endl<<"ID:"<<ID<<" Not Exist"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<"Press Any Key To Continue";
                        SET_FRONT_COLOR(FRONT_WHITE);
                        ch=getch();
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        clear();
                        unhigh_light();
                        moveto(8,50);
                        p_id=0; memset(id,0,sizeof(id));
                        SET_FRONT_COLOR(FRONT_BLUE);
                        cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
                        moveto(9,50);
                        cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

                        moveto(14,30);
                        SET_FRONT_COLOR(FRONT_WHITE);
                        cout<<"SEEK BY BOOK-ID";

                        moveto(14,70);
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        cout<<"SEEK BY BOOK-TITLE";
                        return;
                    }
                    show_book(*BK, 14, 70, false);
                }
                else if(tab_ref==2) {
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    clear();
                    unhigh_light();
                    moveto(8,50);
                    p_id=0; memset(id,0,sizeof(id));
                    SET_FRONT_COLOR(FRONT_BLUE);
                    cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
                    moveto(9,50);
                    cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

                    moveto(14,30);
                    SET_FRONT_COLOR(FRONT_WHITE);
                    cout<<"SEEK BY BOOK-ID";

                    moveto(14,70);
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    cout<<"SEEK BY BOOK-TITLE";
                    return;
                }
                break;
        }
    }
}
void Display::seekTitle(){
    moveto(14,30);
    cout<<"                  ";
    painter();
    int p_title=0;
    char name[52]={0};
    int tab_ref = 0;

    while (true){
        char ch = getch();
        switch (ch) {
            case 9:
                //Search
                if (tab_ref == 1){
                    SET_BACKGROUND_COLOR(BACKGROUND_RED);
                    SET_FRONT_COLOR(FRONT_BLACK);
                    moveto(18,81);
                    for(int i=0;i<10;i++) {
                        if(i<p_title) {
                            cout<<name[i];
                        }
                        else cout<<" ";
                    }

                    SET_BACKGROUND_COLOR(BACKGROUND_RED);
                    SET_FRONT_COLOR(FRONT_BLACK);
                    moveto(22,74);
                    printf("[Search]");
                    tab_ref = 0;
                }
                //Back
                else if(tab_ref == 0) {
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(22,74);
                    printf("[Search]");

                    SET_BACKGROUND_COLOR(BACKGROUND_RED);
                    SET_FRONT_COLOR(FRONT_BLACK);
                    moveto(23,75);
                    printf("[Back]");
                    tab_ref = 2;
                }
                //输入栏
                else {
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    SET_FRONT_COLOR(FRONT_RED);
                    moveto(23,75);
                    printf("[Back]");

                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    SET_FRONT_COLOR(FRONT_RED);
                    show_cursor();
                    moveto(18,81);
                    printf("          ");
                    moveto(18,81);

                    ch=getch();
                    while(ch!=9) {
                        if(ch==127) {
                            if(p_title!=0) {
                                moveto(18,p_title+80);
                                cout<<" ";
                                moveto(18,p_title+80);
                                p_title--;
                            }
                            ch=getch();
                            continue;
                        }
                        if(ch<20||ch>126) {
                            ch=getch();
                            continue;
                        }
                        cout<<ch;
                        name[p_title++]=ch;
                        ch=getch();
                    }
                    hide_cursor();

                    tab_ref = 1;
                }
                break;
            case 10:
                if(tab_ref == 0) {
                    SET_FRONT_COLOR(FRONT_WHITE);
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    Book* BK = seek_book_by_Title(name);
                    p_title=0; memset(name,0,sizeof(name));
                    if(BK==nullptr) {
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        clear();
                        SET_FRONT_COLOR(FRONT_RED);
                        moveto(13,0);
                        cout<<"Error"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<endl<<name<<" Not Exist"<<endl;
                        for(int i=0;i<10;i++) {
                            cout<<"/";
                        }
                        cout<<"Press Any Key To Continue";
                        SET_FRONT_COLOR(FRONT_WHITE);
                        ch=getch();
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        clear();
                        unhigh_light();
                        moveto(8,50);
                        SET_FRONT_COLOR(FRONT_BLUE);
                        cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
                        moveto(9,50);
                        cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

                        moveto(14,30);
                        SET_FRONT_COLOR(FRONT_WHITE);
                        cout<<"SEEK BY BOOK-ID";

                        moveto(14,70);
                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                        cout<<"SEEK BY BOOK-TITLE";
                        return;
                    }
                    int num=0;
                    for(int i=0;i<1000;i++) {
                        if(BK[i].id!=0) num++;
                    }
                    clear(); int p=1;
                    reset_cursor();
                    hide_cursor();
                    SET_FRONT_COLOR(FRONT_WHITE);
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    cout<<"Use Tab to switch options!"<<endl;
                    moveto(12,50);
                    cout<<"[ID Normal order]";
                    moveto(13,50);
                    cout<<"[ID Reverse order]";
                    moveto(14,50);
                    cout<<"[Dictionaary Normal Order]";
                    moveto(15,50);
                    cout<<"[Dictionaary Reverse Order]";
                    moveto(16,57);
                    cout<<"[Back]";
                    while(true) {
                        if(p==1) {
                            moveto(12,50);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[ID Normal order]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    Sort_books(BK,num,p);
                                    unhigh_light();
                                    clear();
                                    moveto(1, 0);
                                    int Book_ref = 0, page = 0, book_num = num - page*BOOK_PAGE_NUM;
                                    if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;
                                    printf("Q->Left");
                                    moveto(1, 15);
                                    printf("E->Right");
                                    moveto(2, 0);
                                    printf("J->Back");
                                    moveto(2, 15);
                                    printf("K->Exit");
                                    for (int i = 0; i < 16; i++) {
                                        show_book(BK[i], 3+(i/4)*7, 0+(i%4)*30, false);
                                    }
                                    show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);

                                    while (true){
                                        ch=getch();
                                        switch (ch) {
                                            case 9:
                                                if (Book_ref<15){
                                                    show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, false);
                                                    show_book(BK[Book_ref+1], 3+((Book_ref+1)/4)*7, 0+((Book_ref+1)%4)*30, true);
                                                } else{
                                                    show_book(BK[book_num-1], 3+((book_num-1)/4)*7, 0+((book_num-1)%4)*30, false);
                                                    show_book(BK[0], 3, 0,true);
                                                }
                                            Book_ref++;
                                            if (Book_ref==book_num) Book_ref = 0;
                                            break;
                                            case 'Q':

                                                if (page == 0) break;

                                            page--;

                                            // book_list = list_books(page);
                                            for (int i = 0; i < 16; i++) {
                                                show_book(BK[i+page*BOOK_PAGE_NUM], 3+(i/4)*7, 0+(i%4)*30, false);
                                            }

                                            show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                                            break;
                                            case 'E':
                                                if (page*BOOK_PAGE_NUM+book_num==num) break;
                                            page++;
                                            book_num = num - page*BOOK_PAGE_NUM;
                                            if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;

                                            // book_list = list_books(page);
                                            for (int i = 0; i < 16; i++) {
                                                show_book(BK[i+page*BOOK_PAGE_NUM], 3+(i/4)*7, 0+(i%4)*30, false);
                                            }

                                            show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                                            break;

                                            case 'K':
                                                clear();
                                                exit(0);
                                            case 'J':
                                                clear();
                                                moveto(8,50);
                                                SET_FRONT_COLOR(FRONT_BLUE);
                                                cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
                                                moveto(9,50);
                                                cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

                                                moveto(14,30);
                                                SET_FRONT_COLOR(FRONT_WHITE);
                                                cout<<"SEEK BY BOOK-ID";

                                                moveto(14,70);
                                                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                cout<<"SEEK BY BOOK-TITLE";
                                                return;
                                        }
                                    }
                                    return;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(12,50);
                            cout<<"[ID Normal order]"<<endl;
                            p++;
                        }
                        if(p==2) {
                            moveto(13,50);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[ID Reverse order]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    Sort_books(BK,num,p);
                                    unhigh_light();
                                    clear();
                                    moveto(1, 0);
                                    int Book_ref = 0, page = 0, book_num = num - page*BOOK_PAGE_NUM;
                                    if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;
                                    printf("Q->Left");
                                    moveto(1, 15);
                                    printf("E->Right");
                                    moveto(2, 0);
                                    printf("J->Back");
                                    moveto(2, 15);
                                    printf("K->Exit");
                                    for (int i = 0; i < 16; i++) {
                                        show_book(BK[i], 3+(i/4)*7, 0+(i%4)*30, false);
                                    }
                                    show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);

                                    while (true){
                                        ch=getch();
                                        switch (ch) {
                                            case 9:
                                                if (Book_ref<15){
                                                    show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, false);
                                                    show_book(BK[Book_ref+1], 3+((Book_ref+1)/4)*7, 0+((Book_ref+1)%4)*30, true);
                                                } else{
                                                    show_book(BK[book_num-1], 3+((book_num-1)/4)*7, 0+((book_num-1)%4)*30, false);
                                                    show_book(BK[0], 3, 0,true);
                                                }
                                            Book_ref++;
                                            if (Book_ref==book_num) Book_ref = 0;
                                            break;
                                            case 'Q':

                                                if (page == 0) break;

                                            page--;

                                            // book_list = list_books(page);
                                            for (int i = 0; i < 16; i++) {
                                                show_book(BK[i+page*BOOK_PAGE_NUM], 3+(i/4)*7, 0+(i%4)*30, false);
                                            }

                                            show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                                            break;
                                            case 'E':
                                                if (page*BOOK_PAGE_NUM+book_num==num) break;
                                            page++;
                                            book_num = num - page*BOOK_PAGE_NUM;
                                            if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;

                                            // book_list = list_books(page);
                                            for (int i = 0; i < 16; i++) {
                                                show_book(BK[i+page*BOOK_PAGE_NUM], 3+(i/4)*7, 0+(i%4)*30, false);
                                            }

                                            show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                                            break;

                                            case 'K':
                                                clear();
                                                exit(0);
                                            case 'J':
                                                clear();
                                                moveto(8,50);
                                                SET_FRONT_COLOR(FRONT_BLUE);
                                                cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
                                                moveto(9,50);
                                                cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

                                                moveto(14,30);
                                                SET_FRONT_COLOR(FRONT_WHITE);
                                                cout<<"SEEK BY BOOK-ID";

                                                moveto(14,70);
                                                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                cout<<"SEEK BY BOOK-TITLE";
                                                return;
                                        }
                                    }
                                    return;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(13,50);
                            cout<<"[ID Reverse order]"<<endl;
                            p++;
                        }
                        if(p==3) {
                            moveto(14,50);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Dictionaary Normal order]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    Sort_books(BK,num,p);
                                    unhigh_light();
                                    clear();
                                    moveto(1, 0);
                                    int Book_ref = 0, page = 0, book_num = num - page*BOOK_PAGE_NUM;
                                    if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;
                                    printf("Q->Left");
                                    moveto(1, 15);
                                    printf("E->Right");
                                    moveto(2, 0);
                                    printf("J->Back");
                                    moveto(2, 15);
                                    printf("K->Exit");
                                    for (int i = 0; i < 16; i++) {
                                        show_book(BK[i], 3+(i/4)*7, 0+(i%4)*30, false);
                                    }
                                    show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);

                                    while (true){
                                        ch=getch();
                                        switch (ch) {
                                            case 9:
                                                if (Book_ref<15){
                                                    show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, false);
                                                    show_book(BK[Book_ref+1], 3+((Book_ref+1)/4)*7, 0+((Book_ref+1)%4)*30, true);
                                                } else{
                                                    show_book(BK[book_num-1], 3+((book_num-1)/4)*7, 0+((book_num-1)%4)*30, false);
                                                    show_book(BK[0], 3, 0,true);
                                                }
                                            Book_ref++;
                                            if (Book_ref==book_num) Book_ref = 0;
                                            break;
                                            case 'Q':

                                                if (page == 0) break;

                                            page--;

                                            // book_list = list_books(page);
                                            for (int i = 0; i < 16; i++) {
                                                show_book(BK[i+page*BOOK_PAGE_NUM], 3+(i/4)*7, 0+(i%4)*30, false);
                                            }

                                            show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                                            break;
                                            case 'E':
                                                if (page*BOOK_PAGE_NUM+book_num==num) break;
                                            page++;
                                            book_num = num - page*BOOK_PAGE_NUM;
                                            if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;

                                            // book_list = list_books(page);
                                            for (int i = 0; i < 16; i++) {
                                                show_book(BK[i+page*BOOK_PAGE_NUM], 3+(i/4)*7, 0+(i%4)*30, false);
                                            }

                                            show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                                            break;

                                            case 'K':
                                                clear();
                                                exit(0);
                                            case 'J':
                                                clear();
                                                moveto(8,50);
                                                SET_FRONT_COLOR(FRONT_BLUE);
                                                cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
                                                moveto(9,50);
                                                cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

                                                moveto(14,30);
                                                SET_FRONT_COLOR(FRONT_WHITE);
                                                cout<<"SEEK BY BOOK-ID";

                                                moveto(14,70);
                                                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                cout<<"SEEK BY BOOK-TITLE";
                                                return;
                                        }
                                    }
                                    return;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(14,50);
                            cout<<"[Dictionaary Normal order]"<<endl;
                            p++;
                        }
                        if(p==4) {
                            moveto(15,50);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Dictionaary Reverse order]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    Sort_books(BK,num,p);
                                    unhigh_light();
                                    clear();
                                    moveto(1, 0);
                                    int Book_ref = 0, page = 0, book_num = num - page*BOOK_PAGE_NUM;
                                    if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;
                                    printf("Q->Left");
                                    moveto(1, 15);
                                    printf("E->Right");
                                    moveto(2, 0);
                                    printf("J->Back");
                                    moveto(2, 15);
                                    printf("K->Exit");
                                    for (int i = 0; i < 16; i++) {
                                        show_book(BK[i], 3+(i/4)*7, 0+(i%4)*30, false);
                                    }
                                    show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);

                                    while (true){
                                        ch=getch();
                                        switch (ch) {
                                            case 9:
                                                if (Book_ref<15){
                                                    show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, false);
                                                    show_book(BK[Book_ref+1], 3+((Book_ref+1)/4)*7, 0+((Book_ref+1)%4)*30, true);
                                                } else{
                                                    show_book(BK[book_num-1], 3+((book_num-1)/4)*7, 0+((book_num-1)%4)*30, false);
                                                    show_book(BK[0], 3, 0,true);
                                                }
                                            Book_ref++;
                                            if (Book_ref==book_num) Book_ref = 0;
                                            break;
                                            case 'Q':

                                                if (page == 0) break;

                                            page--;

                                            // book_list = list_books(page);
                                            for (int i = 0; i < 16; i++) {
                                                show_book(BK[i+page*BOOK_PAGE_NUM], 3+(i/4)*7, 0+(i%4)*30, false);
                                            }

                                            show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                                            break;
                                            case 'E':
                                                if (page*BOOK_PAGE_NUM+book_num==num) break;
                                            page++;
                                            book_num = num - page*BOOK_PAGE_NUM;
                                            if (book_num>BOOK_PAGE_NUM) book_num = BOOK_PAGE_NUM;

                                            // book_list = list_books(page);
                                            for (int i = 0; i < 16; i++) {
                                                show_book(BK[i+page*BOOK_PAGE_NUM], 3+(i/4)*7, 0+(i%4)*30, false);
                                            }

                                            show_book(BK[Book_ref], 3+(Book_ref/4)*7, 0+(Book_ref%4)*30, true);
                                            break;

                                            case 'K':
                                                clear();
                                                exit(0);
                                            case 'J':
                                                clear();
                                                moveto(8,50);
                                                SET_FRONT_COLOR(FRONT_BLUE);
                                                cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
                                                moveto(9,50);
                                                cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

                                                moveto(14,30);
                                                SET_FRONT_COLOR(FRONT_WHITE);
                                                cout<<"SEEK BY BOOK-ID";

                                                moveto(14,70);
                                                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                cout<<"SEEK BY BOOK-TITLE";
                                                return;
                                        }
                                    }
                                    return;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(15,50);
                            cout<<"[Dictionaary Reverse order]"<<endl;
                            p++;
                        }
                        if(p==5) {
                            moveto(16,57);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Back]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    p_title=0;
                                    memset(name,0,sizeof(0));
                                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                    clear();
                                    unhigh_light();
                                    moveto(8,50);
                                    SET_FRONT_COLOR(FRONT_BLUE);
                                    cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
                                    moveto(9,50);
                                    cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

                                    moveto(14,30);
                                    SET_FRONT_COLOR(FRONT_WHITE);
                                    cout<<"SEEK BY BOOK-ID";

                                    moveto(14,70);
                                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                    cout<<"SEEK BY BOOK-TITLE";
                                    return;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(16,57);
                            cout<<"[Back]"<<endl;
                            p=1;
                        }
                    }
                }
                else if(tab_ref == 2) {
                    p_title=0;
                    memset(name,0,sizeof(0));
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    clear();
                    unhigh_light();
                    moveto(8,50);
                    SET_FRONT_COLOR(FRONT_BLUE);
                    cout<<"PRESS [TAB] TO CHOOSE SEARCH-MODE"<<endl;
                    moveto(9,50);
                    cout<<"PRESS [ENTER] TO CONFIRM"<<endl;

                    moveto(14,30);
                    SET_FRONT_COLOR(FRONT_WHITE);
                    cout<<"SEEK BY BOOK-ID";

                    moveto(14,70);
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    cout<<"SEEK BY BOOK-TITLE";
                    return;
                }
                break;
        }
    }
}

int Display::usrman() {
    loading();
    clear();
    hide_cursor();
    reset_cursor();
    cout<<"Use Tab to switch options!"<<endl;
    moveto(15,57);
    cout<<"[Delete]";
    moveto(16,57);
    cout<<"[Modify]";
    moveto(17,58);
    cout<<"[Back]";
    int p=0;
    while(true) {
        //Delete
        if(p==0) {
            SKIP2:
            moveto(15,57);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Delete]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    unhigh_light();
                    clear();
                    reset_cursor();
                    cout<<"Use Tab to switch options!"<<endl;
                    moveto(13,53);
                    SET_FRONT_COLOR(FRONT_RED);
                    cout<<"Input User's ID:";
                    SET_FRONT_COLOR(FRONT_WHITE);
                    moveto(14,55);
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(16,57);
                    cout<<"[Delete]";
                    moveto(17,58);
                    cout<<"[Back]";
                    int p_id=0;
                    int id[20]={0};
                    while(true) {
                        if(p==0) {
                            moveto(14,55);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(14,55);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_id!=0) {
                                        moveto(14,p_id+54);
                                        cout<<" ";
                                        moveto(14,p_id+54);
                                        id[p_id-1]=0;
                                        p_id--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<'0'||ch>'9') {
                                    ch=getch();
                                    continue;
                                }
                                cout<<ch;
                                id[p_id++]=ch-'0';
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(14,55);
                            for(int i=0;i<12;i++) {
                                if(i<p_id) {
                                    cout<<id[i];
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        if(p==1) {
                            SKIP5:
                            moveto(16,57);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Delete]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    int ID=0;
                                    unhigh_light();
                                    for(int i=0;i<p_id;i++) {
                                        ID=ID*10+id[i];
                                    }
                                    int tmp=del_user(ID);
                                    if(tmp==0) {
                                        clear();
                                        p_id=0;
                                        memset(id,0,sizeof(id));
                                        SET_FRONT_COLOR(FRONT_GREEN);
                                        moveto(13,0);
                                        cout<<"Success"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"ID:"<<ID<<" has been deleted"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<"Press Any Key To Continue";
                                        ch=getch();
                                        ID=0;
                                        unhigh_light();
                                        clear();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(13,53);
                                        SET_FRONT_COLOR(FRONT_RED);
                                        cout<<"Input User's ID:";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        moveto(14,55);
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(16,57);
                                        cout<<"[Delete]";
                                        moveto(17,58);
                                        cout<<"[Back]";
                                        goto SKIP5;
                                    }
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(16,57);
                            cout<<"[Delete]"<<endl;
                            p++;
                        }
                        if(p==2) {
                            moveto(17,58);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Back]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    p_id=0;p=0;
                                    unhigh_light();
                                    memset(id,0,sizeof(id));
                                    loading();
                                    clear();
                                    hide_cursor();
                                    reset_cursor();
                                    cout<<"Use Tab to switch options!"<<endl;
                                    moveto(15,57);
                                    cout<<"[Delete]";
                                    moveto(16,57);
                                    cout<<"[Modify]";
                                    moveto(17,58);
                                    cout<<"[Back]"<<endl;
                                    goto SKIP2;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(17,58);
                            cout<<"[Back]"<<endl;
                            p=0;
                        }
                    }
                }
                ch=getch();
            }
            unhigh_light();
            moveto(15,57);
            cout<<"[Delete]"<<endl;
            p++;
        }
        //Modify
        if(p==1) {
            moveto(16,57);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Modify]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    unhigh_light();
                    clear();
                    reset_cursor();
                    cout<<"Use Tab to switch options!"<<endl;
                    moveto(13,53);
                    SET_FRONT_COLOR(FRONT_RED);
                    cout<<"Input User's ID:";
                    SET_FRONT_COLOR(FRONT_WHITE);
                    moveto(14,55);
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(16,57);
                    cout<<"[Modify]";
                    moveto(17,58);
                    cout<<"[Back]";
                    int p_id=0;
                    int id[20]={0};
                    while(true) {
                        //ID
                        if(p==0) {
                            moveto(14,55);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(14,55);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_id!=0) {
                                        moveto(14,p_id+54);
                                        cout<<" ";
                                        moveto(14,p_id+54);
                                        id[p_id-1]=0;
                                        p_id--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<'0'||ch>'9') {
                                    ch=getch();
                                    continue;
                                }
                                cout<<ch;
                                id[p_id++]=ch-'0';
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(14,55);
                            for(int i=0;i<12;i++) {
                                if(i<p_id) {
                                    cout<<id[i];
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        //Modify
                        if(p==1) {
                            SKIP3:
                            moveto(16,57);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Modify]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    int ID=0;
                                    unhigh_light();
                                    for(int i=0;i<p_id;i++) {
                                        ID=ID*10+id[i];
                                    }
                                    User* tmp=get_user(ID);
                                    if(tmp==nullptr) {
                                        ID=0;p_id=0;
                                        clear();
                                        memset(id,0,sizeof(id));
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"User Not Exist"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<":( Please Retry"<<endl;
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        unhigh_light();
                                        clear();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(13,53);
                                        SET_FRONT_COLOR(FRONT_RED);
                                        cout<<"Input User's ID:";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        moveto(14,55);
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(16,57);
                                        cout<<"[Modify]";
                                        moveto(17,58);
                                        cout<<"[Back]";
                                        goto SKIP3;
                                    }
                                    else {
                                        clear();
                                        unhigh_light();
                                        reset_cursor();
                                        int old=p; p=0;
                                        int p_passwd=0,p_again=0;
                                        char passwd[52]={0},again[52]={0};
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(14,48);
                                        cout<<"Password";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(15,49);
                                        cout<<"Again  ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(17,55);
                                        cout<<"[Modify]"<<endl;
                                        moveto(18,57);
                                        cout<<"[Back]"<<endl;
                                        while(true) {
                                            //Passwd
                                            if(p==0) {
                                                moveto(14,56);
                                                SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                                high_light();
                                                for(int i=1;i<=12;i++) cout<<" ";
                                                moveto(14,56);
                                                ch=getch();
                                                while(ch!=9) {
                                                    if(ch==127) {
                                                        if(p_passwd!=0) {
                                                            moveto(14,p_passwd+55);
                                                            cout<<" ";
                                                            moveto(14,p_passwd+55);
                                                            p_passwd--;
                                                        }
                                                        ch=getch();
                                                        continue;
                                                    }
                                                    if(ch<20||ch>126) {
                                                        ch=getch();
                                                        continue;
                                                    }
                                                    if(p_passwd<=11) cout<<"*";
                                                    passwd[p_passwd++]=ch;
                                                    ch=getch();
                                                }
                                                unhigh_light();
                                                moveto(14,56);
                                                for(int i=0;i<12;i++) {
                                                    if(i<p_passwd) {
                                                        cout<<"*";
                                                    }
                                                    else cout<<" ";
                                                }
                                                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                p++;
                                            }
                                            //Again
                                            if(p==1) {
                                                moveto(15,56);
                                                SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                                high_light();
                                                for(int i=1;i<=12;i++) cout<<" ";
                                                moveto(15,56);
                                                ch=getch();
                                                while(ch!=9) {
                                                    if(ch==127) {
                                                        if(p_again!=0) {
                                                            moveto(15,p_again+55);
                                                            cout<<" ";
                                                            moveto(15,p_again+55);
                                                            p_again--;
                                                        }
                                                        ch=getch();
                                                        continue;
                                                    }
                                                    if(ch<20||ch>126) {
                                                        ch=getch();
                                                        continue;
                                                    }
                                                    if(p_again<=11) cout<<"*";
                                                    again[p_again++]=ch;
                                                    ch=getch();
                                                }
                                                unhigh_light();
                                                moveto(15,56);
                                                for(int i=0;i<12;i++) {
                                                    if(i<p_again) {
                                                        cout<<"*";
                                                    }
                                                    else cout<<" ";
                                                }
                                                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                p++;
                                            }
                                            //Modify
                                            if(p==2) {
                                                Back:
                                                hide_cursor();
                                                moveto(17,55);
                                                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                high_light();
                                                cout<<"[Modify]"<<endl;
                                                ch=getch();
                                                while (ch!=9) {
                                                    if(ch==10) {
                                                        unhigh_light();
                                                        if(strcmp(passwd,again)!=0) {
                                                            unhigh_light();
                                                            clear();
                                                            p_again=p_passwd=0;
                                                            memset(passwd,0,sizeof(passwd));
                                                            SET_FRONT_COLOR(FRONT_RED);
                                                            moveto(13,0);
                                                            cout<<"Error"<<endl;
                                                            for(int i=0;i<10;i++) {
                                                                cout<<"/";
                                                            }
                                                            cout<<endl<<"The two inputs are inconsistent"<<endl;
                                                            for(int i=0;i<10;i++) {
                                                                cout<<"/";
                                                            }
                                                            cout<<endl<<":( Please Retry"<<endl;
                                                            cout<<"Press Any Key To Continue";
                                                            SET_FRONT_COLOR(FRONT_WHITE);
                                                            ch=getch();
                                                            clear();
                                                            unhigh_light();
                                                            reset_cursor();
                                                            p_passwd=0;p_again=0;
                                                            memset(passwd,0,sizeof(passwd));
                                                            memset(again,0,sizeof(again));
                                                            cout<<"Use Tab to switch options!"<<endl;
                                                            moveto(14,48);
                                                            cout<<"Password";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                                            for(int i=1;i<=12;i++) cout<<" ";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                            moveto(15,49);
                                                            cout<<"Again  ";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                                            for(int i=1;i<=12;i++) cout<<" ";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                            moveto(17,55);
                                                            cout<<"[Modify]"<<endl;
                                                            moveto(18,57);
                                                            cout<<"[Back]"<<endl;
                                                            high_light();
                                                            p--;
                                                            goto SKIP1;
                                                        }
                                                        if(p_again==0||p_passwd==0) {
                                                            clear();
                                                            p_again=p_passwd=0;
                                                            memset(passwd,0,sizeof(passwd));
                                                            SET_FRONT_COLOR(FRONT_RED);
                                                            moveto(13,0);
                                                            cout<<"Error"<<endl;
                                                            for(int i=0;i<10;i++) {
                                                                cout<<"/";
                                                            }
                                                            cout<<endl<<"Name/Password Block"<<endl;
                                                            for(int i=0;i<10;i++) {
                                                                cout<<"/";
                                                            }
                                                            cout<<endl<<":( Please Retry"<<endl;
                                                            cout<<"Press Any Key To Continue";
                                                            SET_FRONT_COLOR(FRONT_WHITE);
                                                            ch=getch();
                                                            clear();
                                                            unhigh_light();
                                                            reset_cursor();
                                                            p_passwd=0;p_again=0;
                                                            memset(passwd,0,sizeof(passwd));
                                                            memset(again,0,sizeof(again));
                                                            cout<<"Use Tab to switch options!"<<endl;
                                                            moveto(14,48);
                                                            cout<<"Password";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                                            for(int i=1;i<=12;i++) cout<<" ";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                            moveto(15,49);
                                                            cout<<"Again  ";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                                            for(int i=1;i<=12;i++) cout<<" ";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                            moveto(17,55);
                                                            cout<<"[Modify]"<<endl;
                                                            moveto(18,57);
                                                            cout<<"[Back]"<<endl;
                                                            }
                                                        int tmp1=del_user(tmp->ID);
                                                        strcpy(tmp->password,passwd);
                                                        tmp1=tmp1&append_user(tmp);
                                                        if(tmp1==0) {
                                                            clear();
                                                            memset(passwd,0,sizeof(passwd));
                                                            SET_FRONT_COLOR(FRONT_GREEN);
                                                            moveto(13,0);
                                                            cout<<"Success"<<endl;
                                                            for(int i=0;i<10;i++) {
                                                                cout<<"/";
                                                            }
                                                            cout<<endl<<"ID:"<<ID<<"has been modified"<<endl;
                                                            for(int i=0;i<10;i++) {
                                                                cout<<"/";
                                                            }
                                                            cout<<endl<<":) Finish"<<endl;
                                                            cout<<"Press Any Key To Continue";
                                                            SET_FRONT_COLOR(FRONT_WHITE);
                                                            ch=getch();
                                                            user.ID=0;
                                                            memset(passwd,0,sizeof(passwd));
                                                            memset(id,0,sizeof(again));
                                                            p_passwd=0;p_again=0;
                                                            clear();
                                                            unhigh_light();
                                                            reset_cursor();
                                                            cout<<"Use Tab to switch options!"<<endl;
                                                            moveto(14,48);
                                                            cout<<"Password";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                                            for(int i=1;i<=12;i++) cout<<" ";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                            moveto(15,49);
                                                            cout<<"Again  ";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                                            for(int i=1;i<=12;i++) cout<<" ";
                                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                            moveto(17,55);
                                                            cout<<"[Modify]"<<endl;
                                                            moveto(18,57);
                                                            cout<<"[Back]"<<endl;
                                                            p=2;
                                                            goto Back;
                                                        }
                                                        else {
                                                            clear();
                                                            SET_FRONT_COLOR(FRONT_RED);
                                                            reset_cursor();
                                                            cout<<"Error With Document,Please check"<<endl;
                                                            exit(1);
                                                        }
                                                    }
                                                    ch=getch();
                                                }
                                                SKIP1:
                                                unhigh_light();
                                                moveto(17,55);
                                                cout<<"[Modify]"<<endl;
                                                p++;
                                            }
                                            //Back
                                            if(p==3) {
                                                moveto(18,57);
                                                SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                high_light();
                                                cout<<"[Back]"<<endl;
                                                ch=getch();
                                                while(ch!=9) {
                                                    if(ch==10) {
                                                        p_id=0;p=3;ID=0;
                                                        memset(id,0,sizeof(id));
                                                        unhigh_light();
                                                        clear();
                                                        reset_cursor();
                                                        cout<<"Use Tab to switch options!"<<endl;
                                                        moveto(13,53);
                                                        SET_FRONT_COLOR(FRONT_RED);
                                                        cout<<"Input User's ID:";
                                                        SET_FRONT_COLOR(FRONT_WHITE);
                                                        moveto(14,55);
                                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                                        for(int i=1;i<=12;i++) cout<<" ";
                                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                                        moveto(16,57);
                                                        cout<<"[Modify]";
                                                        moveto(17,58);
                                                        cout<<"[Back]";
                                                        p=1;
                                                        goto SKIP3;
                                                    }
                                                    ch=getch();
                                                }
                                                unhigh_light();
                                                moveto(18,57);
                                                cout<<"[Back]"<<endl;
                                                p=0;
                                            }
                                        }
                                    }
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(16,57);
                            cout<<"[Modify]"<<endl;
                            p++;
                        }
                        //Back
                        if(p==2) {
                            moveto(17,58);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Back]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    p_id=0;p=0;
                                    unhigh_light();
                                    memset(id,0,sizeof(id));
                                    loading();
                                    clear();
                                    hide_cursor();
                                    reset_cursor();
                                    cout<<"Use Tab to switch options!"<<endl;
                                    moveto(15,57);
                                    cout<<"[Delete]";
                                    moveto(16,57);
                                    cout<<"[Modify]";
                                    moveto(17,58);
                                    cout<<"[Back]"<<endl;
                                    goto SKIP2;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(17,58);
                            cout<<"[Back]"<<endl;
                            p=0;
                        }
                    }
                }
                ch=getch();
            }
            unhigh_light();
            moveto(16,57);
            cout<<"[Modify]"<<endl;
            p++;
        }
        //Back
        if(p==2) {
            moveto(17,58);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Back]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    unhigh_light();
                    return 0;
                }
                ch=getch();
            }
            unhigh_light();
            moveto(17,58);
            cout<<"[Back]"<<endl;
            p=0;
        }
    }
}

int Display::lbook() {
    loading();
    clear();
    hide_cursor();
    reset_cursor();
    cout<<"Use Tab to switch options!"<<endl;
    moveto(15,57);
    cout<<"[Borrow]";
    moveto(16,57);
    cout<<"[Return]";
    moveto(17,58);
    cout<<"[Back]";
    int p=0,p_id=0;
    int id[20]={0};
    while(true) {
        //Borrow
        if(p==0) {
            SKIP2:
            moveto(15,57);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Borrow]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    unhigh_light();
                    clear();
                    reset_cursor();
                    cout<<"Use Tab to switch options!"<<endl;
                    moveto(13,53);
                    SET_FRONT_COLOR(FRONT_RED);
                    cout<<"Input Book's ID:";
                    SET_FRONT_COLOR(FRONT_WHITE);
                    moveto(14,55);
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(16,57);
                    cout<<"[Borrow]";
                    moveto(17,58);
                    cout<<"[Back]";
                    while(true) {
                        if(p==0) {
                            moveto(14,55);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(14,55);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_id!=0) {
                                        moveto(14,p_id+54);
                                        cout<<" ";
                                        moveto(14,p_id+54);
                                        id[p_id-1]=0;
                                        p_id--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<'0'||ch>'9') {
                                    ch=getch();
                                    continue;
                                }
                                cout<<ch;
                                id[p_id++]=ch-'0';
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(14,55);
                            for(int i=0;i<12;i++) {
                                if(i<p_id) {
                                    cout<<id[i];
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        if(p==1) {
                            SKIP1:
                            moveto(16,57);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Borrow]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    int ID=0;
                                    unhigh_light();
                                    for(int i=0;i<p_id;i++) {
                                        ID=ID*10+id[i];
                                    }
                                    Book* tmp=seek_book_by_id(ID);
                                    if(tmp==nullptr) {
                                        clear();
                                        p_id=0;
                                        memset(id,0,sizeof(id));
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"ID:"<<ID<<" Not Exist"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        ID=0;p=1;
                                        clear();
                                        unhigh_light();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(13,53);
                                        SET_FRONT_COLOR(FRONT_RED);
                                        cout<<"Input Book's ID:";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        moveto(14,55);
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(16,57);
                                        cout<<"[Borrow]";
                                        moveto(17,58);
                                        cout<<"[Back]";
                                        goto SKIP1;
                                    }
                                    else if(tmp->status!=0) {
                                        clear();
                                        p_id=0;
                                        memset(id,0,sizeof(id));
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"ID:"<<ID<<" has been borrowed"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        ID=0;p=1;
                                        clear();
                                        unhigh_light();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(13,53);
                                        SET_FRONT_COLOR(FRONT_RED);
                                        cout<<"Input Book's ID:";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        moveto(14,55);
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(16,57);
                                        cout<<"[Borrow]";
                                        moveto(17,58);
                                        cout<<"[Back]";
                                        goto SKIP1;
                                    }
                                    else if(tmp->status==0) {
                                        int num=0;
                                        for(int i=0;i<5;i++) {
                                            if(user.Borrow[i].id==0) continue;
                                            num++;
                                        }
                                        if(num>=5) {
                                            clear();
                                             p_id=0;
                                            memset(id,0,sizeof(id));
                                            SET_FRONT_COLOR(FRONT_RED);
                                            moveto(13,0);
                                            cout<<"Error"<<endl;
                                            for(int i=0;i<10;i++) {
                                               cout<<"/";
                                            }
                                            cout<<endl<<"Too Many Books Borrowed"<<endl;
                                            for(int i=0;i<10;i++) {
                                            cout<<"/";
                                            }
                                            cout<<"Press Any Key To Continue";
                                            SET_FRONT_COLOR(FRONT_WHITE);
                                            ch=getch();
                                            ID=0;p=1;
                                            clear();
                                            unhigh_light();
                                            reset_cursor();
                                            cout<<"Use Tab to switch options!"<<endl;
                                            moveto(13,53);
                                            SET_FRONT_COLOR(FRONT_RED);
                                            cout<<"Input Book's ID:";
                                            SET_FRONT_COLOR(FRONT_WHITE);
                                            moveto(14,55);
                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                            for(int i=1;i<=12;i++) cout<<" ";
                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                            moveto(16,57);
                                            cout<<"[Borrow]";
                                            moveto(17,58);
                                            cout<<"[Back]";
                                            goto SKIP1;
                                        }
                                        else {
                                            for(int i=0;i<5;i++) {
                                                if(user.Borrow[i].id==0) {
                                                    user.Borrow[i].id=tmp->id;
                                                    tmp->status=user.ID;
                                                    break;
                                                }
                                            }
                                            user_update(&user);
                                            update_book(tmp);
                                            clear();
                                            p_id=0;
                                            memset(id,0,sizeof(id));
                                            SET_FRONT_COLOR(FRONT_GREEN);
                                            moveto(13,0);
                                            cout<<"Success"<<endl;
                                            for(int i=0;i<10;i++) {
                                                cout<<"/";
                                            }
                                            cout<<endl<<"ID:"<<ID<<" Borrowed"<<endl;
                                            for(int i=0;i<10;i++) {
                                                cout<<"/";
                                            }
                                            cout<<"Press Any Key To Continue";
                                            SET_FRONT_COLOR(FRONT_WHITE);
                                            ch=getch();
                                            ID=0;p=1;
                                            clear();
                                            unhigh_light();
                                            reset_cursor();
                                            cout<<"Use Tab to switch options!"<<endl;
                                            moveto(13,53);
                                            SET_FRONT_COLOR(FRONT_RED);
                                            cout<<"Input Book's ID:";
                                            SET_FRONT_COLOR(FRONT_WHITE);
                                            moveto(14,55);
                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                            for(int i=1;i<=12;i++) cout<<" ";
                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                            moveto(16,57);
                                            cout<<"[Borrow]";
                                            moveto(17,58);
                                            cout<<"[Back]";
                                            goto SKIP1;
                                        }
                                    }
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(16,57);
                            cout<<"[Borrow]"<<endl;
                            p++;
                        }
                        if(p==2) {
                            moveto(17,58);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Back]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    p_id=0;p=0;
                                    unhigh_light();
                                    clear();
                                    hide_cursor();
                                    reset_cursor();
                                    cout<<"Use Tab to switch options!"<<endl;
                                    moveto(15,57);
                                    cout<<"[Borrow]";
                                    moveto(16,57);
                                    cout<<"[Return]";
                                    moveto(17,58);
                                    cout<<"[Back]";
                                    goto SKIP2;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(17,58);
                            cout<<"[Back]"<<endl;
                            p=0;
                        }
                    }
                }
            }
            unhigh_light();
            moveto(15,57);
            cout<<"[Borrow]"<<endl;
            p++;
        }
        //Return
        if(p==1) {
            SKIP3:
            moveto(16,57);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Return]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    unhigh_light();
                    clear();
                    reset_cursor();
                    cout<<"Use Tab to switch options!"<<endl;
                    moveto(13,53);
                    SET_FRONT_COLOR(FRONT_RED);
                    cout<<"Input Book's ID:";
                    SET_FRONT_COLOR(FRONT_WHITE);
                    moveto(14,55);
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(16,57);
                    cout<<"[Return]";
                    moveto(17,58);
                    cout<<"[Back]";
                    while(true) {
                        if(p==0) {
                            moveto(14,55);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(14,55);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_id!=0) {
                                        moveto(14,p_id+54);
                                        cout<<" ";
                                        moveto(14,p_id+54);
                                        id[p_id-1]=0;
                                        p_id--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<'0'||ch>'9') {
                                    ch=getch();
                                    continue;
                                }
                                cout<<ch;
                                id[p_id++]=ch-'0';
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(14,55);
                            for(int i=0;i<12;i++) {
                                if(i<p_id) {
                                    cout<<id[i];
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        if(p==1) {
                            SKIP4:
                            moveto(16,57);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Return]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    int ID=0;
                                    unhigh_light();
                                    for(int i=0;i<p_id;i++) {
                                        ID=ID*10+id[i];
                                    }
                                    Book* tmp=seek_book_by_id(ID);
                                    if(tmp==nullptr) {
                                        clear();
                                        p_id=0;
                                        memset(id,0,sizeof(id));
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"ID:"<<ID<<" Not Exist"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        ID=0;p=1;
                                        clear();
                                        unhigh_light();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(13,53);
                                        SET_FRONT_COLOR(FRONT_RED);
                                        cout<<"Input Book's ID:";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        moveto(14,55);
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(16,57);
                                        cout<<"[Return]";
                                        moveto(17,58);
                                        cout<<"[Back]";
                                        goto SKIP4;
                                    }
                                    else if(tmp->status==0) {
                                        clear();
                                        p_id=0;
                                        memset(id,0,sizeof(id));
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"ID:"<<ID<<" has not been borrowed"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        ID=0;p=1;
                                        clear();
                                        unhigh_light();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(13,53);
                                        SET_FRONT_COLOR(FRONT_RED);
                                        cout<<"Input Book's ID:";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        moveto(14,55);
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(16,57);
                                        cout<<"[Return]";
                                        moveto(17,58);
                                        cout<<"[Back]";
                                        goto SKIP4;
                                    }
                                    else if(tmp->status!=0) {
                                        int num=0;
                                        for(int i=0;i<5;i++) {
                                            if(user.Borrow[i].id==tmp->status) continue;
                                            num++;
                                        }
                                        if(num>=5) {
                                            clear();
                                             p_id=0;
                                            memset(id,0,sizeof(id));
                                            SET_FRONT_COLOR(FRONT_RED);
                                            moveto(13,0);
                                            cout<<"Error"<<endl;
                                            for(int i=0;i<10;i++) {
                                               cout<<"/";
                                            }
                                            cout<<endl<<"You Have Not Borrowed This Book"<<endl;
                                            for(int i=0;i<10;i++) {
                                            cout<<"/";
                                            }
                                            cout<<"Press Any Key To Continue";
                                            SET_FRONT_COLOR(FRONT_WHITE);
                                            ch=getch();
                                            ID=0;p=1;
                                            clear();
                                            unhigh_light();
                                            reset_cursor();
                                            cout<<"Use Tab to switch options!"<<endl;
                                            moveto(13,53);
                                            SET_FRONT_COLOR(FRONT_RED);
                                            cout<<"Input Book's ID:";
                                            SET_FRONT_COLOR(FRONT_WHITE);
                                            moveto(14,55);
                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                            for(int i=1;i<=12;i++) cout<<" ";
                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                            moveto(16,57);
                                            cout<<"[Return]";
                                            moveto(17,58);
                                            cout<<"[Back]";
                                            goto SKIP4;
                                        }
                                        else {
                                            for(int i=0;i<5;i++) {
                                                if(user.Borrow[i].id==tmp->id) {
                                                    user.Borrow[i].id=0;
                                                    tmp->status=0;
                                                    break;
                                                }
                                            }
                                            user_update(&user);
                                            update_book(tmp);
                                            clear();
                                            p_id=0;
                                            memset(id,0,sizeof(id));
                                            SET_FRONT_COLOR(FRONT_GREEN);
                                            moveto(13,0);
                                            cout<<"Success"<<endl;
                                            for(int i=0;i<10;i++) {
                                                cout<<"/";
                                            }
                                            cout<<endl<<"ID:"<<ID<<" Returned"<<endl;
                                            for(int i=0;i<10;i++) {
                                                cout<<"/";
                                            }
                                            cout<<"Press Any Key To Continue";
                                            SET_FRONT_COLOR(FRONT_WHITE);
                                            ch=getch();
                                            ID=0;p=1;
                                            clear();
                                            unhigh_light();
                                            reset_cursor();
                                            cout<<"Use Tab to switch options!"<<endl;
                                            moveto(13,53);
                                            SET_FRONT_COLOR(FRONT_RED);
                                            cout<<"Input Book's ID:";
                                            SET_FRONT_COLOR(FRONT_WHITE);
                                            moveto(14,55);
                                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                            for(int i=1;i<=12;i++) cout<<" ";
                                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                            moveto(16,57);
                                            cout<<"[Return]";
                                            moveto(17,58);
                                            cout<<"[Back]";
                                            goto SKIP4;
                                        }
                                    }
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(16,57);
                            cout<<"[Borrow]"<<endl;
                            p++;
                        }
                        if(p==2) {
                            moveto(17,58);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Back]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    p_id=0;p=0;
                                    unhigh_light();
                                    clear();
                                    hide_cursor();
                                    reset_cursor();
                                    cout<<"Use Tab to switch options!"<<endl;
                                    moveto(15,57);
                                    cout<<"[Borrow]";
                                    moveto(16,57);
                                    cout<<"[Return]";
                                    moveto(17,58);
                                    cout<<"[Back]";
                                    goto SKIP3;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(17,58);
                            cout<<"[Back]"<<endl;
                            p=0;
                        }
                    }
                }
            }
            unhigh_light();
            moveto(16,57);
            cout<<"[Return]"<<endl;
            p++;
        }
        //Back
        if(p==2) {
            moveto(17,58);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Back]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    unhigh_light();
                    return 0;
                }
                ch=getch();
            }
            unhigh_light();
            moveto(17,58);
            cout<<"[Back]"<<endl;
            p=0;
        }
    }
}

int Display::modify() {
    loading();
    clear();
    hide_cursor();
    reset_cursor();
    cout<<"Use Tab to switch options!"<<endl;
    moveto(15,57);
    cout<<"[Name]";
    moveto(16,57);
    cout<<"[Password]";
    moveto(17,57);
    cout<<"[Back]";
    int p=0,p_name=0,p_passwd=0,p_again=0;
    char name[52]={0},passwd[52]={0},again[52]={0};
    while(true) {
        //Name
        if(p==0) {
            SKIP1:
            moveto(15,57);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Name]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    clear();
                    unhigh_light();
                    moveto(15,50);
                    cout<<"Name  ";
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(17,56);
                    cout<<"[Change]"<<endl;
                    moveto(18,57);
                    cout<<"[Back]"<<endl;
                    while(true) {
                        //Name
                        if(p==0) {
                            moveto(15,56);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(15,56);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_name!=0) {
                                        moveto(15,p_name+55);
                                        cout<<" ";
                                        moveto(15,p_name+55);
                                        p_name--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<20||ch>126) {
                                    ch=getch();
                                    continue;
                                }
                                cout<<ch;
                                name[p_name++]=ch;
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(15,56);
                            for(int i=0;i<12;i++) {
                                if(i<p_name) {
                                    cout<<name[i];
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        //Change
                        if(p==1) {
                            SKIP2:
                            moveto(17,56);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Change]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    unhigh_light();
                                    if(p_name==0) {
                                        p=0;
                                        clear();
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"Name Block"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<":( Please Retry"<<endl;
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        clear();
                                        hide_cursor();
                                        reset_cursor();
                                        moveto(15,50);
                                        cout<<"Name  ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(17,56);
                                        cout<<"[Change]"<<endl;
                                        moveto(18,57);
                                        cout<<"[Back]"<<endl;
                                        goto SKIP2;
                                    }
                                    strcpy(this->user.name,name);
                                    del_user(this->user.ID);
                                    append_user(&this->user);
                                    clear();
                                    p=p_name=0;
                                    memset(name,0,sizeof(name));
                                    SET_FRONT_COLOR(FRONT_GREEN);
                                    moveto(13,0);
                                    cout<<"Success"<<endl;
                                    for(int i=0;i<10;i++) {
                                        cout<<"/";
                                    }
                                    cout<<endl<<"Your name is "<<user.name<<endl;
                                    for(int i=0;i<10;i++) {
                                        cout<<"/";
                                    }
                                    cout<<endl<<":) Finish"<<endl;
                                    cout<<"Press Any Key To Continue";
                                    SET_FRONT_COLOR(FRONT_WHITE);
                                    ch=getch();
                                    clear();
                                    hide_cursor();
                                    reset_cursor();
                                    moveto(15,50);
                                    cout<<"Name  ";
                                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                    for(int i=1;i<=12;i++) cout<<" ";
                                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                    moveto(17,56);
                                    cout<<"[Change]"<<endl;
                                    moveto(18,57);
                                    cout<<"[Back]"<<endl;
                                    goto SKIP2;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(17,56);
                            cout<<"[Change]"<<endl;
                            p++;
                        }
                        //Back
                        if(p==2) {
                            moveto(18,57);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Back]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    clear();
                                    unhigh_light();
                                    hide_cursor();
                                    reset_cursor();
                                    cout<<"Use Tab to switch options!"<<endl;
                                    moveto(15,57);
                                    cout<<"[Name]";
                                    moveto(16,57);
                                    cout<<"[Password]";
                                    moveto(17,57);
                                    cout<<"[Back]";
                                    p=p_name=0;
                                    memset(name,0,sizeof(name));
                                    goto SKIP1;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(18,57);
                            cout<<"[Back]"<<endl;
                            p=0;
                        }
                    }
                }
                ch=getch();
            }
            unhigh_light();
            moveto(15,57);
            cout<<"[Name]"<<endl;
            p++;
        }
        //Passwd
        if(p==1) {
            SKIP4:
            moveto(16,57);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Password]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    p=0;
                    clear();
                    unhigh_light();
                    reset_cursor();
                    cout<<"Use Tab to switch options!"<<endl;
                    moveto(14,48);
                    cout<<"Password";
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(15,49);
                    cout<<"Again  ";
                    SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                    for(int i=1;i<=12;i++) cout<<" ";
                    SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                    moveto(17,55);
                    cout<<"[Modify]"<<endl;
                    moveto(18,57);
                    cout<<"[Back]"<<endl;
                    while(true) {
                        //Passwd
                        if(p==0) {
                            moveto(14,56);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(14,56);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_passwd!=0) {
                                        moveto(14,p_passwd+55);
                                        cout<<" ";
                                        moveto(14,p_passwd+55);
                                        p_passwd--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<20||ch>126) {
                                    ch=getch();
                                    continue;
                                }
                                if(p_passwd<=11) cout<<"*";
                                passwd[p_passwd++]=ch;
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(14,56);
                            for(int i=0;i<12;i++) {
                                if(i<p_passwd) {
                                    cout<<"*";
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        //Again
                        if(p==1) {
                            moveto(15,56);
                            SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                            high_light();
                            for(int i=1;i<=12;i++) cout<<" ";
                            moveto(15,56);
                            ch=getch();
                            while(ch!=9) {
                                if(ch==127) {
                                    if(p_again!=0) {
                                        moveto(15,p_again+55);
                                        cout<<" ";
                                        moveto(15,p_again+55);
                                        p_again--;
                                    }
                                    ch=getch();
                                    continue;
                                }
                                if(ch<20||ch>126) {
                                    ch=getch();
                                    continue;
                                }
                                if(p_again<=11) cout<<"*";
                                again[p_again++]=ch;
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(15,56);
                            for(int i=0;i<12;i++) {
                                if(i<p_again) {
                                    cout<<"*";
                                }
                                else cout<<" ";
                            }
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            p++;
                        }
                        //Modify
                        if(p==2) {
                            Back:
                            hide_cursor();
                            moveto(17,55);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Modify]"<<endl;
                            ch=getch();
                            while (ch!=9) {
                                if(ch==10) {
                                    unhigh_light();
                                    if(strcmp(passwd,again)!=0) {
                                        unhigh_light();
                                        clear();
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"The two inputs are inconsistent"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<":( Please Retry"<<endl;
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        clear();
                                        unhigh_light();
                                        reset_cursor();
                                        p_passwd=0;p_again=0;
                                        memset(passwd,0,sizeof(passwd));
                                        memset(again,0,sizeof(again));
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(14,48);
                                        cout<<"Password";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(15,49);
                                        cout<<"Again  ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(17,55);
                                        cout<<"[Modify]"<<endl;
                                        moveto(18,57);
                                        cout<<"[Back]"<<endl;
                                        // high_light();
                                        p=0;
                                        goto Back;;
                                    }
                                    if(p_again==0||p_passwd==0) {
                                        clear();
                                        SET_FRONT_COLOR(FRONT_RED);
                                        moveto(13,0);
                                        cout<<"Error"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"Name/Password Block"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<":( Please Retry"<<endl;
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        clear();
                                        unhigh_light();
                                        reset_cursor();
                                        p_passwd=p_again=0;
                                        memset(passwd,0,sizeof(passwd));
                                        memset(again,0,sizeof(again));
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(14,48);
                                        cout<<"Password";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(15,49);
                                        cout<<"Again  ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(17,55);
                                        cout<<"[Modify]"<<endl;
                                        moveto(18,57);
                                        cout<<"[Back]"<<endl;
                                        p=0;
                                        goto Back;
                                    }
                                    int tmp1=del_user(user.ID);
                                    strcpy(user.password,passwd);
                                    tmp1=tmp1&append_user(&user);
                                    if(tmp1==0) {
                                        clear();
                                        memset(passwd,0,sizeof(passwd));
                                        SET_FRONT_COLOR(FRONT_GREEN);
                                        moveto(13,0);
                                        cout<<"Success"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<"ID:"<<user.ID<<"has been modified"<<endl;
                                        for(int i=0;i<10;i++) {
                                            cout<<"/";
                                        }
                                        cout<<endl<<":) Finish"<<endl;
                                        cout<<"Press Any Key To Continue";
                                        SET_FRONT_COLOR(FRONT_WHITE);
                                        ch=getch();
                                        memset(passwd,0,sizeof(passwd));
                                        memset(again,0,sizeof(again));
                                        p_passwd=0;p_again=0;
                                        clear();
                                        unhigh_light();
                                        reset_cursor();
                                        cout<<"Use Tab to switch options!"<<endl;
                                        moveto(14,48);
                                        cout<<"Password";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(15,49);
                                        cout<<"Again  ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_YELLOW);
                                        for(int i=1;i<=12;i++) cout<<" ";
                                        SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                                        moveto(17,55);
                                        cout<<"[Modify]"<<endl;
                                        moveto(18,57);
                                        cout<<"[Back]"<<endl;
                                        p=2;
                                        goto Back;
                                    }
                                    else {
                                        clear();
                                        SET_FRONT_COLOR(FRONT_RED);
                                        reset_cursor();
                                        cout<<"Error With Document,Please check"<<endl;
                                        exit(1);
                                    }
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(17,55);
                            cout<<"[Modify]"<<endl;
                            p++;
                        }
                        //Back
                        if(p==3) {
                            moveto(18,57);
                            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
                            high_light();
                            cout<<"[Back]"<<endl;
                            ch=getch();
                            while(ch!=9) {
                                if(ch==10) {
                                    p_passwd=p_again=0;
                                    memset(passwd,0,sizeof(passwd));
                                    memset(again,0,sizeof(again));
                                    unhigh_light();
                                    clear();
                                    hide_cursor();
                                    reset_cursor();
                                    cout<<"Use Tab to switch options!"<<endl;
                                    moveto(15,57);
                                    cout<<"[Name]";
                                    moveto(16,57);
                                    cout<<"[Password]";
                                    moveto(17,57);
                                    cout<<"[Back]";
                                    p=1;
                                    goto SKIP4;
                                }
                                ch=getch();
                            }
                            unhigh_light();
                            moveto(18,57);
                            cout<<"[Back]"<<endl;
                            p=0;
                        }
                    }
                }
                ch=getch();
            }
            unhigh_light();
            moveto(16,57);
            cout<<"[Password]"<<endl;
            p++;
        }
        //Back
        if(p==2) {
            moveto(17,57);
            SET_BACKGROUND_COLOR(BACKGROUND_BLACK);
            high_light();
            cout<<"[Back]"<<endl;
            char ch=getch();
            while(ch!=9) {
                if(ch==10) {
                    unhigh_light();
                    return 0;
                }
                ch=getch();
            }
            unhigh_light();
            moveto(17,57);
            cout<<"[Back]"<<endl;
            p=0;
        }
    }
}

void Display::loading() {
    char screen[20][122]={
        {"                    ||                  ||                                        ||                   ||            \n" },
        {"                    ||                  |||                     |||||             ||     |             ||            \n" },
        {"                    ||                  ||             |||||||||||||||     ||||||||||||||||            ||             \n"},
        {"                |   ||                  ||             |||||||||            ||||||||||||||||    |      ||      |      \n"},
        {"                ||  || |||             ||                     ||                 ||     |       ||||||||||||||||||   \n"},
        {"               ||   ||   |||           ||       ||            ||     |      ||||||||||||||      |||||||||||||||||     \n"},
        {"               ||   ||    |||   |||||||||||||||||||  ||||||||||||||||||      |||||||||||||      ||     ||      ||      \n"},
        {"              ||    ||     |||  |||||||||||||||||||   ||||||||||||||||||         ||        |    ||     ||      ||      \n"},
        {"              ||    ||   |  ||        ||    ||                ||          |||||||||||||||||||   ||     ||      ||      \n"},
        {"             ||     ||   ||           ||    ||               |||          |||||||||||||||||||   ||     ||      ||      \n"},
        {"             |      ||  |||          ||     ||               ||||               ||||||||||||    |||||||||||||||||      \n"},
        {"            ||      || |||           ||    ||                || |              ||||||||||||||   |||||||||||||||||      \n"},
        {"            |       |||||           |||    ||               ||  ||             |||     ||       ||     ||      ||      \n"},
        {"                     |||              ||| ||               |||   ||           || ||    ||       |      ||              \n"},
        {"                    |||                  ||||             |||    |||         ||   ||   ||              ||              \n"},
        {"                  |||                   |||||||          |||      ||||       |    ||   ||              ||              \n"},
        {"                ||||                  |||    |||       |||         |||||    ||      |  ||              ||              \n"},
        {"              ||||                  |||       |||     |||            ||   ||        |||||              ||              \n"},
        {"           ||||                 |||||          ||    |                    |           ||               ||              \n"},
        {"                                |                                                                                      \n"} };
    clear();
    reset_cursor();
    moveto(5,0);
    hide_cursor();
    for(int i=0;i<20;i++) {
        const int color=rand()%10+31;
        printf("\033[%dm",color);
        cout<<screen[i];
        // usleep(1E5);
    }
    SET_FRONT_COLOR(FRONT_WHITE);
}