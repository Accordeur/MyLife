//
// Created by Zelonge on 2021/4/13.
//

#include "Reminder.h"

Reminder::Reminder(DataBase &dataBase) : Crud(dataBase), reminderTable({}) {
    reminderTable.reminder_id = ID_UNINIT;

}

GTD_RESULT Reminder::create() {
    return GTD_OK;
}

GTD_RESULT Reminder::update() {
    return GTD_OK;
}

GTD_RESULT Reminder::remove() {
    return GTD_OK;
}

GTD_RESULT Reminder::query() {
    return GTD_OK;
}

