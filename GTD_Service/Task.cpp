//
// Created by Zelonge on 2021/4/10.
//

#include "Task.h"
#include "error_type.h"

using namespace sqlite_orm;

GTD_RESULT Task::create(DataBase::Storage &storage) {
    if(taskTable.task_id != ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    taskTable.task_id = storage.insert(taskTable);
    return GTD_OK;
}

GTD_RESULT Task::update(DataBase::Storage &storage) {
    if(taskTable.task_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }

    storage.update(taskTable);
    return GTD_OK;
}

GTD_RESULT Task::remove(DataBase::Storage &storage) {
    if(taskTable.task_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    storage.remove_all<TaskTable>(where(c(&TaskTable::task_id) == taskTable.task_id));
    return GTD_OK;
}

GTD_RESULT Task::query(DataBase::Storage &storage) {
    if(taskTable.task_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    auto all = storage.get_all<TaskTable>(where(c(&TaskTable::task_id) == taskTable.task_id));
    if(all.empty()) {
        return GTD_PARA_INVALID;
    }
    taskTable = all[0];
    return GTD_OK;
}

std::string Task::get_title() const {
    return taskTable.title;
}

GTD_RESULT Task::set_title(const std::string &title) {
    taskTable.title = title;
    return GTD_OK;
}

bool Task::is_starred() const {
    return static_cast<bool>(taskTable.starred);
}

void Task::starred() {
    taskTable.starred = 1;
}

void Task::unstarred() {
    taskTable.starred = 0;
}

bool Task::is_hide_in_todo() const {
    return static_cast<bool>(taskTable.hide_in_todo);
}

void Task::hide_in_todo() {
    taskTable.hide_in_todo = 1;
}

void Task::show_in_todo() {
    taskTable.hide_in_todo = 0;
}

bool Task::is_complete_in_order() const {
    return static_cast<bool>(taskTable.complete_in_order);
}

void Task::complete_in_order(bool order) {
    taskTable.complete_in_order = order;
}

bool Task::is_folder() const {
    return taskTable.folder;
}

void Task::set_folder_flag(bool mark) {
    taskTable.folder = mark;
}

