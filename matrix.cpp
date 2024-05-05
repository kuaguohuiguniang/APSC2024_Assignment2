#include "matrix.hpp"

template <class T, StorageOrder W>
void Algebra::Matrix<T, W>::compress(){
    if (is_compressed){
        return;
    }else{
        is_compressed = true;
    }

    data_cmp.resize(nnz);
    index.resize(nnz);
    ptr.resize(n_row+1);
    ptr[0]=0;

    size_t k=0;
    for (size_t i=0; i<n_row; i++){
        for (auto it=data.lower_bound({i, 0}); it != data.upper_bound({i, n_row}); it++){
            if (it->first[0] != i){
                it++;
            }
            data_cmp[k]=it->second;
            index[k] = it->first[1];
            ++k;
        }
        ptr[i+1] = k;
    }
    data.clear();
};

template <class T>
void Algebra::Matrix<T, column_wise>::compress(){
    if (is_compressed){
        return;
    }else{
        is_compressed = true;
    }

    data_cmp.resize(nnz);
    index.resize(nnz);
    ptr.resize(n_col+1);
    ptr[0]=0;
    
    size_t k=0;
    for (size_t i=0; i<n_col; i++){
        for (auto it=data.lower_bound({0, i}); it != data.upper_bound({n_col, i}); it++){
            if (it->first[1] != i){
                it++;
            }
            data_cmp[k]=it->second;
            index[k] = it->first[0];
            ++k;
        }
        ptr[i+1] = k;
    }
    data.clear();
};

template <class T, StorageOrder W>
void Algebra::Matrix<T, W>::uncompress(){
    if (!is_compressed){
        return;
    }else{
        is_compressed = false;
    }
    size_t k = 0;
    for (size_t i=0; i<n_row; i++){
        for (size_t j=0; j<ptr[i+1]-ptr[i]; j++){
            data[{i, index[k]}] = data_cmp[k];
            k++;
        }
    }

    data_cmp.clear();
    index.clear();
    ptr.clear();
};

template <class T>
void Algebra::Matrix<T, column_wise>::uncompress(){
    if (!is_compressed){
        return;
    }else{
        is_compressed = false;
    }
    size_t k = 0;
    for (size_t i=0; i<n_col; i++){
        for (size_t j=0; j<ptr[i+1]-ptr[i]; j++){
            data[{index[k], i}] = data_cmp[k];
            k++;
        }
    }

    data_cmp.clear();
    index.clear();
    ptr.clear();
};

template<class T, StorageOrder W>
const T Algebra::Matrix<T, W>::operator[](std::array<std::size_t,2>& a) const{
    if (a[0] < n_row && a[1] < n_col){
        if (!is_compressed){
            if (data.find(a)!= data.end()){
                return data[a];
            }else{
                T val{0};
                return val;
            }
        }else{
            for (size_t j=ptr[a[0]]; j<ptr[a[0]+1]; j++){
                if (index[j] == a[1]){
                    return data_cmp[j];
                }
            }
            T val{0};
            return val;
        }
    }else{
        std::cerr<<"out of range"<<std::endl;
    }
};

template<class T, StorageOrder W>
T& Algebra::Matrix<T, W>::operator[](std::array<std::size_t,2>& a){
    if (a[0] < n_row && a[1] < n_col){
        if (!is_compressed){
            return data[a];
        }else{
            for (size_t j=ptr[a[0]]; j<ptr[a[0]+1]; j++){
                if (index[j] == a[1]){
                    return data_cmp[j];
                }
            }
            std::cerr<<"can't change compressed zero value"<<std::endl;
        }
    }else{
        std::cerr<<"out of range"<<std::endl;
    }
};

template<class T>
const T Algebra::Matrix<T, column_wise>::operator[](std::array<std::size_t,2>& a) const{
    if (a[0] < n_row && a[1] < n_col){
        if (!is_compressed){
            if (data.find(a) != data.end()){
                return data[a];
            }else{
                T val{0};
                return val;
            }
        }else{
            for (size_t j=ptr[a[1]]; j<ptr[a[1]+1]; j++){
                if (index[j] == a[0]){
                    return data_cmp[j];
                }
            }
            T val{0};
            return val;
        }
    }else{
        std::cerr<<"out of range"<<std::endl;
    }
};

template<class T>
T& Algebra::Matrix<T, column_wise>::operator[](std::array<std::size_t,2>& a){
    if (a[0] < n_row && a[1] < n_col){
        if (!is_compressed){
            return data[a];
        }else{
            for (size_t j=ptr[a[1]]; j<ptr[a[1]+1]; j++){
                if (index[j] == a[0]){
                    return data_cmp[j];
                }
            }
            std::cerr<<"can't change compressed zero value"<<std::endl;
        }
    }else{
        std::cerr<<"out of range"<<std::endl;
    }
};

template<class T, StorageOrder W>
void Algebra::Matrix<T,W>::resize(std::size_t rows, std::size_t cols){
    if (is_compressed){
        this->uncompress();
    }
    if (n_row < rows && n_col < cols){
        n_row = rows;
        n_col = cols;
    }
};

template<class T, StorageOrder W>
void Algebra::Matrix<T,W>::read(std::string& fname){
    this->uncompress();
    std::ifstream file(fname);
    while (file.peek() == '%') file.ignore(2048, '\n');
    file >> n_row>> n_col >> nnz;
    for (size_t n=0; n<nnz; n++){
        T val;
        size_t i, j;
        file >> i >> j >> val;
        data[{i,j}]= val;
    }
};

template<class T>
void Algebra::Matrix<T,column_wise>::read(std::string& fname){
    this->uncompress();
    std::ifstream file(fname);
    while (file.peek() == '%') file.ignore(2048, '\n');
    file >> n_row>> n_col >> nnz;
    for (size_t n=0; n<nnz; n++){
        T val;
        size_t i, j;
        file >> i >> j >> val;
        data[{i,j}]= val;
    }
    file.close();
};