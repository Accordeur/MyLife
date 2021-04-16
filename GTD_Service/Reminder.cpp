//
// Created by Zelonge on 2021/4/13.
//

#include "Reminder.h"

Reminder::Reminder(DataBase &dataBase) : Crud(dataBase), reminderTable({}) {
    reminderTable.reminder_id = ID_UNINIT;

}

GTD_RESULT Reminder::create() {
    if(reminderTable.reminder_id != ID_UNINIT || reminderTable.local_reminder_date == 0) {
        return GTD_PARA_INVALID;
    }
    reminderTable.reminder_id = database.sql().insert(reminderTable);
    return GTD_OK;
}

GTD_RESULT Reminder::update() {
    if(reminderTable.reminder_id == ID_UNINIT ||  reminderTable.local_reminder_date == 0) {
        return GTD_PARA_INVALID;
    }
    database.sql().update(reminderTable);
    return GTD_OK;
}

GTD_RESULT Reminder::remove() {
    using namespace sqlite_orm;
    if(reminderTable.reminder_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    database.sql().remove_all<ReminderTable>(
            where(is_equal(&ReminderTable::reminder_id, reminderTable.reminder_id)));
    reminderTable.reminder_id = ID_UNINIT;
    return GTD_OK;
}

GTD_RESULT Reminder::query() {
    using namespace sqlite_orm;
    if(reminderTable.reminder_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }

    auto reminder_vec = database.sql().get_all<ReminderTable>(
            where(is_equal(&ReminderTable::reminder_id, reminderTable.reminder_id)));
    if(reminder_vec.empty() || reminder_vec[0].reminder_id != reminderTable.reminder_id) {
        return GTD_PARA_INVALID;
    }
    reminderTable = reminder_vec[0];
    return GTD_OK;
}

GTD_RESULT Reminder::enable_reminder(bool mark) {
    reminderTable.reminder_actions = mark;
    if(mark) {
        reminderTable.dismissed = false;
    }
    return GTD_OK;
}

bool Reminder::is_enable() const {
    return reminderTable.reminder_actions;
}

void Reminder::enable_repeat(bool mark) {
    reminderTable.auto_repeat = mark;
}

bool Reminder::is_enable_repeat() const {
    return reminderTable.auto_repeat;
}

void Reminder::repeat_forever(bool mark) {
    reminderTable.endless_repetition = mark;
}

bool Reminder::is_repeat_forever() const {
    return reminderTable.endless_repetition;
}

void Reminder::stop_after(uint32_t count) {
    reminderTable.stop_after = count;
}

uint32_t Reminder::get_stop_counter() const {
    return reminderTable.stop_after;
}

void Reminder::set_repeat_interval(std::chrono::minutes interval) {
    reminderTable.repeat_interval = interval.count();
}

std::chrono::minutes Reminder::get_repeat_interval() const {
    return std::chrono::minutes(reminderTable.repeat_interval);
}

void Reminder::set_reminder_date(std::chrono::time_point<std::chrono::system_clock> time) {
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(time);
    reminderTable.local_reminder_date = std::chrono::duration_cast<std::chrono::milliseconds>(
            now_ms.time_since_epoch()).count();
    reminderTable.local_next_alert = std::chrono::duration_cast<std::chrono::milliseconds>(
            now_ms.time_since_epoch()).count();
}

std::chrono::time_point<std::chrono::system_clock> Reminder::get_reminder_date() const {
    std::chrono::milliseconds dur(reminderTable.local_reminder_date);
    return std::chrono::time_point<std::chrono::system_clock>(dur);
}

std::chrono::time_point<std::chrono::system_clock> Reminder::get_next_alert_time() const {
    std::chrono::milliseconds dur(reminderTable.local_next_alert);
    return std::chrono::time_point<std::chrono::system_clock>(dur);
}

void Reminder::dismiss() {
    reminderTable.dismissed = true;
}

void Reminder::hide(bool mark) {
    reminderTable.hidden = mark;
}

bool Reminder::is_hide() const {
    return reminderTable.hidden;
}

int64_t Reminder::get_id() const {
    return reminderTable.reminder_id;
}

bool Reminder::is_timeout() const {
    if(!static_cast<bool>(reminderTable.reminder_actions)
       || static_cast<bool>(reminderTable.dismissed)) {
        return false;
    }
    auto now = std::chrono::system_clock::now();
    auto alter_time = std::chrono::time_point<std::chrono::system_clock>(
            std::chrono::milliseconds(reminderTable.local_next_alert));

    if(now >= alter_time) {
        return true;
    }
    return false;
}

void Reminder::refresh_timer() {
    if(!is_timeout()) {
        return;
    }
    // 重复定时器
    if(reminderTable.auto_repeat) {
        // 非无限定时器
        if(!reminderTable.endless_repetition) {
            reminderTable.repeat_counter++;
            if(reminderTable.repeat_counter >= reminderTable.stop_after) {
                reminderTable.dismissed = true;
                return;
            }

            auto reminder_date = std::chrono::time_point<std::chrono::system_clock>(
                    std::chrono::milliseconds(reminderTable.local_reminder_date));

            auto next_alert = reminder_date + std::chrono::minutes(reminderTable.repeat_interval * reminderTable.repeat_counter);
            auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(next_alert);
            reminderTable.local_next_alert = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now_ms.time_since_epoch()).count();

        } else {
            //无限定时器
            reminderTable.repeat_counter++;
            auto reminder_date = std::chrono::time_point<std::chrono::system_clock>(
                    std::chrono::milliseconds(reminderTable.local_reminder_date));

            auto next_alert = reminder_date + std::chrono::minutes(reminderTable.repeat_interval * reminderTable.repeat_counter);
            auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(next_alert);
            reminderTable.local_next_alert = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now_ms.time_since_epoch()).count();
        }
    } else {
        // 单次定时器
        reminderTable.dismissed = true;
    }



}

bool Reminder::is_active() const {
    if(reminderTable.reminder_actions && !reminderTable.dismissed) {
        return true;
    }
    return false;
}

uint32_t Reminder::current_repeat_count() const {
    return reminderTable.repeat_counter;
}

