#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>


#define R2PI 2.5066282

float sigma = 1;

float axes[14];

typedef struct {
	float x;
	float y;
	float theta[14];
} XY;
std::vector<XY> RBF;


void print_axes() {
	for(int i=0; i<14; i++) printf("%f ", axes[i]);
	printf("\n");
	fflush(stdout);
}

/** =1 si pilepoil, =0 si hyperloin */
float kern(float x1, float y1, float x2, float y2) {
	float d = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	return 1.0/(sigma*R2PI)*exp(-(d)/(2*sigma*sigma));
}

float compute_thetas(float x, float y, float* out) {
	for(int i=0; i<14; i++) out[i] = 0;
	float W=0;
	for(int i=0; i<RBF.size(); i++) {
		float w = kern(RBF[i].x, RBF[i].y, x, y);
		for(int j=0; j<14; j++) out[j] += w * RBF[i].theta[j];
		W+=w;
	}
	for(int i=0; i<14; i++) out[i] /= W;
}


#define NBX 2
#define NBY 2

int main(void) {
	float x=0, y=0;
	for(int i=0; i<14; i++) axes[i] = 0.5;

	FILE* fRBF = fopen("RBF.txt", "r");
	while(!feof(fRBF)) {
		XY xy;
		for(int j=0; j<14; j++) xy.theta[j];
		RBF.push_back(xy);
		xy.x = x/NBX;
		xy.y = y/NBY;
		x++;
		if(x>=NBX) {x=0; y++;}
	}
	fclose(fRBF);

	while(1) {
		scanf("%f %f", &x, &y);
		compute_thetas(x,y, axes);
		print_axes();
	}
	return 0;
}
