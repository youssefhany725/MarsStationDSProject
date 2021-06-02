#include <iostream>
#include "hFiles/MarsStation.h"
using namespace std;
int main()
{
	MarsStation Base;
	int n=0;
	while (n<24)
	{
		Base.MExecute();
		Base.Assign();
		Base.Finish();
		Base.Interactive();
		Base.Endday();
		++n;
	}
	//output
	return 0;
}