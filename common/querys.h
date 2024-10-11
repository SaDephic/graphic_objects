#ifndef QUERYS_H
#define QUERYS_H

#include <QString>

struct querys{
    querys(){}
    QString a_region = "SELECT * FROM public.region;";
    QString a_crosses = "SELECT t1.id,t1.describ,t1.subarea,t1.region,t1.area,TO_CHAR(t2.ledit,'hh24:mi:ss dd.mm.yyyy') as ledit "
                        "FROM public.cross as t1 LEFT JOIN public.svg as t2 "
                        "ON t1.id=t2.id AND t1.region=t2.region AND t1.area=t2.area "
                        "WHERE t1.region=%1 AND t1.area=%2;";
    QString get_cross = "SELECT bottom, state, picture, extend, "
                       "TO_CHAR(ledit,'hh24:mi:ss dd.mm.yyyy') as ledit "
                       "FROM public.svg "
                       "WHERE region=%1 and area=%2 and id=%3;";
    QString send_cross = "UPDATE public.svg "
                        "SET bottom=:bottom, picture=:picture, extend=:extend, state=:state, ledit=NOW() "
                        "WHERE region=%1 AND area=%2 AND id=%3;";
};

#endif // QUERYS_H
