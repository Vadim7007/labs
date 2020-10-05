#include "pch.h"
//#include "C:\Users\vadim\Desktop\Я\Программирование\study\lab2++\lab2.h"
#include "C:\Users\vadim\Desktop\Я\Программирование\study\lab2++\lab2.cpp"

#define N 50
const double pi = 3.141592;

class TrTest : public ::testing::Test
{
protected:
	Tr* a[N]; // |cos(i) * i| + 1
	Tr x;
	void SetUp() {
		for (int i = 0; i < N; i++) // положительные double
		{
			a[i] = new Tr(abs(cos(i) * (i)) + 1);
		}
	}
	void TearDown()
	{
		for (int i = 0; i < N; i++)
		{
			delete a[i];
		}
	}
};

TEST_F(TrTest, Test_constructor_1) {
	for (int i = 0; i < N; i++)
	{
		ASSERT_DOUBLE_EQ(abs(cos(i) * (i)) + 1, a[i]->get());
	}
}

TEST_F(TrTest, Test_constructor_2) {
	ASSERT_EQ(1, x.get());
}

TEST(Test_Negative, Test_constructor_3) {
	EXPECT_ANY_THROW(Tr n(-1));
}

TEST(Test_Negative, Test_constructor_4) {
	EXPECT_ANY_THROW(Tr n(-2));
}

TEST(Test_Negative, Test_constructor_5) {
	EXPECT_ANY_THROW(Tr n(0));
}

TEST_F(TrTest, Test_set_1) {
	x.set(2);
	ASSERT_EQ(2, x.get());
}

TEST_F(TrTest, Test_set_2) {
	for (int i = 0; i < N; i++)
	{
		a[i]->set(i + 1);
	}
	for (int i = 0; i < N; i++)
	{
		ASSERT_EQ(i+1, a[i]->get());
	}
}

TEST(Test_Negative, Test_set_3) {
	Tr x;
	EXPECT_ANY_THROW(x.set(0));
}

TEST(Test_Negative, Test_set_4) {
	Tr x;
	EXPECT_ANY_THROW(x.set(-1));
}

TEST_F(TrTest, Test_coord_1) {
	double x1, y1;
	for (int i = 0; i < 50; i++) {
		double c = a[i]->get();
		a[i]->coord(x1, y1, ((double)i / 6) -1);
		double n_pi = (double)i / 6 - 1;
		n_pi = abs(n_pi) - trunc(abs(n_pi));

		ASSERT_DOUBLE_EQ(x1, c * cos(n_pi * pi) + c * log(tan(n_pi * pi / 2)));
		ASSERT_DOUBLE_EQ(y1, (c * sin(n_pi * pi)));
	}
}

TEST_F(TrTest, Test_len_1) {
	for (int i = 0; i < 50; i++) {
		double c = a[i]->get();
		double n_pi = (double)i / 6 - 1;
		double n_pi_t = abs(n_pi) - trunc(abs(n_pi));
		double len = c * log(1 / sin(n_pi_t * pi));

		ASSERT_DOUBLE_EQ(len, a[i]->len(n_pi));
	}
}

TEST_F(TrTest, Test_rad_1) {
	for (int i = 0; i < 50; i++) {
		double c = a[i]->get();
		double n_pi = (double)i / 6 - 1;
		double n_pi_t = abs(n_pi) - trunc(abs(n_pi));
		double rad = (c / tan(n_pi_t * pi));

		ASSERT_DOUBLE_EQ(rad, a[i]->rad(n_pi));
	}
}

TEST_F(TrTest, Test_area_1) {
	for (int i = 0; i < 50; i++) {
		double c = a[i]->get();
		double area = (pi * c * c / 2);

		ASSERT_DOUBLE_EQ(area, a[i]->area());
	}
}

TEST_F(TrTest, Test__surface_1) {
	for (int i = 0; i < 50; i++) {
		double c = a[i]->get();
		double surface = (pi * c * c * 4);

		ASSERT_DOUBLE_EQ(surface, a[i]->surface());
	}
}

TEST_F(TrTest, Test__volume_1) {
	for (int i = 0; i < 50; i++) {
		double c = a[i]->get();
		double volume = pi * c * c * c * 2 / 3;

		ASSERT_DOUBLE_EQ(volume, a[i]->volume());
	}
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}