#include<iostream>
#include<stack>

using namespace std;

bool match(char a, char b) {
	if ((a == '(' && b == ')')||(a=='['&&b==']')) {
		return true;
	}
	return false;
}

char str[105];
bool isMatched[105] = { false };

int main() {
	stack<int>stk;
	cin >> str;
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == '(' || str[i] == '[') {
			stk.push(i);
		}
		else if (str[i] == ')'||str[i]==']') {
			if (!stk.empty()&&match(str[stk.top()],str[i])) {
				isMatched[stk.top()] = true;
				stk.pop();
				isMatched[i] = true;
			}
		}
		i++;
	}

	i = 0;
	while (str[i] != '\0') {
		if (isMatched[i] == false) {
			if (str[i] == '(' || str[i] == ')') {
				cout << "()";
			}
			else {
				cout << "[]";
			}
		}
		else {
			cout << str[i];
		}
		i++;
	}
	return 0;
}