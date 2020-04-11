# OS-Slob-Allocator
Slob Allocator simulation in c++.

The SLOB (Simple list of blocks) allocator is one of three available memory allocators in the Linux kernel. (The other two are SLAB and SLUB.) The SLOB allocator is designed to require little memory for the implementation and housekeeping, for use in small systems such as embedded systems. Unfortunately, a major limitation of the SLOB allocator is that it suffers greatly from internal fragmentation.

SLOB currently uses a first-fit algorithm, which uses the first available space for memory. The intention of this project was to implement three different algorithms, and to determine which algorithm finds the smallest space which fits the required amount available, avoiding loss of performance, both by fragmentation and consolidation of memory. 

## Algorithms
The three algorithms implemented in this project are, Best Fit, Worst Fit, First Fit. 
Best Fit, minimize internal fragmentation by making out the best space chunk but it searches the whole list for collection. 
Worst Fit allocates a process to the partition which is largest sufficient among the freely available partitions available in the main memory.
In the first fit, the partition is allocated which is first sufficient from the top of Main Memory. It does not searches the whole list for collection.

## Furthure Work:
With this slob allocator, I plan to instal the suitable Operating system on the Raspberry Pi 3 named Raspbian(NOOBS). Thereafter instal the Kernel for the configuration of this self-made SLOB allocator.
![Raspberry Pi 3](https://user-images.githubusercontent.com/63517656/79056088-ecf42b80-7c0f-11ea-9411-31414b6f03f9.png)

## Sample run:
<img width="907" alt="Graphical Comparison" src="https://user-images.githubusercontent.com/63517656/79056479-43636900-7c14-11ea-83a3-2d69af3ecab1.png">

## Pre-requisite for running this program:
1.	A windows machine.
2.  Install WinBGIm Graphics Library with the Dev-C++

## How to install WinBGIm Graphics Library:
1. Download and install Dev-C++. I downloaded it from https://www.cs.colorado.edu/~main/bgi/dev-c++/devcpp-4.9.9.2_setup.exe
2. Download graphics.h to the include/ subdirectory of the Dev-C++ directories. I downloaded it from: https://www.cs.colorado.edu/~main/bgi/dev-c++/graphics.h
3. Download libbgi.a to the lib/ In order to use the WinBGIm subdirectory of the Dev-C++ directories. I downloaded it from https://www.cs.colorado.edu/~main/bgi/dev-c++/libbgi.a
4. Whenever you #include <graphics.h> in a program, you must instruct the linker to link in certain libraries. The command to do so from Dev-C++ is Alt-P. Choose the Parameters tab from the pop-up window and type the following into the Linker area:

		-lbgi
		-lgdi32
		-lcomdlg32
		-luuid
		-loleaut32
		-lole32
