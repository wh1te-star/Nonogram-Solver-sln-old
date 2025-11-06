#include "TestData/Repository/TestDataRepository.h"

std::string TestDataRepository::GetEasyColumnHintString(){
	return R"###(
		 ,  ,  ,  , 3, 5, 6,  ,  ,  ,  ,  ,  ,  ,  
		2,  , 7, 7, 5, 3, 1, 6, 6, 5, 3,  ,  ,  , 2
		2, 7, 2, 2, 1, 2, 2, 4, 1, 3, 5, 7, 7, 7, 2
	)###";
}

std::string TestDataRepository::GetEasyRowHintString(){
	return R"###(
		 , 2, 2
		 ,  , 7
		 ,  , 7
		 ,  , 7
		3, 5, 3
		5, 3, 5
		6, 1, 6
		 , 6, 6
		6, 1, 6
		5, 1, 5
		3, 1, 3
		 ,  , 2
		 ,  , 2
		 ,  , 4
		 ,  , 2
	)###";
}
