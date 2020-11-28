#include "tablecollection.h"
#include "tablecellfunction.h"
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <fstream>
#include <QFile>

TableCollection::TableCollection(const int _row, const int _col) {
    if( _col > 0 && _row > 0) {
        collection = new TableCell **[_row];
        for(int i=0;i<_row;i++){
            collection[i] = new TableCell *[_col];
            for(int j=0;j<_col;j++){
                collection[i][j] = nullptr;
            }
        }
        row = _row;
        col = _col;
        number = 0;
    }
    else
        throw "Input error";


}

TableCollection::TableCollection(const TableCollection &father) {

    if(collection) {
        this->~TableCollection();
    }
    row = father.row;
    col = father.col;
    number  =father.number;
    collection = new TableCell **[row];
    for(int i = 0;i < row;i++){
        collection[i] = new TableCell *[col];
        for (int j = 0; j <col; j++)
            if (father.getTableCel(i,j)) {

                TableCell* cell = father.getTableCel(i,j);
                if( cell->getType() == 0)
                    collection[i][j] = new  TableCell (*cell);
                else{
                    TableCellFunction *cellFunc = (TableCellFunction*)cell;
                    collection[i][j] = new TableCellFunction(*cellFunc);
                }
            }
            else
                collection[i][j] = nullptr;

    }
}

TableCollection & TableCollection::operator=(const TableCollection &other) {

    if(this == &other) {
        return *this;
    }
    else {

        if(this->collection) {
            this->~TableCollection();
        }

        row = other.row;
        col = other.col;
        number  =other.number;
        collection = new TableCell **[row];
        for(int i = 0;i < row;i++){
            collection[i] = new TableCell *[col];
            for (int j = 0; j <col; j++)
                if (other.getTableCel(i,j)) {

                    TableCell* cell = other.getTableCel(i,j);
                    if( cell->getType() == 0)
                        collection[i][j] = new  TableCell (*cell);
                    else{
                        TableCellFunction *cellFunc = (TableCellFunction*)cell;
                        collection[i][j] = new TableCellFunction(*cellFunc);
                    }
                }
                else
                    collection[i][j] = nullptr;

        }
        return *this;
    }
}

TableCell* TableCollection::getTableCel(const int x, const int y) const {
    if(x >= 0 && y >= 0 && x < row && y < col) {
        return collection[x][y];
    }
    else
        throw " out of index";
}

void TableCollection::setTableCel(const int x, const int y, TableCell *oneCell) {
    if(x >= 0 && y >= 0 && x < row && y < col) {
        if(collection[x][y]) {
            delete collection[x][y];
            number--;
        }
        if(oneCell) {
        if (oneCell->getType() == 0)
            collection[x][y] =new TableCell (*oneCell);
        else {
            TableCellFunction *cellFunc = (TableCellFunction*)oneCell;
            collection[x][y] = new TableCellFunction(*cellFunc);
        }
            number++;
        }
        else
            collection[x][y] = nullptr;
    }
    else
        cout << "erroer out of range";
}

float TableCollection::summ(const int col_) const {
    if (collection) {
        float summ = 0;
        if(col >0 && col_ < col) {
            for(int i=0;i<row;i++) {
                if(collection[i][col_])
                    summ +=collection[i][col_]->getInt();
            }
        }
        return summ;
    }
    else{
        throw "summ error";
    }
}

float TableCollection::srMean(const int col_) const {
    if (collection){
        float summ = 0;
        if(col >0 && col_ < col) {
            for(int i=0;i<row;i++) {
                if(collection[i][col_])
                    summ +=collection[i][col_]->getInt();
            }
        }
        return summ/row;
    }
    else{
        throw "srMean error";
    }

}


int TableCollection::getCount() const {
    return number;
}
int TableCollection::getLength() const {
    return row;
}
int TableCollection::getWidth() const {
    return col;
}

void TableCollection::writeInFile(const QString &fileName) const {
    if(collection) {
        QFile file(fileName);
        file.open(QFile::WriteOnly);
        QJsonArray arrayOfArray;
        QJsonObject sizeOfArray;
        sizeOfArray.insert("row",row);
        sizeOfArray.insert("col",col);
        arrayOfArray.append(sizeOfArray);

        for(int i=0;i<row;i++) {
            QJsonArray array_row;
            for(int j=0;j<col;j++) {
                QJsonObject lable;
                if(collection[i][j]) {
                    lable.insert("String:", collection[i][j]->getString().c_str());
                    lable.insert("Int:", collection[i][j]->getInt());
                    if( collection[i][j]->getType() == 1)
                    {
                       lable.insert("Type", "TableCellFunction");
                       TableCellFunction* lableFunc = (TableCellFunction*)collection[i][j];
                       lable.insert("i_1",lableFunc->geti_1());
                       lable.insert("j_1",lableFunc->getj_1());
                       lable.insert("i_2",lableFunc->geti_2());
                       lable.insert("j_2",lableFunc->getj_2());
                    }
                    else
                    {
                       lable.insert("Type", "TableCell");
                    }
                }

                else
                    lable.insert("Type", "None");
                    array_row.append(lable);


            }
            arrayOfArray.append(array_row);
        }
        QJsonDocument doc;
        doc.setArray(arrayOfArray);
        file.write(doc.toJson());
        file.close();
    }
    else
        cout << "collection is empty";
}



void  TableCollection::readFromFile(const QString &fileName) {
    QFile file(fileName);
    if(file.open(QFile::ReadOnly)) {
        QJsonDocument readDoc;
        readDoc = QJsonDocument::fromJson(file.readAll());
        QJsonArray arrayOfArray = readDoc.array();
        this->~TableCollection();

        QJsonObject firstObj = arrayOfArray[0].toObject();
        this->row = firstObj["row"].toInt();
        this->col = firstObj["col"].toInt();
        TableCollection collect(row,col);
        collection = new TableCell **[row];
        for(int i=0; i<row;i++) {
            QJsonArray rowArray = arrayOfArray[i+1].toArray();
            collection[i] = new TableCell *[col];
            for(int j=0;j<col;j++) {
                QJsonObject vall = rowArray[j].toObject();
                QString type = vall["Type"].toString();
                if (type == "TableCell"){
                    if ( type == "TableCell")
                    {
                        string collStrValue = vall["String:"].toString().toStdString();
                        float collFloatValue = (float)vall["Int:"].toDouble();
                        if( collStrValue ==""){
                            TableCell one(collFloatValue);
                            collection[i][j] = new TableCell (one);
                            number++;

                        }
                        else{
                            TableCell one(collStrValue);
                            collection[i][j] = new TableCell (one);
                            number++;
                        }
                    }
                }
                else{
                    collection[i][j] = nullptr;
                }

            }
        }
        for(int i=0; i<row;i++) {
            QJsonArray rowArray = arrayOfArray[i+1].toArray();

            for(int j=0;j<col;j++) {
                QJsonObject vall = rowArray[j].toObject();
                QString type = vall["Type"].toString();
                    if ( type == "TableCellFunction")
                    {
                        string collStrValue = vall["String:"].toString().toStdString();
                        float collFloatValue = (float)vall["Int:"].toDouble();
                        int i_1 = vall["i_1"].toInt();
                        int j_1 = vall["j_1"].toInt();
                        int i_2 = vall["i_2"].toInt();
                        int j_2 = vall["j_2"].toInt();

                        if( collStrValue =="") {
                            TableCellFunction  one((*this) ,*collection[i_1][j_1],*collection[i_2][j_2]);
                            one.setint(collFloatValue);
                            one.setIndex();
                            one.setIndexi_1(i_1);
                            one.setIndexi_2(i_2);
                            one.setIndexj_1(j_1);
                            one.setIndexj_2(j_2);
                            collection[i][j] = new TableCellFunction (one);
                            number++;

                        }
                        else{
                            TableCellFunction  one((*this) ,*(this->getTableCel(i_1,j_1)),*(this->getTableCel(i_2,j_2)));
                            one.setstr(collStrValue);
                            collection[i][j] = new TableCellFunction (one);
                            number++;
                        }


                    }

                else{
                }

            }
        }
    }
    else {
        throw "read error";
    }
}


TableCollection::~TableCollection() {
    if(collection) {
        for(int i=0;i<row;i++) {
            for(int j=0; j<col;j++)
                if(collection[i][j]) {
                    delete collection[i][j];
                    collection[i][j] = nullptr;
                }
            delete [] collection[i];
            collection[i] = nullptr;
        }
        delete [] collection;
        collection = nullptr;
        number = 0;
    }

}
bool TableCollection::isequal(const TableCollection &table) {
    if( row!=table.getLength() || col!=table.getWidth())
        return false;
    for (int i=0; i<row; i++)
        for (int j=0; j<col; j++) {
            TableCell * firCell = collection[i][j];
            TableCell * secCell = table.getTableCel(i,j);
            if((firCell != secCell) &&(not firCell || not secCell))
                return false;
            if( firCell && secCell) {
                if(firCell->getInt() != secCell->getInt())
                    return false;
                if(firCell->getString() != secCell->getString())
                    return false;

            }
        }
    return true;
}
// TODO
void printTableCollection(const TableCollection &table) {
    int row = table.getLength();
    int col = table.getWidth();
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++) {
            if(table.getTableCel(i,j))
            {
                cout << "tablecell" <<"["<< i <<"]["<< j<< "] = ";
                if( table.getTableCel(i,j)->getType() == 0){
                    if(table.getTableCel(i,j)->getInt())
                        cout << table.getTableCel(i,j)->getInt() << endl;
                    else
                        cout << table.getTableCel(i,j)->getString() << endl;
                }
                else{
                    std::cout << "Function";
                }
            }
        }
}

