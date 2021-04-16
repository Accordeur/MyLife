//
// Created by Zelonge on 2021/4/13.
//
#include <tuple>
#include <gtest/gtest.h>
#include "../../GTD_Service/Task.h"

TEST(GTD_Task, Init) {
    DataBase dataBase("./sqlite.db");
    Task task(dataBase);

    EXPECT_EQ(task.get_title(), "");
    EXPECT_FALSE(task.is_starred());
    EXPECT_FALSE(task.is_hide_in_todo());
    EXPECT_TRUE(task.is_inherit_date());
    EXPECT_FALSE(task.is_folder());
    EXPECT_FALSE(task.is_generated_by_recurrence());
    EXPECT_FALSE(task.is_project());
    EXPECT_EQ(task.get_effort(), Task::Effort::Normal);
    EXPECT_EQ(task.get_importance(), Task::Importance::Normal);
    EXPECT_EQ(task.get_Urgent(), Task::Urgency::Normal);
    EXPECT_EQ(task.get_project_status(), Task::ProjectStatus::InProgress);
    EXPECT_EQ(task.get_review_rate(), 0);
    EXPECT_EQ(task.get_review_recurrence_type(), Task::ReviewType::None);
    EXPECT_EQ(std::get<0>(task.get_estimate_time()).count(), 0);
    EXPECT_EQ(std::get<1>(task.get_estimate_time()).count(), 0);
    EXPECT_NE(task.get_uuid().version(), boost::uuids::uuid::version_unknown);
}


