#include "shell.h"

/**
* str_concat - concatenates two strings.
* @string1: String to be concatenated
* @string2: String to be concatenated
*
* Return: pointer to the array
*/
char *str_concat(char *string1, char *string2)
{
char *result;
int length1 = 0, length2 = 0;

if (string1 == NULL)
string1 = "";
length1 = str_length(string1);

if (string2 == NULL)
string2 = "";
length2 = str_length(string2);

result = malloc(sizeof(char) * (length1 + length2 + 1));
if (result == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}

/* copy string1 */
for (length1 = 0; string1[length1] != '\0'; length1++)
result[length1] = string1[length1];
free(string1);

/* copy string2 */
for (length2 = 0; string2[length2] != '\0'; length2++)
{
result[length1] = string2[length2];
length1++;
}

result[length1] = '\0';
return (result);
}
/**
* long_to_string - converts a numbers to a string.
* @number: numbers to be converten in an string.
* @string: buffer to save the numbers as a string.
* @base: base to convert the numbers
*
* Return: 0
*/
void long_to_string(long number, char *string, int base)
{
int index = 0, inNegative = 0;
long cociente = number;
char letters[] = {"0123456789abcdef"};

if (cociente == 0)
string[index++] = '0';

if (string[0] == '-')
inNegative = 1;

while (cociente)
{
if (cociente < 0)
string[index++] = letters[-(cociente % base)];
else
string[index++] = letters[cociente % base];
cociente /= base;
}
if (inNegative)
string[index++] = '-';

string[index] = '\0';
str_reverse(string);
}
193,1         Bot

/**
* _atoi - convert the string to an integer.
*
* @s: pointer to origin  string.
* Return: int of string or 0.
*/
int _atoi(char *s)
{
int sign = 1;
unsigned int number = 0;
/*1- analisys sign*/
while (!('0' <= *s && *s <= '9') && *s != '\0')
{
if (*s == '-')
sign *= -1;
if (*s == '+')
sign *= +1;
s++;
}

/*2 - extract the number */
while ('0' <= *s && *s <= '9' && *s != '\0')
{

number = (number * 10) + (*s - '0');
s++;
}
return (number * sign);
}


/**
* count_characters - count the coincidences of character in the string.
*
* @string: pointer to origin string
* @character: string with  characters to be counted
* Return: int of the string or 0.
*/
int count_characters(char *string, char *character)
{
int i = 0, counter = 0;

for (; string[i]; i++)
{
if (string[i] == character[0])
counter++;
}
return (counter);
}
