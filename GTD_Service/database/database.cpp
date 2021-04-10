//
// Created by Zelonge on 2021/4/9.
//

#include "database.h"
using namespace sqlite_orm;

DataBase::DataBase(const std::filesystem::path& path): storage(initDB(path)){
    storage.sync_schema();
}

int32_t DataBase::create(Crud &crud) {
    return crud.create(storage);
}

int32_t DataBase::update(Crud &crud) {
    return crud.update(storage);
}

int32_t DataBase::remove(Crud &crud) {
    return crud.remove(storage);
}

int32_t DataBase::query(Crud &crud) {
    return crud.query(storage);
}
