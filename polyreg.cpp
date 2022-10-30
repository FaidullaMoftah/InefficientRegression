#include "matrix.cpp"
class polyreg{
public:
    matrix X;
    int dependant;
    matrix y;
    int order;
    bool fitted = false;
    matrix theta;
    polyreg(std::string file, int ord, bool label = false, int Y = 0){
        std::vector<double>  yy;
        order = ord;
        matrix x = (new matrix(file, label))->transpose();
        dependant = Y - 1;
        for(int i = 0; i < x.dim.second;i++){
            yy.push_back(x.data[dependant][i]);
        }
        std::vector<std::vector<double>> yyy (1, yy);
        std::vector<double> intercept(x.dim.second, 1);
        y = matrix(yyy);
        std::vector<std::vector<double>> X_vec;
        X_vec.push_back(intercept);
        for(int i = 0;i < x.dim.first;i++){
            if(i == dependant)continue;
            std::vector<double>tmp = x.data[i];
            X_vec.push_back(tmp);
            for(int j = 1; j < order ;j++){
                for(int k = 0; k < x.dim.second;k++) {
                    tmp[k] *= x.data[i][k];
                }
                X_vec.push_back(tmp);
            }
        }

        X = *new matrix(X_vec);
        X = X.transpose();
        y = y.transpose();
    }
    void fit(){
        fitted = true;
        matrix m1 = matrix::product(X.transpose(), X);
        m1 = m1.inverse();
        m1 = matrix::product(m1, X.transpose());
        theta = matrix::product(m1, y);
        theta.print();
    }
/*
    bool predict(std:::vector<double>> x_vec){
        if(!fitted) return false;
    }
    */
};