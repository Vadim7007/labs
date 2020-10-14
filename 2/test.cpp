#include "pch.h"
#include "C:\Users\vadim\Desktop\Я\Программирование\study\lab2++\lab2.cpp"

#define N 50

class TrTest : public ::testing::Test
{
protected:
	Tr* a[N]; // |cos(i) * i| + 1
	Tr x;
	void SetUp() {
		for (int i = 0; i < N; i++) // положительные double
		{
			try
			{
				a[i] = new Tr(abs(cos(i) * (i)) + 0.5);
			}
			catch (const std::exception&)
			{
				std::cout << "Failed to init object." << std::endl;
			}
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
		ASSERT_DOUBLE_EQ(abs(cos(i) * (i)) + 0.5, a[i]->get());
	}
}

TEST_F(TrTest, Test_constructor_2) {
	ASSERT_DOUBLE_EQ(1.00, x.get());
}

TEST(Test_Negative, Test_constructor_3) {
	EXPECT_THROW(Tr n(-1), std::exception);
}

TEST(Test_Negative, Test_constructor_4) {
	EXPECT_THROW(Tr n(-2), std::exception);
}

TEST(Test_Negative, Test_constructor_5) {
	EXPECT_THROW(Tr n(0), std::exception);
}

TEST_F(TrTest, Test_set_1) {
	try
	{
		x.set(2);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
	ASSERT_DOUBLE_EQ(2.00, x.get());
}

TEST_F(TrTest, Test_set_2) {
	for (int i = 0; i < N; i++)
	{
		try
		{
			a[i]->set(i + 1);
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
			return;
		}
	}
	for (int i = 0; i < N; i++)
	{
		ASSERT_DOUBLE_EQ((double)(i+1), a[i]->get());
	}
}

TEST(Test_Negative, Test_set_3) {
	Tr x;
	EXPECT_THROW(x.set(0), std::exception);
}

TEST(Test_Negative, Test_set_4) {
	Tr x;
	EXPECT_THROW(x.set(-1), std::exception);
}

TEST_F(TrTest, Test_coord_1) {
	double x1, y1;
	for (int i = 0; i < N; i++) {
		double c = a[i]->get();
		a[i]->coord(x1, y1, ((double)i*4 / 3));
		double z = (double)i * 4 / 3;
		int k = trunc((double)i * 4 / 3 / 360);
		z = z - k * 360;
		z = z / 180 * M_PI;

		ASSERT_DOUBLE_EQ(x1, c * cos(z) + c * log(tan(z / 2)));
		ASSERT_DOUBLE_EQ(y1, (c * sin(z)));
	}
}

TEST(Test_Negative, Test_coord_2) {
	Tr x;
	double x1, y1;
	EXPECT_THROW(x.coord(x1, y1, -1), std::exception);
}

TEST(Test_Negative, Test_coord_3) {
	Tr x;
	double x1, y1;
	EXPECT_THROW(x.coord(x1, y1, 200), std::exception);
}

TEST_F(TrTest, Test_len_1) {
	for (int i = 0; i < N; i++) {
		double c = a[i]->get();
		double z = (double)i * 4 / 3;
		int k = trunc(z / 360);
		z = z - k * 360;
		z = z / 180 * M_PI;
		double len = c * log(1 / sin(z));

		ASSERT_DOUBLE_EQ(len, a[i]->len((double)i * 4 / 3));
	}
}

TEST(Test_Negative, Test_len_2) {
	Tr x;
	EXPECT_THROW(x.len(-1), std::exception);
}

TEST(Test_Negative, Test_len_3) {
	Tr x;
	EXPECT_THROW(x.len(200), std::exception);
}

TEST_F(TrTest, Test_rad_1) {
	for (int i = 0; i < N; i++) {
		double c = a[i]->get();
		double z = (double)i * 4 / 3;
		int k = trunc(z / 360);
		z = z - k * 360;
		if (z < 0) {
			z += 360;
		}
		z = z / 180 * M_PI;
		double rad = (c / tan(z));

		ASSERT_DOUBLE_EQ(rad, a[i]->rad((double)i * 4 / 3));
	}
}

TEST(Test_Negative, Test_rad_2) {
	Tr x;
	EXPECT_THROW(x.rad(-1), std::exception);
}

TEST(Test_Negative, Test_rad_3) {
	Tr x;
	EXPECT_THROW(x.rad(200), std::exception);
}

TEST_F(TrTest, Test_area_1) {
	for (int i = 0; i < N; i++) {
		double c = a[i]->get();
		double area = (M_PI * c * c / 2);

		ASSERT_DOUBLE_EQ(area, a[i]->area());
	}
}

TEST_F(TrTest, Test__surface_1) {
	for (int i = 0; i < N; i++) {
		double c = a[i]->get();
		double surface = (M_PI * c * c * 4);

		ASSERT_DOUBLE_EQ(surface, a[i]->surface());
	}
}

TEST_F(TrTest, Test__volume_1) {
	for (int i = 0; i < N; i++) {
		double c = a[i]->get();
		double volume = M_PI * c * c * c * 2 / 3;

		ASSERT_DOUBLE_EQ(volume, a[i]->volume());
	}
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}