#include <string>
#include <string_view>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
	// Реализуйте конструктор по умолчанию и объявленные методы
	Editor(): text{}, buffer{} {
		pos = 0;
	}

	void Left() {   		// сдвинуть курсор влево
		if (pos == 0) {
			return;
		}
		--pos;
	}

	void Right() {  		// сдвинуть курсор вправо
		if(pos == text.size()) {
			return;
		}
		++pos;
	}

	// вставить символ token
	void Insert(char token) {
		text.insert(pos, 1, token);
		Right();
	}

	// cкопировать не более tokens символов,  начиная с текущей позиции курсора
	void Copy(size_t tokens) {
		text.copy(buffer, tokens, pos);
	}

	// вырезать не более tokens символов, начиная с текущей позиции курсора
	void Cut(size_t tokens) {
		text.copy(buffer, tokens, pos);
		text.erase(pos, tokens);
	}

	// вставить содержимое буфера в текущую позицию курсора
	void Paste() {
		text.insert(pos, buffer);
	}

	string GetText() const {  // получить текущее содержимое текстового редактора
		return text;
	}
private:
	size_t pos;
	string text;
	char* buffer = new char[1000000];

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
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
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
//  RUN_TEST(tr, TestReverse);
//  RUN_TEST(tr, TestNoText);
//  RUN_TEST(tr, TestEmptyBuffer);
//	Editor editor;
//
//	const size_t text_len = 12;
//	const size_t first_part_len = 7;
//	TypeText(editor, "hello, world");
//	for (size_t i = 0; i < text_len; ++i) {
//		editor.Left();
//	}
//	editor.Cut(first_part_len);
//	for (size_t i = 0; i < text_len - first_part_len; ++i) {
//		editor.Right();
//	}
//	TypeText(editor, ", ");
//	editor.Paste();
//	editor.Left();
//	editor.Left();
//	editor.Cut(3);
//
//	ASSERT_EQUAL(editor.GetText(), "world, hello");
  return 0;
}
