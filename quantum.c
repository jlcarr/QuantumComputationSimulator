#include "quantum.h"

//Common Gates

const qgate Hgate = {.nqubits = 1,
	.matrix = (double complex*[2]){
		(double complex[2]){0.707106781,0.707106781},
		(double complex[2]){0.707106781,-0.707106781}
	}}; //Hadamard gate

const qgate CNOTgate = {.nqubits = 2,
	.matrix = (double complex*[4]){
		(double complex[4]){1,0,0,0},
		(double complex[4]){0,1,0,0},
		(double complex[4]){0,0,0,1},
		(double complex[4]){0,0,1,0}
	}}; //Controlled NOT gate: qubit 0 is target, qubit 1 is control

const qgate Xgate = {.nqubits = 1,
	.matrix = (double complex*[2]){
		(double complex[2]){0,1},
		(double complex[2]){1,0}
	}}; //Pauli X gate / NOT gate

const qgate Ygate = {.nqubits = 1,
	.matrix = (double complex*[2]){
		(double complex[2]){0,-I},
		(double complex[2]){I,0}
	}}; //Pauli Y gate

const qgate Zgate = {.nqubits = 1,
	.matrix = (double complex*[2]){
		(double complex[2]){1,0},
		(double complex[2]){0,-1}
	}}; //Pauli Z gate

const qgate SWAPgate = {.nqubits = 2,
	.matrix = (double complex*[4]){
		(double complex[4]){1,0,0,0},
		(double complex[4]){0,0,1,0},
		(double complex[4]){0,1,0,0},
		(double complex[4]){0,0,0,1}
	}};

const qgate sqrtSWAPgate = {.nqubits = 2,
	.matrix = (double complex*[4]){
		(double complex[4]){1,0,0,0},
		(double complex[4]){0,0.5+0.5*I,0.5-0.5*I,0},
		(double complex[4]){0,0.5-0.5*I,0.5+0.5*I,0},
		(double complex[4]){0,0,0,1}
	}};

const qgate CCNOTgate = {.nqubits = 3,
	.matrix = (double complex*[8]){
		(double complex[8]){1,0,0,0,0,0,0,0},
		(double complex[8]){0,1,0,0,0,0,0,0},
		(double complex[8]){0,0,1,0,0,0,0,0},
		(double complex[8]){0,0,0,1,0,0,0,0},
		(double complex[8]){0,0,0,0,1,0,0,0},
		(double complex[8]){0,0,0,0,0,1,0,0},
		(double complex[8]){0,0,0,0,0,0,0,1},
		(double complex[8]){0,0,0,0,0,0,1,0}
	}}; //(universal) Toffoli gate: qubit 0 is target, qubit 1 and 2 are control

const qgate CSWAPgate = {.nqubits = 3,
	.matrix = (double complex*[8]){
		(double complex[8]){1,0,0,0,0,0,0,0},
		(double complex[8]){0,1,0,0,0,0,0,0},
		(double complex[8]){0,0,1,0,0,0,0,0},
		(double complex[8]){0,0,0,1,0,0,0,0},
		(double complex[8]){0,0,0,0,1,0,0,0},
		(double complex[8]){0,0,0,0,0,0,1,0},
		(double complex[8]){0,0,0,0,0,1,0,0},
		(double complex[8]){0,0,0,0,0,0,0,1}
	}}; //(universal) Fredkin gate: qubit 0 and 1 are target, qubit 2 is control


//To Add:
//add measure Hadamard basis
//combind gates
//size up gates qgate nHgate(int n);
//controlled U gate


static void cprint(double complex z){
	if (fabs(cimag(z))<pow(10,-15)){
		if (fabs(creal(z))<pow(10,-15)) {
			printf("0");
		}
		else{
			printf("%g",creal(z));
		}
	}
	else if (fabs(creal(z))<pow(10,-15)){
		if (cimag(z)==1) {
			printf("i");
		}
		else if (cimag(z)==-1) {
			printf("-i");
		}
		else{
			printf("%gi",cimag(z));
		}
	}
	else{
		if (cimag(z)==1) {
			printf("%g+i",creal(z));
		}
		else if (cimag(z)==-1) {
			printf("%g-i",creal(z));
		}
		else if (cimag(z)>0) {
			printf("%g+%gi",creal(z),cimag(z));
		}
		else{
			printf("%g-%gi",creal(z),-cimag(z));
		}
	}
}

void qprint(qreg reg){
	int temp;
	char* output = malloc((1+reg.nqubits)*sizeof(char));
	output[reg.nqubits] = '\0';
	for(int i=0;i<(int)pow(2,reg.nqubits);i++){
		printf("\n");
		//print binary version of state
		for (int j=i, temp=0; temp<reg.nqubits; temp++, j/=2) j%2?(output[reg.nqubits-1-temp]='1'):(output[reg.nqubits-1-temp]='0');
		printf("%s: ", output);
		//print the probability amplitude of the state
		cprint(reg.state[i]);
	}
	free(output);
	printf("\n");
}


void qgateprint(qgate gate){
	for(int i=0;i<(int)pow(2,gate.nqubits);i++){
		printf("\n\n");
		for (int j=0; j<(int)pow(2,gate.nqubits); j++){
			cprint(gate.matrix[i][j]);
			printf("\t");
		}
	}
	printf("\n");
}


qreg newqreg(int nqubits){
	//initialize the return value
	qreg returnVal;
	returnVal.nqubits = nqubits;
	if (nqubits) {
		//create a fresh new array of 0s
		returnVal.state = calloc((int)pow(2,nqubits),sizeof(double complex));
		//initialize the definite 0 state to 100% probability
		returnVal.state[0] = 1;
	}
	else returnVal.state = NULL;
	return returnVal;
}


qgate newqgate(int nqubits){
	//initialize the return value
	qgate returnVal;
	returnVal.nqubits = nqubits;
	//create a fresh new array of NULLs
	returnVal.matrix = calloc((int)pow(2,nqubits),sizeof(double complex*));
	//in each new pointer space create memory to zeros
	for(int i=0;i<((int) pow(2,nqubits));i++){
		returnVal.matrix[i] = calloc((int)pow(2,nqubits),sizeof(double complex));
	}
	//fill diagonal with 1s to create identity matrix
	for(int i=0;i<((int) pow(2,nqubits));i++){
		returnVal.matrix[i][i] = 1;
	}
	return returnVal;
}


void freeqreg(qreg* reg){
	free(reg->state);
	reg->nqubits=0;
}


void freeqgate(qgate* gate){
	for(int i=0;i<((int) pow(2,gate->nqubits));i++) free(gate->matrix[i]);
	free(gate->matrix);
	gate->nqubits=0;
}


qreg qregcat(qreg* dest, qreg* src ){
	//create new register to fit the concatenated ones into
	qreg newreg = newqreg(dest->nqubits+src->nqubits);
	//fill new register with the combination of the two superpositioned states
	for (int i=0; i<(int)pow(2,newreg.nqubits); i++) newreg.state[i] = dest->state[i%((int)pow(2,dest->nqubits))]*src->state[i/((int)pow(2,dest->nqubits))];
	//free old registers
	freeqreg(src);
	freeqreg(dest);
	//update destination and return
	dest->nqubits = newreg.nqubits;
	dest->state = newreg.state;
	return *dest;
}


int issep(qreg reg, int nqubits, int* qubits){
	int qubits2[reg.nqubits-nqubits], found,index,rows,cols,i,j,k;
	for (i=0, index=0; i<reg.nqubits; i++) {
		for (j=0, found=0; j<nqubits && !found; j++) if(i==qubits[j]) found=1;
		if (!found) qubits2[index++] = i;
	}
	
	//build the separability matrix
	rows=(int)(pow(2,nqubits));
	cols=(int)(pow(2,reg.nqubits-nqubits));
	double complex sepmatrix[rows][cols];
	for (i=0; i<rows; i++) for (j=0; j<cols; j++){
		//convert matrix index to state index
		index=0;
		for (k=0; k<nqubits; k++) if (i%((int)pow(2,k+1))/((int)pow(2,k))) index+=(int)(pow(2,qubits[k]));
		for (k=0; k<reg.nqubits-nqubits; k++) if (j%((int)pow(2,k+1))/((int)pow(2,k))) index+=(int)(pow(2,qubits2[k]));
		//add entry to separability matrix
		sepmatrix[i][j] = reg.state[index];
	}
		
	// now determine if the matrix is rank 1; i.e. an outer product
	int zero, indexzero,mindim, rank;
	double complex tempvector[cols], multi;
	//find the minimum dimension
	if(rows<cols) mindim=rows;
	else mindim=cols;
	
	//row reduce
	for(index=0, indexzero=0;index<mindim;index++){
		//bring rows with a zero in column 'index' down to the bottom (ignoring rows above 'index' as they have already been used.
		for(i=index;i<rows;i++)if(sepmatrix[i][index]==0){ //find a leading zero 'i' in column 'index'
			for(j=i, zero=i;j<rows;j++) if(sepmatrix[j][index]!=0) zero=j; //find the lowest leading non-zero below the leading zero 'i' in column 'index'
			for(j=indexzero;j<index;j++) if(sepmatrix[j][index]!=0) zero=j; //find the lowest leading non-zero above row 'index' in column 'index' and give preference
			if(i!=zero){ //swap the leading zero in 'i' with the best non-zero found 'zero' if applicable
				for(j=0;j<cols;j++) tempvector[j]=sepmatrix[i][j];
				for(j=0;j<cols;j++) sepmatrix[i][j]=sepmatrix[zero][j];
				for(j=0;j<cols;j++) sepmatrix[zero][j]=tempvector[j];
			}
		}
		//if there is a leading 1, then use it to remove all leading 1s below
		if(sepmatrix[index][index]!=0) for (indexzero=index+1, i=0; i<rows; i++) if(i!=index && sepmatrix[i][index]!=0){
			multi=sepmatrix[index][index];
			for (j=0; j<cols; j++) sepmatrix[index][j]*=sepmatrix[i][index];
			for (j=0; j<cols; j++) sepmatrix[i][j]*=multi;
			for (j=0; j<cols; j++) sepmatrix[i][j]-=sepmatrix[index][j];
		}
	}

	//count up the leading 1s to get rank
	rank=mindim;
	for(i=0;i<mindim;i++){
		for (j=0, found=0; j<cols && !found; j++) if(sepmatrix[i][j]!=0) found=1;
		if (!found) rank--;
	}
	
	return rank==1;
}


qreg qregsep(qreg* src, int nqubits, int* qubits){
	//ensure the state is actually separable
	if (!issep(*src,nqubits,qubits)) return newqreg(0);
	
	int qubits2[src->nqubits-nqubits], found,index,rows,cols,i,j,k;
	rows=(int)(pow(2,nqubits));
	cols=(int)(pow(2,src->nqubits-nqubits));
	double complex sepmatrix[rows][cols], temp;
	qreg org = newqreg(src->nqubits-nqubits);
	qreg new = newqreg(nqubits);
	//double complex* org = calloc(cols,sizeof(double complex));
	//double complex* new = calloc(rows,sizeof(double complex));
	
	//create the difference between all the qubits and 'qubits'
	for (i=0, index=0; i<src->nqubits; i++) {
		for (j=0, found=0; j<nqubits && !found; j++) if(i==qubits[j]) found=1;
		if (!found) qubits2[index++] = i;
	}
	//create separability matrix
	for (i=0; i<rows; i++) for (j=0; j<cols; j++){
		//convert matrix index to state index
		index=0;
		for (k=0; k<nqubits; k++) if (i%((int)pow(2,k+1))/((int)pow(2,k))) index+=(int)(pow(2,qubits[k]));
		for (k=0; k<src->nqubits-nqubits; k++) if (j%((int)pow(2,k+1))/((int)pow(2,k))) index+=(int)(pow(2,qubits2[k]));
		//add entry to separability matrix
		sepmatrix[i][j] = src->state[index];
	}
	//search for a nonzero row in the matrix
	for (i=0, found=0; i<rows && !found; i++) for (j=0; j<cols && !found; j++) if(sepmatrix[i][j]!=0) found=i;
	//used that row to create org
	for (i=0; i<cols; i++) org.state[i]=sepmatrix[found][i];
	for (i=0, temp=0; i<cols; i++) temp+=cabs(org.state[i])*cabs(org.state[i]);
	for (i=0; i<cols; i++) org.state[i]/=csqrt(temp);
	
	//search for a nonzero col in the matrix
	for (i=0, found=0; i<cols && !found; i++) for (j=0; j<rows && !found; j++) if(sepmatrix[j][i]!=0) found=i;
	//use that row to create new
	for (i=0; i<rows; i++) new.state[i]=sepmatrix[i][found];
	for (i=0, temp=0; i<rows; i++) temp+=cabs(new.state[i])*cabs(new.state[i]);
	for (i=0; i<rows; i++) new.state[i]/=csqrt(temp);
	
	//replace the sorce
	freeqreg(src);
	src->nqubits = org.nqubits;
	src->state = org.state;
	
	return new;
}

/*
int qregsep(qreg reg, int nqubits, int* qubits){
	//save initial state temporarily
	qreg temp = newqreg(reg.nqubits);
	for (int i=0; i<pow(2, reg.nqubits); i++) temp.state[i] = reg.state[i];
	
	//add up probabilities of all states where 'qubit1' is 1
	double prob1 = 0;
	for (int i=0; i<pow(2, temp.nqubits); i++) if (i%((int)pow(2,qubit1+1))/((int)pow(2,qubit1))) prob1 += cabs(temp.state[i])*cabs(temp.state[i]);
	
	printf("\n'qubit1' is 1: %g\n", prob1);
	
	//collapse qubit1 in temp to 1 if possible
	double prob11 = 0;
	if(prob1!=0){
		for (int i=0; i<pow(2, temp.nqubits); i++){
			//divide out probability of 'qubit1' being 1 since it is now definite
			if (i%((int)pow(2,qubit1+1))/((int)pow(2,qubit1))) temp.state[i] /= csqrt(prob1);
			//set states with 'qubit1' as 0 to 0 probability
			else temp.state[i] = 0;
		}
		//add up probabilities of all states where 'qubit2' is 1 given that 'qubit1' is 1
		for (int i=0; i<pow(2, temp.nqubits); i++) if (i%((int)pow(2,qubit2+1))/((int)pow(2,qubit2))) prob11 += cabs(temp.state[i])*cabs(temp.state[i]);
		//reset temp state
		for (int i=0; i<pow(2, reg.nqubits); i++) temp.state[i] = reg.state[i];
	}
	//otherwise there is no chance of 11 being the result
	
	printf("\n'qubit2' is 1 given that 'qubit1' is 1: %g\n", prob11);
	
	//collapse qubit1 in temp to 0 if possible
	double prob01 = 0;
	if (prob1!=1) {
		for (int i=0; i<pow(2, reg.nqubits); i++){
			//set states with 'qubit1' as 1 to 0 probability
			if (i%((int)pow(2,qubit1+1))/((int)pow(2,qubit1))) reg.state[i] = 0;
			//divide out probability of 'qubit1' being 0 since it is now definite
			else reg.state[i] /= csqrt(1-prob1);
		}
		//add up probabilities of all states where 'qubit2' is 1 given that 'qubit1' is 0
		for (int i=0; i<pow(2, temp.nqubits); i++) if (i%((int)pow(2,qubit2+1))/((int)pow(2,qubit2))) prob01 += cabs(temp.state[i])*cabs(temp.state[i]);
	}
	//otherwise there is no chance of 11 being the result
	
	printf("\n'qubit2' is 1 given that 'qubit1' is 0: %g\n", prob01);
	
	//free the temp state
	free(temp.state);
	
	//return the comparison of the possible states for test of entanglement
	return (prob01==prob11);
}
*/
//qreg* qregsep(qreg* src, int nqubits, int* qubits)


int measure(qreg* reg, int qubit){
	//find probability of 1 outcome
	double prob1 = 0;
	//add up probabilities of all states where 'qubit' is 1
	for (int i=0; i<pow(2, reg->nqubits); i++) if (i%((int)pow(2,qubit+1))/((int)pow(2,qubit))) prob1 += cabs(reg->state[i])*cabs(reg->state[i]);
	//perform measurement
	if (((double) rand())/((double) RAND_MAX)<=prob1) {
		//collapse qubit
		for (int i=0; i<pow(2, reg->nqubits); i++){
			//divide out probability of 'qubit' being 1 since it is now definite
			if (i%((int)pow(2,qubit+1))/((int)pow(2,qubit))) reg->state[i] /= csqrt(prob1);
			//set states with 'qubit' as 0 to 0 probability
			else reg->state[i] = 0;
		}
		return 1;
	}
	else{
		//collapse qubit
		for (int i=0; i<pow(2, reg->nqubits); i++){
			//set states with 'qubit' as 1 to 0 probability
			if (i%((int)pow(2,qubit+1))/((int)pow(2,qubit))) reg->state[i] = 0;
			//divide out probability of 'qubit' being 0 since it is now definite
			else reg->state[i] /= csqrt(1-prob1);
		}
		return 0;
	}
}


int Hmeasure(qreg* reg, int qubit){
	//find probability of + outcome
	double probplus = 0;
	double complex temp;
	for (int i=0; i<pow(2, reg->nqubits); i++) if (i%((int)pow(2,qubit+1))/((int)pow(2,qubit))) probplus += cabs(reg->state[i]+reg->state[i-(int)pow(2,qubit)])*cabs(reg->state[i]+reg->state[i-(int)pow(2,qubit)])/2.0;
	//perform measurement
	if (((double) rand())/((double) RAND_MAX)<=probplus) {
		//collapse qubit
		for (int i=0; i<pow(2, reg->nqubits); i++){
			if (i%((int)pow(2,qubit+1))/((int)pow(2,qubit))){
				temp = reg->state[i];
				reg->state[i] = (reg->state[i - (int)pow(2,qubit)]+reg->state[i])/2.0/sqrt(probplus);
				reg->state[i - (int)pow(2,qubit)] = (reg->state[i - (int)pow(2,qubit)]+temp)/2.0/sqrt(probplus);
			}
		}
		return 0;
	}
	else{
		//collapse qubit
		for (int i=0; i<pow(2, reg->nqubits); i++){
			if (i%((int)pow(2,qubit+1))/((int)pow(2,qubit))){
				temp = reg->state[i];
				reg->state[i] = -(reg->state[i - (int)pow(2,qubit)]-reg->state[i])/2.0/sqrt(1-probplus);
				reg->state[i - (int)pow(2,qubit)] = (reg->state[i - (int)pow(2,qubit)]-temp)/2.0/sqrt(1-probplus);
			}
		}
		return 1;
	}
}


void applyqgate(qgate gate, qreg* reg, int* qubits){
	//save initial state temporarily
	qreg temp = newqreg(reg->nqubits);
	for (int i=0; i<pow(2, reg->nqubits); i++) temp.state[i] = reg->state[i];
	
	int iMatrix;
	int iState;
	
	//reverse order of input qubits
	//int temp1;
	//for (int i=0; i<gate.nqubits/2; i++) {
	//	temp1 = qubits[i];
	//	qubits[i] = qubits[gate.nqubits-1-i];
	//	qubits[gate.nqubits-1-i] = temp1;
	//}
	
	//perform operation
	//examine each state
	for (int i=0; i<pow(2, reg->nqubits); i++){
		
		//read through the bits of the state and map the permutation of bits to the matrix
		iMatrix = 0;
		for (int j=0; j<gate.nqubits; j++){
			if (i%((int)pow(2,qubits[j]+1))/((int)pow(2,qubits[j]))) iMatrix += (int)pow(2,j);
		}
		//iMatrix now holds the row in gate.matrix to the corresponding reg->state

		
		reg->state[i] = 0;
		//map the matrix column position to the state
		//go through the matrix row
		for (int j=0; j<(int)pow(2,gate.nqubits); j++){
			iState = 0;
			//go through the binary rep of the column
			for (int k=0; k<gate.nqubits; k++){
				//map i to statebit[k] of temp
				if (j%((int)pow(2,k+1))/((int)pow(2,k)) && !(i%((int)pow(2,qubits[k]+1))/((int)pow(2,qubits[k])))){
					iState += (int)pow(2,qubits[k]);
				}
				if (!(j%((int)pow(2,k+1))/((int)pow(2,k))) && i%((int)pow(2,qubits[k]+1))/((int)pow(2,qubits[k]))){
					iState -= (int)pow(2,qubits[k]);
				}
			}
			
			//add this temp statebit with matrix density to updated statebit
			reg->state[i] += gate.matrix[iMatrix][j] * temp.state[i + iState];
		}
	}
	free(temp.state);
}


qgate Rgate(double angle){
	qgate returnVal = newqgate(1);
	returnVal.matrix[1][1]=cexp(I*angle);
	return returnVal;
}

qgate QFTgate(int nqubits){
	qgate returnVal = newqgate(nqubits);
	for (int i = 0; i<(int)pow(2,nqubits); i++) for (int j = 0; j<(int)pow(2,nqubits); j++) returnVal.matrix[i][j] = cexp(2*i*j*M_PI*I/pow(2,nqubits))/pow(2,nqubits/2.0);
	return returnVal;
}

qgate CkNOTgate(int k){
	qgate returnVal = newqgate(k+1);
	for (int i = 0; i<(int)pow(2,k+1); i++) for (int j = 0; j<(int)pow(2,k+1); j++) returnVal.matrix[i][j] = (i==j);
	for (int i = (int)pow(2,k+1)-2; i<(int)pow(2,k+1); i++) for (int j = (int)pow(2,k+1)-2; j<(int)pow(2,k+1); j++) returnVal.matrix[i][j] = !(i==j);
	return returnVal;
} //k-Control Controlled NOT gate: qubit 0 is target, all others are control
