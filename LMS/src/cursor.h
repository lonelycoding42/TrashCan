//
// Created by lilon on 24-7-12.
//

#ifndef CURSOR_H
#define CURSOR_H
#include <cstdio>

//清屏
inline void clear() {
    printf("\033[2J");
}

//光标上移
inline void moveup(const int x) {
    printf("\033[%dA", x);
}

//光标下移
inline void movedown(const int x) {
    printf("\033[%dB", x);
}

//光标左移
inline void moveleft(int y) {
    // y+=21;
    printf("\033[%dD", y);
}

//光标右移
inline void moveright(int y) {
    // y+=21;
    printf("\033[%dC", y);
}

//光标移动至指定位置
inline void moveto(const int x, int y) {
    // y+=21;
    printf("\033[%d;%dH", x, y);
}

//重置光标
inline void reset_cursor() {
    printf("\033[H");
}

//隐藏光标
inline void hide_cursor() {
    printf("\033[?25l");
}

//显示光标
inline void show_cursor() {
    printf("\033[?25h");
}

//反色
inline void high_light() {
    printf("\033[7m");
}

//关闭反色
inline void unhigh_light() {
    printf("\033[27m");
}

//getch函数
inline char getch() {
    system("stty -echo");
    system("stty -icanon");
    const char ch=getchar();
    system("stty echo");
    system("stty icanon");
    return ch;
}

//设置颜色
#define SET_FRONT_COLOR(color) printf("\033[%dm",(color))
#define SET_BACKGROUND_COLOR(color) printf("\033[%dm",(color))

//前景色
#define FRONT_BLACK 30
#define FRONT_RED 31
#define FRONT_GREEN 32
#define FRONT_YELLOW 33
#define FRONT_BLUE 34
#define FRONT_PURPLE 35
#define FRONT_DEEP_GREEN 36
#define FRONT_WHITE 37

//背景色
#define BACKGROUND_BLACK 40
#define BACKGROUND_RED 41
#define BACKGROUND_GREEN 42
#define BACKGROUND_YELLOW 43
#define BACKGROUND_BLUE 44
#define BACKGROUND_PURPLE 45
#define BACKGROUND_DEEP_GREEN 46
#define BACKGROUND_WHITE 47

#endif //CURSOR_H
