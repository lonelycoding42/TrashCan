//
// Created by 29396 on 24-7-13.
//

#include "Tag.h"
#include<stdio.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

//char** Load_tag(){
//    char** Tag_list = new char* [100];
//    char this_tag[50] = {0};
//    FILE *fp = fopen(TAG_FILE_NAME, "r");
//    int tag_num = 0;
//    fscanf(fp, "%d\n", &tag_num);
//
//    for (int i = 0; i < tag_num; ++i) {
//        fgets (this_tag, 60, fp);
//        printf("%s\n", this_tag);
//    }
//    fclose(fp);
//    Tag_list[tag_num] = nullptr;
//
//    return Tag_list;
//}
//
//int write_tag(char **list){
//    FILE *fp = fopen(TAG_FILE_NAME, "wt");
//    int tag_num = get_tag_num(list);
//    fprintf(fp, "%d\n", tag_num);
//    printf("%d\n", tag_num);
//
//    for (int i = 0; i < tag_num; i++){
//        fputs(list[i], fp);
//        printf("%s\n", list[i]);
//    }
//
//    return 0;
//}
//
//int append_tag(char** list, char* add_tag){
//    for (int i = 0;;i++){
//        if (list[i]!= nullptr) continue;
//        strcmp(list[i], add_tag);
//        list[i+1] = nullptr;
//        break;
//    }
//
//    return 0;
//}
//
//int get_tag_num(char** list ){
//    int tag_num = 0;
//    while (list[tag_num]!= nullptr) tag_num++;
//    return tag_num;
//}

Tags::Tags() {
    FILE *fp = fopen(TAG_FILE_NAME, "r");
    tag_num = 0;
    fscanf(fp, "%d\n", &tag_num);

    for (int i = 0; i < tag_num; ++i)
        fgets (tag_list[i], 60, fp);
    fclose(fp);
}

Tags::~Tags() {}

int Tags::Write_tag() {
    FILE *fp = fopen(TAG_FILE_NAME, "wt");
    fprintf(fp, "%d\n", tag_num);

    for (int i = 0; i < tag_num; i++)
        fputs(tag_list[i], fp);
    return 0;
}

int Tags::Update_tag(char Tag[]) {
    for (int i = 0; i < tag_num; i++)
        if (strcmp(tag_list[i], Tag) == 0) return 1;

    strcpy(tag_list[tag_num++], Tag);
    return 0;
}

int Tags::Show_tags(){
    for (int i = 0; i < tag_num; i++)
        printf("%s\n", tag_list[i]);
    return 0;
}

int Tags::get_tag_num(){
    return tag_num;
}

char* Tags::seek_tag(int index){
    return tag_list[index];
}