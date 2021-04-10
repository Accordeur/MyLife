//
// Created by Zelonge on 2021/4/10.
//

#ifndef MYLIFE_TASK_H
#define MYLIFE_TASK_H
#include "database/tables.h"
#include "database/database.h"

class Task: public Crud {
public:
    int32_t create(DataBase::Storage& storage) override final;
    int32_t update(DataBase::Storage& storage) override final;
    int32_t remove(DataBase::Storage& storage) override final;
    int32_t query(DataBase::Storage& storage) override final;

private:
    TaskTable taskTable;
};


#endif //MYLIFE_TASK_H
