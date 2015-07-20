#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include "LJS.h"
using namespace std;
using namespace LJS;

void of(string fn, string o)
{
	FILE * fi;
	fopen_s(&fi, fn.c_str(), "w");
	fwrite(o.c_str(), 1, o.size(), fi);
	fclose(fi);
}

string join(vector<string > s, string j = "\n")
{
	string rv = "";
	for(vector<string>::iterator i = s.begin(); i != s.end(); i++)
	{
		rv += *i;
		if(i+1 != s.end())
		{
			rv += j;
		}
	}
	return rv;
}

int main()
{
	cout << "Javascript Interpreter #1" << endl;
	//Lexicon l;
	//cout << l.toString(VAR) << endl;
	string v = string("var a = ")+LJS_int2String( 5)+string(";print('output: ' + a);");
	string fileName = "C:/Users/luke/Desktop/lukes fun project/main.js";
	string compiledName = "C:/Users/luke/Desktop/lukes fun project/compiledData.txt";
	string op = "hello\n";
	
	//LJS_File_Parser l = fileName;
	LexicalAnalyser l;
	vector<Lexicon> lv = l.parse_file(fileName);
	for(vector<Lexicon>::iterator i = lv.begin(); i != lv.end(); i++)
	{
		op += (*i).fullStr() + string("\n");
	}

	of("C:/Users/luke/Desktop/lukes fun project/compiled.txt", op);

	map<string, LJSVar> mp;


	LJS_Parser c;
	c.compile(lv);
	of(compiledName, join(c.assembly_code));
	//c.dumpAssembly();
	cout << "compiled!" << endl;
	LJS_RunTime rt(c.assembly_code, c.literalList);


	//map<string, int> tt;
	
	while(!rt.finished())
	{
		rt.iterate();
	}
	//rt.dumpStack();
	
	system("pause");
	return 0;
}