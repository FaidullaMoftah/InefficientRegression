#include "polyreg.cpp"
int main() {
    polyreg poly = *new polyreg("C:\\Users\\faidu\\Desktop\\polyreg\\data.csv", 1, false, 4);
    poly.X.print();
    poly.y.print();
    poly.fit();
}
