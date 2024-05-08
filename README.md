Sorry for the late invitation, I thought I only need to add the name of Prof.Formaggia and Dr.Artoni and Dr.Crippa in the Readme file initially until I read the email.

To complier the files, simply write "make" in the terminal.
And to run, write "./main". 

In the main.cpp file, matrix readed from the lnsp_131.mtx file are multiplied with a vector whose elements are all one. Therefore, elements of result vector are the row sum of the matrix. One can find that the multiplication for compressed matrix takes less time than the uncompressed one. And in the last few line, I compared the result vectors to make sure the compressed, uncompressed, column-wise, row-wise give the same result. 

In the matrix.hpp, sturct "array_cmp" is used to replace the default array comparison in std::map<std::array<size_t,2>, T>. I fully specified the matrix for column-wise storage. Maybe there is a better way to specify to aviod the code duplication. 
