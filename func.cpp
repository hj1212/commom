#include "func.h"
namespace commom{
	void LOG_INFO(std::string& str){
		std::cout<<str<<std::endl;
	}
	void DEBUG_INFO(std::string& str){

	}

	template <class T> std::string convert2str(T value) {
			std::stringstream ss;	
			ss << value;	
			return ss.str();
		}
		char* readline( char* buffer, unsigned int N, FILE *fp ) {
			memset( buffer,0,N );
			return fgets(buffer, N, fp);
		}
		int writeline( const char *str, FILE *fp ){
			return fputs(str,fp);
		}
		std::string getstr( char* buffer ){
			if()
			int index = 
			if (buffer[strlen(buffer)-2] == '\n')
				buffer[strlen(buffer)-2] = '\0'; 
			if (buffer[strlen(buffer)-1] == '\n')	
				buffer[strlen(buffer)-1] = '\0'; 
			std::string bufferstr = buffer;	
			return bufferstr;	
		}
		std::string  vec2str( unicode& v, int i,int j ){
			std::string str = "";	
			if(i >= j)return str;	
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
		bool str2vec(const std::string& str, size_t siz, unicode& v){ 
			char ch1, ch2;	
			if(str.empty())return false;
			v.clear();
			for( unsigned int i = 0;i < siz; )	{
				if(!(str[i] & 0x80)) {
					v.push_back(str[i++]);
				}	else if ((unsigned char)str[i] <= 0xdf && i + 1 < siz) {
					ch1 = (str[i] >> 2) & 0x07;	
					ch2 = (str[i+1] & 0x3f) | ((str[i] & 0x03) << 6 );	
					v.push_back(twochar2int16(ch1, ch2));	i += 2;
				}	else if ((unsigned char)str[i] <= 0xef && i + 2 < siz) {	
						ch1 = (str[i] << 4) | ((str[i+1] >> 2) & 0x0f );	
						ch2 = ((str[i+1]<<6) & 0xc0) | (str[i+2] & 0x3f); 
						v.push_back(twochar2int16(ch1, ch2));	i += 3;	
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

		std::string vec2string( std::vector<std::string>& v, char* s  ){	
			std::string str = "", ss = s; 
			for( int j =0;  j< v.size();  ++j ){ 
				if(j == 0) str = v.at(j);
				else{	str +=(ss  +v.at(j));}	
			}
			return str;
		}
		void split(const char* d,const std::string& str, std::vector< std::string >& ret){
			std::string  delim = d; 
			ret.clear();
			size_t last = 0, index=str.find_first_of(delim,last);	
			while (index!=std::string::npos){
			ret.push_back(str.substr(last,index-last));	
			last=index+1;index=str.find_first_of(delim,last);
			}	
			if (index-last>0)	ret.push_back(str.substr(last,index-last));
		}
		std::string unit(const std::string& str){
			std::string restr = "";
			std::vector<std::string> words;
			split(" ", str, words);
			for(int jj =0; jj< words.size(); jj++){
				if(words.at(jj) == " ")continue;
				restr += words.at(jj);
			}
			return restr;
		}
		void splittwopart(const char* d,const std::string& str, std::vector< std::string >& ret){
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
		void splitpunct( const std::string& str, std::vector< std::string >& ret ){  
			ret.clear();
			std::string s = "`~!@#%^&*()-_+=[]{}\\|:;\"'<,.>?/\t\n\r¢Ù¢Ú¢Û";
			split(s.c_str(), str,  ret);
		}

		void _split(const char* d,const std::string& str, std::vector< std::string >& ret){
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
		void split(const char* d,const std::string& str, std::map<std::string, int>& ret){
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
		/*
		bool trave_dir(std::vector<std::string>& filename, const char* path, std::string filetypr,int depth){	
			DIR *d; struct dirent *file; 
			struct stat sb;   
			if(!(d = opendir(path))){	
				printf("error opendir %s!!!\n",path);	
				return -1;
			}	
			while((file=readdir(d))!= NULL){	
				if(strncmp(file->d_name, ".", 1) == 0)continue;	
				std::string tempname=file->d_name,	
				strpath=path;	
				strpath=strpath+tempname;
				if(strpath.find(filetypr)!=strpath.npos){
					filename.push_back(strpath);
				}else{	
					strpath=strpath+"/";
					if(stat(strpath.c_str(), &sb) >= 0 && S_ISDIR(sb.st_mode) && depth <= 3){ 
						trave_dir(filename, strpath.c_str(), filetypr, depth + 1);
					}
				} 
			}	
			closedir(d);
			return true;
		}
		*/
		//
		template <class T> int Maxarray(T* prob, int n) {
			if((n < 1 )||(prob == NULL))return -1;
			T temp = prob[0];	int index =0;
			for(int i =0; i< n; i++){
				if(temp < prob[i] ){
					temp = prob[i]; 	index = i;
				}
			}
			return index;
		}

		template <class T> int Minarray(T* prob, int n) {
			if((n < 1 )||(prob == NULL))return -1;
			T temp = prob[0];	int index =0;
			for(int i =0; i< n; i++){
				if(temp > prob[i] ){
					temp = prob[i]; 	index = i;
				}
			}
			return index;
		}

		//ÅÅÐòÄ£°æ
		static bool SortBySecondGreater(const std::pair<std::string, float>& x, const std::pair<std::string, float>& y ){
			return x.second > y.second;
		}
		static bool SortByDistance(const wdlen& x, const wdlen& y){
			return x.d > y.d;
		}

		void DEBUG(const char* loginfo){
			std::cout<<"DEBUG: "<<loginfo<<std::endl;
		}
		void LOG(const char* loginfo){
			std::cout<<"LOG: "<<loginfo<<std::endl;
		}

	};




}