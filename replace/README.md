
# Replace Utility

A command line utility used to replace a certain string in a file/multiple files with another word.

## Specifications
- looks for all occurrences of string from and replaces it with string to.
It is possible to specify one or more files on which to perform the replace operation(s) in a single replace command.  

## Compilation 
- ```make``` will generate the binary file you can use. 
- Or import the project files in you favorite IDE and compile it.

## Usage
```
replace OPT <from> <to> -- <filename> [<filename>]*
 ```
- where OPT can be zero or more of
	- -b : if specified, the replace utility creates a backup copy of each file on which a replace operation is performed before modifying it.
	- -f : if specified, the replace utility only replaces the first occurrence of string from in each file.
	- -l : if specified, the replace utility only replaces the last occurrence of string from in each file.
	- -i : if specified, the replace utility performs the search for string from in a case insensitive way.
- from: string to be replaced with string to.
- to: string that will replace string from.
- filename: the file(s) on which the replace operation has to be performed.

  

## Examples

### Example 1:
```replace -i Howdy Hello -- file1.txt file2.txt file3.txt```
would replace all occurrences of “Howdy” with “Hello” in the files specified. Because the “-i” option is specified, occurrences of “howdy”, “HOwdy”,
“HOWDY”, and so on would also be replaced.
### Example 2:
```replace -b -f Bill William -- file1.txt file2.txt```
would replace the first occurrence of “Bill” with “William” in the two files specified. It would also create a backup copy of the two files before performing the replace.
### Example 3:
```replace -f -l abc ABC -- file1.txt```
would replace both the first and the last occurrences of “abc” with “ABC” in the file specified.
