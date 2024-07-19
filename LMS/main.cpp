#include "src/Display.h"

int main() {
    Display display;
    START:
    display.LogRes();
    while(true) {
        int pagecode=display.mainpage();
        switch (pagecode) {
            case 0:
                display.LogRes();
                break;
            //Book Check
            case 1:
                display.check();
                break;
            //Book Management
            case 2:
                display.manage();
                break;
            //Search
            case 3:
                display.search();
                break;
            //User Management
            case 4:
                display.usrman();
                break;
            //Mine
            case 5:
                display.modify();
                break;
            default:
                display.lbook();
                break;
        }
    }
}