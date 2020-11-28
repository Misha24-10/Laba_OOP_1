#include "test.h"
#include "tablecell.h"
#include "tablecollection.h"
#include "tablecellfunction.h"
#include <assert.h>
#include <iostream>

void test_1() {
    TableCell Film("movie");
    assert(Film.getInt() == 0);
    assert(Film.getString() == "movie");
    cout <<"Done"<< endl;
}

void test_2() {
    TableCell A1(100.0);
    assert(A1.getInt() == 100.0);
    assert(A1.getString() == "");
    cout <<"Done"<< endl;
    TableCell A(111);
}

void test_3() {
    TableCell A1(100);
    TableCell A3(A1);
    assert(A3.getInt() == 100);
    assert(A3.getString() == "");
    cout <<"Done"<< endl;

}

void test_4() {
    TableCell A2;
    assert(A2.getInt() == 0);
    assert(A2.getString() == "");
    cout <<"Done"<< endl;
}

void test_5() {
    TableCell Film("movie");
    Film.setint(18.0);
    assert(Film.getInt() == 18.0);
    assert(Film.getString() == "");
    cout <<"Done"<< endl;
}

void test_6() {
    TableCell Film("movie");
    Film.setstr("movie");
    assert(Film.getInt() == 0);
    assert(Film.getString() == "movie");
    cout <<"Done"<< endl;
}


void testKonstr() {
    TableCollection matr(4,4);
    for(int i=0;i<matr.getLength();i++)
        for(int j=0;j<matr.getWidth();j++){
            TableCell * cell = matr.getTableCel(i,j);
            assert(cell == nullptr);
        }
    cout <<"testKonstr done"<< endl;

}
void testKopy() {
    TableCollection matr(4,4);
    TableCell Film2(20);
    matr.setTableCel(2,2,&Film2);
    TableCollection mass(matr);
    assert(mass.isequal(matr) == true);
        cout <<"testKopy done"<< endl;

}


void testIndexValue() {
    TableCollection matr(4,4);
    TableCell Film(20);
    matr.setTableCel(2,2,&Film);
    assert(matr.getTableCel(2,2)->getInt()==Film.getInt() &&matr.getTableCel(2,2)->getString()==Film.getString());
    cout << "testIndexValue done"<< endl;

}

void testCountNumbers() {
    TableCollection matr(4,4);
    TableCell Film(20);
    TableCell Film2(20);
    matr.setTableCel(1,2,&Film);
    matr.setTableCel(2,2,&Film2);
    assert(matr.getCount() == 2);
    cout << "testCountNumbers done"<< endl;
}

void testSumm() {
    TableCollection matr(4,4);
    TableCell Film(10);
    TableCell Film2(20);
    matr.setTableCel(1,2,&Film);
    matr.setTableCel(2,2,&Film2);
    assert(matr.summ(2) == 30);
    cout << "testSumm done"<< endl;
}


void teas_inheritance(){
    TableCollection matr(4,4);
    TableCell Film(10);
    TableCell Film2(20);
    matr.setTableCel(1,2,&Film);
    matr.setTableCel(2,2,&Film2);
    TableCellFunction   mass(matr, *matr.getTableCel(1,2), *matr.getTableCel(2,2));
    TableCellFunction   mass_2(matr, *matr.getTableCel(1,2), *matr.getTableCel(2,2));
    matr.setTableCel(2,1,&mass);
    matr.setTableCel(1,3,&Film2);
    cout << mass.getSumm();
}


void testReadWrite() {
    TableCollection matr(10,10);
    TableCollection mass(5,5);
    TableCell Film(10);
    TableCell Film2(20);
    TableCell Film3(30);
    TableCell Film4("dfsdfdg");
    mass.setTableCel(1,2,&Film);
    mass.setTableCel(2,2,&Film2);
    mass.setTableCel(3,2,&Film3);
    mass.setTableCel(4,2,&Film4);

    TableCellFunction   mass_(mass, *mass.getTableCel(1,2), *mass.getTableCel(2,2));
    TableCollection A2(1,1);
    mass_.setint(213);
    mass.setTableCel(2,1,&mass_);
    mass.writeInFile("C:\\Users\\Misha\\Desktop\\C\\build-OOP_2-Desktop_Qt_5_14_2_MinGW_64_bit-Release\\sss.txt");
    A2.readFromFile("C:\\Users\\Misha\\Desktop\\C\\build-OOP_2-Desktop_Qt_5_14_2_MinGW_64_bit-Release\\sss.txt");
    A2.writeInFile("C:\\Users\\Misha\\Desktop\\C\\build-OOP_2-Desktop_Qt_5_14_2_MinGW_64_bit-Release\\ans.txt");
    cout << A2.isequal(mass) << endl;
    assert(mass.isequal(A2) == true);
    cout << "\n testReadWrite done"<< endl;
}

void testTablecell() {
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    testKonstr();
    testKopy();
    testIndexValue();
    testCountNumbers();
    testSumm();
    cout << "-----------------------------------------------" << endl;

    teas_inheritance();
    testReadWrite();
    cout << "\nAll tests are passed" << endl;
}
