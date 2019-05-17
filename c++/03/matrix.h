class matrix{
private:
    size_t rows, columns;
    int **m;
    class MatrixRow{
    private:
        int *data;
        size_t size;
    public:
        MatrixRow(size_t size, int* data): size(size), data(data){}
        int& operator[](size_t ind){
            if(ind >= size){
                throw std::out_of_range("");
            }
            return data[ind];
        }
        const int& operator[](size_t ind) const{
            if(ind >= size){
                throw std::out_of_range("");
            }
            return data[ind];
        }
    };
public:
    matrix(size_t rows, size_t columns): rows(rows), columns(columns), m(new int*[rows]){
        for (size_t i = 0; i < rows; i++){
            m[i] = new int[columns];
        }
    }
    size_t  getColumns() const{
        return columns;
    }
    size_t getRows() const{
        return rows;
    }
    const MatrixRow operator[](size_t row) const{
        if(row >= rows){
            throw std::out_of_range("");
        }
        return {columns, m[row]};
    }
    MatrixRow operator[](size_t row){
        if(row >= rows){
            throw std::out_of_range("");
        }
        return {columns, m[row]};
    }
    bool operator==(const matrix& matrix) const{
        if(matrix.getColumns() != columns || matrix.getRows() != rows){
            return false;
        }
        for (size_t row = 0; row < rows; row++){
            for(size_t column = 0; column < columns; column++){
                if(matrix.m[row][column] != m[row][column]){
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const matrix& matrix) const{
        return !(matrix == *this);
    }
    matrix& operator+=(const matrix& matrix){
        if(matrix.getColumns() != columns || matrix.getRows() != rows){
            throw std::out_of_range("");
        }
        for (size_t row = 0; row < rows; row++){
            for (size_t column = 0; column < columns; column++){
                m[row][column] += matrix.m[row][column];
            }
        }
        return *this;
    }
    matrix& operator*=(int factor){
        for (size_t row = 0; row < rows; row++){
            for (size_t column = 0; column < columns; column++){
                m[row][column] *= factor;
            }
        }
        return *this;
    }
    ~matrix(){
        for(size_t row = 0; row < rows; row++){
            delete[] m[row];
        }
        delete[] m;
    }
};
