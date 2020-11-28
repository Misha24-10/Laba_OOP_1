#include "tablecollection.h"
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
                collection[i][j] = new  TableCell (*cell);
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
                    collection[i][j] = new  TableCell (*cell);
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
    if(x > 0 && y > 0 && x < row && y < col) {
        if(collection[x][y]) {
            delete collection[x][y];
            number--;
        }
        if(oneCell) {
            collection[x][y] =new TableCell (*oneCell);
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


int TableCollection::getcount() const {
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
                    array_row.append(lable);
                }
                else{
                    lable.insert("TableCell", "None");
                    array_row.append(lable);
                }

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
        for(int i=0; i<row;i++){
            QJsonArray rowArray = arrayOfArray[i+1].toArray();
            collection[i] = new TableCell *[col];
            for(int j=0;j<col;j++){
                QJsonObject vall = rowArray[j].toObject();
                QString type = vall["TableCell"].toString();
                if (type != "None"){
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
                else{
                    collection[i][j] = nullptr;
                }

            }
        }
        cout <<"OK";
    }
    else {
        throw "read error";
    }
}

TableCollection::~TableCollection() {
    if(collection){
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
void printTableCollection(const TableCollection &table) {
    int row = table.getLength();
    int col = table.getWidth();
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++) {
            if(table.getTableCel(i,j)){
                cout << "tablecell" <<"["<< i <<"]["<< j<< "] = ";
                if(table.getTableCel(i,j)->getInt())
                    cout << table.getTableCel(i,j)->getInt() << endl;
                else
                    cout << table.getTableCel(i,j)->getString() << endl;
            }
        }
}

