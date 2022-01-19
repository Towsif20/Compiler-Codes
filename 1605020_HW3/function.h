#include<bits/stdc++.h>

using namespace std;

class Function
{
	public:
	
	string retType;
	
	vector<string> param_list;
	vector<string> param_type;
	int param_count;
	bool defined;
	
	
	
	Function()
	{
		retType = "";
		param_list.clear();
		param_type.clear();
		
		param_count = 0;
		
		defined = false;
		
		
		
	}
	
	
	void setParamCount(string a, string b)
		{
			param_list.push_back(a);
			
			param_type.push_back(b);
			
			param_count = param_list.size();
		}
	
	
	
	
	
	
	
		
};



















