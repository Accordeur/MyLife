//
// Created by Zelonge on 2021/4/9.
//

#ifndef MYLIFE_TABLES_H
#define MYLIFE_TABLES_H

#include <cstdint>
#include <string>
#include <vector>

struct Task {
    uint64_t task_id;
    std::string title;
    int32_t starred;
    int32_t hide_in_todo;
    int32_t bookmark;
    int32_t complete_in_order;
    int32_t inherit_date;
    int32_t folder;
    int32_t generated_by_recurrence;
    int32_t project;
    int32_t check_all_dependency;
    int32_t has_contexts;
    int32_t expanded;
    int32_t effort;
    int32_t goal;
    int32_t importance;
    int32_t project_completion;
    int32_t project_status;
    int32_t review_recurrence_type;
    int32_t urgency;
    int32_t review_every;
    double depend_postpone;
    double estimate_min;
    double estimate_max;
    int64_t local_start_date;
    int64_t local_due_date;
    std::string time_zone;
    int64_t completion_date;
    int64_t created_date;
    int64_t last_modified;
    int64_t last_review;
    int64_t last_used;
    int64_t next_review_date;
    int64_t starred_date;
    std::string uuid;
    int32_t version;
    uint64_t note_id;
    uint64_t reminder_id;
    uint64_t recurrence_id;
    uint64_t flag_id;
    uint64_t parent_id;
    uint64_t subtask_ordinal;
    std::string text_tag;
};

struct Note {
    uint64_t note_id;
    std::string text;
};

struct Reminder {
    uint64_t reminder_id;
    uint64_t reminder_actions;
    int32_t repeat_counter;
    int32_t stop_after;
    double repeat_interval;
    int32_t hidden;
    int32_t auto_repeat;
    int32_t dismissed;
    int32_t endless_repetition;
    int64_t local_next_alert;
    int64_t local_reminder_date;
    int32_t use_individual_actions;
};

struct Recurrence {
    uint64_t recurrence_id;
    int32_t day_of_month;
    int32_t day_of_week_mask;
    int32_t month_of_year;
    int32_t pattern_instance;
    int32_t recur_when_subtask_completed;
    int32_t recurrence_pattern;
    int32_t generated_count;
    int32_t interval;
    int32_t occurrences;
    double hourly_delta;
    int32_t do_not_create_completed_copy;
    int32_t hidden;
    int32_t uncomplete_subtasks;
    int32_t uncomplete_subtasks_if_all_checked;
    int64_t use_completion_date;
    int64_t pattern_end_date;
    int64_t pattern_start_date;
};

struct Flag {
    uint64_t flag_id;
    std::string title;
    std::string uuid;
    int32_t version;
    uint64_t note_id;
};

struct Context {
    uint64_t context_id;
    std::string title;
    int32_t hide_from_todo;
    int32_t hide_from_item_props;
    std::vector<char> open_hours;
    double latitude;
    double longitude;
    double radius;
    int32_t notify_entering;
    int32_t notify_exiting;
    std::string uuid;
    int32_t version;
    uint64_t note_id;
};

struct ContextToAssignedTask {
    uint64_t context_to_assigned_task_id;
    uint64_t assigned_task_id;
    uint64_t context_id;
};

struct DependentContextToContextContext {
    uint64_t dependent_context_to_context_context_id;
    uint64_t master_context_id;
    uint64_t dependent_context_id;
};

struct DependentTaskToMasterTask {
    uint64_t dependent_task_to_master_task_id;
    uint64_t master_task_id;
    uint64_t dependent_task_id;
};



#endif //MYLIFE_TABLES_H