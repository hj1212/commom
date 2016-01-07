#ifndef _FUNC_H
#define _FUNC_H
#include <stdio.h>
#include <iostream>
#include <string>
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
namespace commom{
	//»’÷æ¿‡
	void LOG_INFO(std::string& str);
	void DEBUG_INFO(std::string& str);
	class Func{
	public:
		std::string GetLine( char* buffer );
		std::string  Unit(const std::string& str);
		void Split(const char* d,const std::string& str, std::vector< std::string >& ret);
		void Split(const char* d,const std::string& str, std::map<std::string, int>& ret);
		void _Split(const char* d,const std::string& str, std::vector< std::string >& ret);
		void SplitOnce(const char* d,const std::string& str, std::vector< std::string >& ret);		
		template <class T> std::string ConvertToStr(T value);
	public:
		char* ReadLine( char* buffer, int  size, FILE *fi );
		int WiteLine( const char *str, FILE *fo );
	public:
		template <class T> int MaxArray(T* prob, int n);
		template <class T> int MinArray(T* prob, int n);
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

