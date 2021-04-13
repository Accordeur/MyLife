//
// Created by Zelonge on 2021/4/9.
//

#ifndef MYLIFE_DATABASE_H
#define MYLIFE_DATABASE_H
#include <sqlite_orm/sqlite_orm.h>
#include <filesystem>
#include <type_traits>
#include "tables.h"
#include "../error_type.h"

class Crud;

inline auto initDB(const std::filesystem::path& path) {
    return sqlite_orm::make_storage(path.string(),
                                    sqlite_orm::make_table("TASK",
                                                           sqlite_orm::make_column("task_id", &TaskTable::task_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("title", &TaskTable::title),
                                                           sqlite_orm::make_column("starred", &TaskTable::starred),
                                                           sqlite_orm::make_column("hide_in_todo", &TaskTable::hide_in_todo),
                                                           sqlite_orm::make_column("complete_in_order", &TaskTable::complete_in_order),
                                                           sqlite_orm::make_column("inherit_date", &TaskTable::inherit_date),
                                                           sqlite_orm::make_column("folder", &TaskTable::folder),
                                                           sqlite_orm::make_column("generated_by_recurrence", &TaskTable::generated_by_recurrence),
                                                           sqlite_orm::make_column("project", &TaskTable::project),
                                                           sqlite_orm::make_column("check_all_dependency", &TaskTable::check_all_dependency),
                                                           sqlite_orm::make_column("has_contexts", &TaskTable::has_contexts),
                                                           sqlite_orm::make_column("effort", &TaskTable::effort),
                                                           sqlite_orm::make_column("goal", &TaskTable::goal),
                                                           sqlite_orm::make_column("importance", &TaskTable::importance),
                                                           sqlite_orm::make_column("project_completion", &TaskTable::project_completion),
                                                           sqlite_orm::make_column("project_status", &TaskTable::project_status),
                                                           sqlite_orm::make_column("review_recurrence_type", &TaskTable::review_recurrence_type),
                                                           sqlite_orm::make_column("urgency", &TaskTable::urgency),
                                                           sqlite_orm::make_column("review_every", &TaskTable::review_every),
                                                           sqlite_orm::make_column("depend_postpone", &TaskTable::depend_postpone),
                                                           sqlite_orm::make_column("estimate_min", &TaskTable::estimate_min),
                                                           sqlite_orm::make_column("estimate_max", &TaskTable::estimate_max),
                                                           sqlite_orm::make_column("local_start_date", &TaskTable::local_start_date),
                                                           sqlite_orm::make_column("local_due_date", &TaskTable::local_due_date),
                                                           sqlite_orm::make_column("time_zone", &TaskTable::time_zone),
                                                           sqlite_orm::make_column("completion_date", &TaskTable::completion_date),
                                                           sqlite_orm::make_column("created_date", &TaskTable::created_date),
                                                           sqlite_orm::make_column("last_modified", &TaskTable::last_modified),
                                                           sqlite_orm::make_column("last_review", &TaskTable::last_review),
                                                           sqlite_orm::make_column("last_used", &TaskTable::last_used),
                                                           sqlite_orm::make_column("next_review_date", &TaskTable::next_review_date),
                                                           sqlite_orm::make_column("starred_date", &TaskTable::starred_date),
                                                           sqlite_orm::make_column("uuid", &TaskTable::uuid),
                                                           sqlite_orm::make_column("version", &TaskTable::version),
                                                           sqlite_orm::make_column("note_id", &TaskTable::note_id),
                                                           sqlite_orm::make_column("reminder_id", &TaskTable::reminder_id),
                                                           sqlite_orm::make_column("recurrence_id", &TaskTable::recurrence_id),
                                                           sqlite_orm::make_column("flag_id", &TaskTable::flag_id),
                                                           sqlite_orm::make_column("parent_id", &TaskTable::parent_id),
                                                           sqlite_orm::make_column("subtask_ordinal", &TaskTable::subtask_ordinal),
                                                           sqlite_orm::make_column("text_tag", &TaskTable::text_tag)),
                                    sqlite_orm::make_table("NOTE",
                                                           sqlite_orm::make_column("note_id", &NoteTable::note_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("text", &NoteTable::text)),
                                    sqlite_orm::make_table("REMINDER",
                                                           sqlite_orm::make_column("reminder_id", &ReminderTable::reminder_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("reminder_actions", &ReminderTable::reminder_actions),
                                                           sqlite_orm::make_column("repeat_counter", &ReminderTable::repeat_counter),
                                                           sqlite_orm::make_column("stop_after", &ReminderTable::stop_after),
                                                           sqlite_orm::make_column("repeat_interval", &ReminderTable::repeat_interval),
                                                           sqlite_orm::make_column("hidden", &ReminderTable::hidden),
                                                           sqlite_orm::make_column("auto_repeat", &ReminderTable::auto_repeat),
                                                           sqlite_orm::make_column("dismissed", &ReminderTable::dismissed),
                                                           sqlite_orm::make_column("endless_repetition", &ReminderTable::endless_repetition),
                                                           sqlite_orm::make_column("local_next_alert", &ReminderTable::local_next_alert),
                                                           sqlite_orm::make_column("local_reminder_date", &ReminderTable::local_reminder_date),
                                                           sqlite_orm::make_column("use_individual_actions", &ReminderTable::use_individual_actions)),
                                    sqlite_orm::make_table("RECURRENCE",
                                                           sqlite_orm::make_column("recurrence_id", &RecurrenceTable::recurrence_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("day_of_month", &RecurrenceTable::day_of_month),
                                                           sqlite_orm::make_column("day_of_week_mask", &RecurrenceTable::day_of_week_mask),
                                                           sqlite_orm::make_column("month_of_year", &RecurrenceTable::month_of_year),
                                                           sqlite_orm::make_column("pattern_instance", &RecurrenceTable::pattern_instance),
                                                           sqlite_orm::make_column("recur_when_subtask_completed", &RecurrenceTable::recur_when_subtask_completed),
                                                           sqlite_orm::make_column("recurrence_pattern", &RecurrenceTable::recurrence_pattern),
                                                           sqlite_orm::make_column("generated_count", &RecurrenceTable::generated_count),
                                                           sqlite_orm::make_column("interval", &RecurrenceTable::interval),
                                                           sqlite_orm::make_column("occurrences", &RecurrenceTable::occurrences),
                                                           sqlite_orm::make_column("hourly_delta", &RecurrenceTable::hourly_delta),
                                                           sqlite_orm::make_column("do_not_create_completed_copy", &RecurrenceTable::do_not_create_completed_copy),
                                                           sqlite_orm::make_column("hidden", &RecurrenceTable::hidden),
                                                           sqlite_orm::make_column("uncomplete_subtasks", &RecurrenceTable::uncomplete_subtasks),
                                                           sqlite_orm::make_column("uncomplete_subtasks_if_all_checked", &RecurrenceTable::uncomplete_subtasks_if_all_checked),
                                                           sqlite_orm::make_column("use_completion_date", &RecurrenceTable::use_completion_date),
                                                           sqlite_orm::make_column("pattern_end_date", &RecurrenceTable::pattern_end_date),
                                                           sqlite_orm::make_column("pattern_start_date", &RecurrenceTable::pattern_start_date)),
                                    sqlite_orm::make_table("FLAG",
                                                           sqlite_orm::make_column("flag_id", &FlagTable::flag_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("title", &FlagTable::title),
                                                           sqlite_orm::make_column("uuid", &FlagTable::uuid),
                                                           sqlite_orm::make_column("version", &FlagTable::version),
                                                           sqlite_orm::make_column("note_id", &FlagTable::note_id)),
                                    sqlite_orm::make_table("CONTEXT",
                                                           sqlite_orm::make_column("context_id", &ContextTable::context_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("title", &ContextTable::title),
                                                           sqlite_orm::make_column("hide_from_todo", &ContextTable::hide_from_todo),
                                                           sqlite_orm::make_column("hide_from_item_props", &ContextTable::hide_from_item_props),
                                                           sqlite_orm::make_column("open_hours", &ContextTable::open_hours),
                                                           sqlite_orm::make_column("latitude", &ContextTable::latitude),
                                                           sqlite_orm::make_column("longitude", &ContextTable::longitude),
                                                           sqlite_orm::make_column("radius", &ContextTable::radius),
                                                           sqlite_orm::make_column("notify_entering", &ContextTable::notify_entering),
                                                           sqlite_orm::make_column("notify_exiting", &ContextTable::notify_exiting),
                                                           sqlite_orm::make_column("uuid", &ContextTable::uuid),
                                                           sqlite_orm::make_column("version", &ContextTable::version),
                                                           sqlite_orm::make_column("note_id", &ContextTable::note_id)),
                                    sqlite_orm::make_table("CONTEXT_TO_ASSIGNED_TASK",
                                                           sqlite_orm::make_column("context_to_assigned_task_id", &ContextToAssignedTaskTable::context_to_assigned_task_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("assigned_task_id", &ContextToAssignedTaskTable::assigned_task_id),
                                                           sqlite_orm::make_column("context_id", &ContextToAssignedTaskTable::context_id),
                                                           sqlite_orm::unique(&ContextToAssignedTaskTable::assigned_task_id, &ContextToAssignedTaskTable::context_id)),
                                    sqlite_orm::make_table("DEPENDENT_CONTEXT_TO_MASTER_CONTEXT",
                                                           sqlite_orm::make_column("dependent_context_to_context_context_id", &DependentContextToContextContextTable::dependent_context_to_context_context_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("master_context_id", &DependentContextToContextContextTable::master_context_id),
                                                           sqlite_orm::make_column("dependent_context_id", &DependentContextToContextContextTable::dependent_context_id),
                                                           sqlite_orm::unique(&DependentContextToContextContextTable::master_context_id, &DependentContextToContextContextTable::dependent_context_id)),
                                    sqlite_orm::make_table("DEPENDENT_TASK_TO_MASTER_TASK",
                                                           sqlite_orm::make_column("dependent_task_to_master_task_id", &DependentTaskToMasterTaskTable::dependent_task_to_master_task_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("master_task_id", &DependentTaskToMasterTaskTable::master_task_id),
                                                           sqlite_orm::make_column("dependent_task_id", &DependentTaskToMasterTaskTable::dependent_task_id),
                                                           sqlite_orm::unique(&DependentTaskToMasterTaskTable::master_task_id, &DependentTaskToMasterTaskTable::dependent_task_id))

    );
}

class DataBase {
public:
    using Storage = std::invoke_result<decltype(&initDB), typename std::filesystem::path>::type;
    DataBase() = delete;
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;
    DataBase(const DataBase&&) = delete;
    DataBase& operator=(const DataBase&&) = delete;

    explicit DataBase(const std::filesystem::path& path);
    ~DataBase();

    GTD_RESULT create(Crud& crud);
    GTD_RESULT update(Crud& crud);
    GTD_RESULT remove(Crud& crud);
    GTD_RESULT query(Crud& crud);
    Storage& sql() {return storage;};
private:
    Storage storage;
};

class Crud {
public:
    Crud() = delete;
    Crud(DataBase& db): datebase(db){};
    Crud(const Crud& crud) = default;
    Crud& operator=(const Crud& crud) = default;
    Crud(Crud&& crud) = default;
    Crud& operator=(Crud&& crud) = default;

    virtual GTD_RESULT create() = 0;
    virtual GTD_RESULT update() = 0;
    virtual GTD_RESULT remove() = 0;
    virtual GTD_RESULT query() = 0;

    virtual ~Crud() = default;

protected:
    DataBase& datebase;
};



#endif //MYLIFE_DATABASE_H
