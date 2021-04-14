//
// Created by Zelonge on 2021/4/9.
//

#include <iostream>
#include "database.h"
using namespace sqlite_orm;

DataBase::DataBase(const std::filesystem::path& path): storage(initDB(path)){
    storage.sync_schema();
    //强制sqlite需要以串行模式运行
    assign(sqlite_orm::threadsafe(), 1);
}

GTD_RESULT DataBase::create(Crud &crud) {
    return crud.create();
}

GTD_RESULT DataBase::update(Crud &crud) {
    return crud.update();
}

GTD_RESULT DataBase::remove(Crud &crud) {
    return crud.remove();
}

GTD_RESULT DataBase::query(Crud &crud) {
    return crud.query();
}

DataBase::~DataBase() {

}
