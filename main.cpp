#include "matrix.hpp"
#include <iostream>
#include <map>
#include <array>
#include <fstream>
#include <chrono>

int main(){

    Algebra::Matrix<double, row_wise> M;
    std::string fname("lnsp_131.mtx");
    M.read(fname);
    int N=M.get_row();
    std::vector<double> test(N, 1.);
    
    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    std::vector<double> result1 = M*test;
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    std::cout << "Uncompressed Row-wise Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> 
    (end1 - begin1).count() << "[ns]" << std::endl;

    M.compress();
    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    std::vector<double> result2 = M*test;
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    std::cout << "Compressed Row-wise Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> 
    (end2 - begin2).count() << "[ns]" << std::endl;

    Algebra::Matrix<double, column_wise> M_col;
    M_col.read(fname);
    
    std::chrono::steady_clock::time_point begin3 = std::chrono::steady_clock::now();
    std::vector<double> result3 = M_col*test;
    std::chrono::steady_clock::time_point end3 = std::chrono::steady_clock::now();
    std::cout << "Uncompressed Column-wise Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> 
    (end3 - begin3).count() << "[ns]" << std::endl;
    
    M_col.compress();
    std::chrono::steady_clock::time_point begin4 = std::chrono::steady_clock::now();
    std::vector<double> result4 = M_col*test;
    std::chrono::steady_clock::time_point end4 = std::chrono::steady_clock::now();
    std::cout << "Compressed Column-wise Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> 
    (end4 - begin4).count() << "[ns]" << std::endl;
    
    bool equal=(result1 == result2) && (result3 == result4);
    std::cout<<equal<<std::endl;
    
    return 0;
    
};