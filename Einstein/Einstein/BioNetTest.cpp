#include "CppUnitTest.h"
#include "Net.h"

#define NETWORK_SIZE 5

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using BioNet::Net;

namespace UnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Net<float> b = Net<float>();
			b.resize(NETWORK_SIZE);
			for (int i = 0; i < b.size(); ++i)
			{
				for (int j = 0; j < b.size(); ++j)
				{
					float min = b.getMinWeight();
					float max = b.getMaxWeight();

					Assert::IsTrue(b.getEdge(i, j) >= min);
					Assert::IsTrue(b.getEdge(i, j) <= max);
				}
			}

		}

	};
}