// Author: Chris Kau
// CECS 325-02
// Prog 6 BigInt
// Due 05/9/2024
// I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;
class BigInt
{
	private:
		vector<char> v;
		//BigInt fiboHelper(BigInt n, BigInt a = 0, BigInt b = 1);
	public:
		BigInt(){};
		BigInt(int a){
			string temp = to_string(a);
			for(int i = temp.size() - 1; i >= 0 ; i--)
			{
				v.push_back(temp[i] - 48);
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
			int size = 0;
			for(int i = 0; i < v.size(); i++)
				size++;
			return size;
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
			vector<char> k;
			//putting all of n into a new vector k
			for(int i = 0; i < n.size(); i++)
				k.push_back(int(n[i]));
			//pads the numbers with zeroes so the sizes are the same
			if(v.size() < n.size())
			{
				while(v.size() < n.size())
					v.push_back('0' - 48);
			}else if(n.size() < v.size())
			{
				while(k.size() < v.size())
					k.push_back('0' - 48);
			}
				
			//assuming v and n are now the same size
			for(int i = 0; i < v.size(); i++)
			{
				sum = int(v[i]) + int(k[i]) + carry;
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
			vector<char> k;
			vector<char> temp;
			string tempans;
			for(int i = 0; i < n.size(); i++)
			{
				k.push_back(int(n[i]));
			}
			//assuming v is bigger than n so we only pad n
			if(n.size() < v.size())
			{
				while(k.size() < v.size())
				{
					k.push_back('0' - 48);
				}
			}
			for(int i = 0; i < v.size(); i++)
			{
				if(int(v[i]) < int(k[i]))
				{
					v[i+1] = int(v[i+1]) - 1;
					v[i] = int(v[i]) + 10;
				}
				difference = (int(v[i])) - int(k[i]);
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
			BigInt one(1);
			if (num > n)
			{
				while(true)
				{
					counter = counter + one;
					num = num - n;
					if(n > num)
						break;
				}
			}
			return counter;
		}


		BigInt operator*(BigInt n)
		{
			string temp;
			BigInt min = *this;
			BigInt factor = n;
			BigInt one(1);
			int count = 0;
			if(min > n)
			{
				min = n;
				factor = *this;
			}
			BigInt result(factor);
			if(min > one && n > one)
			{
				for(BigInt i(0); min > i + 1; i++)
				{
					count++;
					result = result + factor;
				}
			}
			cout << "factor " << factor << endl << " min " << min << endl;
			cout << "count " << count << endl;
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
};

int main()
{
	//testUnit();	
	BigInt n1("1234");
	n1.print();
	BigInt n2("1234");
	BigInt n3("1234");
	BigInt bigNum("9223372036854775807");
	BigInt result = n1 * bigNum;
	cout << result << endl;
	return 0;
}
