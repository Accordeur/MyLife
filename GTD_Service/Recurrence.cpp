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

GTD_RESULT Recurrence::set_period(std::chrono::time_point<std::chrono::system_clock> start,
                                  std::chrono::time_point<std::chrono::system_clock> due, std::chrono::minutes lead) {
    using namespace std::chrono;
    if(due <= start) {
        return GTD_PARA_INVALID;
    }

    recurrenceTable.pattern_start_date = time_point_cast<milliseconds>(start).time_since_epoch().count();
    recurrenceTable.pattern_end_date = time_point_cast<milliseconds>(due).time_since_epoch().count();

    recurrenceTable.hourly_delta = lead.count();
    return GTD_OK;
}

std::chrono::time_point<std::chrono::system_clock> Recurrence::get_start_date() const {
    using namespace std::chrono;
    auto start_mil = milliseconds(recurrenceTable.pattern_start_date);
    return std::chrono::time_point<std::chrono::system_clock>(start_mil);
}

std::chrono::time_point<std::chrono::system_clock> Recurrence::get_due_date() const {
    using namespace std::chrono;
    auto due_mil = milliseconds(recurrenceTable.pattern_end_date);
    return std::chrono::time_point<std::chrono::system_clock>(due_mil);
}

std::chrono::minutes Recurrence::get_lead_time() const {
    return std::chrono::minutes(recurrenceTable.hourly_delta);
}

GTD_RESULT Recurrence::set_end_occur(Recurrence::EndType type, uint32_t times) {
    if(type != EndType::EndAfter && type != EndType::NoEnd) {
        return GTD_PARA_INVALID;
    }
    recurrenceTable.end_type = static_cast<int32_t>(type);
    recurrenceTable.occurrences = times;
    return GTD_OK;
}

GTD_RESULT
Recurrence::set_end_occur(Recurrence::EndType type, std::chrono::time_point<std::chrono::system_clock> date) {
    using namespace std::chrono;
    if(type != EndType::EndUntil) {
        return GTD_PARA_INVALID;
    }
    recurrenceTable.end_type = static_cast<int32_t>(type);
    recurrenceTable.use_completion_date = time_point_cast<milliseconds>(date).time_since_epoch().count();
    return GTD_OK;
}

Recurrence::EndType Recurrence::get_end_type() const {
    return static_cast<EndType>(recurrenceTable.end_type);
}

uint32_t Recurrence::get_occur_times() const {
    return recurrenceTable.occurrences;
}

std::chrono::time_point<std::chrono::system_clock> Recurrence::get_occur_until() const {
    using namespace std::chrono;
    return time_point<system_clock>(milliseconds(recurrenceTable.use_completion_date));
}

GTD_RESULT Recurrence::completed_current() {
    return GTD_ID_HAS_EXIST;
}

bool Recurrence::is_ended() const {
    //未开启循环模式
    if(recurrenceTable.recurrence_id == ID_UNINIT || recurrenceTable.recurrence_pattern == static_cast<int32_t>(Pattern::None)) {
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
        if(recurrenceTable.generated_count < recurrenceTable.occurrences) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

std::tuple<std::chrono::time_point<std::chrono::system_clock>,
        std::chrono::time_point<std::chrono::system_clock>> Recurrence::get_next_date() const {
    return std::tuple<std::chrono::time_point<std::chrono::system_clock>, std::chrono::time_point<std::chrono::system_clock>>();
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
        case Pattern::Hour:
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

