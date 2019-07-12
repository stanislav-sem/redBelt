#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> && tokens) {
	vector<Sentence<Token>> result;
	Sentence<Token> tmp_cont;
	for (auto el : tokens) {
		if (!el.is_end_sentence_punctuation) {
			tmp_cont.push_back(move(el));
		} else {
			if (tmp_cont.size() != 0) {
				tmp_cont.push_back(move(el));
				result.push_back(move(tmp_cont));
			} else {
				result.back().push_back(el);
			}
		}
	}
	if (tmp_cont.size() != 0) {
		result.push_back(move(tmp_cont));
	}
	return result;
}

template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token>& tokens) {
	vector<Sentence<Token>> result;
	Sentence<Token> tmp_cont;
	for (auto el : tokens) {
		if (!el.is_end_sentence_punctuation) {
			tmp_cont.push_back(move(el));
		} else {
			if (tmp_cont.size() != 0) {
				tmp_cont.push_back(move(el));
				result.push_back(move(tmp_cont));
			} else {
				result.back().push_back(el);
			}
		}
	}
	if (tmp_cont.size() != 0) {
		result.push_back(move(tmp_cont));
	}
	return result;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

// Тест на отсутствие копирования
void TestNoCopy() {
	vector<TestToken> from = {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}};
	ASSERT_EQUAL(
			SplitIntoSentences(from),
			vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
		                                {{"Without"}, {"copies"}, {".", true}}}
	            )
	);

	ASSERT_EQUAL(from.size(), 0);

}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
