# OSP-Segmented Memory Allocator

## Table of contents
* [Structure](#structure)
* [Language](#language)
* [Setup](#setup)

## Structure
This project includes some classes:
* main: read the arguments from console, call necessary functions (read input file -> generate random numbers for deallocation 
-> perform on each allocation strategy -> output details to file)

* AllocationStrategy: a super class contains the similar functions between 3 allocation strategies
including getter, setter, constructor (create 2 LinkedLists and initialize an amount of total memory allocated)
and output all necessary details to file.

* FirstFit, BestFit, WorstFit: 3 child classes represent each strategy, with different 'perform' function based on 
different implementation.

* LinkedList: a class acts as a linkedlist to represent allocMBList and freedMBList

* MemoryBlock: represent a memory block which consists of address, size, content and id (helpful for sorting freedMBList)

* Utility: store helper methods including read names from file, generate random numbers for deallocation, allocate memory to hole (or split hole),
perform read 1000 and delete 500 names.

* first-names-1.txt, middle-names.txt: files with dataset
	
## Language
C++ is used so instead of c file, this project contains .h file and .cpp file
* .h file: declaration of the class
* .cpp file: definition of the class
	
## Setup
* To run this project using Makefile from terminal:

```
$ make
$ ./main inputFileName outputFileNameForFirstFit outputFileNameForBestFit outputFileNameForWorstFit
```
* Example: ./main middle-names.txt firstfit.txt bestfit.txt worstfit.txt

* If not enough output file names are provided, the default file for each strategy (FF.txt, BF.txt, WF.txt for First Fit, Best Fit, Worst Fit respectively)
will be generated automatically
