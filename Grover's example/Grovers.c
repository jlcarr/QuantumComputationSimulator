#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include <time.h>
#include <stdio.h>

#include "clinalg.h"
#include "quantum.h"


int main (){
	srand((unsigned int)time(NULL));
	rand();
	rand();
		
	//Grover's Algorithm
	
	int size = 3; //size dep
	int states = (int)pow(2,size);
	
	int qubits1[1]={0};
	int qubits[3]={0,1,2}; //size dep
	
	qreg qRegister1 = newqreg(size);
	printf("\nNew register of size %d:", size);
	qprint(qRegister1);
	
	for (int i=0; i<size; i++){
		qubits1[0]=i;
		applyqgate(Hgate,&qRegister1,qubits1);
	}
	printf("\nRegister set to full superposition:");
	qprint(qRegister1);
	
	cvector tempvec;
	tempvec.size = states;
	tempvec.entries = qRegister1.state;
	cmatrix tempmat = matadd(scalarmatmul(2, outprod(tempvec, tempvec)),scalarmatmul(-1, identity(states)));
	qgate groverdiffusion;
	groverdiffusion.nqubits = size;
	groverdiffusion.matrix = tempmat.entries;
	printf("\nGrover diffusion operator:");
	qgateprint(groverdiffusion);
	
	tempvec = zerovec(states);
	//chose what searching for;
	tempvec.entries[5]=1; //size dep
	tempmat = matadd(identity(states),scalarmatmul(-2, outprod(tempvec, tempvec)));
	qgate quantumoracle;
	quantumoracle.nqubits = size;
	quantumoracle.matrix = tempmat.entries;
	printf("\nQuantum oracle:");
	qgateprint(quantumoracle);
	
	
	//Grover Iteration
	for (int i=0; i<(int)sqrt(states); i++) {
		printf("\nBegin Grover iteration %d:\n",i);
		qprint(qRegister1);
		applyqgate(quantumoracle, &qRegister1,qubits);
		applyqgate(groverdiffusion, &qRegister1,qubits);
		printf("\nEnd Grover iteration %d:\n",i);
		qprint(qRegister1);
	}
	
	printf("\nMeasurement result:");
	for (int i=0; i<size; i++) printf("%d",measure(&qRegister1, size-1-i));
	printf("\n");
	
	return 0;
	 
}
