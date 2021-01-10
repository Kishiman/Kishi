#include <iostream>
#include <stdio.h>
#include "Expression/Base/ExpressionInc.h"
#include <cmath>
Ptr<ThBaseOperatorLV<int, float>> GetSymbol()
{
	using Sym = ThBaseOperatorLV<int, float>::Sym;
	using Dyn = ThBaseOperatorLV<int, float>::Dyn;

	Sym _floor(new Dyn([](float x) { return floor(x); }));
	Sym _ceil(new Dyn([](float x) { return ceil(x); }));
	Sym res = (_ceil + _floor);
	return res.Clone();
}
void TestTheory()
{
	using Sym = ThBaseOperatorLV<int, float>::Sym;
	using Dyn = ThBaseOperatorLV<int, float>::Dyn;
	ThBaseOperatorLV<int>::Dyn one([]() { return 1; });
	ThBaseOperatorLV<int>::Dyn two([]() { return 2; });
	ThBaseOperatorLV<int>::Dyn three([]() { return 3; });
	ThBaseOperatorLV<float, int>::Dyn intTofloat([](int x) { return (float)(x); });
	ThBaseOperatorLV<float, void>::Sym oneTofloat = intTofloat.op(one);
	cout << oneTofloat()<<std::endl;
	ThBaseOperatorLV<float, void>::Sym symbol = 7 * intTofloat.op(one - two + three);
	printf("(1-2+3)*7=14=%f\n", symbol());
	Dyn _floor([](float f) { return floor(f); });
	Dyn _ceil([](float f) { return ceil(f); });
	ThBaseOperatorLV<float, float>::Dyn _power2([](float f) { return powf(f, 2); });
	Sym res = _floor.op(_power2 + _power2) + _ceil;
	for (int i = 0; i < 10; i++)
	{
		float result = res(0.7 * (float)i);
		printf("(floor(power2 + power2)+ceil)(%f)=%f\n", 0.7 * (float)(i), result);
	}
	Sym x = GetSymbol();
	Sym a = x + _ceil;
	ThBaseOperatorLV<float, int>::Sym half(new Dyn([](int x) { return x + 0.5f; }));
	ThBaseOperatorLV<float, float>::Sym d = half.op(a);
	for (int i = 0; i < 10; i++)
	{
		float result = d(0.7 * (float)i);
		printf("half(floor + ceil) (%f)=%f\n", 0.7 * (float)(i), result);
	}
};

int main(int argc, char *argv[])
{
	TestTheory();
}