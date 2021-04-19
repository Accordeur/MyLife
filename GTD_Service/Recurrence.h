//
// Created by Zelonge on 2021/4/13.
//

#ifndef MYLIFE_RECURRENCE_H
#define MYLIFE_RECURRENCE_H
#include <gtest/gtest.h>
#include "database/database.h"
#include "database/tables.h"

class Recurrence: public Crud {
public:
    enum class Pattern {
        None = 0,
        Hour = 1,
        Daily,
        Weekly,
        Monthly,
        Yearly
    };

    enum class PatternInstance {
        ByDay,
        ByWeek,
        ByComplete
    };

    enum class Week {
        Monday = 1,
        Tuesday = 2,
        Wednesday = 4,
        Thursday = 8,
        Friday = 16,
        Saturday = 32,
        Sunday = 64,
        FirstDay = 128,
        LastDay = 256
    };

    enum class OrdinalWeek {
        First = 1,
        Second,
        Third,
        Fourth,
        Last
    };
    enum class Month {
        Jan,
        Feb,
        Mar,
        Apr,
        May,
        Jun,
        Jul,
        Aug,
        Sept,
        Oct,
        Nov,
        Dec
    };

    enum class Skip {
        NoSkip = 0,
        Holiday = 1,
        Weekend = 2,
    };
    enum class Calendar {
        Solar = 1,
        Lunar
    };

    enum class EndType {
        NoEnd = 1,  //从不停止
        EndAfter,   //多少次后停止
        EndUntil    //直到某日停止
    };

    struct RecurConfig {
        enum Calendar calendar = Calendar::Solar;
        enum Pattern recurrence_pattern = Pattern::None;   //循环频率: 小时, 天, 周, 月, 年
        enum PatternInstance pattern_instance = PatternInstance::ByDay;//计算方式: 完成后生成，到期后生成（按天算，按星期算）
        enum Week day_of_week_mask = Week::Monday;                           //周哪几天重复
        int32_t of_month = 0;                                   //月第几天/周重复, 不要直接使用
        enum Month month_of_year = Month::Jan;                              //年第几月重复
        int32_t interval = 0;                                   //间隔
        enum Skip skip = Skip::NoSkip;                                //跳过节假日,周末
        #define week_of_month  of_month                             //月第几周重复
        #define day_of_month of_month                               //月第几天重复
        bool operator==(const RecurConfig&)const = default;
    };

    Recurrence() = delete;
    explicit Recurrence(DataBase& dataBase);
    Recurrence(const Recurrence&) = default;
    Recurrence& operator=(const Recurrence&) = default;
    Recurrence(Recurrence&&) = default;
    Recurrence& operator=(Recurrence&&) = default;

    GTD_RESULT set_recur(const RecurConfig& config);
    RecurConfig get_recur_config() const;

    GTD_RESULT set_period(std::chrono::time_point<std::chrono::system_clock> start,
                          std::chrono::time_point<std::chrono::system_clock> due,
                          std::chrono::minutes lead = std::chrono::minutes(0));
    std::chrono::time_point<std::chrono::system_clock> get_start_date() const;
    std::chrono::time_point<std::chrono::system_clock> get_due_date() const;
    std::chrono::minutes get_lead_time() const;

    GTD_RESULT set_end_occur(enum EndType type, uint32_t times = 0);
    GTD_RESULT set_end_occur(enum EndType type, std::chrono::time_point<std::chrono::system_clock> date);

    enum EndType get_end_type() const;
    uint32_t get_occur_times() const;
    std::chrono::time_point<std::chrono::system_clock> get_occur_until() const;

protected:
    GTD_RESULT create() override final;
    GTD_RESULT update() override final;
    GTD_RESULT remove() override final;
    GTD_RESULT query() override final;
private:
    RecurrenceTable recurrenceTable;

    FRIEND_TEST(GTD_Recurrence, SQL);
};


#endif //MYLIFE_RECURRENCE_H
