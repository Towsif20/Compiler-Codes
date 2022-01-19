#include<bits/stdc++.h>

using namespace std;

class Function
{
	public:
	
	string retType;
	
	vector<string> param_list;
	vector<string> param_type;
	vector<string> var_list;
	int param_count;
	bool defined;
	
	
	
	Function()
	{
		retType = "";
		param_list.clear();
		param_type.clear();
		var_list.clear();
		
		param_count = 0;
		
		defined = false;
		
		
		
	}
	
	
	void setParamCount()
		{
			//param_list.push_back(a);
			
			//param_type.push_back(b);
			
			param_count = param_list.size();
		}
		
		
		void add_number_of_parameter(string newpara,string type)
			{
                param_list.push_back(newpara);
                param_type.push_back(type);
              //  cout<<newpara<<endl;
                setParamCount();
            }
		void getclear()
			{
                param_list.clear();
                param_type.clear();
                setParamCount();
            }
	
	
	
	
	
	
	
		
};



















