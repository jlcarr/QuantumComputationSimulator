#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include <stdio.h>

//ifndef clinalg
//include "clinalg.h"
//endif

//qubit register and quantum gate structs
struct qreg{
	int nqubits;
	double complex* state;
};
typedef struct qreg qreg;

struct qgate{
	int nqubits;
	double complex** matrix;
};
typedef struct qgate qgate;


//Basic functions
void qprint(qreg reg);
void qgateprint(qgate gate);
qreg newqreg(int nqubits);
qgate newqgate(int nqubits);
void freeqreg(qreg* reg);
void freeqgate(qgate* gate);
qreg qregcat(qreg* dest, qreg* src );
int issep(qreg reg, int nqubits, int* qubits);
qreg qregsep(qreg* src, int nqubits, int* qubits);

int measure(qreg* reg, int qubit);
int Hmeasure(qreg* reg, int qubit);

void applyqgate(qgate gate, qreg* reg, int* qubits);



//Common Gates

extern const qgate Hgate; //Hadamard gate
extern const qgate CNOTgate; //Controlled NOT gate: qubit 0 is target, qubit 1 is control
extern const qgate Xgate; //Pauli X gate / NOT gate
extern const qgate Ygate; //Pauli Y gate
extern const qgate Zgate; //Pauli Z gate
extern const qgate SWAPgate;
extern const qgate sqrtSWAPgate;
extern const qgate CCNOTgate; //(universal) Toffoli gate: qubit 0 is target, qubit 1 and 2 are control
extern const qgate CSWAPgate; //(universal) Fredkin gate: qubit 0 and 1 are target, qubit 2 is control


qgate Rgate(double angle); //Phase shift gate
qgate QFTgate(int nqubits); //Quantum Fourrier Transform gate
qgate CkNOTgate(int k); //k-Control Controlled NOT gate: qubit 0 is target, all others are control


//To Add:
//combind gates (matmul)
//size up gates ex: qgate nHgate(int n);
//controlled U gate (IMPORTANT)



