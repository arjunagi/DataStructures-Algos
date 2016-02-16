### Calculator for “Infinitely” Long Numbers

Given two really large non-negative integers, A and B, of unknown length (could be hundreds of digits), compute the accurate values of 
A+B, A-B, and A*B. However, you can only perform +, -, * for very small numbers directly. In this project, the goal is to implement a 
calculator for such “infinitely” long numbers. The 2 integers A and B are stored in seperate txt files.

The program should write to an output file the sum, difference, and product of the two input long numbers, 
as well as the number of block operations performed to obtain each of these values. 

**Block Size:** The number of digits considered at a time for each operation. For example if the numbers are **1234** and **5678** and
block size is **3**, the operations will start with the number **234** and **678**, i.e, 3 digits at a time. 

**Example:**                                                                                                                            
For the below input with block size equal to 2:                                                                                         
1234554321098761111100022                                                                                                           
3205                                                                                                                                    

The output file will be                                                                                                               
**sum:** 1 block operation.                                                                                                             
1234554321098761111103227                                                                                                               
**difference:** 4 block operations.                                                                                                      
1234554321098761111096817                                                                                                               
**product:** 55 block operations.                                                                                                       
3956746599121529361075570510                                                                                                            

**Execution:**                                                                                                                        
The program will run using the below command:                                                                                         
a.out –k op1 op2 result                                                                                                                 
where k is the block size and result is the name of the result file.



