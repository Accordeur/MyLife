//
// Created by Zelonge on 2021/4/14.
//

#ifndef MYLIFE_NOTE_H
#define MYLIFE_NOTE_H

#include "database/database.h"
#include "database/tables.h"
#include <gtest/gtest.h>

class Note: protected Crud {
public:
    Note() = delete;
    explicit Note(DataBase& dataBase);
    Note(const Note&) = default;
    Note& operator=(const Note&) = default;
    Note(Note&&) = default;
    Note& operator=(Note&&) = default;

    std::string get_note() const;
    void set_note(std::string note);

    int64_t get_id() const;

protected:
    void set_id(int64_t id);
    GTD_RESULT create() override final;
    GTD_RESULT update() override final;
    GTD_RESULT remove() override final;
    GTD_RESULT query() override final;
private:
    NoteTable noteTable;

    FRIEND_TEST(GTD_Note, SQL);
};


#endif //MYLIFE_NOTE_H
