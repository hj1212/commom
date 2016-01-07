#include "func.h"
namespace commom{
	void LOG_INFO(std::string& str){
		std::cout<<"LOG_INFO :"<<str<<std::endl;
	}
	void DEBUG_INFO(std::string& str){
		std::cout<<"DEBUG_INFO :"<<str<<std::endl;
	}
	std::string Func::GetLine( char* buffer ){
		//TODO
		if (buffer[strlen(buffer)-2] == '\n')
			buffer[strlen(buffer)-2] = '\0'; 
		if (buffer[strlen(buffer)-1] == '\n')	
			buffer[strlen(buffer)-1] = '\0'; 
		std::string bufferstr = buffer;	
		return bufferstr;	
	}	
	void  Func::Split(const char* d,const std::string& str, std::vector< std::string >& ret){
		std::string  delim = d; 
		ret.clear();
		size_t last = 0, index=str.find_first_of(delim,last);	
		while (index!=std::string::npos){
		ret.push_back(str.substr(last,index-last));	
		last=index+1;index=str.find_first_of(delim,last);
		}	
		if (index-last>0)	ret.push_back(str.substr(last,index-last));
	}
	std::string  Func::Unit(const std::string& str){
		std::string restr = "";
		std::vector<std::string> words;
		Split(" ", str, words);
		for(int jj =0; jj< words.size(); jj++){
			if(words.at(jj) == " ")continue;
			restr += words.at(jj);
		}
		return restr;
	}
	void  Func::SplitOnce(const char* d,const std::string& str, std::vector< std::string >& ret){
		std::string delim = d;
		ret.clear();
		int index = str.find(delim);
		std::string temp ="";
		temp.append(str, 0, index);
		ret.push_back(temp);
		temp = "";
		temp.append(str, index+1,str.size()-index );
		ret.push_back(temp);
	}

	void  Func::_Split(const char* d,const std::string& str, std::vector< std::string >& ret){
		std::string delim = d;
		ret.clear();
		std::map<std::string, int>temp;
		size_t last = 0, index=str.find_first_of(delim,last);
		while (index!=std::string::npos){	
			temp[str.substr(last,index-last)]++;	
			last=index+1;
			index=str.find_first_of(delim,last);
		}
		if (index-last>0)	
			temp[str.substr(last,index-last)]++;	
		for(std::map<std::string, int>::iterator it = temp.begin(); it!= temp.end(); it++)
			ret.push_back(it->first);
	}
	void  Func::Split(const char* d,const std::string& str, std::map<std::string, int>& ret){
		std::string delim = d;
		ret.clear();
		size_t last = 0,index=str.find_first_of(delim,last);
		while (index!=std::string::npos){	
			ret[str.substr(last,index-last)]++;	
			last=index+1;
			index=str.find_first_of(delim,last);
		}	
		if (index-last>0)	ret[str.substr(last,index-last)]++;	
	}
	template <class T> std::string Func::ConvertToStr(T value) {
			std::stringstream ss;	
			ss << value;	
			return ss.str();
	}

	char* Func::ReadLine( char* buffer, int  size, FILE *fi ){
		memset( buffer,0,size );
		return fgets(buffer, size, fi);
	}
	int Func::WiteLine( const char *str, FILE *fo ){
		return fputs(str,fo);
	}

	template <class T> int Func::MaxArray(T* prob, int n) {
		if((n < 1 )||(prob == NULL))return -1;
		T temp = prob[0];	int index =0;
		for(int i =0; i< n; i++){
			if(temp > prob[i] ){
				temp = prob[i]; 	index = i;
			}
		}
		return index;
	}
	template <class T> int Func::MinArray(T* prob, int n) {
		if((n < 1 )||(prob == NULL))return -1;
		T temp = prob[0];	int index =0;
		for(int i =0; i< n; i++){
			if(temp < prob[i] ){
				temp = prob[i]; 	index = i;
			}
		}
		return index;
	}
};
