//
// Created by Zelonge on 2021/4/9.
//

#ifndef MYLIFE_DATABASE_H
#define MYLIFE_DATABASE_H
#include <sqlite_orm/sqlite_orm.h>
#include <filesystem>
#include <type_traits>
#include "tables.h"


inline auto initDB(const std::filesystem::path& path) {
    return sqlite_orm::make_storage(path.string(),
                                    sqlite_orm::make_table("TASK",
                                                           sqlite_orm::make_column("task_id", &Task::task_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("title", &Task::title),
                                                           sqlite_orm::make_column("starred", &Task::starred),
                                                           sqlite_orm::make_column("hide_in_todo", &Task::hide_in_todo),
                                                           sqlite_orm::make_column("bookmark", &Task::bookmark),
                                                           sqlite_orm::make_column("complete_in_order", &Task::complete_in_order),
                                                           sqlite_orm::make_column("inherit_date", &Task::inherit_date),
                                                           sqlite_orm::make_column("folder", &Task::folder),
                                                           sqlite_orm::make_column("generated_by_recurrence", &Task::generated_by_recurrence),
                                                           sqlite_orm::make_column("project", &Task::project),
                                                           sqlite_orm::make_column("check_all_dependency", &Task::check_all_dependency),
                                                           sqlite_orm::make_column("has_contexts", &Task::has_contexts),
                                                           sqlite_orm::make_column("expanded", &Task::expanded),
                                                           sqlite_orm::make_column("effort", &Task::effort),
                                                           sqlite_orm::make_column("goal", &Task::goal),
                                                           sqlite_orm::make_column("importance", &Task::importance),
                                                           sqlite_orm::make_column("project_completion", &Task::project_completion),
                                                           sqlite_orm::make_column("project_status", &Task::project_status),
                                                           sqlite_orm::make_column("review_recurrence_type", &Task::review_recurrence_type),
                                                           sqlite_orm::make_column("urgency", &Task::urgency),
                                                           sqlite_orm::make_column("review_every", &Task::review_every),
                                                           sqlite_orm::make_column("depend_postpone", &Task::depend_postpone),
                                                           sqlite_orm::make_column("estimate_min", &Task::estimate_min),
                                                           sqlite_orm::make_column("estimate_max", &Task::estimate_max),
                                                           sqlite_orm::make_column("local_start_date", &Task::local_start_date),
                                                           sqlite_orm::make_column("local_due_date", &Task::local_due_date),
                                                           sqlite_orm::make_column("time_zone", &Task::time_zone),
                                                           sqlite_orm::make_column("completion_date", &Task::completion_date),
                                                           sqlite_orm::make_column("created_date", &Task::created_date),
                                                           sqlite_orm::make_column("last_modified", &Task::last_modified),
                                                           sqlite_orm::make_column("last_review", &Task::last_review),
                                                           sqlite_orm::make_column("last_used", &Task::last_used),
                                                           sqlite_orm::make_column("next_review_date", &Task::next_review_date),
                                                           sqlite_orm::make_column("starred_date", &Task::starred_date),
                                                           sqlite_orm::make_column("uuid", &Task::uuid),
                                                           sqlite_orm::make_column("version", &Task::version),
                                                           sqlite_orm::make_column("note_id", &Task::note_id),
                                                           sqlite_orm::make_column("reminder_id", &Task::reminder_id),
                                                           sqlite_orm::make_column("recurrence_id", &Task::recurrence_id),
                                                           sqlite_orm::make_column("flag_id", &Task::flag_id),
                                                           sqlite_orm::make_column("parent_id", &Task::parent_id),
                                                           sqlite_orm::make_column("subtask_ordinal", &Task::subtask_ordinal),
                                                           sqlite_orm::make_column("text_tag", &Task::text_tag)),
                                    sqlite_orm::make_table("NOTE",
                                                           sqlite_orm::make_column("note_id", &Note::note_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("text", &Note::text)),
                                    sqlite_orm::make_table("REMINDER",
                                                           sqlite_orm::make_column("reminder_id", &Reminder::reminder_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("reminder_actions", &Reminder::reminder_actions),
                                                           sqlite_orm::make_column("repeat_counter", &Reminder::repeat_counter),
                                                           sqlite_orm::make_column("stop_after", &Reminder::stop_after),
                                                           sqlite_orm::make_column("repeat_interval", &Reminder::repeat_interval),
                                                           sqlite_orm::make_column("hidden", &Reminder::hidden),
                                                           sqlite_orm::make_column("auto_repeat", &Reminder::auto_repeat),
                                                           sqlite_orm::make_column("dismissed", &Reminder::dismissed),
                                                           sqlite_orm::make_column("endless_repetition", &Reminder::endless_repetition),
                                                           sqlite_orm::make_column("local_next_alert", &Reminder::local_next_alert),
                                                           sqlite_orm::make_column("local_reminder_date", &Reminder::local_reminder_date),
                                                           sqlite_orm::make_column("use_individual_actions", &Reminder::use_individual_actions)),
                                    sqlite_orm::make_table("RECURRENCE",
                                                           sqlite_orm::make_column("recurrence_id", &Recurrence::recurrence_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("day_of_month", &Recurrence::day_of_month),
                                                           sqlite_orm::make_column("day_of_week_mask", &Recurrence::day_of_week_mask),
                                                           sqlite_orm::make_column("month_of_year", &Recurrence::month_of_year),
                                                           sqlite_orm::make_column("pattern_instance", &Recurrence::pattern_instance),
                                                           sqlite_orm::make_column("recur_when_subtask_completed", &Recurrence::recur_when_subtask_completed),
                                                           sqlite_orm::make_column("recurrence_pattern", &Recurrence::recurrence_pattern),
                                                           sqlite_orm::make_column("generated_count", &Recurrence::generated_count),
                                                           sqlite_orm::make_column("interval", &Recurrence::interval),
                                                           sqlite_orm::make_column("occurrences", &Recurrence::occurrences),
                                                           sqlite_orm::make_column("hourly_delta", &Recurrence::hourly_delta),
                                                           sqlite_orm::make_column("hidden", &Recurrence::hidden),
                                                           sqlite_orm::make_column("uncomplete_subtasks", &Recurrence::uncomplete_subtasks),
                                                           sqlite_orm::make_column("uncomplete_subtasks_if_all_checked", &Recurrence::uncomplete_subtasks_if_all_checked),
                                                           sqlite_orm::make_column("use_completion_date", &Recurrence::use_completion_date),
                                                           sqlite_orm::make_column("pattern_end_date", &Recurrence::pattern_end_date),
                                                           sqlite_orm::make_column("pattern_start_date", &Recurrence::pattern_start_date)),
                                    sqlite_orm::make_table("FLAG",
                                                           sqlite_orm::make_column("flag_id", &Flag::flag_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("title", &Flag::title),
                                                           sqlite_orm::make_column("uuid", &Flag::uuid),
                                                           sqlite_orm::make_column("version", &Flag::version),
                                                           sqlite_orm::make_column("note_id", &Flag::note_id)),
                                    sqlite_orm::make_table("CONTEXT",
                                                           sqlite_orm::make_column("context_id", &Context::context_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("title", &Context::title),
                                                           sqlite_orm::make_column("hide_from_todo", &Context::hide_from_todo),
                                                           sqlite_orm::make_column("hide_from_item_props", &Context::hide_from_item_props),
                                                           sqlite_orm::make_column("open_hours", &Context::open_hours),
                                                           sqlite_orm::make_column("latitude", &Context::latitude),
                                                           sqlite_orm::make_column("longitude", &Context::longitude),
                                                           sqlite_orm::make_column("radius", &Context::radius),
                                                           sqlite_orm::make_column("notify_entering", &Context::notify_entering),
                                                           sqlite_orm::make_column("notify_exiting", &Context::notify_exiting),
                                                           sqlite_orm::make_column("uuid", &Context::uuid),
                                                           sqlite_orm::make_column("version", &Context::version),
                                                           sqlite_orm::make_column("note_id", &Context::note_id)),
                                    sqlite_orm::make_table("CONTEXT_TO_ASSIGNED_TASK",
                                                           sqlite_orm::make_column("context_to_assigned_task_id", &ContextToAssignedTask::context_to_assigned_task_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("assigned_task_id", &ContextToAssignedTask::assigned_task_id),
                                                           sqlite_orm::make_column("context_id", &ContextToAssignedTask::context_id),
                                                           sqlite_orm::unique(&ContextToAssignedTask::assigned_task_id, &ContextToAssignedTask::context_id)),
                                    sqlite_orm::make_table("DEPENDENT_CONTEXT_TO_MASTER_CONTEXT",
                                                           sqlite_orm::make_column("dependent_context_to_context_context_id", &DependentContextToContextContext::dependent_context_to_context_context_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("master_context_id", &DependentContextToContextContext::master_context_id),
                                                           sqlite_orm::make_column("dependent_context_id", &DependentContextToContextContext::dependent_context_id),
                                                           sqlite_orm::unique(&DependentContextToContextContext::master_context_id, &DependentContextToContextContext::dependent_context_id)),
                                    sqlite_orm::make_table("DEPENDENT_TASK_TO_MASTER_TASK",
                                                           sqlite_orm::make_column("dependent_task_to_master_task_id", &DependentTaskToMasterTask::dependent_task_to_master_task_id, sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("master_task_id", &DependentTaskToMasterTask::master_task_id),
                                                           sqlite_orm::make_column("dependent_task_id", &DependentTaskToMasterTask::dependent_task_id),
                                                           sqlite_orm::unique(&DependentTaskToMasterTask::master_task_id, &DependentTaskToMasterTask::dependent_task_id))

    );
}

class DataBase {
public:
    DataBase() = delete;
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;
    DataBase(const DataBase&&) = delete;
    DataBase& operator=(const DataBase&&) = delete;

    DataBase(const std::filesystem::path& path);

private:
    typename std::invoke_result<decltype(&initDB), typename std::filesystem::path>::type storage;
};



#endif //MYLIFE_DATABASE_H
