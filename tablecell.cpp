#include "tablecell.h"
#include <string>

TableCell::TableCell(const string text_box) {
    this->text_box = text_box;
    this->float_box = 0;
    this->is_float = false;
}

TableCell::TableCell(const float int_box) {
    this->float_box = int_box;
    this->text_box = "";
    this->is_float = true;
}

TableCell::TableCell() {
    this->float_box = 0;
    this->text_box = "";
    this->is_float = false;
}

TableCell::TableCell(const TableCell &other) {
    if(other.is_float){
        this->float_box = other.float_box;
        this->text_box = "";
        this->is_float = true;
    }
    else{
        this->text_box = other.text_box;
        this->float_box = 0;
        this->is_float = false;
    }
}



string TableCell::getString() const {
        return this->text_box;
}

float TableCell::getInt() const {
    return this->float_box;
}




void TableCell::setint(const float int_box_) {
    this->float_box = int_box_;
    this->text_box = "";
    this->is_float = true;
}

void TableCell::setstr(const string text_box_) {
    this->float_box = 0;
    this->text_box = text_box_;
    this->is_float = false;

}
