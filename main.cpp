#include "polyreg.cpp"
int main() {
    //edit path
    string path = "";
    polyreg poly = *new polyreg(path, 1, false, 4);
    poly.X.print();
    poly.y.print();
    poly.fit();
}
