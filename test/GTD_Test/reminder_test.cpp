//
// Created by Zelonge on 2021/4/16.
//
#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "../../GTD_Service/Reminder.h"
TEST(GTD_Reminder, Init) {
    DataBase dataBase("./sqlite.db");
    Reminder reminder(dataBase);
    EXPECT_FALSE(reminder.is_enable());
    EXPECT_EQ(reminder.get_stop_counter(), 0);
    EXPECT_EQ(reminder.get_repeat_interval(), std::chrono::minutes(0));
    EXPECT_FALSE(reminder.is_hide());
    EXPECT_FALSE(reminder.is_enable_repeat());
    EXPECT_FALSE(reminder.is_repeat_forever());
    EXPECT_EQ(reminder.get_reminder_date().time_since_epoch().count(), 0);
    EXPECT_EQ(reminder.get_next_alert_time().time_since_epoch().count(), 0);
}

TEST(GTD_Reminder, SQL) {
    DataBase dataBase("./sqlite.db");
    Reminder reminder(dataBase);
    reminder.set_reminder_date(std::chrono::system_clock::now());
    EXPECT_EQ(reminder.create(), GTD_OK);
    auto interval = std::chrono::minutes(25);
    reminder.set_repeat_interval(interval);
    EXPECT_EQ(reminder.update(), GTD_OK);

    auto reminder1 = Reminder(dataBase);
    reminder1.reminderTable.reminder_id = reminder.reminderTable.reminder_id;
    EXPECT_EQ(reminder1.query(), GTD_OK);
    EXPECT_EQ(reminder, reminder1);
    EXPECT_EQ(reminder1.get_repeat_interval(), interval);


    EXPECT_EQ(reminder.remove(), GTD_OK);
    EXPECT_EQ(reminder.get_id(), ID_UNINIT);
    EXPECT_NE(reminder1.query(), GTD_OK);

    dataBase.sql().remove_all<ReminderTable>();
    for(int i = 0; i < 100; i++) {
        Reminder reminder(dataBase);
        reminder.set_reminder_date(std::chrono::system_clock::now());
        EXPECT_EQ(reminder.create(), GTD_OK);
        EXPECT_EQ(reminder.get_id(), i+1);
    }
    using namespace sqlite_orm;
    auto arr = dataBase.sql().get_all<ReminderTable>(where(c(&ReminderTable::reminder_id) < 1000));
    EXPECT_EQ(arr.size(), 100);
    dataBase.sql().remove_all<ReminderTable>();
}

TEST(GTD_Reminder, Timer) {
    using namespace std::chrono_literals;
    DataBase dataBase("./sqlite.db");
    Reminder reminder(dataBase);

    //单次定时器
    reminder.enable_reminder(true);
    reminder.set_reminder_date(std::chrono::system_clock::now() + std::chrono::milliseconds (500));
    EXPECT_EQ(reminder.is_active(), true);
    EXPECT_EQ(reminder.is_timeout(), false);
    std::this_thread::sleep_for(500ms);
    EXPECT_EQ(reminder.is_timeout(), true);
    EXPECT_EQ(reminder.is_active(), true);
    reminder.refresh_timer();
    EXPECT_EQ(reminder.is_active(), false);
    EXPECT_EQ(reminder.is_enable(), true);
    EXPECT_EQ(reminder.is_repeat_forever(), false);

    //重复无限定时器
    reminder.enable_reminder(true);
    reminder.enable_repeat(true);
    reminder.repeat_forever(true);
    reminder.set_reminder_date(std::chrono::system_clock::now() + 50ms);
    reminder.set_repeat_interval(1min);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(reminder.is_active(), true);
        EXPECT_EQ(reminder.is_timeout(), false);
        std::this_thread::sleep_for(1min);
        EXPECT_EQ(reminder.is_timeout(), true);
        EXPECT_EQ(reminder.is_active(), true);
        reminder.refresh_timer();
        EXPECT_EQ(reminder.current_repeat_count(), i+1);
    }
    EXPECT_EQ(reminder.is_active(), true);
    EXPECT_EQ(reminder.is_enable(), true);
    EXPECT_EQ(reminder.current_repeat_count(),10);
}