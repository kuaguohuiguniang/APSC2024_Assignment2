#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <fstream>

enum StorageOrder{ row_wise, column_wise};

// order object that will be used in the uncompressed std::map
template<StorageOrder W>
struct array_cmp
{
    bool operator()(const std::array<std::size_t,2>& a, 
                    const std::array<std::size_t,2>& b) const{
                        return a<b;
    };
};

// order object specified for column-wise
template<>
struct array_cmp<column_wise>
{
    bool operator()
    (const std::array<std::size_t,2>& a, const std::array<std::size_t,2>& b) const{
        if (a[1] != b[1]){
            return a[1] < b[1];
        }
        else{
            return a[0] < b[0];
        }
    };
};

namespace Algebra{
    // row-wise storage matrix
    template <class T, StorageOrder W>
    class Matrix{
        private:
            std::map<std::array<std::size_t, 2>, T, array_cmp<W>> data;
            std::size_t n_row;
            std::size_t n_col;
            std::size_t nnz;
            bool is_compressed;
            T zero{0}; //default zero 
            
            // The following three vectors are for compressed matrix
            std::vector<T> data_cmp;
            std::vector<unsigned int> index;
            std::vector<unsigned int> ptr;
        
        public:
            Matrix() : n_row(0), n_col(0), nnz(0), is_compressed(false) {};

            Matrix(std::size_t rows, std::size_t cols,
                    std::map<std::array<std::size_t, 2>, T>& new_data): 
                    n_row(rows), n_col(cols){
                        for (auto it=new_data.cbegin(); it != new_data.cend(); it++){
                            data[it->first]=it->second;
                        }
            };

            inline size_t get_col(){
                return n_col;
            };

            inline size_t get_row(){
                return n_row;
            };

            void compress();

            void uncompress();

            inline bool is_compress() const {
                return is_compressed;
            };

            const T& operator[](std::array<std::size_t,2>&) const;
  
            T& operator[](std::array<std::size_t,2>&);
            
            void resize(std::size_t rows, std::size_t cols);

            void read(std::string&);

            //template <class U, StorageOrder V> friend 
            //std::vector<U> operator*(const Matrix<U, V>& M, const std::vector<U>& x);
            std::vector<T> operator*(const std::vector<T>&);
    };

    // column-wise storage matrix
    template <class T>
    class Matrix<T, column_wise>{
        private:
            std::map<std::array<std::size_t, 2>, T, array_cmp<column_wise>> data;
            std::size_t n_row;
            std::size_t n_col;
            std::size_t nnz;
            bool is_compressed;
            T zero{0};
            
            // The following three vectors are for compressed matrix
            std::vector<T> data_cmp;
            std::vector<unsigned int> index;
            std::vector<unsigned int> ptr;
        
        public:
            Matrix() : n_row(0), n_col(0), nnz(0), is_compressed(false) {};

            Matrix(std::size_t rows, std::size_t cols,
                    std::map<std::array<std::size_t, 2>, T>& new_data): 
                    n_row(rows), n_col(cols){
                        for (auto it=new_data.cbegin(); it != new_data.cend(); it++){
                            data[it->first]=it->second;
                        }
                    };

            inline size_t get_col(){
                return n_col;
            };

            inline size_t get_row(){
                return n_row;
            };

            void compress();

            void uncompress();

            inline bool is_compress() const {
                return is_compressed;
            };

            const T& operator[](std::array<std::size_t,2>&) const;
  
            T& operator[](std::array<std::size_t,2>&);
            
            void resize(std::size_t rows, std::size_t cols);
            
            void read(std::string& fname);

            //template <class U, StorageOrder V> friend 
            //std::vector<U> operator*(const Matrix<U, V>& M, const std::vector<U>& x);
            std::vector<T> operator*(const std::vector<T>&);
    };
}

#include "matrix_def.hpp"

#endif