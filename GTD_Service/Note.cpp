//
// Created by Zelonge on 2021/4/14.
//

#include "Note.h"
Note::Note(DataBase &dataBase) : Crud(dataBase), noteTable({}) {
    noteTable.note_id = ID_UNINIT;
}

GTD_RESULT Note::create() {
    if(noteTable.note_id != ID_UNINIT || noteTable.text.empty()) {
        return GTD_PARA_INVALID;
    }
    noteTable.note_id = datebase.sql().insert(noteTable);
    return GTD_OK;
}

GTD_RESULT Note::update() {
    if(noteTable.note_id == ID_UNINIT || noteTable.text.empty()) {
        return GTD_PARA_INVALID;
    }
    datebase.sql().update(noteTable);
    return GTD_OK;
}

GTD_RESULT Note::remove() {
    using namespace sqlite_orm;
    if(noteTable.note_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }
    datebase.sql().remove_all<NoteTable>(where(is_equal(&NoteTable::note_id, noteTable.note_id)));
    noteTable.note_id = ID_UNINIT;
    noteTable.text.clear();
    return GTD_OK;
}

GTD_RESULT Note::query() {
    using namespace sqlite_orm;
    if(noteTable.note_id == ID_UNINIT) {
        return GTD_PARA_INVALID;
    }

    auto note = datebase.sql().get_all<NoteTable>(where(is_equal(&NoteTable::note_id, noteTable.note_id)));
    if(note[0].note_id != noteTable.note_id) {
        return GTD_PARA_INVALID;
    }
    noteTable = note[0];
    return GTD_OK;
}

std::string Note::get_note() const {
    return noteTable.text;
}

void Note::set_note(std::string note) {
    noteTable.text = note;
}

int64_t Note::get_id() const {
    return noteTable.note_id;
}

void Note::set_id(int64_t id) {
    noteTable.note_id = id;
}

