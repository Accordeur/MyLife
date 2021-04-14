//
// Created by Zelonge on 2021/4/13.
//

#ifndef MYLIFE_FLAG_H
#define MYLIFE_FLAG_H
#include "database/database.h"
#include "database/tables.h"

class Flag: public Crud {
public:
    Flag() = delete;
    explicit Flag(DataBase& dataBase);
    Flag(const Flag&) = default;
    Flag& operator=(const Flag&) = default;
    Flag(Flag&&) = default;
    Flag& operator=(Flag&&) = default;

protected:
    GTD_RESULT create() override final;
    GTD_RESULT update() override final;
    GTD_RESULT remove() override final;
    GTD_RESULT query() override final;
private:
    FlagTable flagTable;
};


#endif //MYLIFE_FLAG_H
