#include "TestFSM.h"
#include <Windows.h>

int main()
{
	TestFSM test("colorchange.txt");
	test.Start();
	std::string tmp = "";
	while (true)
	{
		test.Update(30.f);
		Sleep(2);
		if (tmp == "")
		{
			std::cout << "ban co' muon' raise event OnRed khong ? input yes or no :";
			std::cin >> tmp;
			if (tmp == "yes")
			{
				test.RaiseEvent("OnRed");
			}
		}
	}
	
	
}