for(int ii = 0; ii < maxI; ii += blockSize)
{
	for(int jj = 0; jj < maxJ; jj += blockSize)
	{
		for(int kk = 0; kk < maxK; kk += blockSize)
		{
			minI = MIN(maxI, ii + blockSize);

			for(int i = ii; i < minI; i++)
			{
				minJ = MIN(maxJ, jj + blockSize);

				for(int j = jj; j < minJ; j++)
				{
					minK = MIN(maxK, kk + blockSize);

					for(int k = kk; k < minK; k++)
						//동작
				}
			}
		}
	}
}
