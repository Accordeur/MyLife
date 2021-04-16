//
// Created by Zelonge on 2021/4/10.
//

#ifndef MYLIFE_TASK_H
#define MYLIFE_TASK_H
#include <boost/uuid/uuid.hpp>
#include "database/tables.h"
#include "database/database.h"
#include "Reminder.h"
#include "Recurrence.h"
#include "Flag.h"
#include "Note.h"

class Task: protected Crud {
public:
    Task() = delete;
    explicit Task(DataBase& dataBase);
    Task(const Task& task) = default;
    Task& operator=(const Task& task) = default;
    Task(Task&& task) = default;
    Task& operator=(Task&& task) = default;

    enum class Effort: int32_t {
        Relaxed = 20,
        Easy = 40,
        Normal = 60,
        Hard = 80,
        Crazy = 100
    };
    enum class Importance: int32_t {
        Unimportant = 20,
        LittleImportant = 40,
        Normal = 60,
        SomeImportant = 80,
        VeryImportant = 100
    };
    enum class Urgency: int32_t {
        NonUrgent = 20,
        LittleUrgent = 40,
        Normal = 60,
        SomeUrgent = 80,
        VeryUrgent = 100
    };
    enum class ProjectStatus: int32_t {
        NoStarted = 25,
        InProgress = 50,
        Suspended = 75,
        Completed = 100
    };
    enum class ReviewType: int32_t {
        None,
        Day,
        Weekly,
        Month,
        Quarter,
        Year
    };

    [[nodiscard]] std::string get_title() const;
    GTD_RESULT set_title(const std::string& title);

    bool is_starred() const;
    void starred();
    void unstarred();

    bool is_hide_in_todo() const;
    void hide_in_todo();
    void show_in_todo();

    bool is_complete_in_order() const;
    void complete_in_order(bool order);

    bool is_inherit_date() const;
    void set_inherit_date(bool mark);

    bool is_folder() const;
    void set_folder_flag(bool mark);

    bool is_generated_by_recurrence() const;
    void generated_by_recurrence(bool mark);

    bool is_project() const;
    void set_project_flag(bool mark);

    //check_all_dependency
    //has_contexts

    Effort get_effort() const;
    void set_effort(Effort effort);

    //goal

    Importance get_importance() const;
    void set_importance(Importance importance);

    Urgency get_Urgent() const;
    void set_urgent(Urgency urgent);

    //project_completion

    ProjectStatus get_project_status() const;
    void set_project_status(ProjectStatus status);

    int32_t get_review_rate() const;
    void set_review_rate(int32_t every);

    ReviewType get_review_recurrence_type() const;
    void set_review_recurrence_type(ReviewType type);

    //depend_postpone

    [[nodiscard]] std::tuple<std::chrono::minutes, std::chrono::minutes> get_estimate_time() const;
    void set_estimate_time(std::chrono::minutes min, std::chrono::minutes max);

    //local_start_date
    //local_due_date
    //time_zone
    //completion_date
    //created_date
    //last_modified

    boost::uuids::uuid get_uuid() const;

    std::string get_note() const;
    void set_note(std::string note);

    Reminder& get_reminder();
    Recurrence& get_recurrence();
    Flag& get_flag();

protected:
    GTD_RESULT create() override final;
    GTD_RESULT update() override final;
    GTD_RESULT remove() override final;
    GTD_RESULT query() override final;

private:
    std::chrono::system_clock::time_point inherit_date;
    std::chrono::system_clock::time_point local_start_date;
    std::chrono::system_clock::time_point local_due_date;
    std::chrono::system_clock::time_point completion_date;
    std::chrono::system_clock::time_point created_date;
    std::chrono::system_clock::time_point last_modified;
    std::chrono::system_clock::time_point last_review;
    std::chrono::system_clock::time_point last_used;
    std::chrono::system_clock::time_point next_review_date;
    std::chrono::system_clock::time_point starred_date;

    Note note;
    Reminder reminder;
    Recurrence recurrence;
    Flag flag;
    TaskTable taskTable;
};


#endif //MYLIFE_TASK_H
