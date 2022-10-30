#include "vector"
#include "string"
#include "cstring"
#include "iostream"
#include "fstream"
#include "linear_op.cpp"
class matrix{
public:
    std::pair<int, int> dim;
    std::vector<std::vector<double>> data;
    double EPS = 1e-8;
    matrix(){

    }
    matrix(const std::string& filename, bool labeled){
        char fname[filename.size() + 1];
        std::strcpy(fname, filename.c_str());
        std::vector<std::string> file_array;
        std::ifstream file(filename);
        std::string s;
        if(labeled)
            getline(file, s);
        while (getline(file, s))
        {
            if(*s.rbegin() != ',')
                s.push_back(',');
            std::vector<double> tok;
            std::string tmp = "";
            int p = 0;
            while(s.size() > 0){
                tmp = s.substr(0, s.find(','));
                s =  s.substr(s.find(',') + 1);
                tok.push_back(std::stod(tmp));
            }
            data.push_back(tok);
        }
        dim = {data.size(), data[0].size()};
    }

    matrix(int i){
        this -> dim = {i, i};
        this -> data = std::vector<std::vector<double>>(i, std::vector<double>(i));
        for(int x = 0; x < i; x++)
            this -> data[x][x] = 1;
    }

    matrix transpose(){
        std::vector<std::vector<double>> trans(dim.second, std::vector<double> (dim.first));
        for(int i = 0; i < dim.first; i++){
            for(int j = 0; j < dim.second; j++){
                trans[j][i] = this -> data[i][j];
            }
        }
        return (*new matrix(trans));
    }

    matrix(std::vector<std::vector<double>> vec){
        this -> dim = {vec.size(), vec[0].size()};
        this -> data = vec;
    }

    matrix inverse(){
        matrix elim = *new matrix(dim.first);
        elim.data = this->data;
        if(dim.first != dim.second)
            throw std::runtime_error("The inverse is not defined for non-square matrices!");
        matrix inv = *new matrix(dim.first);
        for(int p = 0; p < dim.first;p++) {
            bool found = false;
            for (int i = p; i < dim.first; i++) {
                if (elim.data[i][p] != 0) {
                    found = true;
                    swap(elim.data[p], elim.data[i]);
                    swap(inv.data[p], inv.data[i]);
                    break;
                }
            }
            if (!found)throw std::runtime_error("The matrix is non-invertible!");
            auto fix_to_1 = *new linear_op(1.0 / elim.data[p][p]);

            elim.data[p] = fix_to_1.apply(elim.data[p]);
            inv.data[p] = fix_to_1.apply(inv.data[p]);

            for(int i = p+1;i<dim.first;i++){
                auto add = *new linear_op((new linear_op(-1.0 * elim.data[i][p]))-> apply(elim.data[p]));
                auto add2 = *new linear_op((new linear_op(-1.0 * elim.data[i][p]))-> apply(inv.data[p]));

                elim.data[i] = add.apply(elim.data[i]);
                inv.data[i] = add2.apply(inv.data[i]);
            }
        }
        for(int p = dim.first-1; p >= 0;p--){
            for(int i = p-1; i >= 0; i--){
                auto add = *new linear_op((new linear_op(-1.0 * elim.data[i][p]))-> apply(elim.data[p]));
                auto add2 = *new linear_op((new linear_op(-1.0 * elim.data[i][p]))-> apply(inv.data[p]));

                elim.data[i] = add.apply(elim.data[i]);
                inv.data[i] = add2.apply(inv.data[i]);
            }
        }
        inv.fix_floats();
        return inv;
    }
    void fix_floats(){
        for(int i  =0 ;i < dim.first;i++) {
            for (int j = 0; j < dim.second; j++) {
                if(std::abs(this->data[i][j]) < EPS){
                    this->data[i][j] = 0;
                }
            }
        }
    }
    void print(){
        for(int i  =0 ;i < dim.first;i++)
        {
            for(int j = 0; j <dim.second; j++){
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    static matrix product(matrix a, matrix b){
        if(a.dim.second != b.dim.first){
            throw std::runtime_error("Multiplication is not defined!");
        }
        std::vector<std::vector<double>> ans (a.dim.first, std::vector<double>(b.dim.second));
        for(int i = 0; i < a.dim.first;i++){
            for(int j = 0; j < b.dim.second;j++){
                for(int k = 0; k < a.dim.second;k++)
                    ans[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
        matrix m = *new matrix(ans);
        m.fix_floats();
        return m;
    }
};
