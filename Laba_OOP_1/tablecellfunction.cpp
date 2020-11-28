#include "tablecellfunction.h"
#include "tablecollection.h"
#include "iostream"
#include "tablecell.h"

TableCellFunction::TableCellFunction(TableCollection &Table_, TableCell &first_, TableCell &last_) {
    this->first = &first_;
    this->last = &last_;
    this->Table = &Table_;
    this->setIndex();
}

TableCellFunction::TableCellFunction() : first(nullptr), last(nullptr), Table(nullptr) {
    this->setIndex();
}
TableCellFunction::TableCellFunction(TableCellFunction &fathet) {
    this->i_1 = fathet.geti_1();
    this->j_1 = fathet.getj_1();
    this->i_2 = fathet.geti_2();
    this->j_2 = fathet.getj_2();
    this->last = fathet.last;
    this->first = fathet.first;
    this->Table = fathet.Table;
}
TableCellFunction::~TableCellFunction()
{
    this->first = nullptr;
    this->last = nullptr;
    this->Table = nullptr;
    this->setIndex();
}

void TableCellFunction::printParams() {
    cout << this->getInt();
    cout << this->getString();
}
int TableCellFunction::getType() const {
    return 1;
}

float TableCellFunction::getSumm() const {
    float summ = 0;
    if(Table){
        for(int i=this->geti_1();i<this->geti_2();i++) {
            for(int j =this->getj_1();j< this->getj_2();j++) {
                if((*Table).getTableCel(i,j) &&(*Table).getTableCel(i,j)->getType() == 0)
                    summ += (*Table).getTableCel(i,j)->getInt();


            }
        }
    }
    return summ;

}

float TableCellFunction::getPr() const {
    float pr = 1;
    if(Table){
        for(int i=this->geti_1();i<this->geti_2();i++){
            for(int j =this->getj_1();j< this->getj_2();j++){
                if((*Table).getTableCel(i,j) &&(*Table).getTableCel(i,j)->getType() == 0)
                    pr *= (*Table).getTableCel(i,j)->getInt();


            }
        }
    }
    return pr;

}


float TableCellFunction::getSt() const {
    float summ = 0;
    int num = 0;
    if(Table){
        for(int i=this->geti_1();i<this->geti_2();i++) {
            for(int j =this->getj_1();j< this->getj_2();j++) {
                if((*Table).getTableCel(i,j) &&(*Table).getTableCel(i,j)->getType() == 0)
                {summ += (*Table).getTableCel(i,j)->getInt(); num++;}


            }
        }
    }
    return summ/num;

}

void TableCellFunction::setFirst(TableCell &first_) {
    this->first = &first_;
}
void TableCellFunction::setlast(TableCell &last_) {
    this->last = &last_;
}

void TableCellFunction::setTable(TableCollection &Table_) {
    this->Table = &Table_;
}

void TableCellFunction::setIndex() {
    this->i_1 = -1;
    this->i_2 = -1;
    this->j_1 = -1;
    this->j_2 = -1;
    if(Table && first && last) {
        for(int i=0; i<(*Table).getLength();i++)
            for(int j=0; j<(*Table).getWidth();j++){
                if((*Table).getTableCel(i,j) == first) { i_1 = i; j_1 = j; }
                if((*Table).getTableCel(i,j) == last) { i_2 = i; j_2 = j; }
            }
    }
}
