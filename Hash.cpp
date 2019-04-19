struct HASH {
    typedef unsigned int typec;
    static const int MaxN = 100000 + 16;
    static const int key = 137;

    typec H[MaxN], xp[MaxN];

    void init(const char s[], int len) {
        H[len] = 0;
        for(int i = len - 1; i >= 0; --i) {
            H[i] = H[i + 1] * key + s[i];
        }
        xp[0] = 1;
        for(int i = 1; i <= len; ++i) {
            xp[i] = xp[i - 1] * key;
        }
    }
    typec get(int pos, int len) {
        return H[pos] - H[pos + len] * xp[len];
    }
};
