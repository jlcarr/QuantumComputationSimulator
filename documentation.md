# quantum.c Documentation

## Todo
- Combind gates
- Size up gates qgate nHgate(int n);
- Add in matrix operations
- Controlled U gate
- Binary arithmetic using basic gates


## Index

1. The Structs
   - Quantum register (qreg)
   - Quantum gate (qgate)
2. The Functions
   - New quantum register (newqreg)
   - New quantum gate (newqgate)
   - Clear quantum register (freeqreg)
   - Clear quantum gate (freeqgate)
   - Concatenate quantum registers (qregcat)
   - Print quantum register (qprint)
   - Print quantum gate (qgateprint)
   - Measure qubit in standard basis (measure)
   - Measure qubit in hadamard basis (Hmeasure)
   - Apply quantum gate (applyqgate)
3. The gates
   - Hadamard gate (Hgate)
   - Controlled NOT gate (CNOTgate)
   - Pauli X gate (Xgate)
   - Pauli Y gate (Ygate)
   - Pauli Z gate (Zgate)
   - Swap gate (SWAPgate)
   - Square root of Swap gate (sqrtSWAPgate)
   - Toffoli gate (CCNOTgate)
   - Fredkin gate (CSWAPgate)
   - Phase shift gate (Rgate)
   - Quantum Fourier transform gate (QFTgate)


## The Structs

### Quantum registers
#### Declaration
`qreg`
#### Contents
- `int nqubits`
    - The number of qubits inside the register.
- `double complex* state`
   - A pointer to a complex double array containing the potability amplitudes of the states; must be of size `(1<<nqubits)`.
#### Description
A simulation of a quantum register holding the superposition of states ordered such that listing the states in the order they are contained in `state` counts upwards in binary. See `qprint`.
#### Example
```
int main(){
	qreg newregister;
	return 0;
}
```

### Quantum gate
#### Declaration
`qgate`
#### Contents
- `int nqubits`
   - The number of qubits acted upon by the gate.
- `double complex** matrix`
   - A pointer to an array of complex double array, i.e. a complex double matrix, describing the gate ordered in a manner corresponding to that of the quantum registers; must be of size `(1<<nqubits) * (1<<nqubits)`.
#### Description
A simulation of a quantum gate that may act upon a qubit in a superposition of states. See `printgate`.
#### Example
```
int main(){
	qgate newgate;
	return 0;
}
```


## The Functions

### New register
#### Prototype
`qreg newqreg(int nqubits);`
#### Performance
- **Time complexity**: O(1)
- **Memory complexity**: O(2^`nqubits`)
#### Description
Takes an integer `nqubits` and returns a quantum register with `nqubits` and the `state` allocated and initialized to `0`.
#### Example
```
int main(){
	//create a new quantum register with 2 qubits
	qreg newregister = newqreg(2);
	//print the newly created quantum register
	printf("\nInitialized register:");
	qprint(newregister);
	//exit successfully
	return 0;
}
```
Output:
```
Initialized register:
00: 1
01: 0
10: 0
11: 0
```


### New gate
#### Prototype
`qgate newqgate(int nqubits);`
#### Performance
- **Time complexity**: O(2^`nqubits`)
- **Memory complexity**: O(4^`nqubits`)
#### Description
Takes an integer `nqubits` and creates a quantum gate acting on `nqubits`, and allocates an array of arrays containing the action of the gate initialized to the identity matrix, which is given as the gate's matrix.
#### Example
```
int main(){
	//create a new quantum gate acting on 2 qubits
	qgate newgate = newqgate(2);
	//print the newly created quantum gate
	printf("\nInitialized gate:");
	qgateprint(newgate);
	//exit successfully
	return 0;
}
```
Output:
```
Initialized gate:
1	0	0	0	
0	1	0	0	
0	0	1	0	
0	0	0	1
```


### Clear register
#### Prototype
`void freeqreg(qreg* reg);`
#### Performance
- **Time complexity**: O(1)
- **Memory complexity**: O(1)
#### Description
Takes a quantum register `reg` and frees the array assigned to `reg->state` and sets `reg->nqubits` to `0`.
#### Example
```
int main(){
	//create a new quantum register with 2 qubits
	qreg newregister = newqreg(2);
	//print the newly created quantum register
	printf("\nInitialized register of size 2:");
	qprint(newregister);
	freeqreg(&newregister);
	newregister = newqreg(1);
	printf("\nReinitialized register of size 1:");
	qprint(newregister);
	//exit successfully
	return 0;
}
```
Output:
```
Initialized register of size 2:
00: 1
01: 0
10: 0
11: 0

Reinitialized register of size 1:
0: 1
1: 0
```


### Clear gate
#### Prototype
`void freeqgate(qgate* gate);`
#### Performance
- **Time complexity**: O(2^`gate->nqubits`)
- **Memory complexity**: O(1)
#### Description
Takes a quantum gate 'gate' and frees the arrays in to gate->matrix, frees gate->matrix and sets gate->nqubits to 0.
#### Example
```
int main(){
	//create a new quantum register with 2 qubits
	qgate newgate = newqgate(2);
	//print the newly created quantum register
	printf("\nInitialized gate of size 2:");
	qgateprint(newgate);
	freeqgate(&newgate);
	newgate = newqgate(1);
	printf("\nReinitialized gate of size 1:");
	qgateprint(newgate);
	//exit successfully
	return 0;
}
```
Output:
```
Initialized gate of size 2:
1	0	0	0	
0	1	0	0	
0	0	1	0	
0	0	0	1	

Reinitialized gate of size 1:
1	0	
0	1
```


### Print quantum register
#### Prototype
`void qprint(qreg reg);`
#### Performance
- *Time complexity*: O(`reg.nqubits`*2^`reg.nqubits`)
- *Memory complexity*: O(`reg.nqubits`)
#### Description
This function prints the states of a quantum register along with the associated probability amplitude. The order is the standard in which the list of states counts upwards in binary. The nth qubit hence corresponds to the 2^n binary position.
#### Example
```
int main(){
	//create a new quantum register with 2 qubits
	qreg newregister = newqreg(2);
	//print the newly created quantum register
	printf("\nInitialized register:");
	qprint(newregister);
	//exit successfully
	return 0;
}
```
Output:
```
Initialized register:
00: 1
01: 0
10: 0
11: 0
```


### Print quantum gate
#### Prototype
`void printgate(qgate gate);`
#### Performance
- *Time complexity*: O(4^(gate.nqubits))
- *Memory complexity*: O(1)
#### Description
This function prints the matrix representing a quantum gate. The order is the standard in which the list of states of the quantum register state vector counts upwards in binary. The nth qubit hence corresponds to the 2^n binary position.
#### Example
```
int main(){
	//print the Hadamard gate
	printf("\nThe Hadamard gate:");
	qgateprint(Hgate);
	//exit successfully
	return 0;
}
```
Output:
```
The Hadamard gate:
0.707107	0.707107	
0.707107	-0.707107
```


### Concatenate quantum registers
#### Prototype
`qreg* qregcat(qreg* dest, qreg* src);`
#### Performance
- *Time complexity*: O(2^(`dest->nqubits`+`src->nqubits`))
- *Memory complexity*: O(1)
#### Description
This function takes two quantum registers, `qreg` and `src` and combines them into a single register which is stored in `dest`, while `src` is freed. The function returns the updated pointer `dest`. Note that the size of the new register will be `dest->nqubits+src->nqubits`, and hence the length of the state of the return value will be `1<<(dest->nqubits+src->nqubits)`. Note that the register `src` is appended to the end of `dest` and therefore when printing the result of qregcat the states in the 2^(x+`dest->nqubits`) binary places correspond to the x states of `src`.
#### Example
```
int main(){
	//create a new quantum register with 2 qubits
	qreg register1 = newqreg(2);
	//print the newly created quantum register1
	printf("\nInitialized register1:");
	qprint(register1);

	qreg register2 = newqreg(1);
	//print the newly created quantum register2
	printf("\nInitialized register2:");
	qprint(register2);

	int qubits1[1]={1};
	applyqgate(Hgate, &register1, qubits1);
	printf("\nRegister1 after Hadamard gate on qubit 1:");
	qprint(register1);


	qregcat(&register1, &register2);
	printf("\nThe concatenation of register1 and register 2:");
	qprint(register1);

	//exit successfully
	return 0;
}
```
Output
```
Initialized register1:
00: 1
01: 0
10: 0
11: 0

Initialized register2:
0: 1
1: 0

Register1 after Hadamard gate on qubit 1:
00: 0.707107
01: 0
10: 0.707107
11: 0

The concatenation of register1 and register 2:
000: 0.707107
001: 0
010: 0.707107
011: 0
100: 0
101: 0
110: 0
111: 0
```


### Measure qubit in standard basis
#### Prototype
`int measure(qreg* reg, int qubit);`
#### Performance
- *Time complexity*: O(`reg->nqubits`)
- *Memory complexity*: O(1)
#### Description
This function makes a measurement on the `qubit`th qubit of `reg` in the standard basis. It collapses the wave function of the qubit and returns the result of the measurement (`1`, or `0`). Note that `rand()` from the `stdlib` is used for random number generation, and therefore must have been seeded with `srand();`.
#### Example
```
void main(){
	//create a new quantum register with 2 qubits
	qreg newregister = newqreg(1);
	//print the newly created quantum register
	printf("\nInitialized register:");
	qprint(newregister);

	//print the measurement result: will be definitely 0 in this case
	printf("\nMeasurement of qubit 0 result: %d\n", measure(&newregister, 0));

	//exit successfully
	return 0;
}
```
Output:
```
Initialized register:
0: 1
1: 0

Measurement of qubit 0 result: 0
```


Name:			Measure qubit in Hadmard basis
Prototype: 		int measure(qreg* reg, int qubit);
Time complexity: 	O(reg->nqubits)
Memory complexity: 	O(1)
Description: 		This function makes a measurement on the 'qubit'th qubit of 'reg' in the Hadamard basis. It collapses the wave function of the qubit and returns the result of the measurement (0 for +, or 1 for -). Note that rand() from the stdlib is used for random number generation, and therefore must have been seeded with srand().
Example:
void main(){
	//create a new quantum register with 2 qubits
	qreg newregister = newqreg(1);
	//print the newly created quantum register
	printf("\nInitialized register:");
	qprint(newregister);

	int qubits1[1]={1};
	applyqgate(Hgate, &newregister, qubits1);
	printf("\nRegister after Hadamard gate on qubit 0:");
	qprint(newregister);

	//print the measurement result: will be definitely 0, i.e. +, in this case
	if(measure(&newregister, 0) == 0) printf("\nHadamard measurement of qubit 0 result: +\n");
	else printf("\nHadamard measurement of qubit 0 result: -\n");
	
	//exit successfully
	return 0;
}
Output:
Initialized register:
Initialized register:
0: 1
1: 0

Register after Hadamard gate on qubit 0:
0: 0.707107
1: 0

Hadamard measurement of qubit 0 result: +


Name:			Apply quantum gate
Prototype: 		void applyqgate(qgate gate, qreg* reg, int* qubits);
Time complexity: 	O((gate.nqubits)*2^(gate.nqubits+reg->nqubits))
Memory complexity: 	O(2^(reg->nqubits))
Description: 		This function applies the quantum gate 'gate' to the qubits in 'reg'. The qubits of 'reg' upon which the gate acts are defined in the array 'qubits', which must be of length gate->nqubits.
Example:
void main(){
	//create a new quantum register with 2 qubits
	qreg newregister = newqreg(1);
	//print the newly created quantum register
	printf("\nInitialized register:");
	qprint(newregister);

	int qubits1[1]={0};
	applyqgate(Hgate, &newregister, qubits1);
	printf("\nRegister after Hadamard gate on qubit 0:");
	qprint(newregister);

	//exit successfully
	return 0;
}
Output:
Initialized register:
0: 1
1: 0

Register after Hadamard gate on qubit 0:
0: 0.707107
1: 0.707107




## The gates


Name:			Hadamard Gate 
Variable name: 		Hgate
nQubits: 		1
Description: 		Gives a 1-qubit rotation. When applied to a qubit in a definite state it will put the qubit in a superposition of states with equal weight.
Example:
void main(){
	//print the gate
	printf("\nThe Hadamard gate:");
	qgateprint(Hgate);
	
	//create a new initialized register
	qreg newregister = newqreg(1);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Hadamard gate
	int qubits1[1]={0};
	applyqgate(Hgate, &newregister, qubits1);
	printf("\nAfter Hadamard gate:");
	qprint(newregister);
	
	//exit successfully
	return 0;
}
Output:
The Hadamard gate:
0.707107	0.707107	
0.707107	-0.707107	

Initialized register:
0: 1
1: 0

After Hadamard gate:
0: 0.707107
1: 0.707107


Name:			Controlled NOT gate 
Variable name: 		CNOTgate
nQubits: 		2: 0 is target, 1 is control
Description: 		Also called Controlled Pauli-X gate. When the control qubit's state is 1 it flips the state of the target qubit.
Example:
void main(){
	//print the gate
	printf("\nThe Controlled NOT gate:");
	qgateprint(CNOTgate);
	
	//create a new initialized register
	qreg newregister = newqreg(2);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Hadamard gate first to better demonstrate the effect of the Controlled NOT gate
	int qubits1[1]={1};
	applyqgate(Hgate, &newregister, qubits1);
	printf("\nAfter Hadamard gate on qubit 1:");
	qprint(newregister);
	
	//apply the Controlled NOT gate
	int qubits2[2]={0,1};
	applyqgate(CNOTgate, &newregister, qubits2);
	printf("\nAfter Controlled NOT gate on qubits 0 (target) and 1 (control):");
	qprint(newregister);
	

	//exit successfully
	return 0;
}
Output:
Controlled NOT gate:
1	0	0	0	
0	1	0	0	
0	0	0	1	
0	0	1	0	

Initialized register:
00: 1
01: 0
10: 0
11: 0

After Hadamard gate on qubit 1:
00: 0.707107
01: 0
10: 0.707107
11: 0

After Controlled NOT gate on qubits 0 (target) and 1 (control):
00: 0.707107
01: 0
10: 0
11: 0.707107


Name:			Pauli-X gate
Variable name: 		Xgate
nQubits: 		1
Description: 		Also called quantum NOT gate. Rotates the qubit by pi radians around the X axis of the Bloch sphere. 
Example:
void main(){
	//print the gate
	printf("\nThe Pauli-X gate:");
	qgateprint(Xgate);
	
	//create a new initialized register
	qreg newregister = newqreg(1);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Pauli-X
	int qubits1[1]={0};
	applyqgate(Xgate, &newregister, qubits1);
	printf("\nAfter Pauli-X gate:");
	qprint(newregister);
	
	//exit successfully
	return 0;
}
Output:
The Pauli-X gate:
0	1	
1	0	

Initialized register:
0: 1
1: 0

After Pauli-X gate:
0: 0
1: 1


Name:			Pauli-Y gate
Variable name: 		Ygate
nQubits: 		1
Description: 		Rotates the qubit by pi radians around the Y axis of the Bloch sphere. 
Example:
void main(){
	//print the gate
	printf("\nThe Pauli-Y gate:");
	qgateprint(Ygate);
	
	//create a new initialized register
	qreg newregister = newqreg(1);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Pauli-Y
	int qubits1[1]={0};
	applyqgate(Ygate, &newregister, qubits1);
	printf("\nAfter Pauli-Y gate:");
	qprint(newregister);
	
	//exit successfully
	return 0;
}
Output:
The Pauli-Y gate:
0	-i	
i	0	

Initialized register:
0: 1
1: 0

After Pauli-Y gate:
0: 0
1: i


Name:			Pauli-Z gate
Variable name: 		Zgate
nQubits: 		1
Description: 		Also called a phase flip gate. Rotates the qubit by pi radians around the Z axis of the Bloch sphere. 
Example:
void main(){
	//print the gate
	printf("\nThe Pauli-Z gate:");
	qgateprint(Zgate);
	
	//create a new initialized register
	qreg newregister = newqreg(1);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Hadamard gate first, to better demonstrate the effect of the Pauli-Z gate
	int qubits1[1]={0};
	applyqgate(Hgate, &newregister, qubits1);
	printf("\nAfter Hadamard gate:");
	qprint(newregister);

	//apply the Pauli-Z
	applyqgate(Zgate, &newregister, qubits1);
	printf("\nAfter Pauli-Z gate:");
	qprint(newregister);
	
	//exit successfully
	return 0;
}
Output:
The Pauli-Z gate:
1	0	
0	-1	

Initialized register:
0: 1
1: 0

After Hadamard gate:
0: 0.707107
1: 0.707107

After Pauli-Z gate:
0: 0.707107
1: -0.707107


Name:			Swap gate 
Variable name: 		SWAPgate
nQubits: 		2
Description: 		Swaps the states of two qubits with eachother.
Example:
void main(){
	//print the gate
	printf("\nThe swap gate:");
	qgateprint(SWAPgate);
	
	//create a new initialized register
	qreg newregister = newqreg(2);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Hadamard gate first to better demonstrate the effect of the swap gate
	int qubits1[1]={0};
	applyqgate(Hgate, &newregister, qubits1);
	printf("\nAfter Hadamard gate on qubit 1:");
	qprint(newregister);
	
	//apply the swap
	int qubits2[2]={0,1};
	applyqgate(SWAPgate, &newregister, qubits2);
	printf("\nAfter swap gate on qubits 0 and 1:");
	qprint(newregister);
	
	//exit successfully
	return 0;
}
Output:
The swap gate:
1	0	0	0	
0	0	1	0	
0	1	0	0	
0	0	0	1	

Initialized register:
00: 1
01: 0
10: 0
11: 0

After Hadamard gate on qubit 1:
00: 0.707107
01: 0.707107
10: 0
11: 0

After swap gate on qubits 0 and 1:
00: 0.707107
01: 0
10: 0.707107
11: 0


Name:			Square root of Swap gate 
Variable name: 		sqrtSWAPgate
nQubits: 		2
Description: 		Half-way swaps the states of two qubits with eachother. It is considered universal as many quantum gates can be constructed from 'sqrtSWAP' and single qubit gates.
Example:
void main(){
	//print the gate
	printf("\nThe square root of Swap gate:");
	qgateprint(sqrtSWAPgate);
	
	//create a new initialized register
	qreg newregister = newqreg(2);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Hadamard gate first to better demonstrate the effect of the square root of the swap gate
	int qubits1[1]={0};
	applyqgate(Hgate, &newregister, qubits1);
	printf("\nAfter Hadamard gate on qubit 1:");
	qprint(newregister);
	
	//apply the sqrtSWAP gate
	int qubits2[2]={0,1};
	applyqgate(sqrtSWAPgate, &newregister, qubits2);
	printf("\nAfter square root of swap gate on qubits 0 and 1:");
	qprint(newregister);

	//apply the sqrtSWAP gate a second time to demonstrate full swap
	applyqgate(sqrtSWAPgate, &newregister, qubits2);
	printf("\nAfter second square root of swap gate on qubits 0 and 1:");
	qprint(newregister);
	
	//exit successfully
	return 0;
}
Output:
The square root of Swap gate:
1	0	0	0	
0	0.5+0.5i	0.5-0.5i	0	
0	0.5-0.5i	0.5+0.5i	0	
0	0	0	1	

Initialized register:
00: 1
01: 0
10: 0
11: 0

After Hadamard gate on qubit 1:
00: 0.707107
01: 0.707107
10: 0
11: 0

After square root of swap gate on qubits 0 and 1:
00: 0.707107
01: 0.353553+0.353553i
10: 0.353553-0.353553i
11: 0

After second square root of swap gate on qubits 0 and 1:
00: 0.707107
01: 0
10: 0.707107
11: 0


Name:			Toffoli gate
Variable name: 		CCNOTgate
nQubits: 		3: 0 is target, 1 and 2 are control
Description: 		 When the both the control qubits' states are 1 it flips the state of the target qubit. It is universal for classical computation.
Example:
void main(){
	//print the gate
	printf("\nThe Toffoli gate:");
	qgateprint(CCNOTgate);
	
	//create a new initialized register
	qreg newregister = newqreg(3);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Pauli-X gate first to better demonstrate the effect of the Toffoli gate
	int qubits1[1]={1};
	applyqgate(Xgate, &newregister, qubits1);
	printf("\nAfter Pauli-X gate on qubit 1:");
	qprint(newregister);

	//apply the Pauli-X gate first to better demonstrate the effect of the Toffoli gate
	qubits1[0]=2;
	applyqgate(Xgate, &newregister, qubits1);
	printf("\nAfter Pauli-X gate on qubit 2:");
	qprint(newregister);
	
	//apply the Toffoli gate
	int qubits3[3]={0,1,2};
	applyqgate(CCNOTgate, &newregister, qubits3);
	printf("\nAfter Toffoli gate on qubit 0 (target) and qubits 1 and 2 (control):");
	qprint(newregister);

	
	//exit successfully
	return 0;
}
Output:
The Toffoli gate:
1	0	0	0	0	0	0	0	
0	1	0	0	0	0	0	0	
0	0	1	0	0	0	0	0	
0	0	0	1	0	0	0	0	
0	0	0	0	1	0	0	0	
0	0	0	0	0	1	0	0	
0	0	0	0	0	0	0	1	
0	0	0	0	0	0	1	0	

Initialized register:
000: 1
001: 0
010: 0
011: 0
100: 0
101: 0
110: 0
111: 0

After Pauli-X gate on qubit 1:
000: 0
001: 0
010: 1
011: 0
100: 0
101: 0
110: 0
111: 0

After Pauli-X gate on qubit 2:
000: 0
001: 0
010: 0
011: 0
100: 0
101: 0
110: 1
111: 0

After Toffoli gate on qubit 0 (target) and qubits 1 and 2 (control):
000: 0
001: 0
010: 0
011: 0
100: 0
101: 0
110: 0
111: 1


Name:			Fredkin gate
Variable name: 		CSWAPgate
nQubits: 		3: 0 and 1 are target, 2 is control
Description: 		 When the the control qubit's states is 1 it flips the states of the target qubits. It is universal for classical computation.
Example:
void main(){
	//print the gate
	printf("\nThe Fredkin gate:");
	qgateprint(CSWAPgate);
	
	//create a new initialized register
	qreg newregister = newqreg(3);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Pauli-X gate first to better demonstrate the effect of the Fredkin gate
	int qubits1[1]={1};
	applyqgate(Xgate, &newregister, qubits1);
	printf("\nAfter Pauli-X gate on qubit 1:");
	qprint(newregister);

	//apply the Pauli-X gate first to better demonstrate the effect of the Fredkin gate
	qubits1[0]=2;
	applyqgate(Xgate, &newregister, qubits1);
	printf("\nAfter Pauli-X gate on qubit 2:");
	qprint(newregister);
	
	//apply the Fredkin gate
	int qubits3[3]={0,1,2};
	applyqgate(CSWAPgate, &newregister, qubits3);
	printf("\nAfter Fredkin gate on qubits 0 and 1 (target) and qubit 2 (control):");
	qprint(newregister);

	
	//exit successfully
	return 0;
}
Output:
The Fredkin gate:
1	0	0	0	0	0	0	0	
0	1	0	0	0	0	0	0	
0	0	1	0	0	0	0	0	
0	0	0	1	0	0	0	0	
0	0	0	0	1	0	0	0	
0	0	0	0	0	0	1	0	
0	0	0	0	0	1	0	0	
0	0	0	0	0	0	0	1	

Initialized register:
000: 1
001: 0
010: 0
011: 0
100: 0
101: 0
110: 0
111: 0

After Pauli-X gate on qubit 1:
000: 0
001: 0
010: 1
011: 0
100: 0
101: 0
110: 0
111: 0

After Pauli-X gate on qubit 2:
000: 0
001: 0
010: 0
011: 0
100: 0
101: 0
110: 1
111: 0

After Fredkin gate on qubits 0 and 1 (target) and qubit 2 (control):
000: 0
001: 0
010: 0
011: 0
100: 0
101: 1
110: 0
111: 0


Name:			Phase shift gate
Prototype: 		qgate Rgate(double angle);
Time complexity: 	O(1)
Memory complexity: 	O(1)
nQubits: 		1
Description: 		This function returns a quantum phase shift gate of 'angle' radians. This is equivalent to tracing a horizontal arc (a line of latitude) on the Bloch Sphere by 'angle' radians.
Example:
void main(){
	//print the gate
	printf("\nThe pi/4 phase shift gate:");
	qgateprint(Rgate(M_PI/4.0));
	
	//create a new initialized register
	qreg newregister = newqreg(1);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Hadamard gate first, to better demonstrate the effect of the phase shift gate
	int qubits1[1]={0};
	applyqgate(Hgate, &newregister, qubits1);
	printf("\nAfter Hadamard gate:");
	qprint(newregister);

	//apply the Pauli-Z
	applyqgate(Rgate(M_PI/4.0), &newregister, qubits1);
	printf("\nAfter pi/4 phase shift gate:");
	qprint(newregister);
	
	//exit successfully
	return 0;
}
Output:
The pi/4 phase shift gate:
1	0	
0	0.707107+0.707107i	

Initialized register:
0: 1
1: 0

After Hadamard gate:
0: 0.707107
1: 0.707107

After pi/4 phase shift gate:
0: 0.707107
1: 0.5+0.5i


Name:			Quantum Fourier transform
Prototype: 		qgate QFTgate(int nqubits);
Time complexity: 	O(1)
Memory complexity: 	O(4^(nqubits))
nQubits: 		1
Description: 		This function returns a quantum phase shift gate of 'angle' radians. This is equivalent to tracing a horizontal arc (a line of latitude) on the Bloch Sphere by 'angle' radians.
Example:
void main(){
	//print the gate
	printf("\nThe quantum Fourier transform gate of size 4:");
	qgateprint(QFTgate(2));
	
	//create a new initialized register
	qreg newregister = newqreg(2);
	printf("\nInitialized register:");
	qprint(newregister);
	
	//apply the Hadamard gate first, to better demonstrate the effect of the quantum Fourier transform gate
	int qubits1[1]={1};
	applyqgate(Hgate, &newregister, qubits1);
	printf("\nAfter Hadamard gate:");
	qprint(newregister);
	
	

	
	qubits1[0]=1;
	applyqgate(Zgate, &newregister, qubits1);
	printf("\nAfter Z gate:");
	qprint(newregister);
	
	
	//apply the quantum Fourier transform gate
	int qubits4[2]={0,1};
	applyqgate(QFTgate(2), &newregister, qubits4);
	printf("\nAfter the quantum Fourier transform gate:");
	qprint(newregister);
	
	//exit successfully
	return 0;
}
Output:
The quantum Fourier transform gate of size 4:
0.5	0.5	0.5	0.5	
0.5	0.5i	-0.5	-0.5i	
0.5	-0.5	0.5	-0.5	
0.5	-0.5i	-0.5	0.5i	

Initialized register:
00: 1
01: 0
10: 0
11: 0

After Hadamard gate:
00: 0.707107
01: 0
10: 0.707107
11: 0

After Z gate:
00: 0.707107
01: 0
10: -0.707107
11: 0

After the quantum Fourier transform gate:
00: 0
01: 0.707107
10: 0
11: 0.707107



