#include <cctype>
#include <cstring>
#include <functional>

#include "AdjacencyList.h"
#include "ArrayWrapper.h"
#include "catch.hpp"
#include "LinkedList.h"
#include "Stack.h"
#include "String.h"

TEST_CASE("String class", "[string]")
{
	String testBase = "testing";
	char testCS[] = "testingCS";

	SECTION("COPY CONSTRUCTOR")
	{
		String s = testBase;
		String t = s;
		REQUIRE(s == testBase);
		REQUIRE(t == s);
		REQUIRE(t == testBase);
	}

	SECTION("COPY CSTRING CONSTRUCTOR")
	{
		String s = testCS;
		String t = s.c_string();
		REQUIRE(s == testCS);
		REQUIRE(t == s);
		REQUIRE(t == String(testCS));
	}

	SECTION("ASSIGNMENT OPERATOR")
	{
		String s;
		String t;
		s = testBase;
		t = s;
		REQUIRE(s == testBase);
		REQUIRE(t == s);
		REQUIRE(t == testBase);
	}

	SECTION("CSTRING ASSIGNMENT OPERATOR")
	{
		String s;
		String t;
		s = testCS;
		t = s.c_string();
		REQUIRE(s == testCS);
		REQUIRE(t == s);
		REQUIRE(t == testCS);
	}

	SECTION("STRING STRING EQUALITY OPERATOR")
	{
		REQUIRE(String("a") == String("a"));
		REQUIRE(String("b") == String("b"));
		REQUIRE(String("c") == String("c"));
	}

	SECTION("LESS THAN OPERATOR")
	{
		REQUIRE(String("a") < String("ba"));
		REQUIRE(String("b") < String("be"));
		REQUIRE(!(String("a") < String("a")));
	}

	SECTION("GREATER THAN OPERATOR")
	{
		REQUIRE(String("ba") > String("a"));
		REQUIRE(String("be") > String("b"));
		REQUIRE(!(String("a") > String("a")));
	}

	SECTION("LESS THAN/EQUAL TO OPERATOR")
	{
		REQUIRE(String("a") <= String("a"));
		REQUIRE(String("b") <= String("be"));
		REQUIRE(!(String("b") <= String("a")));
	}

	SECTION("GREATER THAN/EQUAL TO OPERATOR")
	{
		REQUIRE(String("a") >= String("a"));
		REQUIRE(String("be") >= String("b"));
		REQUIRE(!(String("a") >= String("b")));
	}

	SECTION("STRING CSTRING EQUALITY OPERATOR")
	{
		REQUIRE(String("a") == "a");
		REQUIRE(String("b") == "b");
		REQUIRE(String("c") == "c");
	}

	SECTION("CSTRING STRING EQUALITY OPERATOR")
	{
		REQUIRE("a" == String("a"));
		REQUIRE("b" == String("b"));
		REQUIRE("c" == String("c"));
	}

	SECTION("STRING STRING INEQUALITY OPERATOR")
	{
		REQUIRE(String("a") != String("b"));
		REQUIRE(String("b") != String("c"));
		REQUIRE(String("c") != String("a"));
	}

	SECTION("STRING CSTRING INEQUALITY OPERATOR")
	{
		REQUIRE(String("a") != "b");
		REQUIRE(String("b") != "c");
		REQUIRE(String("c") != "a");
	}

	SECTION("CSTRING STRING INEQUALITY OPERATOR")
	{
		REQUIRE("a" != String("b"));
		REQUIRE("b" != String("c"));
		REQUIRE("c" != String("a"));
	}

	SECTION("STRING APPEND OPERATOR")
	{
		String base = "base";
		String a = "a";
		String b = "b";
		String c = "c";
		REQUIRE((base += a) == "basea");
		REQUIRE((base += b) == "baseab");
		REQUIRE((base += c) == "baseabc");
	}

	SECTION("CSTRING APPEND OPERATOR")
	{
		String base = "base";
		char a[] = "a";
		char b[] = "b";
		char c[] = "c";
		REQUIRE((base += a) == "basea");
		REQUIRE((base += b) == "baseab");
		REQUIRE((base += c) == "baseabc");
	}

	SECTION("CHAR APPEND OPERATOR")
	{
		String base = "base";
		char a = 'a';
		char b = 'b';
		char c = 'c';
		REQUIRE((base += a) == "basea");
		REQUIRE((base += b) == "baseab");
		REQUIRE((base += c) == "baseabc");
	}

	SECTION("CHAR AT INDEX OPERATOR")
	{
		String base = "test";
		REQUIRE(base[0] == 't');
		REQUIRE(base[1] == 'e');
		REQUIRE(base[2] == 's');
	}

	SECTION("STRING STRING ADDITION OPERATOR")
	{
		String left = "left";
		String right = "right";

		REQUIRE((left + right) == "leftright");
		REQUIRE((right + left) == "rightleft");
		REQUIRE((left + right + left) == "leftrightleft");
	}

	SECTION("STRING CSTRING ADDITION OPERATOR")
	{
		String left = "left";
		char right[] = "right";
		char mid[] = "mid";

		REQUIRE((left + right) == "leftright");
		REQUIRE((left + right + right) == "leftrightright");
		REQUIRE((left + mid) == "leftmid");
	}

	SECTION("STRING CHAR ADDITION OPERATOR")
	{
		String left = "left";
		char r = 'r';
		char s = 's';

		REQUIRE((left + r) == "leftr");
		REQUIRE((left + r + r) == "leftrr");
		REQUIRE((left + s) == "lefts");
	}

	SECTION("CSTRING STRING ADDITION OPERATOR")
	{
		char left[] = "left";
		String right = "right";
		String mid = "mid";

		REQUIRE((left + right) == "leftright");
		REQUIRE((left + (left + right)) == "leftleftright");
		REQUIRE((left + mid) == "leftmid");

	}

	SECTION("CHAR STRING ADDITION OPERATOR")
	{
		String left = "left";
		String right = "right";
		char s = 's';

		REQUIRE((s + left) == "sleft");
		REQUIRE((s + right) == "sright");
		REQUIRE((s + (s + right)) == "ssright");
	}

	SECTION("GETLENGTH")
	{
		REQUIRE(String("testing").getLength() == 7);
		REQUIRE(String("left").getLength() == 4);
		REQUIRE(String().getLength() == 0);
	}

	SECTION("SUBSTRING")
	{
		String base = "testing";
		REQUIRE(base.substring(1, 3) == "es");
		REQUIRE(base.substring(0, 1) == "t");
		REQUIRE(base.substring(1, base.getLength()) == "esting");
	}

	SECTION("SUBSTRINGLENGTH")
	{
		String base = "testing";
		REQUIRE(base.substringLength(1, 3) == "est");
		REQUIRE(base.substringLength(1, 1) == "e");
		REQUIRE(base.substringLength(1, 2) == "es");
	}

	SECTION("STRING SPLIT")
	{
		String split = "testing";
		String toSplit = "atestingbtestingctestingd";
		REQUIRE(toSplit.split(split).arrayLength() == 4);
		REQUIRE(toSplit.split(split)[0] == "a");
		REQUIRE(toSplit.split(split)[1] == "b");
	}

	SECTION("CSTRING SPLIT")
	{
		char split[] = "testingCS";
		String toSplit = "atestingCSbtestingCSctestingCSd";

		REQUIRE(toSplit.split(split).arrayLength() == 4);
		REQUIRE(toSplit.split(split)[0] == "a");
		REQUIRE(toSplit.split(split)[1] == "b");
	}

	SECTION("CHAR SPLIT")
	{
		String toSplit = "atbtctd";

		REQUIRE(toSplit.split('t').arrayLength() == 4);
		REQUIRE(toSplit.split('t')[0] == "a");
		REQUIRE(toSplit.split('t')[1] == "b");
	}

	SECTION("PREDICATE SPLIT")
	{
		String toSplit = "a.b?c!d";
        
		std::function<bool(char)> p = [](char c) -> bool
		{
			return ispunct(c);
		};
        
		REQUIRE(toSplit.split(p).arrayLength() == 4);
		REQUIRE(toSplit.split(p)[0] == "a");
		REQUIRE(toSplit.split(p)[1] == "b");
	}

	SECTION("STRING FIND")
	{
		String find = "testing";
		String toSearch = "hiTESTINGhilo";
		REQUIRE(toSearch.find(find, false) == 2);
		REQUIRE(toSearch.find(find, true) == toSearch.getLength());
		REQUIRE(toSearch.find(find, false, 4) == toSearch.getLength());
	}

	SECTION("CSTRING FIND")
	{
		char find[] = "testingCS";
		String toSearch = "hiTESTINGCShilo";
		REQUIRE(toSearch.find(find, false) == 2);
		REQUIRE(toSearch.find(find, true) == toSearch.getLength());
		REQUIRE(toSearch.find(find, false, 4) == toSearch.getLength());
	}

	SECTION("CHAR FIND")
	{
		String toSearch = "hiThilo";
		REQUIRE(toSearch.find('t', false) == 2);
		REQUIRE(toSearch.find('t', true) == toSearch.getLength());
		REQUIRE(toSearch.find('t', false, 4) == toSearch.getLength());
	}

	SECTION("GETHASHCODE")
	{
		REQUIRE(String().getHashCode() == 0);
		REQUIRE(String("a").getHashCode() == 97);
		REQUIRE(String("testing").getHashCode() == 105951736336);
	}

	SECTION("TRIM")
	{
		String spaced = "   ha   ";
		String spaceOut = "  t t  ";
		REQUIRE(spaced.trim() == "ha");
		REQUIRE((' ' + String("testing") + ' ').trim() == "testing");
		REQUIRE(spaceOut.trim() == "t t");
	}

	SECTION("TRIMSTART")
	{
		String spaced = "   ha   ";
		String spaceOut = "  t t  ";
		REQUIRE(spaced.trimStart() == "ha   ");
		REQUIRE((' ' + String("testing")).trimStart() == "testing");
		REQUIRE(spaceOut.trimStart() == "t t  ");
	}

	SECTION("TRIMEND")
	{
		String spaced = "   ha   ";
		String spaceOut = "  t t  ";
		REQUIRE(spaced.trimEnd() == "   ha");
		REQUIRE((String("testing") + ' ').trimEnd() == "testing");
		REQUIRE(spaceOut.trimEnd() == "  t t");
	}

	SECTION("STRIPCHARACTER CHAR")
	{
		String base = "abcbdBebfB";

		REQUIRE(base.stripCharacter('b') == "acdBefB");
		REQUIRE(base.stripCharacter('b', false) == "acdef");
		REQUIRE(String("b").stripCharacter('b') == "");
	}

	SECTION("STRIPCHARACTER PREDICATE")
	{
		String base = "abcbdBebfB";
        
		std::function<bool(char)> p1 = [](char c) -> bool
		{
			return c == 'b';
		};
        
		std::function<bool(char)> p2 = [](char c) -> bool
		{
			return tolower(c) == 'b';
		};

		REQUIRE(base.stripCharacter(p1) == "acdBefB");
		REQUIRE(base.stripCharacter(p2) == "acdef");
		REQUIRE(String("b").stripCharacter(p1) == "");
	}

	SECTION("TOLOWER")
	{
		REQUIRE(String("A").toLower() == "a");
		REQUIRE(String("TESTING").toLower() == "testing");
		REQUIRE(String("B").toLower() != "B");
	}

	SECTION("TOUPPER")
	{
		REQUIRE(String("a").toUpper() == "A");
		REQUIRE(String("testing").toUpper() == "TESTING");
		REQUIRE(String("b").toUpper() != "b");
	}

	SECTION("CLONE")
	{
		String base = "testing";
		String cloned = base.clone();
		REQUIRE(cloned == base);
		REQUIRE(cloned.getLength() == base.getLength());
		REQUIRE((cloned + 'a') == (base + 'a'));
	}

	SECTION("C_STRING")
	{
		REQUIRE(strcmp(String("testing").c_string(), "testing") == 0);
		REQUIRE(strcmp(String("a").c_string(), "a") == 0);
		REQUIRE(strcmp(String("b").c_string(), "b") == 0);
	}
}

TEST_CASE("LinkedList class", "[linkedlist]")
{
	int numbers[] = {0, 1, 2, 3, 4, 5};

	SECTION("COPY CONSTRUCTOR")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);

		LinkedList<int> listTwo = listOne;

		REQUIRE(listOne.getSize() == listTwo.getSize());
		REQUIRE(listOne.getElement(0) == listTwo.getElement(0));
		REQUIRE(listOne.getElement(1) == listTwo.getElement(1));
	}

	SECTION("ASSIGNMENT OPERATOR")
	{
		LinkedList<int> listOne;
		LinkedList<int> listTwo;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);

		listTwo = listOne;

		REQUIRE(listOne.getSize() == listTwo.getSize());
		REQUIRE(listOne.getElement(0) == listTwo.getElement(0));
		REQUIRE(listOne.getElement(1) == listTwo.getElement(1));
	}

	SECTION("GETSIZE")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);
		LinkedList<int> listTwo;
		listTwo.addElement(numbers[2]);

		REQUIRE(listOne.getSize() == 2);
		REQUIRE(listTwo.getSize() == 1);
		REQUIRE(LinkedList<int>().getSize() == 0);
	}

	SECTION("ISEMPTY")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		LinkedList<int> listTwo;
		listTwo.addElement(numbers[1]);

		REQUIRE(!listOne.isEmpty());
		REQUIRE(!listTwo.isEmpty());
		REQUIRE(LinkedList<int>().isEmpty());
	}

	SECTION("ITERATOR")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);
		listOne.addElement(numbers[2]);

		int index = 0;
        
		for (int i : listOne)
		{
			REQUIRE(i == listOne.getElement(index++));
		}
        
		REQUIRE(index == listOne.getSize());
        
		REQUIRE_THROWS([&]()
		{
			for (int i : listOne)
			{
				listOne.removeElement(i);
			}
		}());
	}

	SECTION("CONTAINSELEMENT")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[1]);
		listOne.addElement(numbers[2]);

		REQUIRE(listOne.containsElement(numbers[1]));
		REQUIRE(listOne.containsElement(numbers[2]));
		REQUIRE(!listOne.containsElement(numbers[3]));
	}

	SECTION("CONTAINSELEMENTBYVALUE")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[1]);
		listOne.addElement(numbers[2]);

		REQUIRE(listOne.containsElementByValue(1));
		REQUIRE(listOne.containsElementByValue(2));
		REQUIRE(!listOne.containsElementByValue(3));
	}

	SECTION("GETELEMENT BY INDEX")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);

		REQUIRE(listOne.getElement(0) == numbers[0]);
		REQUIRE(listOne.getElement(1) == numbers[1]);
		REQUIRE_THROWS(listOne.getElement(2));
	}

	SECTION("INDEXOF")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);

		REQUIRE(listOne.indexOf(numbers[0]) == 0);
		REQUIRE(listOne.indexOf(numbers[1]) == 1);
		REQUIRE(listOne.indexOf(numbers[2]) == listOne.getSize());
	}

	SECTION("INDEXOFBYVALUE")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);

		REQUIRE(listOne.indexOfByValue(0) == 0);
		REQUIRE(listOne.indexOfByValue(1) == 1);
		REQUIRE(listOne.indexOfByValue(2) == listOne.getSize());
	}

	SECTION("ADDELEMENT")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);
		listOne.addElement(numbers[2]);

		REQUIRE(listOne.getElement(0) == numbers[0]);
		REQUIRE(listOne.getElement(1) == numbers[1]);
		REQUIRE(listOne.getElement(2) == numbers[2]);
	}

	SECTION("ADDELEMENTBYVALUE")
	{
		LinkedList<int> listOne;
		listOne.addElementByValue(0);
		listOne.addElementByValue(1);
		listOne.addElementByValue(2);

		REQUIRE(listOne.getElement(0) == 0);
		REQUIRE(listOne.getElement(1) == 1);
		REQUIRE(listOne.getElement(2) == 2);
	}

	SECTION("INSERTELEMENT")
	{
		LinkedList<int> listOne;
		listOne.insertElement(numbers[1], 0);
		listOne.insertElement(numbers[2], 0);
		listOne.insertElement(numbers[3], 1);

		REQUIRE(listOne.getElement(0) == numbers[2]);
		REQUIRE(listOne.getElement(1) == numbers[3]);
		REQUIRE(listOne.getElement(2) == numbers[1]);
	}

	SECTION("INSERTELEMENTBYVALUE")
	{
		LinkedList<int> listOne;
		listOne.insertElementByValue(1, 0);
		listOne.insertElementByValue(2, 0);
		listOne.insertElementByValue(3, 1);

		REQUIRE(listOne.getElement(0) == 2);
		REQUIRE(listOne.getElement(1) == 3);
		REQUIRE(listOne.getElement(2) == 1);
	}

	SECTION("REMOVEELEMENT")
	{
		char chars[] = {'a', 'b', 'c'};
		LinkedList<char> listOne;
		listOne.addElement(chars[0]);
		listOne.addElement(chars[1]);

		listOne.removeElement(chars[2]);
		REQUIRE(listOne.getSize() == 2);
		listOne.removeElement(chars[0]);
		REQUIRE(listOne.getElement(0) == chars[1]);
		listOne.removeElement(chars[1]);
		REQUIRE(listOne.isEmpty());
	}

	SECTION("REMOVEELEMENTBYVALUE")
	{
		char chars[] = {'a', 'b', 'c'};
		LinkedList<char> listOne;
		listOne.addElement(chars[0]);
		listOne.addElement(chars[1]);

		listOne.removeElementByValue('c');
		REQUIRE(listOne.getSize() == 2);
		listOne.removeElementByValue('a');
		REQUIRE(listOne.getElement(0) == 'b');
		listOne.removeElementByValue('b');
		REQUIRE(listOne.isEmpty());
	}

	SECTION("REMOVEELEMENTAT")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);

		listOne.removeElementAt(0);
		REQUIRE(listOne.getElement(0) == numbers[1]);
		listOne.removeElementAt(0);
		REQUIRE(listOne.isEmpty());
		REQUIRE_THROWS(listOne.removeElementAt(0));
	}

	SECTION("PEEKBACK")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		REQUIRE(listOne.peekBack() == numbers[0]);
		listOne.addElement(numbers[1]);
		REQUIRE(listOne.peekBack() == numbers[1]);
		listOne.addElement(numbers[2]);
		REQUIRE(listOne.peekBack() == numbers[2]);
	}

	SECTION("POPBACK")
	{
		LinkedList<int> listOne;
		listOne.addElement(numbers[0]);
		listOne.addElement(numbers[1]);

		REQUIRE(listOne.popBack() == numbers[1]);
		REQUIRE(listOne.popBack() == numbers[0]);
		REQUIRE(listOne.isEmpty());
	}
}

TEST_CASE("Stack class", "[stack]")
{
	int numbers[] = {0, 1, 2, 3, 4, 5};

	SECTION("ISEMPTY")
	{
		Stack<int> stackOne;
		stackOne.push(numbers[0]);
		Stack<int> stackTwo;
		stackTwo.push(numbers[1]);

		REQUIRE(!stackOne.isEmpty());
		REQUIRE(!stackTwo.isEmpty());
		REQUIRE(Stack<int>().isEmpty());
	}

	SECTION("PEEK")
	{
		Stack<int> s;
		s.push(numbers[0]);
		REQUIRE(s.peek() == numbers[0]);
		s.push(numbers[1]);
		REQUIRE(s.peek() == numbers[1]);
		s.push(numbers[2]);
		REQUIRE(s.peek() == numbers[2]);
	}

	SECTION("POP")
	{
		Stack<int> s;
		s.push(numbers[0]);
		s.push(numbers[1]);

		REQUIRE(s.pop() == numbers[1]);
		REQUIRE(s.pop() == numbers[0]);
		REQUIRE(s.isEmpty());
	}

	SECTION("PUSH")
	{
		Stack<int> s;
		s.push(numbers[0]);
		REQUIRE(s.peek() == numbers[0]);
		s.push(numbers[1]);
		REQUIRE(s.peek() == numbers[1]);
		s.push(numbers[2]);
		REQUIRE(s.peek() == numbers[2]);
	}

	SECTION("PUSHBYVALUE")
	{
		Stack<int> s;
		s.pushByValue(0);
		REQUIRE(s.peek() == 0);
		s.pushByValue(1);
		REQUIRE(s.peek() == 1);
		s.pushByValue(2);
		REQUIRE(s.peek() == 2);
	}
}

TEST_CASE("AdjacencyList class", "[adjacencylist]")
{
	int numbers[] = {0, 1, 2, 3, 4, 5};

	SECTION("COPY CONSTRUCTOR")
	{
		AdjacencyList<int, int> listOne(numbers[0], [](const int& key) -> long
		{
			if (key < 0)
			{
				return key * -1;
			}
            
			return key;
		});
        
		listOne[numbers[0]] = numbers[1];
		listOne[numbers[1]] = numbers[2];

		AdjacencyList<int, int> listTwo = listOne;

		REQUIRE(listOne.getSize() == listTwo.getSize());
		REQUIRE(listOne[numbers[0]] == listTwo[numbers[0]]);
		REQUIRE(listOne[numbers[1]] == listTwo[numbers[1]]);
	}

	SECTION("ASSIGNMENT OPERATOR")
	{
		AdjacencyList<int, int> listOne(numbers[0], [](const int& key) -> long
		{
			if (key < 0)
			{
				return key * -1;
			}
            
			return key;
		});
        
		AdjacencyList<int, int> listTwo(numbers[0], [](const int& key) -> long
		{
			if (key < 0)
			{
				return key * -1;
			}
            
			return key;
		});
        
		listOne[numbers[0]] = numbers[1];
		listOne[numbers[1]] = numbers[2];

		listTwo = listOne;

		REQUIRE(listOne.getSize() == listTwo.getSize());
		REQUIRE(listOne[numbers[0]] == listTwo[numbers[0]]);
		REQUIRE(listOne[numbers[1]] == listTwo[numbers[1]]);
	}

	SECTION("GETSIZE")
	{
		AdjacencyList<int, int> listOne(numbers[0], [](const int& key) -> long
		{
			if (key < 0)
			{
				return key * -1;
			}
            
			return key;
		});

		REQUIRE(listOne.getSize() == 0);
		listOne[numbers[0]] = numbers[1];
		REQUIRE(listOne.getSize() == 1);
		listOne[numbers[1]] = numbers[2];
		REQUIRE(listOne.getSize() == 2);
	}

	SECTION("KEY LOOKUP OPERATOR")
	{
		AdjacencyList<int, int> listOne(numbers[0], [](const int& key) -> long
		{
			if (key < 0)
			{
				return key * -1;
			}
            
			return key;
		});
        
		listOne[numbers[0]] = numbers[1];
		listOne[numbers[1]] = numbers[2];

		REQUIRE(listOne[numbers[0]] == numbers[1]);
		REQUIRE(listOne[numbers[1]] == numbers[2]);
		REQUIRE(listOne[numbers[2]] == numbers[0]);
		REQUIRE(listOne.getSize() == 3);
	}

	SECTION("REMOVE")
	{
		AdjacencyList<int, int> listOne(numbers[0], [](const int& key) -> long
		{
			if (key < 0)
			{
				return key * -1;
			}
            
			return key;
		});
        
		listOne[numbers[0]] = numbers[1];
		listOne[numbers[1]] = numbers[2];

		listOne.remove(numbers[0]);
		REQUIRE(listOne.getSize() == 1);
		listOne.remove(numbers[1]);
		REQUIRE(listOne.getSize() == 0);
		listOne.remove(numbers[2]);
		REQUIRE(listOne.getSize() == 0);
	}
}
