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
    //Hourly, Daily, Weekly, Monthly, Yearly
    enum class Pattern: int32_t {
        None = 0,
        Minutely = 1,
        Hourly = 2,
        Daily,
        Weekly,
        Monthly,
        Yearly
    };

    enum class PatternInstance: int32_t {
        ByDay,
        ByWeekday,
        ByComplete
    };

    enum class Week: int32_t {
        None = 0x0,
        Monday = 0x1,
        Tuesday = 0x2,
        Wednesday = 0x4,
        Thursday = 0x8,
        Friday = 0x10,
        Saturday = 0x20,
        Sunday = 0x40,
        FirstDay = 0x80,
        LastDay = 0x100
    };

    enum class OrdinalWeek: int32_t {
        None = 0,
        First = 1,
        Second,
        Third,
        Fourth,
        Last
    };
    enum class Month: int32_t {
        None = 0,
        Jan = 1,
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

    enum class Skip: int32_t {
        NoSkip = 0,
        Holiday = 1,
        Weekend = 2,
    };
    enum class Calendar: int32_t {
        Solar = 1,
        Lunar
    };

    enum class EndType: int32_t {
        NoEnd = 1,  //从不停止
        EndAfter,   //多少次后停止
        EndUntil    //直到某日停止
    };

    struct RecurConfig {
        enum Calendar calendar = Calendar::Solar;
        enum Pattern recurrence_pattern = Pattern::None;   //循环频率: 小时, 天, 周, 月, 年
        enum PatternInstance pattern_instance = PatternInstance::ByDay;//计算方式: 完成后生成，到期后生成（按天算，按星期算）
        enum Week day_of_week_mask = Week::None;                           //周哪几天重复
        enum Month month_of_year = Month::None;                              //年第几月重复
        int32_t interval = 0;                                   //间隔
        enum Skip skip = Skip::NoSkip;                                //跳过节假日,周末
        enum OrdinalWeek week_of_month = OrdinalWeek::None;                            //月第几周重复
        int32_t day_of_month = 0;                               //月第几天重复
        //int32_t of_month = 0;                                   //月第几天/周重复, 被day_of_month，week_of_month替代
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

    GTD_RESULT completed_current();
    bool is_ended(std::chrono::time_point<std::chrono::system_clock> time) const;
    std::chrono::time_point<std::chrono::system_clock> get_next(std::chrono::time_point<std::chrono::system_clock> start) const;

    std::vector<std::chrono::time_point<std::chrono::system_clock>>
    occur_in(std::chrono::time_point<std::chrono::system_clock> start,
                        std::chrono::time_point<std::chrono::system_clock> due) const;

protected:
    GTD_RESULT create() override final;
    GTD_RESULT update() override final;
    GTD_RESULT remove() override final;
    GTD_RESULT query() override final;
private:
    GTD_RESULT checkRecurConfig(const RecurConfig& config) const;
    RecurrenceTable recurrenceTable;

    FRIEND_TEST(GTD_Recurrence, SQL);
};


#endif //MYLIFE_RECURRENCE_H
