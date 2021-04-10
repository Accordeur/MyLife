//
// Created by Zelonge on 2021/4/9.
//

#include "database.h"
using namespace sqlite_orm;

DataBase::DataBase(const std::filesystem::path& path): storage(initDB(path)){
    storage.sync_schema();
}
