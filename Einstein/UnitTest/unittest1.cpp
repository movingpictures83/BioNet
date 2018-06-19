#include "CppUnitTest.h"
#include "../../BioNet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BioNet b = BioNet();
			for (int i = 0; i < NETWORK_SIZE; ++i)
			{
				for (int j = 0; j < NETWORK_SIZE; ++j)
				{
					float min = b.getMinWeight();
					float max = b.getMaxWeight();

					Assert::IsTrue(b.getEdge(i,j) >= min);
					Assert::IsTrue(b.getEdge(i,j) <= max);
				}
			}
			
		}

	};
}