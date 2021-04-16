//
// Created by Zelonge on 2021/4/13.
//

#ifndef MYLIFE_REMINDER_H
#define MYLIFE_REMINDER_H
#include <gtest/gtest.h>
#include "database/database.h"
#include "database/tables.h"

class Reminder: public Crud {
public:
    Reminder() = delete;
    explicit Reminder(DataBase& dataBase);
    Reminder(const Reminder&) = default;
    Reminder& operator=(const Reminder&) = default;
    Reminder(Reminder&&) = default;
    Reminder& operator=(Reminder&&) = default;

    //auto operator<=>(const Reminder&) const = default;

    GTD_RESULT enable_reminder(bool mark);
    bool is_enable() const;

    void enable_repeat(bool mark);
    bool is_enable_repeat() const;

    void repeat_forever(bool mark);
    bool is_repeat_forever() const;

    void stop_after(uint32_t count);
    uint32_t get_stop_counter() const;
    uint32_t current_repeat_count() const;

    void set_repeat_interval(std::chrono::minutes interval);
    std::chrono::minutes get_repeat_interval() const;

    void set_reminder_date(std::chrono::time_point<std::chrono::system_clock> time);
    std::chrono::time_point<std::chrono::system_clock> get_reminder_date() const;

    std::chrono::time_point<std::chrono::system_clock> get_next_alert_time() const;

    void dismiss();

    void hide(bool mark);
    bool is_hide() const;

    int64_t get_id() const;

    bool is_active() const;
    bool is_timeout() const;
    void refresh_timer();

protected:
    GTD_RESULT create() override final;
    GTD_RESULT update() override final;
    GTD_RESULT remove() override final;
    GTD_RESULT query() override final;
private:
    ReminderTable reminderTable;

    FRIEND_TEST(GTD_Reminder, SQL);
};


#endif //MYLIFE_REMINDER_H
