#include "main.h"

#define COSINE

float computeSimilarity(float* ref, float* tar) {
	int dim = 59 * 49 * 41;
	float score;

#ifdef COSINE
	int k;
	float nomi = 0, denomi;
	float refMag = 0, tarMag = 0;

	for (k = 0; k < dim; k++) {
		nomi += ref[k] * tar[k];
		refMag += ref[k] * ref[k];
		tarMag += tar[k] * tar[k];
	}
	denomi = sqrt(refMag) * sqrt(tarMag);
	score = nomi / denomi;
#endif // COSINE

	return score;
}