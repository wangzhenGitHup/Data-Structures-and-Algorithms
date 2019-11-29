#include <iostream>

#include "MyArray.h"
#include "ArrayStack.h"

using namespace std;

bool MatchSignLA(const char* sign)
{
	ArrayStack<char> charStack;
	while (*sign != '\0')
	{
		if ((*sign == '{') ||
			(*sign == '[') ||
			(*sign == '('))
		{
			charStack.Push(*sign);
		}
		else
		{
			char topSign = charStack.Top();
			if (topSign == '{' && (*sign) == '}')
			{
				charStack.Pop();
			}
			else if (topSign == '[' && (*sign) == ']')
			{
				charStack.Pop();
			}
			else if (topSign == '(' && (*sign) == ')')
			{
				charStack.Pop();
			}
		}

		sign++;
	}

	return charStack.IsEmpty();
}

int main()
{
	char* sign = "{[()]}";
	bool bRet = MatchSignLA(sign);
	bRet ? cout << "·ûºÅÆ¥Åä\n" : cout << "·ûºÅ²»Æ¥Åä\n";
	return 0;
}