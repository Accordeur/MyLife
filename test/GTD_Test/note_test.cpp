//
// Created by Zelonge on 2021/4/14.
//

#include <tuple>
#include <gtest/gtest.h>
#include "../../GTD_Service/Note.h"

TEST(GTD_Note, Init)
{
    DataBase dataBase("./sqlite.db");
    Note note(dataBase);

    EXPECT_EQ(note.get_id(), ID_UNINIT);
    EXPECT_TRUE(note.get_note().empty());
}

TEST(GTD_Note, SQL) {
    using namespace sqlite_orm;
    DataBase dataBase("./sqlite.db");
    dataBase.sql().remove_all<NoteTable>();
    Note note(dataBase);

    note.set_note("Note Test");
    EXPECT_EQ(note.create(), GTD_OK);
    EXPECT_NE(note.get_id(), ID_UNINIT);

    auto id = note.get_id();
    Note note1(dataBase);
    note1.set_id(id);
    note1.query();
    EXPECT_EQ(note1.get_note(), note.get_note());

    dataBase.sql().remove_all<NoteTable>();
    for(int i = 0; i < 1000; i++) {
        Note note2(dataBase);
        note2.set_note("Note Test");
        EXPECT_EQ(note2.create(), GTD_OK);
    }
    auto arr = dataBase.sql().get_all<NoteTable>(where(c(&NoteTable::note_id) < 10000));
    EXPECT_EQ(arr.size(), 1000);
}