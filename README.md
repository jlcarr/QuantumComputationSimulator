# Quantum Computation Simulator

A c library for simulating quantum computation in ideal conditions.

## Features
* Uses standard c complex number library.
* Common quantum logic gates included.
* Measurements in standard basis and Hadamard basis included.
* Easily integrated with linear algebra libraries.
* Simple design and usage.

## Installation
None required; simply dowload the library, compile it, then include it in your main.c

```console
$ gcc -c -g quantum.c
$ gcc -c -g main.c
$ gcc -g -o main main.o quantum.o
```

## Usage
### Creating Quantum Registers

```c
qreg newRegister = newqreg(3); //3 is the number of qubits in the new register for a total of 2^3=8 states
qprint(newRegister);
```

Output will be:
```console
000: 1
001: 0
010: 0
011: 0
100: 0
101: 0
110: 0
111: 0
```

### Applying Quantum Logic Gates

To apply a quantum logic gate to a quantum register you must tell the function 'applyqgate' which gate you want to apply, to which register and upon which qubits in the register.

```c
qreg newRegister = newqreg(2);
int qubittarget[1]={0};
applyqgate(Hgate, &newRegister, qubittarget);
qprint(newRegister);
```

Output will be:
```console
00: 0.707107
01: 0.707107
10: 0
11: 0
```
