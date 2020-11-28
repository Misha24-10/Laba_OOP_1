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

    string getString() const;
    float getInt() const;
    void setint(const float int_box_);
    void setstr(const string text_box_);

private:
    string text_box;
    float float_box;
    bool is_float;

};

#endif // E_H
