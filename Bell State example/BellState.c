#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include <time.h>
#include <stdio.h>

#include "quantum.h"

int main (){
	srand((unsigned int)time(NULL));
	rand();
	rand();
	
	//Bell state example
	
	int qubits1[1] = {1};
	int qubits2[2] = {0,1};
	
	qreg newregister = newqreg(2);
	printf("\nInitialize1:");
	qprint(newregister);
	
	printf("\nHgate1:");
	applyqgate(Hgate, &newregister, qubits1);
	qprint(newregister);
	
	printf("\nCNOT1:");
	applyqgate(CNOTgate, &newregister, qubits2);
	qprint(newregister);
	
	printf("\nmeasurement0: %d",measure(&newregister, 0));
	qprint(newregister);
	printf("\nmeasurement1: %d",measure(&newregister, 1));
	qprint(newregister);
	
	
	return 0;
	 
}
