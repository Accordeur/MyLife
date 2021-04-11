//
// Created by Zelonge on 2021/4/9.
//

#include "database.h"
using namespace sqlite_orm;

DataBase::DataBase(const std::filesystem::path& path): storage(initDB(path)){
    storage.sync_schema();
}

GTD_RESULT DataBase::create(Crud &crud) {
    return crud.create(storage);
}

GTD_RESULT DataBase::update(Crud &crud) {
    return crud.update(storage);
}

GTD_RESULT DataBase::remove(Crud &crud) {
    return crud.remove(storage);
}

GTD_RESULT DataBase::query(Crud &crud) {
    return crud.query(storage);
}

DataBase::~DataBase() {

}
