//
// Created by Zelonge on 2021/4/10.
//

#include "Task.h"

int32_t Task::create(DataBase::Storage &storage) {
    taskTable.task_id = storage.insert(taskTable);
    return 0;
}

int32_t Task::update(DataBase::Storage &storage) {
    return 0;
}

int32_t Task::remove(DataBase::Storage &storage) {
    return 0;
}

int32_t Task::query(DataBase::Storage &storage) {
    return 0;
}
