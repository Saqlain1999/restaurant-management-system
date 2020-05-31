# restaurant-management-system
Restaurant Management System using C Programming Language, its an basic script made as a project for first semester programming Course

C Syntax Cheat sheet we created to help us when using the commands and functions

fopen("filename.filetype","mode");
feof(file_pointer)
fprintf(file_pointer,"comment");
fprintf(file_pointer,array);
fprintf(file_pointer,'character');
gets doesn't give new line
fgets(array_name,array_size,file_pointer);//stops at new line
fscanf(file_pointer,"%s",array or startaddress);//stops at spaces
puts(array_name);//gives new line at the end of array
fputs(array_name,file_pointer);
fseek(data_file,0,SEEK_SET);//SEEK_SET,SEEK_CUR, SEEK_END
ftell(filename); //tells the position of the pointer in the file.

NOTE - int array doesn't have \0 at the end of the array

requires <ctype.h>
isalpha(variable)//checks if variable has an alphabet in it
isdigit(variable)//checks if variable has a number in it
isupper(variable)//checks if variable has an upper case alphabet in it
toupper(variable)//converts a lower case alphabet to an upper case letter


strcat(variable,"" or array or '');//appends variable //btw you cant strcat a character into a string its called strcat for a reason!.
strnicmp(string1,string2,stringlengthtobecomparedfromstart)//compares substrings without case sensitivity and ignores a new line char.
strstr(string1,string2); //string 2 being compared with each of the character anywhere in the string. If similar.. Gives abnormal value else 0.



typecasting
(float)int_variable//treats the integer variable as a float


floor(variable)//rounds down the number
ceil(variable)//rounds to the next number
abs(variable)//absolute value of the number
power(n,power)//where n is the number you want to find power of
sqrt(variable)//gives square root value
