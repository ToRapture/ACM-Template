for(int x = 0, y; x < m; x = y) {
	for(y = x; y < m && Q[x] == Q[y]; ++y);
	int len = y - x;
}