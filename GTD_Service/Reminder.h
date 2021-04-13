//
// Created by Zelonge on 2021/4/13.
//

#ifndef MYLIFE_REMINDER_H
#define MYLIFE_REMINDER_H
#include "database/database.h"
#include "database/tables.h"

class Reminder: public Crud {
public:

private:
    ReminderTable reminder;
};


#endif //MYLIFE_REMINDER_H
