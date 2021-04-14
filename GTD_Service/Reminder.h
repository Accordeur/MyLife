//
// Created by Zelonge on 2021/4/13.
//

#ifndef MYLIFE_REMINDER_H
#define MYLIFE_REMINDER_H
#include "database/database.h"
#include "database/tables.h"

class Reminder: public Crud {
public:
    Reminder() = delete;
    explicit Reminder(DataBase& dataBase);
    Reminder(const Reminder&) = default;
    Reminder& operator=(const Reminder&) = default;
    Reminder(Reminder&&) = default;
    Reminder& operator=(Reminder&&) = default;
protected:
    GTD_RESULT create() override final;
    GTD_RESULT update() override final;
    GTD_RESULT remove() override final;
    GTD_RESULT query() override final;
private:
    ReminderTable reminderTable;
};


#endif //MYLIFE_REMINDER_H
