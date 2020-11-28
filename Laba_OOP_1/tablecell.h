#ifndef E_H
#define E_H
#include <string>

using namespace std;

class TableCell {
public:
    TableCell(const string text_box);
    TableCell(const float int_box);
    TableCell(const TableCell &other);
    TableCell();
    virtual ~TableCell();

    void printParams();
    virtual int getType() const;


    string getString() const;
    float getInt() const;
    void setint(const float int_box_);
    void setstr(const string text_box_);
    bool is_float;

private:
    string text_box;
    float float_box;

};

#endif // E_H
