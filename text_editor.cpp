#include <string>
#include <string_view>
#include <list>
#include "test_runner.h"
using namespace std;

/*
class Editor {
public:
	// Реализуйте конструктор по умолчанию и объявленные методы
	Editor(): text{} {
		pos = 0;
	}

	// сдвинуть курсор влево
	void Left() {
		if (pos == 0) {
			return;
		}
		--pos;
	}

	// сдвинуть курсор вправо
	void Right(size_t p = 1) {
		if(pos == text.size()) {
			return;
		}
		pos+=p;
	}

	// вставить символ token
	void Insert(char token) {
		text.insert(pos, 1, token);
		Right();
	}

	// cкопировать не более tokens символов,  начиная с текущей позиции курсора
	void Copy(size_t tokens) {
		buffer = text.substr(pos, tokens);
	}

	// вырезать не более tokens символов, начиная с текущей позиции курсора
	void Cut(size_t tokens) {
		Copy(tokens);
		text.erase(pos, tokens);
	}

	// вставить содержимое буфера в текущую позицию курсора
	void Paste() {
		text.insert(pos, buffer);
		Right(buffer.size());
	}

	string GetText() const {  // получить текущее содержимое текстового редактора
		return text;
	}

	void ShowPos() const {
		cout << "Current Position (pos/lenght): " << pos << '/' << text.size() << endl;
	}

	void ShowBuffer() const {
		cout << "Buffer: " << buffer << endl;
	}

private:
	size_t pos;
	string text;
	string buffer;
};
*/

class Editor {
public:
  Editor() : text{} {
	  pos = text.begin();
  }

  // сдвинуть курсор влево
  void Left() {
	  if (pos != text.begin()) {
		  --pos;
	  }
  }

  // сдвинуть курсор вправо
  void Right() {
	  if (pos != text.end()) {
		  ++pos;
	  }
  }

  // вставить символ token
  void Insert(char token) {
	  text.insert(pos, token);
  }

  // cкопировать не более tokens символов, начиная с текущей позиции курсора
  void Copy(size_t tokens) {
	  list<char>::iterator destPos = pos;
	  for (size_t i = 0; i < tokens; ++i) {
		  buffer.push_back(*destPos);
		  ++destPos;
	  }
  }

  // вырезать не более tokens символов, начиная с текущей позиции курсора
  void Cut(size_t tokens) {
	  for (size_t i = 0; i < tokens; ++i) {
		  buffer.push_back(*pos);
		  text.erase(pos);
	  }
  }

  // вставить содержимое буфера в текущую позицию курсора
  void Paste() {
	  text.insert(pos, buffer.begin(), buffer.end());
  }

  // получить текущее содержимое текстового редактора
  string GetText() const {
	  string result;
	  for (auto el : text) {
		  result += el;
	  }
	  return result;
  }

private:
  list<char> text;
  list<char> buffer;
  list<char>::iterator pos;

};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello,.world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ",.");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world,.hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);

  return 0;
}
