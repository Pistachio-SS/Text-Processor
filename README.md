# Text-Processor
In terms of your task, it is fairly easy to describe. You will be writing a simple text processor
console application. The application, namely ‘kode’, received a command, a parameter, and a
filename in the command line and processes the file based on the given command.
1. kode RC <word> <file>
(Remove Case Sensitive)
Replaces all instance of <word> in <file> with asterisks. The number of asterisks
correspond to the number of characters in <word>. The search is case-sensitive. The
word replacement is in-place (same file is modified). At the end the program reports of
the changes to the console.
2. kode RI <word> <file>
(Remove Ignore Case)
Replaces all instance of <word> in <file> with asterisks. The number of asterisks
correspond to the number of characters in <word>. The search is case-insensitive. The
word replacement is in-place (same file is modified).
3. kode UK <word> <file>
(Un-remove Keep Case)
Searches for possible places that <word> may have been removed (by matching the
number of asterisks with the word length).
Replaces the asterisks with <word> in <file>. The number of asterisks correspond to the
number of characters in <word>. The exact word is replaced. The user confirms each
change.
4. kode UM <word> <file>
(Un-remove Match Case)
Searches for possible places that <word> may have been removed (by matching the
number of asterisks with the word length). The user confirms each change.
2
Replaces the asterisks with <word> in <file>. The number of asterisks correspond to the
number of characters in <word>. The word is transformed to upper-case or lower-case,
depending on the letter before. If there is no letter before the placeholder, the letter after
is checked. If there is no letter after, it follows the UM option above.
Whitespaces
Blank, tab, newlines, line/form feed characters are all considered as white spaces. All words are
separated by whitespaces. You may not consider punctuations as separators.
Examples:
Suppose you have the following text file called file.txt
This is a text file that contains ~Apples and Oranges~.
An apple a day keeps the doctor away!
Apples or Oranges? That is the question!
Example 1: kode RC apple file.txt will result in the text file to be changed to:
This is a text file that contains ~Apples and Oranges~.
An ***** a day keeps the doctor away!
Apples or Oranges? That is the question!
Example 2: kode RI apple file.txt will result in the text file to be changed to:
This is a text file that contains ~*****s and Oranges~.
An ***** a day keeps the doctor away!
*****s or Oranges? That is the question!
Example 3: kode UK APPLE file.txt will result in the text file to be changed to the
following, assuming it runs on the resulting file in example 2.
This is a text file that contains ~APPLEs and Oranges~.
An APPLE a day keeps the doctor away!
APPLEs or Oranges? That is the question!
Example 4: kode UM ApplE file.txt will result in the text file to be changed to the
following, assuming it runs on the resulting file in example 2.
This is a text file that contains ~apples and Oranges~.
An ApplE a day keeps the doctor away!
apples or Oranges? That is the question!
Change Confirmations:
For all cases, the user must confirm the change, before it is applied on the file. To do so, the
following message must be displayed to the user, where <before> is the actual text in the line
<lineno> in given text file, and <after> is the proposed change.
3
Changing line <lineno> from
<before>
to
<after>
Confirm (Yes, No, All, Quit)?
Upon Y or Yes from the user, the change is accepted, upon receiving N or No, the change is
skipped (no change is applied), upon receiving A or All the change is accepted and no further
confirmation is asked, and upon receiving Q or Quit, the program exists without any further
changes. All inputs are case insensitive.
For instance, in running Example 3, the first message will display:
Changing line 1 from
This is a text file that contains ~*****s and Oranges~.
to
This is a text file that contains ~APPLEs and Oranges~.
Confirm (Yes, No, All, Quit)? _
The ‘_’ symbol indicates where the cursor must wait for the user’s response. Upon typing `a’
followed by an enter, no more messages will be displayed.
Summary and Return Code:
After making all changes, the program displays the summary of changes and exists with return
code 0. For instance in example 1, the following message is displayed:
Changed 1 word(s) in 1 line(s).
If no matches are found, the program displays 0 change and terminates with return code 2.
If the user selects Quit at some point, the program displays the changes so far and terminates
with return code 1.
Abnormal Errors:
In case of any abnormal error (i.e. file IO error, memory error, etc.), you program must display
the error message on stderr and abnormally terminate using return code 3.
File I/O
If you haven’t done much programming with files and directories, it isn’t especially difficult.
That said, the facilities for doing so in C are somewhat more primitive than those in languages
such as Java. First, you want to make use of the functions associated with <stdio.h>. As we
discussed in class, these are the basic IO functions, and can be applied not only to the screen
and keyboard, but to disk files as well (There are countless online examples of basic C-based
I/O). Here, you will use functions for opening and closing files, reading and writing
bytes/chars to and from files, and for checking to see if you have reached the end of the file. 
