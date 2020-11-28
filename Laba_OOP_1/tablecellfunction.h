#ifndef TABLECELLFUNCTION_H
#define TABLECELLFUNCTION_H


#include "tablecell.h"
#include "tablecollection.h"
class TableCellFunction : public TableCell
{
public:
    TableCellFunction();
    TableCellFunction(TableCollection &Table_,TableCell &first_, TableCell &last_);
    TableCellFunction(TableCellFunction &fathet);

    virtual void printParams();
    virtual  int getType() const;

    float getSumm() const;
    float getPr() const;
    float getSt()const;

    void setFirst(TableCell &first_);
    void setlast(TableCell &last_);
    void setTable(TableCollection &Table_);
    void setIndex();
    virtual ~TableCellFunction();
    int geti_1() const { return i_1; }
    int getj_1() const { return j_1; }
    int geti_2() const { return i_2; }
    int getj_2() const { return j_2; }
    void setIndexi_1(int x) { this->i_1 = x; }
    void setIndexj_1(int x) { this->j_1 = x; }
    void setIndexi_2(int x) { this->i_2 = x; }
    void setIndexj_2(int x) { this->j_2 = x; }

private:
    TableCell *first = nullptr;
    TableCell *last = nullptr;
    TableCollection *Table = nullptr;
    int i_1, j_1;
    int i_2, j_2;

};

#endif // TABLECELLFUNCTION_H
