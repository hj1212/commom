#ifndef _FUNC_H
#define _FUNC_H
#include <stdio.h>
#include <iostream>
#include <string>
#include "string.h"
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>    
#include <sys/stat.h>
#include <vector>
#include <sstream>
#include <map>
//#include <boost\algorithm\string.hpp>
#define SHORT_LENTH 250
#define MAX_LENTH 50000
typedef struct{ std::string word; 	float d;}wdlen;
typedef  std::vector<uint16_t>  intvector;
namespace commom{
	//日志类
	void LOG_INFO(std::string str);
	void DEBUG_INFO(std::string str);
	class Func{
	public://字符串处理
		std::string GetLine( char* buffer );
		std::string  Unit(const std::string& str);
		void Split(const char* d,const std::string& str, std::vector< std::string >& vec);
		void Split(const char* d,const std::string& str, std::map<std::string, int>& vec);
		void _Split(const char* d,const std::string& str, std::vector< std::string >& vec);
		void SplitOnce(const char* d,const std::string& str, std::vector< std::string >& vec);			
		inline uint16_t Combine(char high, char low){	return (((uint16_t(high) & 0x00ff ) << 8) | (uint16_t(low) & 0x00ff));	}		
		bool StrToVec(const std::string& str,  intvector& v);
		std::string  VecToStr(intvector& v, int i,int j );
	public://文件处理
		char* ReadLine( char* buffer, int  size, FILE *fi );
		int WiteLine( const char *str, FILE *fo );
	public://常用模版
		template <class T> int MaxArray(T* prob, int n);
		template <class T> int MinArray(T* prob, int n);
		template <class T> std::string ConvertToStr(T value) {
			std::stringstream ss;	ss << value;	return ss.str();
		}
		static bool SortByDistance(const wdlen& x, const wdlen& y){
			return x.d > y.d;
		}
		static bool SortBySecondGreater(const std::pair<std::string, float>& x, 
			const std::pair<std::string, float>& y ){
				return x.second > y.second;
		}
		static bool SortBySecondLess(const std::pair<std::string, float>& x, 
			const std::pair<std::string, float>& y ){
				return x.second < y.second;
		}
	};

}
#endif

