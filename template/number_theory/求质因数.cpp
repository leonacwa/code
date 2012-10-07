int nFac;
long long fac[NN];

void getFactor(long long f)
{
	nFac = 1;
	fac[0] = 1;
	for (int i = 0; i < prm_cnt && f > 1; ++i) {
		int l = 0, r;
		while (f % prm[i] == 0) {
			r = nFac;
			for (int j = l; j < r; ++j) {
				fac[nFac++] = fac[j] * prm[i];
			}
			l = r;
			f /= prm[i];
		}
	}
	if (f > 1) {
		int r = nFac;
		for (int j = 0; j < r; ++j) {
			fac[nFac++] = fac[j] * f;
		}
	}
}
