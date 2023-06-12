# Final-projrct
This is a simple program for personal accounting.


* In addition to the standard C library, this program also utilizes the <conio.h> library. To fully execute the program, you need to install this library beforehand.
* To compile all the program files into an executable, you can enter the following command in the terminal:
```
gcc main.c functions.c  file.c op1_add.c op2_delete.c op3_search.c op4_show.c op5_search_category.c op6_count.c -o program
```

Upon entering the program, you will first see the following interface.

![image](https://github.com/910605jeremy/Final-projrct/assets/132763427/307e6f1f-9a4a-4905-ab30-5262df1df63f)

Entering 1 will load the contents of file.txt, where you can make simple personalization settings according to the specified format.


Format:
> Category:
> (Enter the number of desired account categories here)
> (Enter the name of each account category on a separate line)
> 
> Date: date, amount, category, type, note
> (Each line represents an input entry, with the format **YYYY MM DD amount category type note**)

The following is an example input format:
> Category:
> 3
> Food
> Transportation
> Clothing
> Date: date, amout, category, type, note
> 0002 02 02 2.000000 Transportation 0 no
> 0001 01 01 3.000000 Food 1 no
> 0001 01 01 2.000000 Food 1 no
> 0001 01 01 1.000000 Food 1 no


This example input includes 3 category names: Food, Transportation, and Clothing, and 4 records of transactions.

Here is the breakdown of the first record:

* Date: 0002/02/02
* Amount: 2
* Category: Transportation
* Type: Expense (0 indicates an expense)
* Note: "no" (no specific note for this transaction)

After selecting option 1, the program will display the following interface.

![image](https://github.com/910605jeremy/Final-projrct/assets/132763427/c01b9478-849b-4f1b-bb89-66876840f30a)



---

Next, you will enter this interface where you can select the desired functionality. After selecting the function, follow the input instructions on the screen to proceed.

![image](https://github.com/910605jeremy/Final-projrct/assets/132763427/7c4fd989-1c5d-4078-92bd-609b076e7351)

* The "help" function provides information about input length or number size restrictions.
* The "setting" function allows users to change the number of decimal places displayed and the number of records shown in function 4.
* Function 7 saves the current records in a specific format in the "output.txt" file (the format is the same as "file.txt").
* When choosing "exit," the program will ask if you want to save the current data before closing. The saving method is the same as in function 7.
*the dfs game:the user will enter an integer n that indicates the number of vertices in a graph. The value of n must be between 2 and 100 (inclusive). The following n lines will contain an adjacency list. Each line represents a list of vertices that are adjacent to the vertex represented by the first number on the line. Your program should output "YES" if there’s a cycle in this graph, and "NO" if there’s no cycle. 

Wishing you a smooth user experience.
