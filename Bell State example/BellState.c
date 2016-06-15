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
	
	qreg qRegister1;
	qRegister1.nqubits = 2;
	printf("\nInitialize1:");
	qinit(&qRegister1);
	qprint(qRegister1);
	
	printf("\nHgate1:");
	qgate(Hgate, &qRegister1, qubits1);
	qprint(qRegister1);
	
	printf("\nCNOT1:");
	qgate(CNOTgate, &qRegister1, qubits2);
	qprint(qRegister1);
	
	printf("\nmeasurement0: %d",measure(&qRegister1, 0));
	qprint(qRegister1);
	printf("\nmeasurement1: %d",measure(&qRegister1, 1));
	qprint(qRegister1);
	
	
	return 0;
	 
}
