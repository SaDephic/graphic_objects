#include "passcene.h"

QByteArray passcene::emptyMap(QSize size){
    QByteArray map;
    QPixmap pix(size);
    pix.fill();
    QBuffer buffer(&map);
    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer, "PNG");
    buffer.close();
    return map;
}
