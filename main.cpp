#include "matrix.hpp"
#include <iostream>
#include <map>
#include <array>

int main(){

    std::map<std::array<std::size_t, 2>, double, array_cmp<row_wise>> data;
    for (size_t i=0; i<6; i++){
        for (size_t j=0; j<7; j++){
            data.insert(std::pair<std::array<std::size_t, 2>, double>({i,j}, i*(j+1)));
        }
    }

    std::array<std::size_t, 2> a{0,3};
    std::array<std::size_t, 2> b{1,0};
    auto itlow = data.lower_bound(a);
    auto itup = data.upper_bound(b);

    for (auto it=itlow; it != itup; it++){
        std::cout << it->first[0]<<" "<<it->first[1] << " " << it->second << std::endl;
    }

    Algebra::Matrix<double, column_wise> M;
    std::string fname = "lnsp_131.mtx";
    M.read(fname);

    //std::cout<<M[{9,1}]<<std::endl;

    return 0;
};