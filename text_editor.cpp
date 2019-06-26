#include <string>
#include<list>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor(): textdata{}, buffer{} {
	  curPos = textdata.begin();
  }

  void Left() {
	  if (curPos != textdata.begin())
	  {
		  curPos--;
	  }
  }

  void Right(size_t input = 1) {
	  if (curPos != textdata.end()) {
		  advance(curPos, input);
	  }
  }

  void Insert(char token) {
	  textdata.insert(curPos, token);
  }

  void Cut(size_t tokens = 1) {
	  list<char>::iterator tmpPos{curPos};
	  advance(tmpPos, tokens);
//	  buffer.splice(buffer.begin(), textdata, curPos, tmpPos);
	  buffer = {curPos,  tmpPos};
	  textdata.erase(curPos, tmpPos);
  }

  void Copy(size_t tokens = 1) {
	  list<char>::iterator tmpPos{curPos};
	  advance(tmpPos, tokens);
	  buffer = {curPos, tmpPos};
  }

  void Paste() {
	  textdata.insert(curPos, buffer.begin(), buffer.end());
  }

  string GetText() const {
	  return {textdata.begin(), textdata.end()};
  }

  string GetBuffer() const {
	  return {buffer.begin(), buffer.end()};
  }

 private:
  list<char> textdata;
  list<char> buffer;
  list<char>::iterator curPos;
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
    cout << "text: " << editor.GetText() << endl;
    cout << "buffer: " << editor.GetBuffer() << endl;
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ",.");
    cout << "Typing" << endl;
    cout << "text: " << editor.GetText() << endl;
    cout << "buffer: " << editor.GetBuffer() << endl;
    editor.Paste();
    cout << "Pasting" << endl;
    cout << "text: " << editor.GetText() << endl;
    cout << "buffer: " << editor.GetBuffer() << endl;
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
