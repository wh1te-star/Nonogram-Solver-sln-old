#include "TestData/Repository/TestDataRepository.h"

std::string TestDataRepository::GetLambdaRowString(){
	return R"###(
		2, 1, 2, 3,  ,  ,  ,  ,  ,  
		1, 3, 4, 4, 4, 3, 3, 3, 2, 2
	)###";
}

std::string TestDataRepository::GetLambdaColumnString(){
	return R"###(
		 ,  , 2
		 , 1, 2
		 , 1, 1
		 ,  , 2
		 ,  , 1
		 ,  , 3
		 ,  , 3
		 , 2, 2
		 , 2, 1
		2, 2, 1
		 , 2, 3
		 , 2, 2
	)###";
}
