void strassen(double* a, double* b, double* c, int ma, int mb, int mc, int p, int q, int r)
{
	if((long long)p * q * r <= 36000)
	{
		for(int i = 0; i < p; ++i)
		{
			for(int k = 0; k < q; ++k)
			{
				double t = a[i * ma + k];
				if(t == 0.0) continue;
				for(int j = 0; j < r; ++j)
				{
					c[i * mc + j] += t * b[k * mb + j];
				}
			}
		}
		return;
	}

	int pp = p / 2, qq = q / 2, rr = r / 2;

	double* m1 = (double*)calloc(pp * rr, sizeof(double));
	double* m2 = (double*)calloc(pp * rr, sizeof(double));
	double* m3 = (double*)calloc(pp * rr, sizeof(double));
	double* m4 = (double*)calloc(pp * rr, sizeof(double));
	double* m5 = (double*)calloc(pp * rr, sizeof(double));

	double* at1 = (double*)malloc(sizeof(double) * pp * qq);
	double* at2 = (double*)malloc(sizeof(double) * pp * qq);
	double* at3 = (double*)malloc(sizeof(double) * pp * qq);

	double* bt1 = (double*)malloc(sizeof(double) * qq * rr);
	double* bt2 = (double*)malloc(sizeof(double) * qq * rr);
	double* bt3 = (double*)malloc(sizeof(double) * qq * rr);

	int i, j;
	double t1, t2, t3, t4, t5;
	for(i = 0; i < pp; ++i) for(j = 0; j < qq; ++j)
	{
		t1 = a[i * ma + j]; t2 = a[(i + pp) * ma + j + qq];
		at1[i * qq + j] = t1 + a[i * ma + j + qq];
		at2[i * qq + j] = t1 + t2;
		at3[i * qq + j] = t2 + a[(i + pp) * ma + j];
	}

	for(i = 0; i < qq; ++i) for(j = 0; j < rr; ++j)
	{
		t1 = b[i * mb + j]; t2 = b[(i + qq) * mb + j + rr];
		bt1[i * rr + j] = t1;
		bt2[i * rr + j] = t1 + t2;
		bt3[i * rr + j] = t2;
	}

	strassen(at1, bt3, m5, qq, rr, rr, pp, qq, rr);
	strassen(at2, bt2, m1, qq, rr, rr, pp, qq, rr);
	strassen(at3, bt1, m2, qq, rr, rr, pp, qq, rr);

	for(i = 0; i < qq; ++i) for(j = 0; j < rr; ++j)
	{
		bt1[i * rr + j] += b[i * mb + j + rr];
		bt3[i * rr + j] += b[(i + qq) * mb + j];
	}

	for(i = 0; i < pp; ++i) for(j = 0; j < qq; ++j)
	{
		t1 = at2[i * qq + j];
		at1[i * qq + j] -= t1;
		at3[i * qq + j] -= t1;
	}

	strassen(at1, bt3, c, qq, rr, mc, pp, qq, rr);
	strassen(at3, bt1, c + pp * mc + rr, qq, rr, mc, pp, qq, rr);

	for(i = 0; i < qq; ++i) for(j = 0; j < rr; ++j)
	{
		t1 = bt2[i * rr + j];
		bt1[i * rr + j] -= t1;
		bt3[i * rr + j] -= t1;
	}

	strassen(a, bt1, m3, ma, rr, rr, pp, qq, rr);
	strassen(a + pp * ma + qq, bt3, m4, ma, rr, rr, pp, qq, rr);

	for(i = 0; i < pp; ++i) for(j = 0; j < rr; ++j)
	{
		t1 = m1[i * rr + j];
		t2 = m2[i * rr + j];
		t3 = m3[i * rr + j];
		t4 = m4[i * rr + j];
		t5 = m5[i * rr + j];
		c[i * mc + j] += t1 + t4 - t5;
		c[i * mc + j + rr] += t3 + t5;
		c[(i + pp) * mc + j] += t2 + t4;
		c[(i + pp) * mc + j + rr] += t1 - t2 + t3;
	}

	free(m1);
	free(m2);
	free(m3);
	free(m4);
	free(m5);

	free(at1);
	free(at2);
	free(at3);

	free(bt1);
	free(bt2);
	free(bt3);
}

void matmul_strassen(double* a, double* b, double* c, int p, int q, int r)
{
	int pp = p, qq = q, rr = r;
	int mod = 1;
	while((long long)pp * qq * rr > 36000)
	{
		if(pp & 1) pp++;
		pp >>= 1;
		if(qq & 1) qq++;
		qq >>= 1;
		if(rr & 1) rr++;
		rr >>= 1;
		mod <<= 1;
	}
	pp *= mod;
	qq *= mod;
	rr *= mod;

	double* a_re = (double*)calloc(pp * qq, sizeof(double));
	double* b_re = (double*)calloc(qq * rr, sizeof(double));
	double* c_re = (double*)calloc(pp * rr, sizeof(double));

	for(int i = 0; i < p; ++i)
	{
		for(int j = 0; j < q; ++j)
		{
			a_re[i * qq + j] = a[i * q + j];
		}
	}

	for(int i = 0; i < q; ++i)
	{
		for(int j = 0; j < r; ++j)
		{
			b_re[i * rr + j] = b[i * r + j];
		}
	}

	strassen(a_re, b_re, c_re, qq, rr, rr, pp, qq, rr);

	for(int i = 0; i < p; ++i)
	{
		for(int j = 0; j < r; ++j)
		{
			c[i * r + j] += c_re[i * rr + j];
		}
	}

	free(a_re);
	free(b_re);
	free(c_re);
}
