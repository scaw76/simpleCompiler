#ifndef _DEBUG_H_
#define _DEBUG_H_

#define ShowMessages 1;

#if ShowMessages
	#define ERROR(msg) std::cout<<"Error: " << msg<<std::endl
	#define TEST(msg) std::cout<<"Test: " << msg<<std::endl
	#define MSG(x) std::cout<< x <<std::endl

#else
	#define ERROR(msg) 
	#define TEST(msg)
	#define MSG(x)

#endif


#endif //_DEBUG_H_