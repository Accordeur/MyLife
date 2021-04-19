//
// Created by Zelonge on 2021/4/19.
//
#include <tuple>
#include <gtest/gtest.h>
#include "../../GTD_Service/Recurrence.h"

TEST(GTD_Recurrence, Init) {
    DataBase dataBase("./sqlite.db");
    Recurrence recurrence(dataBase);
    EXPECT_EQ(recurrence.get_recur_config(), Recurrence::RecurConfig());
}

TEST(GTD_Recurrence, SQL) {

}