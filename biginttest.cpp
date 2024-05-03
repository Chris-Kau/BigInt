// Author: Chris Kau
// CECS 325-02
// Prog 6 BigInt
// Due 05/9/2024
// I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <iterator>
#include <limits.h>
#include <iomanip>
using namespace std;
class BigInt
{
	private:
		vector<char> v;
		BigInt fiboHelper(BigInt n, BigInt a = 0, BigInt b = 1)
		{
			if(n == 0)
			{
				return a;
			}else if(n == 1)
			{
				return b;
			}else
				return fiboHelper(n-1, b, a+b);
		}
	public:
		BigInt(){};
		BigInt(int a){
			if(a == 0)
				v.push_back(0);
			else
			{
				while(a > 0)
				{
					char digit = a%10;
					v.push_back(digit);
					a /= 10;
				}
			}
		};
		BigInt(string a){
			string temp = a;
			for(int i = temp.size() - 1; i >= 0; i--)
			{
				v.push_back(temp[i] - 48);
			}
		};

		int size()
		{
			return v.size();
		}
		void print()
		{
			for(int i = v.size() - 1; i >= 0; i--)
			{
				cout << int(v[i]);
			}
			cout << endl;
		}
		BigInt operator+(BigInt n)
		{
			int sum;
			int carry = 0;
			string temp;
			string temp2;
			//pads the numbers with zeroes so the sizes are the same
			if(v.size() < n.size())
			{
				while(v.size() < n.size())
					v.push_back(0);
			}else if(n.size() < v.size())
			{
				while(n.v.size() < v.size())
					n.v.push_back(0);
			}
				
			//assuming v and n are now the same size
			for(int i = 0; i < v.size(); i++)
			{
				sum = (v[i]-0) + (n[i] - 0) + carry;
				if(sum >= 10)
				{
					carry = 1;
					temp.append(to_string(sum - 10));
				}
				else{
					carry = 0;
					temp.append(to_string(sum));
				}
			}
			//carry at the end of addition
			if(carry == 1)
				temp.append("1");
			//reverses the string to give the correct number
			for(int i = temp.size()-1; i >= 0; i--)
			{
				temp2.append(to_string(temp[i] - 48));
			}
			BigInt result(temp2);
			return result;
		}

		BigInt operator-(BigInt n)
		{
			int difference;
			int carry = 0;
			vector<char> temp;
			string tempans;
			//assuming v is bigger than n so we only pad n
			if(n.size() < v.size())
			{
				while(n.size() < v.size())
				{
					n.v.push_back(0);
				}
			}
			for(int i = 0; i < v.size(); i++)
			{
				if(int(v[i]) < int(n[i]))
				{
					v[i+1] = int(v[i+1]) - 1;
					v[i] = int(v[i]) + 10;
				}
				difference = (int(v[i])) - int(n[i]);
				temp.push_back(difference);
			}

			for(int i = temp.size() - 1; i >= 0; i--)
			{
				tempans.append(to_string(temp[i]));
			}
			BigInt result(stoi(tempans));
			return result;

		}
		//subtraction of an int instead of BigInt
		BigInt operator-(int n)
		{
			BigInt temp(n);
			return *this - temp;
		}
		//addition of an int instead of BigInt
		BigInt operator+(int n)
		{
			BigInt temp(n);
			return *this + temp;
		}
		BigInt operator/(BigInt n)
		{

			BigInt counter(0);
			BigInt num = *this;
			if (num > n)
			{
				while(true)
				{
					counter++;	
					num = num - n;
					if(n > num)
						break;
				}
			}
			return counter;
		}


		BigInt operator*(BigInt n)
		{
			BigInt min = *this;
			BigInt factor = n;
			if(min > n)
			{
				min = n;
				factor = *this;
			}
			BigInt result(factor);
			if(min > 1 && n > 1)
			{
				for(BigInt i(0); min > i + 1; i++)
				{
					result = result + factor;
				}
			}
			return result;
		}
		BigInt operator%(BigInt n)
		{
			BigInt quotient(*this / n);
			return *this - (n * (quotient - 0));
		}
		//postfix
		BigInt operator++(int n)
		{
			BigInt temp(*this);
			++*this;
			return temp; 
		}
		//prefix
		BigInt operator++()
		{
			BigInt one(1);
			v =(*this + one).v;
			return *this;
		}
		//postfix
		BigInt operator--(int n)
		{
			BigInt temp(*this);
			--*this;
			return temp;
		}
		//prefix
		BigInt operator--()
		{
			BigInt one(1);
			v = (*this - one).v;
			return *this;
		}

		bool operator>(BigInt n)
		{
			if(v.size() > n.size())
			{
				return true;
			}
			else if(v.size() < n.size()){
				return false;
			}
			//goes through every digit and compares each one to see which one is larger
			for(int i = v.size() - 1; i >= 0; i--)
			{
				if(int(v[i]) > int(n.v[i]))
				{
					return true;
				}
				if(int(v[i]) < int(n.v[i]))
				{
					return false;
				}
			}
			return false;
		}

		bool operator==(BigInt n)
		{
			if(size() != n.size())
			{
				return false;
			}
			for(int i = v.size()-1; i>= 0; i--)
			{
				if(v[i] - 0 != n.v[i] - 0)
					return false;
			}
			return true;
		}

		bool operator==(int n)
		{
			BigInt temp(n);
			return *this == temp;
		}

		bool operator!=(BigInt n)
		{
			if(size() != n.size())
			{
				return true;
			}
			for(int i = size()-1; i >= 0; i--)
			{
				if(v[i] - 0 != n.v[i] - 0)
					return true;
			}
			return false;
		}

		bool operator!=(int n)
		{
			BigInt temp(n);
			return *this != temp;
		}
		char operator[](int idx)
		{
			return v[idx];
		}
		friend ostream & operator<<(ostream & out, BigInt b)
		{	
			vector<char>::iterator it;
			//if more than 12 digits, print number in scientific notation
			if(b.size() > 12)
			{
				out << int(b.v[b.size()-1]) << '.';
				for(it = b.v.end()-2; it >= b.v.end() - 7; it--)
				{
					out << int(*it);
				}
				out << 'e' << b.size() - 1;  
			}
			else
			{
				for(it = b.v.end()-1; it >= b.v.begin(); it--)
					out << int(*it);
			}
			return out;
        	}

		friend BigInt operator+(int n, BigInt bn)
		{
			BigInt temp(n);
			return bn + temp;
		}

		BigInt fibo()
		{
			return fiboHelper(*this);	
		}
		
		BigInt fact()
		{
			BigInt temp(1);
			for(BigInt i(*this); i > 0; i--)
			{
				temp = temp * i;
			}
			return temp;
		}
};

void testUnit()
{
	int space = 10;
	cout << "\a\nTestUnit:\n"<<flush;
	system("whoami");
	system("date");
	// initialize variables
	BigInt n1(25);
	BigInt s1("25");
	BigInt n2(1234);
	BigInt s2("1234");
	BigInt n3(n2);
	BigInt fibo(12345);
	BigInt fact(50);
	BigInt imax = INT_MAX;
	BigInt big("9223372036854775807");
	// display variables
	cout << "n1(int) :"<<setw(space)<<n1<<endl;
	cout << "s1(str) :"<<setw(space)<<s1<<endl;
	cout << "n2(int) :"<<setw(space)<<n2<<endl;
	cout << "s2(str) :"<<setw(space)<<s2<<endl;
	cout << "n3(n2) :"<<setw(space)<<n3<<endl;
	cout << "fibo(12345):"<<setw(space)<<fibo<<endl;
	cout << "fact(50) :"<<setw(space)<<fact<<endl;
	cout << "imax :"<<setw(space)<<imax<<endl;
	cout << "big :"<<setw(space)<<big<<endl;
	cout << "big.print(): "; big.print(); cout << endl;
	cout << n2 << "/"<< n1<< " = "<< n2/n1 <<" rem "<<n2%n1<<endl;
	cout << "fibo("<<fibo<<") = "<<fibo.fibo() << endl;
	cout << "fact("<<fact<<") = "<<fact.fact() << endl;
	cout << "10 + n1 = " << 10+n1 << endl;
	cout << "n1 + 10 = " << n1+10 << endl;
	cout << "(n1 == s1)? --> "<<((n1==s1)?"true":"false")<<endl;
	cout << "n1++ = ? --> before:"<<n1++<<" after:"<<n1<<endl;
	cout << "++s1 = ? --> before:"<<++s1<<" after:"<<s1<<endl;
	cout << "s2 * big = ? --> "<< s2 * big<<endl;
	cout << "big * s2 = ? --> "<< big * s2<<endl;
}

int main()
{
	testUnit();	
	return 0;
}
