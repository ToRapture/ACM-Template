struct RMQ { // ������ֵ��ѯ(ST)�����㷨 init O(n*logn) query O(1)
    typedef int typec; // ��Ȩ����
    static const int M = 100000 + 16; // ��ĸ���
    int LOG[M];
    typec dpmax[M][20], dpmin[M][20];

    RMQ() {
        LOG[0] = -1;
        for(int i = 1; i < M; ++i) {
            LOG[i] = LOG[i >> 1] + 1;
        }
    }
    void init(int n, typec a[]) { // �����ĸ������±��1��ʼ
        for(int i = 1; i <= n; ++i) {
            dpmax[i][0] = dpmin[i][0] = a[i];
        }
        for(int j = 1; j <= LOG[n]; ++j) {
            for(int i = 1; i + (1 << j) - 1 <= n; ++i) {
                int k = i + (1 << (j - 1));
                dpmax[i][j] = max(dpmax[i][j - 1], dpmax[k][j - 1]);
                dpmin[i][j] = min(dpmin[i][j - 1], dpmin[k][j - 1]);
            }
        }
    }
    typec get(int l, int r, bool big) { // ����1����max������0����min
        int k = LOG[r - l + 1];
        r = r - (1 << k) + 1;
        if(big) return max(dpmax[l][k], dpmax[r][k]);
        else return min(dpmin[l][k], dpmin[r][k]);
    }
};