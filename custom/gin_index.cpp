#include "gin_index.h"

int gin_index::get(){
    int num = 0;
    while(list.contains(num) || num == 0){
        num = rand()%1000;
    }
    list.push_back(num);
    return num;
}

void gin_index::setId(int num){
    list.push_back(num);
}

void gin_index::remove(int num){
    list.removeOne(num);
}

void gin_index::restore(int old_num, int new_num){
    list.removeOne(old_num);
    list.push_back(new_num);
}
