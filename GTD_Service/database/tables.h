//
// Created by Zelonge on 2021/4/9.
//

#ifndef MYLIFE_TABLES_H
#define MYLIFE_TABLES_H

#include <cstdint>
#include <string>
#include <vector>

constexpr const int64_t ID_UNINIT = -1;
constexpr const int64_t ID_ROOT = 1;
struct TaskTable {
    int64_t task_id = ID_UNINIT;
    std::string title;
    int32_t starred;
    int32_t hide_in_todo;
    int32_t complete_in_order;
    int64_t inherit_date;
    int32_t folder;
    int32_t generated_by_recurrence;
    int32_t project;
    int32_t check_all_dependency;
    int32_t has_contexts;
    int32_t effort;
    int32_t goal;
    int32_t importance;
    int32_t project_completion;
    int32_t project_status;
    int32_t review_recurrence_type;
    int32_t urgency;
    int32_t review_every;
    int64_t depend_postpone;
    int64_t estimate_min;
    int64_t estimate_max;
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
    int64_t note_id;
    int64_t reminder_id;
    int64_t recurrence_id;
    int64_t flag_id;
    int64_t parent_id;
    int32_t subtask_ordinal;
    std::string text_tag;
};

struct NoteTable {
    int64_t note_id = ID_UNINIT;
    std::string text;
};

struct ReminderTable {
    int64_t reminder_id = ID_UNINIT;
    int64_t reminder_actions;    //开关
    int32_t repeat_counter;      //重复计数器
    int32_t stop_after;          //多少个后停止
    int32_t repeat_interval;     //重复间隔时间
    int32_t hidden;              //
    int32_t auto_repeat;         //重复开关
    int32_t dismissed;           //解雇闹钟， 之后不在提醒
    int32_t endless_repetition;  //一直重复
    int64_t local_reminder_date; //提醒时间
    int64_t local_next_alert;    //下一次提醒时间
    int32_t use_individual_actions;  //自定义提示行为
    //auto operator<=>(const ReminderTable&) const = default;
};

struct RecurrenceTable {
    int64_t recurrence_id = ID_UNINIT;
    int32_t recurrence_pattern;     //循环方式: 小时, 天, 周, 月, 年
    int32_t pattern_instance;       //
    int32_t day_of_week_mask;       //每周哪几天重复
    int32_t day_of_month;           //每月第几天重复
    int32_t month_of_year;          //每年第几月重复
    int32_t generated_count;        //计数
    int32_t interval;               //间隔
    int32_t occurrences;
    int64_t use_completion_date;
    int64_t pattern_start_date;
    int64_t pattern_end_date;
    int32_t hourly_delta;           //预计时间
    int32_t hidden;
    int32_t recur_when_subtask_completed;
    int32_t do_not_create_completed_copy;
    int32_t uncomplete_subtasks;
    int32_t uncomplete_subtasks_if_all_checked;
};

struct FlagTable {
    int64_t flag_id = ID_UNINIT;
    std::string title;
    std::string uuid;
    int32_t version;
    int64_t note_id;
};

struct ContextTable {
    int64_t context_id = ID_UNINIT;
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
    int64_t note_id;
};

struct ContextToAssignedTaskTable {
    int64_t context_to_assigned_task_id = ID_UNINIT;
    int64_t assigned_task_id;
    int64_t context_id;
};

struct DependentContextToContextContextTable {
    int64_t dependent_context_to_context_context_id = ID_UNINIT;
    int64_t master_context_id;
    int64_t dependent_context_id;
};

struct DependentTaskToMasterTaskTable {
    int64_t dependent_task_to_master_task_id = ID_UNINIT;
    int64_t master_task_id;
    int64_t dependent_task_id;
};



#endif //MYLIFE_TABLES_H
