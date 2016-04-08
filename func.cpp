#include "func.h"
namespace commom{
	void LOG_INFO(std::string str){
		std::cout<<"LOG_INFO :"<<str<<std::endl;
	}
	void DEBUG_INFO(std::string str){
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
	void  Func::Split(const char* d,const std::string& str, std::vector< std::string >& vec){
		std::string  delim = d; 
		vec.clear();
		size_t last = 0, index=str.find_first_of(delim,last);	
		while (index!=std::string::npos){
			vec.push_back(str.substr(last,index-last));	
			last=index+1;index=str.find_first_of(delim,last);
		}	
		if (index-last>0)	vec.push_back(str.substr(last,index-last));
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
	void  Func::SplitOnce(const char* d,const std::string& str, std::vector< std::string >& vec){
		std::string delim = d;
		vec.clear();
		int index = str.find(delim);
		std::string temp ="";
		temp.append(str, 0, index);
		vec.push_back(temp);
		temp = "";
		temp.append(str, index+1,str.size()-index );
		vec.push_back(temp);
	}

	void  Func::_Split(const char* d,const std::string& str, std::vector< std::string >& vec){
		std::string delim = d;
		vec.clear();
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
			vec.push_back(it->first);
	}
	void  Func::Split(const char* d,const std::string& str, std::map<std::string, int>& vec){
		std::string delim = d;
		vec.clear();
		size_t last = 0,index=str.find_first_of(delim,last);
		while (index!=std::string::npos){	
			vec[str.substr(last,index-last)]++;	
			last=index+1;
			index=str.find_first_of(delim,last);
		}	
		if (index-last>0)	vec[str.substr(last,index-last)]++;	
	}
	
	uint16_t Func::StrToInt(const std::string& str){
		char leftstr, rightstr;	
		if(str.empty())return 0;
		int i =0;
		if(!(str[i] & 0x80)) {
			return str[i];
		}	else if ((unsigned char)str[i] <= 0xdf && i + 1 < str.size()) {
			leftstr = (str[i] >> 2) & 0x07;	
			rightstr = (str[i+1] & 0x3f) | ((str[i] & 0x03) << 6 );	
			return Combine(leftstr, rightstr);
		}	else if ((unsigned char)str[i] <= 0xef && i + 2 < str.size()) {	
			leftstr = (str[i] << 4) | ((str[i+1] >> 2) & 0x0f );	
			rightstr = ((str[i+1]<<6) & 0xc0) | (str[i+2] & 0x3f); 
			return Combine(leftstr, rightstr);	
		}else{
			return 0;
		}
		
	}
	bool Func::StrToVec(const std::string& str,  intvector& v){
		char leftstr, rightstr;	
		if(str.empty())return false;
		v.clear();
		for( unsigned int i = 0; i <str.size(); ){
			if(!(str[i] & 0x80)) {
				v.push_back(str[i++]);
			}	else if ((unsigned char)str[i] <= 0xdf && i + 1 < str.size()) {
				leftstr = (str[i] >> 2) & 0x07;	
				rightstr = (str[i+1] & 0x3f) | ((str[i] & 0x03) << 6 );	
				v.push_back(Combine(leftstr, rightstr));	i += 2;
			}	else if ((unsigned char)str[i] <= 0xef && i + 2 < str.size()) {	
				leftstr = (str[i] << 4) | ((str[i+1] >> 2) & 0x0f );	
				rightstr = ((str[i+1]<<6) & 0xc0) | (str[i+2] & 0x3f); 
				v.push_back(Combine(leftstr, rightstr));	i += 3;	
			} else if((unsigned char)str[i] <= 0xf7 ){
				i += 4;
			} else if((unsigned char)str[i] <= 0xfb ){
				i += 5;
			} else if((unsigned char)str[i] <= 0xfd ){
				i += 6;
			}else{
				return false;
			}
		}	
		return true;
}		
	std::string Func::VecToStr(intvector& v, int i,int j ){
		std::string str = "";	
		if(i >= j) return str;	
		while( i != j )	{	
			if( v[i] <= 0x7f )	str += char( v[i]);	
			else if( v[i] <= 0x7ff ){
				str += char((( v[i]>>6) & 0x1f) | 0xc0);	
				str += char(( v[i] & 0x3f) | 0x80);
			} else{
				str += char((( v[i] >> 12) & 0x0f )| 0xe0);
				str += char((( v[i]>>6) & 0x3f )| 0x80 );	
				str += char(( v[i] & 0x3f) | 0x80);
			}	
			i++;
		}
		return str;
	}
	char* Func::ReadLine( char* buffer, int  size, FILE *fi ){
		memset( buffer,0,size );
		return fgets(buffer, size, fi);
	}
	int Func::WiteLine( const char *str, FILE *fo ){
		return fputs(str,fo);
	}
};
