#ifndef GIN_INDEX_H
#define GIN_INDEX_H

#include <QVector>

struct gin_index{
private:
    QVector<int> list;
public:
    int get();
    void setId(int num);
    void remove(int num);
    void restore(int old_num, int new_num);
};


#endif // GIN_INDEX_H
