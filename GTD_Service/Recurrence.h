//
// Created by Zelonge on 2021/4/13.
//

#ifndef MYLIFE_RECURRENCE_H
#define MYLIFE_RECURRENCE_H
#include "database/database.h"
#include "database/tables.h"

class Recurrence: public Crud {
public:
    Recurrence() = delete;
    explicit Recurrence(DataBase& dataBase);
    Recurrence(const Recurrence&) = default;
    Recurrence& operator=(const Recurrence&) = default;
    Recurrence(Recurrence&&) = default;
    Recurrence& operator=(Recurrence&&) = default;
protected:
    GTD_RESULT create() override final;
    GTD_RESULT update() override final;
    GTD_RESULT remove() override final;
    GTD_RESULT query() override final;
private:
    RecurrenceTable recurrenceTable;
};


#endif //MYLIFE_RECURRENCE_H
