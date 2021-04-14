//
// Created by Zelonge on 2021/4/13.
//

#include "Recurrence.h"

GTD_RESULT Recurrence::create() {
    return GTD_OK;
}

GTD_RESULT Recurrence::update() {
    return GTD_OK;
}

GTD_RESULT Recurrence::remove() {
    return GTD_OK;
}

GTD_RESULT Recurrence::query() {
    return GTD_OK;
}

Recurrence::Recurrence(DataBase &dataBase) : Crud(dataBase), recurrenceTable({}) {
    recurrenceTable.recurrence_id = ID_UNINIT;
}
