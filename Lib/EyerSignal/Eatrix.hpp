#ifndef EYERLIB_EATRIX_HPP
#define EYERLIB_EATRIX_HPP

namespace Eyer
{
    template<typename T>
    class Eatrix {
    public:
        Eatrix(int _row = 0, int _col = 0)
        {
            Resize(_row, _col);
        }

        ~Eatrix()
        {
            free();
        }

        int Resize(int _row, int _col)
        {
            free();

            row = _row;
            col = _col;

            init(row, col);
            return 0;
        }

        T Get(int y, int x)
        {
            return mat[y][x];
        }

        int Set(int y, int x, T t)
        {
            mat[y][x] = t;
            return 0;
        }

    public:
        int row = 0;
        int col = 0;
        T * * mat = nullptr;

    private:
        void init(int row, int col)
        {
            if (row && col) {
                mat = new T * [row];
                for (int i = 0; i < row; i++) {
                    mat[i] = new T[col];
                    for (int j = 0; j < col; j++){
                        mat[i][j] = 0;
                        if(i == j){
                            mat[i][j] = 1;
                        }
                    }
                }
            }
        }

        void free()
        {
            if (mat != nullptr) {
                for (int i = 0; i < row; i++){
                    if (mat[i]) {
                        delete[] mat[i];
                        mat[i] = nullptr;
                    }
                }
                if (mat){
                    delete[] mat;
                }
                mat = nullptr;
            }
        }
    };
}

#endif //EYERLIB_EATRIX_HPP
