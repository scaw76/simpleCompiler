#ifndef _DEBUG_H_
#define _DEBUG_H_


#define ShowMessages 1

#if ShowMessages == 1
	#define ERROR(msg) std::cout<<"Error: " << msg<<std::endl
	#define TEST(msg) std::cout<<"Test: " << msg<<std::endl
	#define MSG(x) std::cout<< x <<std::endl
	#define PASSED(msg) std::cout<<"Passed: " << msg<< std::endl
	#define FAILED(msg) std::cout<<"Failed: " << msg<< std::endl	
#else
	#define ERROR(msg) 
	#define TEST(msg)
	#define MSG(x)
	#define PASSED(msg)
	#define FAILED(x)
#endif





#endif //_DEBUG_H_