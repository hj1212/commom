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
#include <boost\algorithm\string.hpp>
#define SHORT_LENTH 250
#define MAX_LENTH 50000
//
//typedef std::vector<uint16_t> unicode;
//typedef struct{ std::string word; 	float d;}wdlen;
namespace commom{
	//»’÷æ¿‡
	void LOG_INFO(std::string& str);
	void DEBUG_INFO(std::string& str);
	

	class Func{
	public:
		Func(){}
		~Func(){}
	};

}
#endif

