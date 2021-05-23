//
// Created by Zelonge on 2021/4/13.
//

#include "Recurrence.h"
#include <chrono>
#include <date/date.h>

using namespace sqlite_orm;

GTD_RESULT Recurrence::create() {
    if(recurrenceTable.recurrence_id != ID_UNINIT) {
        return GTD_ID_HAS_EXIST;
    }
    recurrenceTable.recurrence_id = database.sql().insert(recurrenceTable);
    return GTD_OK;
}

GTD_RESULT Recurrence::update() {
    if(recurrenceTable.recurrence_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }

    database.sql().update(recurrenceTable);
    return GTD_OK;
}

GTD_RESULT Recurrence::remove() {
    if(recurrenceTable.recurrence_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    database.sql().remove_all<RecurrenceTable>(where(c(&RecurrenceTable::recurrence_id) == recurrenceTable.recurrence_id));
    recurrenceTable.recurrence_id = ID_UNINIT;
    return GTD_OK;
}

GTD_RESULT Recurrence::query() {
    if(recurrenceTable.recurrence_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    auto all = database.sql().get_all<RecurrenceTable>(where(c(&RecurrenceTable::recurrence_id) == recurrenceTable.recurrence_id));
    if(all.empty()) {
        return GTD_PARA_INVALID;
    }
    recurrenceTable = all[0];
    return GTD_OK;
}

Recurrence::Recurrence(DataBase &dataBase) : Crud(dataBase), recurrenceTable({}) {
    recurrenceTable.recurrence_id = ID_UNINIT;
    set_recur(RecurConfig());
}


GTD_RESULT Recurrence::set_recur(const Recurrence::RecurConfig &config) {
    //合法性检查
    GTD_RESULT result = checkRecurConfig(config);
    if(result != GTD_OK) {
        return result;
    }
    recurrenceTable.calendar = static_cast<int32_t>(config.calendar);
    recurrenceTable.recurrence_pattern = static_cast<int32_t>(config.recurrence_pattern);
    recurrenceTable.pattern_instance = static_cast<int32_t>(config.pattern_instance);
    recurrenceTable.day_of_week_mask = static_cast<int32_t>(config.day_of_week_mask);
    recurrenceTable.of_month = config.pattern_instance == PatternInstance::ByDay ?
            config.day_of_month : static_cast<int32_t>(config.week_of_month);
    recurrenceTable.month_of_year = static_cast<int32_t>(config.month_of_year);
    recurrenceTable.interval = config.interval;
    recurrenceTable.skip = static_cast<int32_t>(config.skip);
    return GTD_OK;
}

Recurrence::RecurConfig Recurrence::get_recur_config() const {
    RecurConfig config;
    config.calendar = static_cast<Calendar>(recurrenceTable.calendar);
    config.recurrence_pattern = static_cast<Pattern>(recurrenceTable.recurrence_pattern);
    config.pattern_instance = static_cast<PatternInstance>(recurrenceTable.pattern_instance);
    config.day_of_week_mask = static_cast<Week>(recurrenceTable.day_of_week_mask);
    if(config.pattern_instance == PatternInstance::ByDay) {
        config.day_of_month = recurrenceTable.of_month;
    } else {
        config.week_of_month = static_cast<OrdinalWeek>(recurrenceTable.of_month);
    }

    config.month_of_year = static_cast<Month>(recurrenceTable.month_of_year);
    config.interval = recurrenceTable.interval;
    config.skip = static_cast<Skip>(recurrenceTable.skip);
    return config;
}

GTD_RESULT Recurrence::set_period(const DateTime& start, const DateTime& end, bool lead) {
    using namespace std::chrono;
    if(start > end) {
        return GTD_PARA_INVALID;
    }

    recurrenceTable.pattern_start_date = date::make_zoned(date::current_zone(), start.get_local_time_milliseconds())
            .get_sys_time().time_since_epoch().count();
    recurrenceTable.pattern_end_date = date::make_zoned(date::current_zone(), end.get_local_time_milliseconds())
            .get_sys_time().time_since_epoch().count();

    if(lead) {
        recurrenceTable.hourly_delta = recurrenceTable.pattern_end_date - recurrenceTable.pattern_start_date;
    } else {
        recurrenceTable.hourly_delta = 0;
    }

    return GTD_OK;
}

Recurrence::DateTime Recurrence::get_start_date() const {
    using namespace std::chrono;
    auto start_mil = milliseconds(recurrenceTable.pattern_start_date);
    auto zone_time = date::make_zoned(date::current_zone(), date::sys_time<milliseconds>(start_mil));
    auto day = date::year_month_day(floor<date::days>(zone_time.get_local_time()));
    auto time = date::make_time(floor<date::days>(zone_time.get_local_time()) - zone_time.get_local_time());

    return DateTime(day, date::time_of_day<seconds>(duration_cast<seconds>(time.to_duration())));
}

Recurrence::DateTime Recurrence::get_due_date() const {

    using namespace std::chrono;
    auto end_mil = milliseconds(recurrenceTable.pattern_end_date);
    auto zone_time = date::make_zoned(date::current_zone(), date::sys_time<milliseconds>(end_mil));
    auto day = date::year_month_day(floor<date::days>(zone_time.get_local_time()));
    auto time = date::make_time(floor<date::days>(zone_time.get_local_time()) - zone_time.get_local_time());

    return DateTime(day, date::time_of_day<seconds>(duration_cast<seconds>(time.to_duration())));
}

std::chrono::seconds Recurrence::get_lead_time() const {
    using namespace std::chrono;
    return duration_cast<seconds>(milliseconds(recurrenceTable.pattern_end_date - recurrenceTable.pattern_start_date));
}

GTD_RESULT Recurrence::set_end_occur_times(EndType type, uint32_t times) {
    if(type != EndType::EndAfter && type != EndType::NoEnd) {
        return GTD_PARA_INVALID;
    }

    recurrenceTable.end_type = static_cast<int32_t>(type);
    recurrenceTable.occurrences = times;
    return GTD_OK;
}

GTD_RESULT
Recurrence::set_end_occur_day(const Recurrence::DateTime& date) {
    using namespace std::chrono;

    recurrenceTable.end_type = static_cast<int32_t>(EndType::EndUntil);
    recurrenceTable.use_completion_date = date::make_zoned(date::current_zone(), date.get_local_time_milliseconds())
            .get_sys_time().time_since_epoch().count();
    return GTD_OK;
}

Recurrence::EndType Recurrence::get_end_type() const {
    return static_cast<EndType>(recurrenceTable.end_type);
}

uint32_t Recurrence::get_occur_times() const {
    return recurrenceTable.occurrences;
}

Recurrence::DateTime Recurrence::get_occur_until() const {
    using namespace std::chrono;
    auto zone_time =  date::make_zoned(date::current_zone(), date::sys_time<milliseconds>(milliseconds(recurrenceTable.use_completion_date)));
    return DateTime(date::year_month_day(floor<date::days>(zone_time.get_local_time())), {});
}

GTD_RESULT Recurrence::completed_current() {
    return GTD_ID_HAS_EXIST;
}

GTD_RESULT Recurrence::checkRecurConfig(const Recurrence::RecurConfig &config) const {

    switch(config.recurrence_pattern) {
        //enum class Pattern: int32_t {
        //        None = 0,
        //        Hour = 1,
        //        Daily,
        //        Weekly,
        //        Monthly,
        //        Yearly
        //    };
        case Pattern::None: {
            return GTD_PARA_INVALID;
        }
        case Pattern::Hourly:
        case Pattern::Daily: {
            if(config.interval <= 0 || config.interval > 31) {
                return GTD_PARA_INVALID;
            }
            return GTD_OK;
        }
        case Pattern::Weekly: {
            if(config.interval <= 0 || config.interval > 52) {
                return GTD_PARA_INVALID;
            }
            if(config.day_of_week_mask == Week::None && config.pattern_instance != PatternInstance::ByComplete) {
                return GTD_PARA_INVALID;
            }
            return GTD_OK;
        }
        case Pattern::Monthly: {
            if(config.interval <= 0 || config.interval > 12) {
                return GTD_PARA_INVALID;
            }
            if(config.pattern_instance == PatternInstance::ByDay) {
                if(config.day_of_month <= 0 || config.day_of_month >= 31) {
                    return GTD_PARA_INVALID;
                }
            } else if(config.pattern_instance == PatternInstance::ByWeekday) {
                if(config.week_of_month == OrdinalWeek::None || config.day_of_week_mask == Week::None) {
                    return GTD_PARA_INVALID;
                }
            } else {
                if(config.pattern_instance != PatternInstance::ByComplete) {
                    return GTD_PARA_INVALID;
                }
            }
            return GTD_OK;
        }
        case Pattern::Yearly: {
            if(config.interval <= 0) {
                return GTD_PARA_INVALID;
            }
            if(config.pattern_instance == PatternInstance::ByDay) {
                if(config.month_of_year == Month::None || config.day_of_month <= 0 || config.day_of_month > 31) {
                    return GTD_PARA_INVALID;
                }
            } else if(config.pattern_instance == PatternInstance::ByWeekday) {
                if(config.month_of_year == Month::None || config.week_of_month == OrdinalWeek::None
                    || config.day_of_week_mask == Week::None) {
                    return GTD_PARA_INVALID;
                }
            } else {
                if(config.pattern_instance != PatternInstance::ByComplete) {
                    return GTD_PARA_INVALID;
                }
            }
            return GTD_OK;
        }
        default: {
            return GTD_PARA_INVALID;
        }
    }
    return GTD_OK;
}

Recurrence::DateTime Recurrence::get_next(const Recurrence::DateTime& time) const {
    using namespace std::chrono;
    if(is_ended(time)) {
        return DateTime({});
    }
    //ToDO:

    auto end_date = date::make_zoned(date::current_zone(), date::sys_time<milliseconds>(milliseconds(recurrenceTable.pattern_end_date)));
    auto start_date = date::make_zoned(date::current_zone(), date::sys_time<milliseconds>(milliseconds(recurrenceTable.pattern_start_date)));

    if(time.get_local_time_milliseconds() <= end_date.get_local_time()) {
        auto day = date::year_month_day(floor<date::days>(end_date.get_local_time()));
        return DateTime(day, date::time_of_day<seconds>(duration_cast<seconds>(end_date.get_local_time() - date::local_days(day))));
    }

    auto config = get_recur_config();

    if(config.pattern_instance == PatternInstance::ByComplete) {
        return DateTime({});
    }
    switch (config.recurrence_pattern) {
        case Pattern::None: {
            return DateTime({});
        }
        case Pattern::Minutely: {
            auto interval = minutes(config.interval);
            auto mod = (time.get_local_time_milliseconds() - end_date.get_local_time()) % interval;

            if(mod == minutes(0)) {
                return time;
            } else {
                auto result = time.get_local_time_milliseconds() + (interval - mod);
                return DateTime::from_local_time(result);
            }
        }
        case Pattern::Hourly: {
            auto interval = hours(config.interval);
            auto mod = (time.get_local_time_milliseconds() - end_date.get_local_time()) % interval;

            if(mod == hours(0)) {
                return time;
            } else {
                auto result = time.get_local_time_milliseconds() + (interval - mod);
                return DateTime::from_local_time(result);
            }
        }
        case Pattern::Daily: {
            auto interval = date::days(config.interval);
            auto mod = (time.get_local_time_milliseconds() - end_date.get_local_time()) % interval;

            if(mod == date::days(0)) {
                return time;
            } else {
                auto result = time.get_local_time_milliseconds() + (interval - mod);
                return DateTime::from_local_time(result);
            }
            return DateTime({});
        }
        case Pattern::Weekly: {
            if(config.pattern_instance != PatternInstance::ByWeekday || config.day_of_week_mask == Week::None) {
                return DateTime({});
            }
            auto interval = date::weeks(config.interval);
            auto mod = (time.get_local_time_milliseconds() - end_date.get_local_time()) % interval;

            std::cout << mod << std::endl;
            if(mod == date::weeks(0)) {
                return time;
            } else {
                auto base_time = time.get_local_time_milliseconds() + (interval - mod);
                auto first_date = adjustToFirst(DateTime::from_local_time(base_time));

                if(mod < date::weeks(1)) {
                    base_time = time.get_local_time_milliseconds();
                    first_date = adjustToFirst(DateTime::from_local_time(base_time));
                }

                if(config.day_of_week_mask == Week::None) {
                    return DateTime({});
                }
                if(static_cast<int32_t>(config.day_of_week_mask) | static_cast<int32_t>(Week::Monday)) {
                    if(first_date >= time) {
                        return first_date;
                    }
                }
                if(static_cast<int32_t>(config.day_of_week_mask) | static_cast<int32_t>(Week::Tuesday)) {
                    auto result = Recurrence::DateTime(DateTime{
                        date::year_month_day(date::local_days(first_date.date) + date::days(1)), first_date.time});
                    if(result >= time) {
                        return result;
                    }
                }
                if(static_cast<int32_t>(config.day_of_week_mask) | static_cast<int32_t>(Week::Wednesday)) {
                    auto result = Recurrence::DateTime(DateTime{
                        date::year_month_day(date::local_days(first_date.date) + date::days(2)), first_date.time});
                    if(result >= time) {
                        return result;
                    }
                }
                if(static_cast<int32_t>(config.day_of_week_mask) | static_cast<int32_t>(Week::Thursday)) {
                    auto result = Recurrence::DateTime(DateTime{
                        date::year_month_day(date::local_days(first_date.date) + date::days(3)), first_date.time});
                    if(result >= time) {
                        return result;
                    }
                }
                if(static_cast<int32_t>(config.day_of_week_mask) | static_cast<int32_t>(Week::Friday)) {
                    auto result = Recurrence::DateTime(DateTime{
                        date::year_month_day(date::local_days(first_date.date) + date::days(4)), first_date.time});
                    if(result >= time) {
                        return result;
                    }
                }
                if(static_cast<int32_t>(config.day_of_week_mask) | static_cast<int32_t>(Week::Saturday)) {
                    auto result = Recurrence::DateTime(DateTime{
                        date::year_month_day(date::local_days(first_date.date) + date::days(5)), first_date.time});
                }
                if(static_cast<int32_t>(config.day_of_week_mask) | static_cast<int32_t>(Week::Sunday)) {
                    auto result = Recurrence::DateTime(DateTime{
                        date::year_month_day(date::local_days(first_date.date) + date::days(6)), first_date.time});
                    if(result >= time) {
                        return result;
                    }
                }
                return DateTime({});
            }
            return DateTime({});
        }
        case Pattern::Monthly: {

        }
        case Pattern::Yearly: {

        }
    }
    return DateTime({});
}

std::vector<Recurrence::DateTime> Recurrence::occur_in(const DateTime& start, const DateTime& end) const {
    return {};
}


bool Recurrence::is_ended(Recurrence::DateTime time) const {
    using namespace std::chrono;
    //未开启循环模式
    if(/*recurrenceTable.recurrence_id == ID_UNINIT ||*/ recurrenceTable.recurrence_pattern == static_cast<int32_t>(Pattern::None)) {
        return true;
    }
    //从不结束循环模式
    if(recurrenceTable.end_type == static_cast<int32_t>(EndType::NoEnd)) {
        return false;
    }

    //指定次数后停止
    if(recurrenceTable.end_type == static_cast<int32_t>(EndType::EndUntil)) {
        if(recurrenceTable.generated_count < recurrenceTable.occurrences) {
            return false;
        } else {
            return true;
        }
    }

    //某一日期后停止
    if(recurrenceTable.end_type == static_cast<int32_t>(EndType::EndAfter)) {

        if(date::make_zoned(date::current_zone(), floor<milliseconds>(date::local_days(time.date))).get_sys_time().time_since_epoch().count() <= recurrenceTable.use_completion_date) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

Recurrence::DateTime Recurrence::adjustToFirst(Recurrence::DateTime time) const {
    using namespace std::chrono;
    auto date = time.date;
    auto weekday = date::year_month_weekday(date::local_days(date));
    auto interval = weekday.weekday() - date::Monday;
    auto firstOfWeek = date::local_days(time.date) - interval;

    return Recurrence::DateTime(DateTime{date::year_month_day(firstOfWeek), time.time});
}

