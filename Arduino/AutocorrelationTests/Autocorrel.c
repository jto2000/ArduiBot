//nombre de valeurs : temps / valeur => 

//Autocorrelation obtient la période par tour. => On en déduit le nombre de tour par seconde

// On préférera un pointeur vers le tableau ?
void autocorrelation(int *xvalues, float *r, int nvalues, int maxDelay, int delayStep)
{	double avg,sx,denom,sxx;
	//int r[maxDelay];

	// Moyenne de la serie :
	avg = 0;
	nvalues; //sizeof xvalues ?
	for (i=0;i<n;i++)
	{
		avg += x[i];
	}
	avg /= nvalues;

	// Dénominateur de la serie :
	sx = 0;
	for (i=0;i<n;i++) {
	  sx += (x[i] - avg) * (x[i] - avg);
	}
	denom = abs(sx);

	// Compute correlation serie :
	for (delay=0;delay<maxDelay;delay +=delayStep)
	{
		sxx = 0;
		for (i=0;i<nvalues;i++)
		{
			j = i + delay;
			if (j >= delay) {
				continue;
			}
			else {
				sxx += (x[i] - avg) * x[j] - avg);
			}
		}
		r[delay] = sxx / denom;
	}
}
