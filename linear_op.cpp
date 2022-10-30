#ifndef vector
#include "vector"
#endif
class linear_op{
    int type;
    double mult;
    std::vector<double> add;
public:
    linear_op(std::vector<double> vec){
        type = 0;
        add = vec;
    }

    linear_op(double i){
        type = 1;
        mult = i;
    }

    std::vector<double> apply(const std::vector<double> vec){
        std::vector<double> ans = vec;
        if(type){
            for(auto &iter : ans)
                iter *= mult;
        }
        else{
            for(int i = 0; i < add.size();i++)ans[i] += add[i];
        }
        return ans;
    };
};