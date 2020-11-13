#ifndef TABLECOLLECTION_H
#define TABLECOLLECTION_H

#include "tablecell.h"
#include <QString>

class TableCollection
{

public:
    TableCollection(const int _row, const int _col);
    TableCollection(const TableCollection &father);

    TableCollection & operator=(const TableCollection &other);

    TableCell*  getTableCel(const int x, const int y) const;
    void setTableCel(const int x, const int y, TableCell * oneCell);

    int getLength() const;
    int getWidth() const;
    int getcount() const;

    void writeInFile(const QString &fileName)const;
    void readFromFile(const QString &fileName);

    float summ(const int col_) const;
    float srMean(const int col_) const;
    bool isequal(const TableCollection &table);
    ~TableCollection();
private:
    int row, col;
    TableCell ***collection = nullptr;
    int  number;
};
void printTableCollection(const TableCollection &table);
#endif // TABLECOLLECTION_H
