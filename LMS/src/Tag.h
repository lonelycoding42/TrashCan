#ifndef LMS_TAG_H
#define LMS_TAG_H

#define TAG_FILE_NAME "./data/Tag"

//干脆写成了类
class Tags{
public:
    Tags();

    ~Tags();

    //将tag记录在Tag文件中
    int Write_tag();

    //添加一个tag, 如果tag已经存在，则添加失败并返回1，成功返回0
    int Update_tag(char Tag[]);

    //调试用函数
    int Show_tags();

    //获取tag数量
    int get_tag_num();

    //获取对应下标的tag,index为tag对应下标
    char* seek_tag(int index);

private:
    int tag_num;
    char tag_list[][52];

};

////加载tag的函数,返回一个二维数组的指针
//char** Load_tag();
//
////填写tag的函数,成功返回0
//int write_tag(char **list);
//
////添加tag的函数
//int append_tag(char** list, char* add_tag);
//
//int get_tag_num(char** list );

#endif //LMS_TAG_H
