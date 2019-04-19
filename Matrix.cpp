struct Matrix {
    typedef LL typev;
    typedef LL typep;
    static const int MaxN = 16;
    static const LL MOD = 998244353LL;
    int _n, _m;
    typev mat[MaxN][MaxN];

    Matrix(int __n = 0, int __m = 0) {
        this->init(__n, __m);
    }
    void init(int __n, int __m = 0) {
        if(__m == 0) __m = __n;
        this->_n = __n;
        this->_m = __m;
        memset(mat, 0, sizeof(mat));
    }
    void unit(int __n) {
        this->init(__n);
        for(int i = 0; i < __n; ++i) mat[i][i] = 1;
    }
    Matrix operator * (const Matrix &rhs) const {
        assert(this->_m == rhs._n);
        Matrix res(_n, rhs._m);
        for(int i = 0; i < _n; ++i)
        for(int j = 0; j < rhs._m; ++j)
        for(int k = 0; k < _m; ++k)
            res.mat[i][j] = (res.mat[i][j] + mat[i][k] * rhs.mat[k][j]) % MOD;
        return res;
    }
    Matrix operator *= (const Matrix &rhs) {
        return *this = *this * rhs;
    }
    Matrix operator ^ (typep __n) const {
        Matrix res(_n);
        res.unit(_n);
        Matrix tmp = *this;
        while(__n) {
            if(__n & 1) res *= tmp;
            tmp *= tmp;
            __n >>= 1;
        }
        return res;
    }
    Matrix operator ^= (typep __n) {
        return *this = *this ^ __n;
    }
};
