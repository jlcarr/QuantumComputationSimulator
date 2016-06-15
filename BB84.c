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
	
	
	//BB84
	int iseve=0; //boolean for example have an eve (1) or not (0)
	int keylength = 32;
	int qubits1[1]={0};
	
	//Alice's key
	printf("\n\n\n\nAlice's Preparation:\n");
	int Astatestring[keylength];
	int Abasisstring[keylength];
	for (int i=0; i<keylength; i++) Astatestring[i] = rand()%2;
	for (int i=0; i<keylength; i++) Abasisstring[i] = rand()%2;
	
	printf("\nAlice's basis string: ");
	for (int i=0; i<keylength; i++) printf("%d",Abasisstring[i]);
	printf("\nAlice's state string: ");
	for (int i=0; i<keylength; i++) printf("%d",Astatestring[i]);
	
	qreg qkey[keylength];
	for (int i=0; i<keylength; i++) qkey[i] = newqreg(1);
	for (int i=0; i<keylength; i++){
		//Hadamard basis
		if (Abasisstring[i]) {
			applyqgate(Hgate,&qkey[i],qubits1);
			//-
			if (Astatestring[i]) applyqgate(Zgate,&qkey[i],qubits1);
			//else +
		}
		//Standard basis
		else{
			//1
			if (Astatestring[i]) applyqgate(Xgate,&qkey[i],qubits1);
			//else 0
		}
	}
	
	printf("\n\nAlice's resulting quantum register:\n");
	for (int i=0; i<keylength; i++) {
		printf("qubit %d:",i);
		qprint(qkey[i]);
	}
	
	
	//Eve's eavesdropping
	
	if (iseve) {
		printf("\n\n\n\nEve's Eavesdropping:\n");
		int Estatestring[keylength];
		int Ebasisstring[keylength];
		for (int i=0; i<keylength; i++) Ebasisstring[i] = rand()%2;
		printf("\nEve's basis string: ");
		for (int i=0; i<keylength; i++) printf("%d",Ebasisstring[i]);
		
		for (int i=0; i<keylength; i++) {
			if (Ebasisstring[i]) Estatestring[i] = Hmeasure(&qkey[i], 0);
			else Estatestring[i] = measure(&qkey[i], 0);
		}
		
		printf("\nEve's state string: ");
		for (int i=0; i<keylength; i++) printf("%d",Estatestring[i]);
		
		printf("\n\nEve's resulting quantum register:\n");
		for (int i=0; i<keylength; i++) {
			printf("qubit %d:",i);
			qprint(qkey[i]);
		}
	}
	
	
	
	
	
	//Bob's reading
	printf("\n\n\n\nBob's Reading:\n");
	int Bstatestring[keylength];
	int Bbasisstring[keylength];
	for (int i=0; i<keylength; i++) Bbasisstring[i] = rand()%2;
	printf("\nBob's basis string: ");
	for (int i=0; i<keylength; i++) printf("%d",Bbasisstring[i]);
	
	for (int i=0; i<keylength; i++) {
		if (Bbasisstring[i]) Bstatestring[i] = Hmeasure(&qkey[i], 0);
		else Bstatestring[i] = measure(&qkey[i], 0);
	}

	printf("\nBob's state string: ");
	for (int i=0; i<keylength; i++) printf("%d",Bstatestring[i]);
	
	printf("\n\nXNOR, i.e. comparison of Alice's and Bob's basis strings: ");
	for (int i=0; i<keylength; i++) printf("%d", Abasisstring[i] == Bbasisstring[i]);
	
	printf("\n\n\n\nShared summary:\n");
	printf("\nA basis string: ");
	for (int i=0; i<keylength; i++) printf("%d",Abasisstring[i]);
	printf("\nB basis string: ");
	for (int i=0; i<keylength; i++) printf("%d",Bbasisstring[i]);
	printf("\ncompare string: ");
	for (int i=0; i<keylength; i++) printf("%d", Abasisstring[i] == Bbasisstring[i]);
	printf("\nA state string: ");
	for (int i=0; i<keylength; i++) printf("%d",Astatestring[i]);
	printf("\nB state string: ");
	for (int i=0; i<keylength; i++) printf("%d",Bstatestring[i]);
	
	printf("\n\nShared private key: ");
	for (int i=0; i<keylength; i++) if (Abasisstring[i] == Bbasisstring[i]) printf("%d", Astatestring[i]);
	
	
	//Eavesdropping detection
	printf("\n\n\n\nEavesdropping detection:\n");
	int eve=0;
	for (int i=0; i<keylength/2 && !eve; i++) if (Abasisstring[i] == Bbasisstring[i] && Astatestring[i] != Bstatestring[i]) eve=1;
	
	if (eve) {
		printf("\nAn evesdropper was detected! Try again.\n\n");
	}
	else{
		printf("\nKey transfer was secure\n");
		printf("\nFinal shared private key: ");
		for (int i=keylength/2; i<keylength; i++) if (Abasisstring[i] == Bbasisstring[i]) printf("%d", Astatestring[i]);
		printf("\n\n");
	}
	
	
		/*
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
	tempvec.entries[1]=1; //size dep
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
	for (int i=0; i<size; i++) measure(&qRegister1, size-1-i);
	printf("\n");
	*/
	return 0;
	 
}
