## Unix File Operations

A program that performs some basic file operations similar to UNIX commands. It will first identify the operation to perform 
from the command line and then perform the operation on the data from input file(s).

#### Operations & Their Execution:
You will need 2 seperate text files file1.txt and file2.txt to perform the below operations.

1. Copy contents of file1 to file 2.                                                                                                       
   **Execution:** a.out 0 file1.txt file2.txt 
2. Interleave lines from file1 and file2. Store the result in file3.                                                                      
   **Execution:** a.out 1 file1.txt file2.txt file3.txt 
3. More - This operation simulates the UNIX more command. Your program should first print out the first 10 lines of the input 
file file1.txt on the screen and then wait for user input 
   * If the user inputs ‘n’, your program should print out the next line of the file 
   * If the user inputs ‘p’, your program should print out the next ten lines of the file 
   * If the user inputs ‘q’, your program should terminate without any more print out                                                      
  **Execution:** a.out 2 file1.txt 
4. Grep - print out every line that contains at least one instance of the input character string in file1.txt.                                                                                                                                 
   **Execution:** a.out 3 file1.txt 
5. Word count - count number of lines, words, characters, shortest line in terms of words and shortest line in terms of characters.        
   **Execution:** a.out 4 file1.txt
  
