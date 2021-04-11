//
// Created by Zelonge on 2021/4/10.
//

#ifndef MYLIFE_TASK_H
#define MYLIFE_TASK_H
#include "database/tables.h"
#include "database/database.h"

class Task: public Crud {
public:
    GTD_RESULT create(DataBase::Storage& storage) override final;
    GTD_RESULT update(DataBase::Storage& storage) override final;
    GTD_RESULT remove(DataBase::Storage& storage) override final;
    GTD_RESULT query(DataBase::Storage& storage) override final;

    enum Effort: int32_t {
        Relaxed = 20,
        Easy = 40,
        Normal = 60,
        Hard = 80,
        Crazy = 100
    };
    enum Importance: int32_t {
        Unimportant = 20,
        LittleImportant = 40,
        Important = 60,
        SomeImportant = 80,
        VeryImportant = 100
    };
    enum Urgency: int32_t {
        NonUrgent = 25,
        //Urgent = 50,
        LittleUrgent = 75,
        VeryUrgent = 100
    };
    enum ProjectStatus: int32_t {
        NoStarted = 25,
        InProgress = 50,
        Suspended = 75,
        Completed = 100
    };
    enum ReviewRate: int32_t {
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

    //inherit_date;

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

    ReviewRate get_review_recurrence_type() const;
    void set_review_recurrence_type(ReviewRate type);

    //depend_postpone

    std::tuple<std::chrono::minutes, std::chrono::minutes> get_estimate_time() const;
    void set_estimate_time(std::chrono::minutes min, std::chrono::minutes max);

    //local_start_date
    //local_due_date
    //time_zone
    //completion_date
    //created_date
    //last_modified
    


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


    TaskTable taskTable;
};


#endif //MYLIFE_TASK_H
