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

TEST(GTD_Recurrence, get_next_date) {
    using namespace std::chrono;
    using namespace date;
    DataBase dataBase("./sqlite.db");

    Recurrence recurrence(dataBase);
    recurrence.set_period(Recurrence::DateTime(2021_y/May/1, {}), Recurrence::DateTime(2021_y/May/8));
    Recurrence::RecurConfig config;
    config.recurrence_pattern = Recurrence::Pattern::Daily;
    config.pattern_instance = Recurrence::PatternInstance::ByDay;
    config.interval = 3;
    recurrence.set_recur(config);
    recurrence.set_end_occur_times(Recurrence::EndType::NoEnd);

    EXPECT_EQ(recurrence.get_next(Recurrence::DateTime(2021_y/May/9)), Recurrence::DateTime(2021_y/May/11));
    EXPECT_EQ(recurrence.get_next(Recurrence::DateTime(2021_y/May/8)), Recurrence::DateTime(2021_y/May/8));


    recurrence.set_period(Recurrence::DateTime(2021_y/May/1, {}), Recurrence::DateTime(2021_y/May/3));
    config.recurrence_pattern = Recurrence::Pattern::Weekly;
    config.pattern_instance = Recurrence::PatternInstance::ByWeekday;
    config.interval = 3;
    config.day_of_week_mask = static_cast<Recurrence::Week>(static_cast<int32_t>(Recurrence::Week::Monday) | static_cast<int32_t>(Recurrence::Week::Thursday));
    recurrence.set_recur(config);
    recurrence.set_end_occur_times(Recurrence::EndType::NoEnd);

    EXPECT_EQ(recurrence.get_next(Recurrence::DateTime(2021_y/May/10)), Recurrence::DateTime(2021_y/May/24));
    //std::cout << recurrence.get_next(Recurrence::DateTime(2021_y/May/25)).date << std::endl;
    EXPECT_EQ(recurrence.get_next(Recurrence::DateTime(2021_y/May/25)), Recurrence::DateTime(2021_y/May/25));

}