// TextBuffer.cpp
#include "TextBuffer.hpp"
#include <cassert>

TextBuffer::TextBuffer() {
    cursor = data.end();
    row = 1;
    column = 0;
    index = 0;
}

bool TextBuffer::forward() {
    if (cursor == data.end()){
        return false;}

    if(*cursor == '\n') {
        row++;
        column = 0;
    }
    else {
        column++;
    }
    cursor++;
    index++;
    return true;
}

bool TextBuffer::backward() {
    if (cursor == data.begin()){
        return false;}
    --cursor;
    --index;
    if (*cursor == '\n') {
        row--;
        column = compute_column();
    }
    else {
        column--;
    }
    return true;
}


void TextBuffer::insert(char c) {
    cursor = data.insert(cursor, c);
    cursor++;
    if (c == '\n') {
        row++;
        column = 0;
    }
    else {
        column++;
    }
    index++;
}


bool TextBuffer::remove() {
    if (cursor == data.end()) {
        return false;
    }

    cursor = data.erase(cursor);

    row = 1;
    index = 0;
    for (Iterator it = data.begin(); it != cursor; ++it) {
        if (*it == '\n') {
            ++row;
        }
        ++index;
    }
    column = compute_column();
    return true;
}

void TextBuffer::move_to_row_start() {
    while (cursor != data.begin()) {
        Iterator prev = cursor;
        --prev;
        if (*prev == '\n') {
            break;
        }
        cursor = prev;
        --index;
    }

    column = 0;
}

void TextBuffer::move_to_row_end() {
    while (cursor != data.end() && *cursor != '\n') {
        ++cursor;
        ++index;
        ++column;
    }
}

void TextBuffer::move_to_column(int new_column) {
    move_to_row_start();
    column = 0;

    while (cursor != data.end() && *cursor != '\n' && column < new_column) {
        ++cursor;
        ++index;
        ++column;
    }
}

bool TextBuffer::up() {
    if (row == 1){
        return false;}
    int target_column = column;
    move_to_row_start();
    cursor--;
    index--;
    row--;
    move_to_column(target_column);
    return true;
}



bool TextBuffer::down() {
    int target_column = column;
    move_to_row_end();
    if (cursor == data.end()) {
        move_to_column(target_column);
        return false;
    }
    cursor++;
    index++;
    row++;
    column = 0;
    while (cursor != data.end() && *cursor != '\n' && column < target_column) {
        ++cursor;
        ++index;
        ++column;
    }
    return true;
}


bool TextBuffer::is_at_end() const {
    return cursor == data.end();
}


char TextBuffer::data_at_cursor() const {
    assert(cursor != data.end());
    return *cursor;
}

int TextBuffer::get_row() const {
    return row;
}

int TextBuffer::get_column() const {
    return column;
}

int TextBuffer::get_index() const {
    return index;
}

int TextBuffer::size() const {
    return static_cast<int>(data.size());
}

std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
}


int TextBuffer::compute_column() const {
    int col = 0;
    Iterator it = cursor;
    while (it != data.begin()) {
        Iterator prev = it;
        --prev;
        if (*prev == '\n'){
            break;}
        ++col;
        it = prev;
    }
    return col;
}
