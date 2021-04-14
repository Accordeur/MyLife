//
// Created by Zelonge on 2021/4/13.
//

#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include "Flag.h"

GTD_RESULT Flag::create() {
    return GTD_OK;
}

GTD_RESULT Flag::update() {
    return GTD_OK;
}

GTD_RESULT Flag::remove() {
    return GTD_OK;
}

GTD_RESULT Flag::query() {
    return GTD_OK;
}

Flag::Flag(DataBase &dataBase) : Crud(dataBase), flagTable({}) {
    flagTable.flag_id = ID_UNINIT;
    flagTable.uuid = boost::uuids::to_string(boost::uuids::random_generator()());
    flagTable.note_id = ID_UNINIT;
}
