#include <string>
#include <string_view>
#include <list>
#include "test_runner.h"
using namespace std;

using IT = list<char>::iterator;

class Editor {
public:
<<<<<<< HEAD
  Editor() : text{} {
	  pos = 0;
  }

  // сдвинуть курсор влево
  void Left() {
	  if (pos != 0) {
		  pos--;
	  }
  }

  // сдвинуть курсор вправо
  void Right() {
	  if (pos != text.size()) {
		  pos++;
	  }
  }

  // вставить символ token
  void Insert(char token) {
	  text.insert(GetIt(), token);
   }
=======
  Editor();
  // сдвинуть курсор влево
  void Left(){
	  text = {};
	  pos = 0;
  };

  // сдвинуть курсор вправо
  void Right();

  // вставить символ token
  void Insert(char token);
>>>>>>> parent of 5ecb0c8... Update text_editor.cpp

  // cкопировать не более tokens символов, начиная с текущей позиции курсора
  void Copy(size_t tokens);

  // вырезать не более tokens символов, начиная с текущей позиции курсора
<<<<<<< HEAD
  void Cut(size_t tokens) {
	  for (size_t i = 0; i < tokens; ++i) {
		  buffer.push_back(*pos);
		  text.erase(pos);
	  }
//	  cout << "Text: " << GetText() << endl;
   }
=======
  void Cut(size_t tokens);
>>>>>>> parent of 5ecb0c8... Update text_editor.cpp

  // вставить содержимое буфера в текущую позицию курсора
  void Paste();

  // получить текущее содержимое текстового редактора
<<<<<<< HEAD
  string GetText() const {
	  return {text.begin(), text.end()};
  }

private:
  list<char> text;
  list<char> buffer;
  size_t pos;

  IT GetIt(size_t input = pos) {
	  IT result = text.begin();
	  for (size_t i = 0; i != input; i++) {
		  result++;
	  }
	  return result;
  }
=======
  string GetText() const;

private:
  list<char> text;
  size_t pos;
>>>>>>> parent of 5ecb0c8... Update text_editor.cpp

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
//    cout << editor.GetText() << endl;
//    cout << "Current pos: " << editor.GetPos() << endl;
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }


    editor.Cut(first_part_len);
    cout << editor.GetText() << endl;
//    cout << "Current pos: " << editor.GetPos() << endl;

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
