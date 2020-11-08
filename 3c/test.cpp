#include "pch.h"
#include "C:\Users\vadim\Desktop\Я\Программирование\study\lab3++(c)\lib3_2.cpp"


char* getstr(std::istream& istream) {
	char* str = nullptr;
	char c;
	int i = 0;
	do
	{
		i++;
		str = r_alloc(str, i, i - 1);
		if (!str) {
			istream.setstate(std::ios_base::failbit);
			return nullptr;
		}
		istream.get(c);
		str[i - 1] = c;
	} while (c != '\n');
	str[i - 1] = '\0';
	return str;
}
int random(const int N) noexcept {
	int n = ((rand() + clock()) % (2 * N)) - N;
	return n;
}
char* random_str(const int n) noexcept {
	char* str;
	try
	{
		str = new char[n + 1];
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
	for (int i = 0; i < n; i++)
	{
		int k = (rand() % 2 + 1) * 32 + 33 + rand() % 26;
		str[i] = k;
	}
	str[n] = '\0';
	return str;
}


using namespace ABC_class_c;
#define N 10
Alphabet y;


class AlphabetTest : public ::testing::Test
{
protected:
	Alphabet* array[N];
	void SetUp() {
		for (int i = 0; i < N; i++)
		{
			array[i] = new Alphabet;
		}
	}
	void TearDown()
	{
		for (int i = 0; i < N; i++)
		{
			delete array[i];
		}
	}
};

TEST_F(AlphabetTest, Test_constructor_1) {
	Alphabet a;
	ASSERT_EQ(a.get_len(), 0);
}

TEST_F(AlphabetTest, Test_constructor_2) {
	for (int i = 0; i < N; i++)
	{
		ASSERT_EQ(array[i]->get_len(), 0);
	}
}

TEST_F(AlphabetTest, Test_constructor_3) {
	Alphabet y(10);
	ASSERT_EQ(y.get_len(), 10);
}

TEST_F(AlphabetTest, Test_constructor_4) {
	for (int i = 0; i < N; i++)
	{
		array[i] = new Alphabet(i);
		ASSERT_EQ(array[i]->get_len(), i);
	}
}

TEST_F(AlphabetTest, Test_constructor_5) {
	Alphabet y(-1);
	ASSERT_EQ(y.get_len(), 0);
}

TEST(Test_Negative, Test_constructor_6) {
	EXPECT_THROW(Alphabet y(INT_MAX), std::bad_alloc);
}

TEST_F(AlphabetTest, Test_constructor_7) {
	Alphabet y('c');
	ASSERT_EQ(y.get_len(), 1);
	ASSERT_TRUE(y.is_char('c'));
}

TEST_F(AlphabetTest, Test_constructor_8) {
	Alphabet y("abc");
	ASSERT_EQ(y.get_len(), 3);
	ASSERT_TRUE(y.is_char('c'));
	ASSERT_TRUE(!y.is_char('F'));
}

TEST_F(AlphabetTest, Test_constructor_9) {
	Alphabet y("abca");
	ASSERT_EQ(y.get_len(), 3);
	ASSERT_TRUE(!y.is_char('F'));
}

TEST_F(AlphabetTest, Test_constructor_10) {
	Alphabet y(nullptr);
	ASSERT_EQ(y.get_len(), 0);
	ASSERT_TRUE(!y.is_char('F'));
}

TEST_F(AlphabetTest, Test_constructor_11) {
	for (int i = 0; i < N; i++)
	{
		ASSERT_NO_THROW(array[i] = new Alphabet(random_str(i)));
		ASSERT_TRUE(array[i]->get_len() <= i);
	}
}

// тесты 12 - 16 фактически тестируют перегруженный опертаор =
TEST_F(AlphabetTest, Test_constructor_12) {
	Alphabet y("abca");
	Alphabet a = y;
	ASSERT_EQ(a.get_len(), 3);
	ASSERT_TRUE(a.is_char('c'));
	ASSERT_EQ(y.get_len(), 3);
	ASSERT_TRUE(y.is_char('b'));
}

TEST_F(AlphabetTest, Test_constructor_13) {
	Alphabet y = Alphabet("abca");
	ASSERT_EQ(y.get_len(), 3);
	ASSERT_TRUE(y.is_char('b'));
	ASSERT_TRUE(!y.is_char(' '));
}

TEST_F(AlphabetTest, Test_constructor_14) {
	Alphabet y("abca");
	Alphabet a = std::move(y);
	ASSERT_EQ(a.get_len(), 3);
	ASSERT_TRUE(a.is_char('c'));
	ASSERT_EQ(y.get_len(), 0);
	ASSERT_TRUE(!y.is_char('b'));
}

TEST_F(AlphabetTest, Test_constructor_15) {
	Alphabet y("abcde");
	y = Alphabet("abca");
	ASSERT_EQ(y.get_len(), 3);
	ASSERT_TRUE(y.is_char('b'));
	ASSERT_TRUE(!y.is_char('d'));
}

TEST_F(AlphabetTest, Test_constructor_16) {
	Alphabet a("abcde");
	Alphabet y("abca");
	a = y;
	ASSERT_EQ(a.get_len(), 3);
	ASSERT_TRUE(a.is_char('c'));
	ASSERT_TRUE(!a.is_char('d'));
	ASSERT_EQ(y.get_len(), 3);
	ASSERT_TRUE(y.is_char('b'));
}

TEST_F(AlphabetTest, Test_constructor_17) {
	Alphabet y(Alphabet("abca"));
	ASSERT_EQ(y.get_len(), 3);
	ASSERT_TRUE(y.is_char('b'));
	ASSERT_TRUE(!y.is_char('d'));
}

TEST_F(AlphabetTest, Test_constructor_18) {
	Alphabet y("abca");
	Alphabet a(y);
	ASSERT_EQ(a.get_len(), 3);
	ASSERT_TRUE(a.is_char('c'));
	ASSERT_TRUE(!a.is_char('d'));
	ASSERT_EQ(y.get_len(), 3);
	ASSERT_TRUE(y.is_char('b'));
}

TEST_F(AlphabetTest, Test_operator_1) {
	Alphabet a("abcde");
	y = y + a;
	ASSERT_TRUE(y.get_len() >= 5);
	ASSERT_TRUE(y.is_char('c'));
}

TEST_F(AlphabetTest, Test_operator_2) {
	Alphabet y("abca");
	Alphabet a("abcde");
	y = y + a;
	ASSERT_EQ(y.get_len(), 5);
	ASSERT_TRUE(y.is_char('e'));
}

TEST_F(AlphabetTest, Test_operator_3) {
	y = y + 'a';
	ASSERT_TRUE(y.get_len() > 0);
	ASSERT_TRUE(y.is_char('a'));
}

TEST_F(AlphabetTest, Test_operator_4) {
	ASSERT_NO_THROW(y = y + Alphabet());
}

TEST_F(AlphabetTest, Test_operator_5) {
	y = y + 5;
	ASSERT_TRUE(y.get_len() > 4);
	ASSERT_TRUE(y.is_char(' '));
}

TEST_F(AlphabetTest, Test_operator_6) {
	Alphabet y("abc");
	Alphabet a("xyz");
	y = y + a;
	ASSERT_EQ(y.get_len(), 6);
	ASSERT_TRUE(y.is_char('x'));
	ASSERT_TRUE(y.is_char('a'));
	ASSERT_TRUE(!y.is_char('d'));
}

TEST_F(AlphabetTest, Test_operator_7) {
	Alphabet y("abca");
	Alphabet a("abcde");
	Alphabet z = y + a;
	ASSERT_EQ(z.get_len(), 5);
	ASSERT_TRUE(z.is_char('e'));
}

TEST_F(AlphabetTest, Test_operator_8) {
	Alphabet a("abcde");
	a+='a';
	ASSERT_EQ(a.get_len(), 5);
	ASSERT_TRUE(a.is_char('c'));
}

TEST_F(AlphabetTest, Test_operator_9) {
	Alphabet y("abca");
	y +='d';
	ASSERT_EQ(y.get_len(), 4);
	ASSERT_TRUE(y.is_char('d'));
}

TEST_F(AlphabetTest, Test_operator_10) {
	Alphabet a;
	a += 'd';
	ASSERT_EQ(a.get_len(), 1);
	ASSERT_TRUE(a.is_char('d'));
}

TEST_F(AlphabetTest, Test_operator_11) {
	for (int i = 0; i < N; i++)
	{
		ASSERT_NO_THROW(*array[i] += i);
		ASSERT_TRUE((*array[i]).is_char(i));
	}
}

TEST_F(AlphabetTest, Test_is_char_1) {
	Alphabet a('a');
	ASSERT_TRUE(!a.is_char('b'));
	ASSERT_TRUE(a.is_char('a'));
}

TEST_F(AlphabetTest, Test_get_len_1) {
	Alphabet a('a');
	Alphabet b(2);
	Alphabet c("str");
	Alphabet d;
	ASSERT_EQ(a.get_len(), 1);
	ASSERT_EQ(b.get_len(), 2);
	ASSERT_EQ(c.get_len(), 3);
	ASSERT_EQ(d.get_len(), 0);
}

TEST_F(AlphabetTest, Test_coding_1) {
	Alphabet a(100);
	char* str = random_str(10);
	char* cipher = new char[10];
	a.coding(str, 10, 2, 1, cipher);
	char* str2 = new char[10];
	a.coding(cipher, 10, 2, 0, str2);
	for (int i = 0; i < 10; i++)
	{
		ASSERT_TRUE(str[i] == str2[i]);
	}
}

TEST_F(AlphabetTest, Test_coding_2) {
	Alphabet a(100);
	char* str = random_str(10);
	char* cipher = new char[10];
	a.coding(str, 10, -1, 1, cipher);
	char* str2 = new char[10];
	a.coding(cipher, 10, -1, 0, str2);
	for (int i = 0; i < 10; i++)
	{
		ASSERT_TRUE(str[i] == str2[i]);
	}
}

TEST_F(AlphabetTest, Test_coding_3) {
	Alphabet a(100);
	char* str = random_str(10);
	char* cipher = new char[10];
	ASSERT_EQ(a.coding(str, 11, -1, 1, cipher), -1);
}

TEST_F(AlphabetTest, Test_coding_4) {
	char* str = random_str(10);
	char* cipher = new char[10];
	ASSERT_EQ(y.coding(str, 9, -1, 1, cipher), -1);
}

TEST_F(AlphabetTest, Test_coding_5) {
	Alphabet a;
	char* str = random_str(10);
	char* cipher = new char[10];
	ASSERT_EQ(a.coding(str, 10, -1, 1, cipher), -1);
}

TEST_F(AlphabetTest, Test_coding_6) {
	Alphabet a;
	char* str = random_str(10);
	char* cipher = new char[9];
	ASSERT_EQ(a.coding(str, 10, -1, 1, cipher), -1);
}

int main(int argc, char* argv[]) {
	::testing::FLAGS_gtest_shuffle = 1;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}