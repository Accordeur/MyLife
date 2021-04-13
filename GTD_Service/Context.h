//
// Created by Zelonge on 2021/4/13.
//

#ifndef MYLIFE_CONTEXT_H
#define MYLIFE_CONTEXT_H
#include "database/database.h"
#include "database/tables.h"

class Context: public Crud {
public:
private:
    ContextTable contextTable;
};


#endif //MYLIFE_CONTEXT_H
