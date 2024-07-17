#include<iostream>
using namespace std;

unsigned int strlen(const char* str);
char* strcat(char* dst, const char* src);
char* strcpy(char* dst, const char* src);
int strcmp(const char* str1, const char* str2);
char* convert_case(char* str);
int* count_char(const char* str);
int match_substr(const char* str, const char* pattern, int* &pos);

bool match(const char* str, const char *pattern);

int main()
{
	return 0;
}

unsigned int strlen(const char* str)
{
	const char* eos = str;
	while (*eos)
		eos++;
	return eos - str;
}

char* strcat(char* dst, const char* src)
{
	char* tmp = dst;
	while (*tmp)
		tmp++;
	while (*src)
		*tmp++ = *src++;
	*tmp = *src;
	return dst;
}

char* strcpy(char* dst, const char* src)
{
	char* tmp = dst;
	while (*src)
		*tmp++ = *src++;
	*tmp = *src;
	return dst;
}

int strcmp(const char* str1, const char* str2)
{
	while (*str1 == *str2 && *str1 && *str2)
		str1++, str2++;
	return int(*str1 - *str2);
}

char* convert_case(char* str)
{
	char *tmp = str;
	while (*tmp)
	{
		if (*tmp >= 'A' && *tmp <= 'Z')
			*tmp += 'a' - 'A';
		else if (*tmp >= 'a' && *tmp <= 'z')
			*tmp += 'A' - 'a';
		tmp++;
	}
	return str;
}

int* count_char(const char* str)
{
	int* count = new int[128];
	for (int i = 0; i < 128; i++)
		*(count + i) = 0;
	while (*str)
		count[*str++]++;
	return count;
}

int match_substr(const char* str, const char* pattern, int* &pos)
{
	int count = 0;
	if (pos == nullptr)
		pos = new int[strlen(str)];
	for (int i = 0; i < strlen(str); i++)
		if (match(str + i, pattern))
			pos[count++] = i;
	return count;
}

bool match(const char* str, const char *pattern)
{
	while (*pattern)
	{
		if (*str == '\0' || *str != *pattern)
			return false;
		str++, pattern++;
	}
	return true;
}