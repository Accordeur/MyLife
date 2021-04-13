//
// Created by Zelonge on 2021/4/10.
//

#include "Task.h"
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace sqlite_orm;

Task::Task(DataBase &dataBase) : Crud(dataBase), taskTable({}){
    taskTable.task_id = ID_UNINIT;
    taskTable.inherit_date = true;
    taskTable.urgency = static_cast<int32_t>(Urgency::Normal);
    taskTable.importance = static_cast<int32_t>(Importance::Normal);
    taskTable.effort = static_cast<int32_t>(Effort::Normal);
    taskTable.project_status = static_cast<int32_t>(ProjectStatus::InProgress);
    //uuid
    taskTable.note_id = ID_UNINIT;
    taskTable.reminder_id = ID_UNINIT;
    taskTable.recurrence_id = ID_UNINIT;
    taskTable.flag_id = ID_UNINIT;
    taskTable.parent_id = ID_ROOT;
    taskTable.uuid = boost::uuids::to_string(boost::uuids::random_generator()());
}

GTD_RESULT Task::create() {
    if(taskTable.task_id != ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    taskTable.task_id = datebase.sql().insert(taskTable);
    return GTD_OK;
}

GTD_RESULT Task::update() {
    if(taskTable.task_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }

    datebase.sql().update(taskTable);
    return GTD_OK;
}

GTD_RESULT Task::remove() {
    if(taskTable.task_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    datebase.sql().remove_all<TaskTable>(where(c(&TaskTable::task_id) == taskTable.task_id));
    taskTable.task_id = ID_UNINIT;
    return GTD_OK;
}

GTD_RESULT Task::query() {
    if(taskTable.task_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    auto all = datebase.sql().get_all<TaskTable>(where(c(&TaskTable::task_id) == taskTable.task_id));
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

bool Task::is_generated_by_recurrence() const {
    return static_cast<bool>(taskTable.generated_by_recurrence);
}

void Task::generated_by_recurrence(bool mark) {
    taskTable.generated_by_recurrence = mark;
}

bool Task::is_project() const {
    return static_cast<bool>(taskTable.project);
}

void Task::set_project_flag(bool mark) {
    taskTable.project = mark;
}

Task::Effort Task::get_effort() const {
    return static_cast<Effort>(taskTable.effort);
}

void Task::set_effort(Task::Effort effort) {
    taskTable.effort= static_cast<int32_t>(effort);
}

Task::Importance Task::get_importance() const {
    return static_cast<Importance>(taskTable.importance);
}

void Task::set_importance(Task::Importance importance) {
    taskTable.importance = static_cast<int32_t>(importance);
}

Task::Urgency Task::get_Urgent() const {
    return static_cast<Urgency>(taskTable.urgency);
}

void Task::set_urgent(Task::Urgency urgent) {
    taskTable.urgency = static_cast<int32_t>(urgent);
}

Task::ProjectStatus Task::get_project_status() const {
    return static_cast<ProjectStatus>(taskTable.project_status);
}

void Task::set_project_status(Task::ProjectStatus status) {
    taskTable.project_status = static_cast<int32_t>(status);
}

int32_t Task::get_review_rate() const {
    return taskTable.review_every;
}

void Task::set_review_rate(int32_t every) {
    taskTable.review_every = every;
}

Task::ReviewType Task::get_review_recurrence_type() const {
    return static_cast<ReviewType>(taskTable.review_recurrence_type);
}

void Task::set_review_recurrence_type(Task::ReviewType type) {
    taskTable.review_recurrence_type = static_cast<int32_t>(type);
}

std::tuple<std::chrono::minutes, std::chrono::minutes> Task::get_estimate_time() const {
    return std::tuple<std::chrono::minutes, std::chrono::minutes>(std::chrono::minutes(taskTable.estimate_min), std::chrono::minutes(taskTable.estimate_max));
}

void Task::set_estimate_time(std::chrono::minutes min, std::chrono::minutes max) {
    taskTable.estimate_min = min.count();
    taskTable.estimate_max = max.count();
}

boost::uuids::uuid Task::get_uuid() const {
    return boost::uuids::string_generator()(taskTable.uuid);
}

std::string Task::get_note() const {
    return std::string();
}

void Task::set_note(std::string) {

}

bool Task::is_inherit_date() const {
    return taskTable.inherit_date;
}

void Task::set_inherit_date(bool mark) {
    taskTable.inherit_date = mark;
}

