#ifndef LJScript
#define LJScript

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
using namespace std;

namespace LJS
{

	//enums for various things:
#define NUMBER_OF_TYPES 56
	enum
	{
		VARIABLE, TEMPORARY, LITERAL, REFERENCE, LABELT, NOTYPE
	};

	enum
	{
		VAR, NAME, NUMBER, STRING, //4
		NEW, FUNCTION, RETURN, IF, ELSE, //5
		CONTINUE, BREAK, SWITCH, FOR, DO, //5
		WHILE, TRUE, FALSE, COMMA, SEMICOLON, //5
		OPENBRACK, CLOSEBRACK, OPENBRACE, CLOSEBRACE, //4
		QMARK, COLON, SINGLEQ, DOUBLEQ, LT, LEQ, //6
		GT, GEQ, NE, EQ, OR, AND, NOT, ASSIGN, //8
		OPENSQR, CLOSESQR, DOT, MULT, PLUS, //5
		MINUS, DIVIDE, MODULO, NULLT, CASE, 
		PLUSASSIGN, MINUSASSIGN, DIVIDEASSIGN, MULTASSIGN, MODULOASSIGN, INCREMENT, DECREMENT, DEFAULT, OTHER //6
		// 56

	};


	enum
	{
		BT_POINTER, BT_NUMBER, BT_STRING, BT_UNDEFINED
	};

	//pointer types
	enum
	{
		PT_ARRAY, PT_ARRAY_ELEMENT, PT_FUNCTION, PT_OBJECT, PT_OBJECT_ELEMENT, PT_FUNCTION_ELEMENT, PT_NULL
	};

	string LexiconTypeToString(int type)
	{
		string sar[] = {"VAR","NAME","NUMBER","STRING","NEW","FUNCTION","RETURN","IF","ELSE",
			"CONTINUE","BREAK","SWITCH","FOR","DO","WHILE","TRUE","FALSE","COMMA","SEMICOLON","OPENBRACK",
			"CLOSEBRACK","OPENBRACE","CLOSEBRACE","QMARK","COLON","SINGLEQ","DOUBLEQ","LT","LEQ","GT","GEQ",
			"NE","EQ","OR","AND","NOT","ASSIGN","OPENSQR","CLOSESQR","DOT","MULT","PLUS","MINUS","DIVIDE","MODULO", "NULL", "CASE", 
			"PLUSASSIGN", "MINUSASSIGN", "DIVIDEASSIGN", "MULTASSIGN", "MODULOASSIGN", "INCREMENT", "DECREMENT", "DEFAULT", "OTHER"};
		if(type < 0 || type >= NUMBER_OF_TYPES) return "OTHER";
		return sar[type];
	}
	int LexiconStringToType(string s)
	{
		string sar[] = {"VAR","NAME","NUMBER","STRING","NEW","FUNCTION","RETURN","IF","ELSE",
			"CONTINUE","BREAK","SWITCH","FOR","DO","WHILE","TRUE","FALSE","COMMA","SEMICOLON","OPENBRACK",
			"CLOSEBRACK","OPENBRACE","CLOSEBRACE","QMARK","COLON","SINGLEQ","DOUBLEQ","LT","LEQ","GT","GEQ",
			"NE","EQ","OR","AND","NOT","ASSIGN","OPENSQR","CLOSESQR","DOT","MULT","PLUS","MINUS","DIVIDE","MODULO", "NULL", "CASE", 
			"PLUSASSIGN", "MINUSASSIGN", "DIVIDEASSIGN", "MULTASSIGN", "MODULOASSIGN", "INCREMENT", "DECREMENT", "DEFAULT", "OTHER"};
		
		for(int i = 0; i < NUMBER_OF_TYPES; i++)
		{
			if(s == sar[i]) return i;
		}
		return -1;
	}
	vector<string> LJS_split(string s, char delim)
	{
		vector<string> rv;
		string tmp = "";
		for(int i = 0; i < s.size(); i++)
		{
			char c = s[i];
			if(c == delim)
			{
				rv.push_back(tmp);
				tmp = "";
			}else
			{
				tmp += c;
			}
		}
		rv.push_back(tmp);
		return rv;
	}
	bool LJS_in(string set, char c)
	{
		for(int i = 0; i < set.size(); i++)
		{
			if(set[i] == c)
			{
				return true;
			}
		}
		return false;
	}
	bool LJS_tin(int* st, int sl, int t)
	{
		for(int i = 0; i < sl; i++)
		{
			if(st[i] == t) return true;
		}
		return false;
	}
	void LJS_error(string er, int er_no = 0)
	{
		cout << er << endl;
		system("pause");
		exit(er_no);
	}
	string LJS_int2String(int i)
	{
		char buf[100];
		//ssprintf(buf, "%i", i);
		sprintf_s(buf, "%i", i);
		return string(buf);
	}
	string LJS_double2String(double i)
	{
		char buf[100];
		//ssprintf(buf, "%i", i);
		sprintf_s(buf, "%f", i);
		return string(buf);
	}
	int LJS_string2Int(string s)
	{
		int i = 0;
		//ssprintf(buf, "%i", i);
		sscanf_s(s.c_str(), "%i", &i);
		return i;
	}
	double LJS_string2Double(string s)
	{
		double d=0.0;
		sscanf_s(s.c_str(), "%lf", &d);
		return d;
	}
	bool LJS_isKewWord(string st)
	{
		//kws.len = 17
		string kws[] = {"var", "new", "function", "return", "if", "else", "continue", "break", "switch", "for", "while", "do", "true", "false", "null", "case", "default"};
		int rv[] = {VAR, NEW, FUNCTION, RETURN, IF, ELSE, CONTINUE, BREAK, SWITCH, FOR, WHILE, DO, TRUE, FALSE, NULLT, CASE, DEFAULT};
		for(int i = 0; i < 17; i++)
		{
			if(st == kws[i])
			{
				return true;
			}
		}
		return false;

	}
	int LJS_getKewWord(string st)
	{
		//kws.len = 17
		string kws[] = {"var", "new", "function", "return", "if", "else", "continue", "break", "switch", "for", "while", "do", "true", "false", "null", "case", "default"};
		int rv[] = {VAR, NEW, FUNCTION, RETURN, IF, ELSE, CONTINUE, BREAK, SWITCH, FOR, WHILE, DO, TRUE, FALSE, NULLT, CASE, DEFAULT};
		for(int i = 0; i < 17; i++)
		{
			if(st == kws[i])
			{
				return rv[i];
			}
		}
		return OTHER;
	}
	int LJS_getKWOrVar(string st)
	{
		if(LJS_isKewWord(st))
		{
			return LJS_getKewWord(st);
		}
		return NAME;
	}
	bool LJS_varType(int t)
	{
		if(t == NAME || t == NUMBER || t == STRING)
		{
			return true;
		}
		return false;
	}
	//todo::> isprefix and finish below.
	bool LJS_hasPrefix(string st, string prefix)
	{
		if(prefix.size() <= st.size())
		{
			for(int i = 0; i < prefix.size(); i++)
			{
				if(prefix[i] != st[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	int LJS_typeOfVar(string inp)
	{
		if(LJS_hasPrefix(inp, "V'"))
		{
			return VARIABLE;
		}else if(LJS_hasPrefix(inp, "T't_"))
		{
			return TEMPORARY;
		}else if(LJS_hasPrefix(inp, "L't_"))
		{
			return LITERAL;
		}else if(LJS_hasPrefix(inp, "R't_"))
		{
			return REFERENCE;
		}else if(LJS_hasPrefix(inp, "Label't_"))
		{
			return LABELT;
		}
		return NOTYPE;
	}
	string LJS_BT2String(int t)
	{
		string rva[] = {"BT_POINTER", "BT_NUMBER", "BT_STRING", "BT_UNDEFINED_OR_NULL"};
		int rvi[] = {BT_POINTER, BT_NUMBER, BT_STRING, BT_UNDEFINED};
		for(int i = 0; i < 4; i++)
		{
			if(t == rvi[i])
			{
				return rva[i];
			}
		}
		return "OTHER";
	}

	template <class T>
	class LIndexMap
	{
		string * key;
		T * elems;
		int blen, len;
	public:
		LIndexMap()
		{
			blen = 2;
			key = new string[blen];
			elems = new T[blen];
			len = 0;
		}

		LIndexMap(const LIndexMap & i)
		{
			deep_copy(i);
		}

		LIndexMap&operator=(const LIndexMap & i)
		{
			deep_copy(i);
			return *this;
		}

		~LIndexMap()
		{
			freeIfNeed();
		}
	private:
		void freeIfNeed()
		{
			if(blen > 0)
			{
				delete [] key;
				delete [] elems;
				blen = len = 0;
			}
		}

		void shallow_copy(const LIndexMap & i)
		{
			len = i.len;
			blen = i.blen;
			elems = i.elems;
			key = i.key;
		}

		void deep_copy(const LIndexMap & i)
		{
			freeIfNeed();
			len = i.len;
			blen = i.blen;
			key = new string[blen];
			elems = new T[blen];
			for(int b = 0; b < len; b++)
			{
				key[b] = i.key[b];
				elems[b] = i.elems[b];
			}
		}

		int get_index(string k)
		{
			for(int i = 0; i < len; i++)
			{
				if(key[i] == k)
				{
					return i;
				}
			}
			return -1;
		}

		void force_add(string k)
		{
			if(len+3 >= blen)
			{
				inc_buffer();
			}
			key[len] = k;
			elems[len] = 0;
			len++;
		}

		T & access(string k)
		{
			int index = get_index(k);
			if(index == -1)
			{
				force_add(k);
				index = get_index(k);
			}
			return elems[index];
		}

		T & access(int k)
		{
			if(k < 0 || k >= len)
			{
				LJS_error("accessing array out of bounds!");
			}
			return elems[k];
		}

		void inc_buffer()
		{
			int nblen = blen * 2;
			int nlen = len;
			string * k2 = new string[nblen];
			T * e2 = new T[nblen];
			for(int i = 0; i < nlen; i++)
			{
				k2[i] = key[i];
				e2[i] = elems[i];
			}
			freeIfNeed();
			blen = nblen;
			len = nlen;
			key = k2;
			elems = e2;
		}

	public:
		T & operator[](string k)
		{
			return access(k);
		}
		T & operator[](int k)
		{
			return access(k);
		}

		int indexOf(string k)
		{
			int index = get_index(k);
			if(index == -1)
			{
				force_add(k);
				return get_index(k);
			}
			return index;
		}

		vector<string> keys()
		{
			vector<string> ks;
			for(int i = 0; i < len; i++)
			{
				ks.push_back(key[i]);
			}
			return ks;
		}
		int size()
		{
			return len;
		}

	};

	class Lexicon
	{
	public:
		int type, line_number;
		string str;
		Lexicon(){ type = OTHER; line_number = -1; str = "";}
		Lexicon(int typeIn, string stringIn, int lineNumberIn = -1)
		{
			type = typeIn;
			str = stringIn;
			line_number = lineNumberIn;
		}
		Lexicon(const Lexicon & inp)
		{
			type = inp.type;
			str = inp.str;
			line_number = inp.line_number;
		}
		Lexicon&operator=(const Lexicon&inp)
		{
			type = inp.type;
			str = inp.str;
			line_number = inp.line_number;
			return *this;
		}
		string toStr(){return LexiconTypeToString(type);}
		string toStrL(){return string("{") + toStr() + str + "}";}
		string fullStr()
		{
			return toStr() + string(" ") + str + string(" ") + LJS_int2String(line_number);
		}
	};

	class LJS_File_Parser
	{
	public:
		string file;
		int index, length;
		int new_line;
		LJS_File_Parser()
		{
			file = ""; index = length = new_line = 0;
		}
		void copy(const LJS_File_Parser & p)
		{
			file = p.file; length = p.length; index = p.index;
		}
		LJS_File_Parser (const LJS_File_Parser & p){copy(p);}
		LJS_File_Parser&operator=(const LJS_File_Parser & p){copy(p); return *this;}
		void openString(string st)
		{
			file = st;
			index = 0;
			new_line = 0;
			length = file.size();
		}
		void openFile(string fname)
		{
			file = "";
			char buf[100]; FILE * f;
			fopen_s(&f, fname.c_str(), "r");
			while(!feof(f))
			{
				int ar = fread_s(buf, 100, 1, 99, f);
				buf[ar] = '\0';
				file += buf;
			}
			fclose(f);
			index = 0;
			new_line = 0;
			length = file.size();
		}
		char pop()
		{
			char rv = 0x00;
			if(eof()) return rv;
			rv = file[index];
			if(rv == '\n') new_line++;
			index++;
			return rv;
			
		}
		void unpop()
		{
			index--;
			if(index < 0){ index = 0; new_line = 0; }
			else if(file[index] == '\n') new_line--;
			new_line = (new_line < 0) ? 0 : new_line;
			
		}
		bool eof()
		{
			if(index >= length) return true; return false;
		}
		char check()
		{
			char rv = pop();
			unpop();
			return rv;
		}
	};

	class LexicalAnalyser
	{
	public:
		LexicalAnalyser(){}
		vector<Lexicon> parse_file(string fname)
		{
			LJS_File_Parser s; s.openFile(fname);
			return parse(s);
		}
		vector<Lexicon> parse_string(string f)
		{
			LJS_File_Parser s; s.openString(f);
			return parse(s);
		}


		int find_single_lex_type(string a, string st)
		{
			int iv[] = {COMMA, SEMICOLON, OPENBRACK, CLOSEBRACK, OPENBRACE, CLOSEBRACE, QMARK, COLON, OPENSQR, CLOSESQR};
			//length of iv = 10
			for(int i = 0; i < 10; i++)
			{
				if(a[i] == st[0])
				{
					return iv[i];
				}
			}
			return OTHER;
		}

		

		vector<Lexicon> parse(LJS_File_Parser & fp)
		{
			vector<Lexicon> rv;
			int state = 0;
			string st = "";
			string L = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_$abcdefghijklmnopqrstuvwxyz";
			string N = "0123456789";
			string a = ",;(){}?:[]";
			string b = "'";
			string cs = "\"";
			string d = "<";
			string e = ">";
			string f = "=";
			string g = "!";
			string h = "|";
			string i = "&";
			string k = ".";
			string n = "\\";
			string nL = "\n";
			string p = "/";
			string s = "*";
			string w = "+";
			string x = "-";
			string mod = "%";
			while(!fp.eof())
			{
				char c = fp.pop();
				//cout << c << " , state = " << state << endl;
				switch(state)
				{
				case 0:
					if(LJS_in(N,c))
					{
						st = c; state = 1;
					}else if(LJS_in(L,c))
					{
						st = c; state = 5;
					}else if(LJS_in(a,c))
					{
						st = c; state = 7;
					}else if(LJS_in(b,c))
					{
						st = ""; state = 8;
					}else if(LJS_in(cs,c))
					{
						st = ""; state = 12;
					}else if(LJS_in(d,c))
					{
						st = c; state = 16;
					}else if(LJS_in(e,c))
					{
						st = c; state = 18;
					}else if(LJS_in(f,c))
					{
						st = c; state = 20;
					}else if(LJS_in(g,c))
					{
						st = c; state = 22;
					}else if(LJS_in(h,c))
					{
						st = c; state = 24;
					}else if(LJS_in(i,c))
					{
						st = c; state = 26;
					}else if(LJS_in(k,c))
					{
						st = c; state = 28;
					}else if(LJS_in(s,c))
					{
						st = c; state = 33;
					}else if(LJS_in(p,c))
					{
						st = c; state = 29;
					}else if(LJS_in(w,c))
					{
						st = c; state = 34;
					}else if(LJS_in(x,c))
					{
						st = c; state = 36;
					}else if(LJS_in(mod,c))
					{
						st = c; state = 38;
					}else
					{
						state = 0;
					}
					break;
				case 1:
					if(LJS_in(N, c))
					{
						st += c; state = 1;
					}else if(LJS_in(k, c))
					{
						st += c; state = 2;
					}else
					{
						fp.unpop();
						state = 4;
					}
					break;
				case 2:
					if(LJS_in(N, c))
					{
						st += c; state = 3;
					}else
					{
						LJS_error("error in state 2 lex analyser");
					}
					break;
				case 3:
					if(LJS_in(N, c))
					{
						st += c; state = 3;
					}else
					{
						fp.unpop();
						state = 4;
					}
					break;
				case 4:
					fp.unpop();
					rv.push_back(Lexicon(NUMBER, st, fp.new_line));
					st = "";
					state = 0;
					break;
				case 5:
					if(LJS_in(N, c) || LJS_in(L,c))
					{
						st += c; state = 5;
					}else
					{
						fp.unpop();
						state = 6;
					}
					break;
				case 6:
					fp.unpop();
					rv.push_back(Lexicon(LJS_getKWOrVar(st), st, fp.new_line));
					st = "";
					state = 0;
					break;
				case 7:
					fp.unpop();
					rv.push_back(Lexicon(find_single_lex_type(a, st), st, fp.new_line));
					st = "";
					state = 0;
					break;
				case 8:
					if(LJS_in(n, c))
					{
						state = 9;
					}else if(LJS_in(b, c))
					{
						state = 11;
					}else
					{
						st += c; state = 8;
					}
					break;
				case 9:
					if(c == 'n')
					{
						st += "\n";
					}else if(c == '\\')
					{
						st += "\\";
					}else if(c == '\'')
					{
						st += "'";
					}
					state = 10;
					break;
				case 10:
					fp.unpop();
					state = 8;
					break;
				case 11:
					fp.unpop();
					rv.push_back(Lexicon(STRING, st, fp.new_line));
					state = 0;
					st = "";
					break;
				case 12:
					if(LJS_in(n, c))
					{
						state = 13;
					}else if(LJS_in(cs, c))
					{
						state = 15;
					}else
					{
						st += c; state = 12;
					}
					break;
				case 13:
					if(c == 'n')
					{
						st += "\n";
					}else if(c == '\\')
					{
						st += "\\";
					}else if(c == '"')
					{
						st += "\"";
					}
					state = 14;
					break;
				case 14:
					fp.unpop();
					state = 12;
					break;
				case 15:
					fp.unpop();
					rv.push_back(Lexicon(STRING, st, fp.new_line));
					state = 0;
					break;
				case 16:
					if(LJS_in(f,c))
					{
						st += c;
						state = 17;
					}else
					{
						fp.unpop();
						rv.push_back(Lexicon(LT, st, fp.new_line));
						state = 0;
					}
					break;
				case 17:
					fp.unpop();
					rv.push_back(Lexicon(LEQ, st, fp.new_line));
					state = 0;
					break;
				case 18:
					if(LJS_in(f,c))
					{
						st += c;
						state = 19;
					}else
					{
						fp.unpop();
						rv.push_back(Lexicon(GT,st,fp.new_line));
						state = 0;
					}
					break;
				case 19:
					fp.unpop();
					rv.push_back(Lexicon(GEQ,st,fp.new_line));
					state = 0;
					break;
				case 20:
					if(LJS_in(f,c))
					{
						st += c;
						state = 21;
					}else
					{
						fp.unpop();
						rv.push_back(Lexicon(ASSIGN,st,fp.new_line));
						state = 0;
					}
					break;
				case 21:
					fp.unpop();
					rv.push_back(Lexicon(EQ,st,fp.new_line));
					state = 0;
					break;
				case 22:
					if(LJS_in(f,c))
					{
						st += c;
						state = 23;
					}else
					{
						fp.unpop();
						rv.push_back(Lexicon(NOT,st,fp.new_line));
						state = 0;
					}
					break;
				case 23:
					fp.unpop();
					rv.push_back(Lexicon(NE,st,fp.new_line));
					state = 0;
					break;
				case 24:
					if(LJS_in(h,c))
					{
						st += c;
						state = 25;
					}else
					{
						LJS_error("error in LA - | without 2nd |");
					}
					break;
				case 25:
					fp.unpop();
					rv.push_back(Lexicon(OR, st, fp.new_line));
					state = 0;
					break;
				case 26:
					if(LJS_in(i,c))
					{
						st += c;
						state = 27;
					}else
					{
						LJS_error("error in LA - & without 2nd &");
					}
					break;
				case 27:
					fp.unpop();
					rv.push_back(Lexicon(AND, st, fp.new_line));
					st= "";
					state = 0;
					break;
				case 28:
					fp.unpop();
					rv.push_back(Lexicon(DOT, st, fp.new_line));
					st = "";
					state = 0;
					break;
				case 29:
					if(LJS_in(p, c))
					{
						st = "";
						state = 30;
					}else if(LJS_in(s, c))
					{
						st = "";
						state = 31;
					}else if(LJS_in(f, c))
					{
						st += c;
						state = 40;
					}else
					{
						fp.unpop();
						rv.push_back(Lexicon(DIVIDE, st, fp.new_line));
						st = "";
						state = 0;
					}
					break;
				case 30:
					if(c == '\n')
					{
						st = "";
						state = 0;
					}else
					{
						state = 30;
					}
					break;
				case 31:
					if(LJS_in(s,c))
					{
						state = 32;
					}else
					{
						state = 31;
					}
					break;
				case 32:
					if(LJS_in(p, c))
					{
						st = "";
						state = 0;
					}else
					{
						state = 31;
					}
					break;
				case 33:
					if(LJS_in(f, c))
					{
						st += c; state = 41;
					}else
					{
						fp.unpop();
						rv.push_back(Lexicon(MULT, st, fp.new_line));
						st = "";
						state = 0;
					}
					break;
				case 34:
					if(LJS_in(f, c))
					{
						st += c; state = 35;
					}else if(LJS_in(w, c))
					{
						st += c; state = 42;
					}else
					{
						fp.unpop();
						rv.push_back(Lexicon(PLUS, st, fp.new_line));
						st = "";
						state = 0;
					}
					break;
				case 35:
					fp.unpop();
					rv.push_back(Lexicon(PLUSASSIGN, st, fp.new_line));
					st = "";
					state = 0;
					break;
				case 36:
					if(LJS_in(f, c))
					{
						st += c; state = 37;
					}else if(LJS_in(x, c))
					{
						st += c; state = 43;
					}else
					{
						fp.unpop();
						rv.push_back(Lexicon(MINUS, st, fp.new_line));
						st = "";
						state = 0;
					}
					break;
				case 37:
					fp.unpop();
					rv.push_back(Lexicon(MINUSASSIGN, st, fp.new_line));
					st = "";
					state = 0;
					break;
					break;
				case 38:
					if(LJS_in(f, c))
					{
						st += c; state = 39;
					}else
					{
						fp.unpop();
						rv.push_back(Lexicon(MODULO, st, fp.new_line));
						st = "";
						state = 0;
					}
					break;
				case 39:
					fp.unpop();
					rv.push_back(Lexicon(MODULOASSIGN, st, fp.new_line));
					st = "";
					state = 0;
					break;
				case 40:
					fp.unpop();
					rv.push_back(Lexicon(DIVIDEASSIGN, st, fp.new_line));
					st = "";
					state = 0;
					break;
				case 41:
					fp.unpop();
					rv.push_back(Lexicon(MULTASSIGN, st, fp.new_line));
					st = "";
					state = 0;
					break;
				case 42:
					fp.unpop();
					rv.push_back(Lexicon(INCREMENT, st, fp.new_line));
					st = "";
					state = 0;
					break;
				case 43:
					fp.unpop();
					rv.push_back(Lexicon(DECREMENT, st, fp.new_line));
					st = "";
					state = 0;
					break;
				}
			}
			return rv;
		}
	};

	class LJS_Lexicon_Parser
	{
	public:
		vector<Lexicon> l;
		int index;
		int length;
		LJS_Lexicon_Parser()
		{
			index = 0; length = 0;
		}
		LJS_Lexicon_Parser(vector<Lexicon> l)
		{
			this->l = l;
			this->l.push_back(Lexicon(SEMICOLON, ";", -1));
			index = 0;
			length = l.size();
		}
		void deepCopy(const LJS_Lexicon_Parser & inp)
		{
			l = inp.l;
			index = inp.index;
			length = inp.length;
		}
		LJS_Lexicon_Parser(const LJS_Lexicon_Parser & inp)
		{
			deepCopy(inp);
		}
		LJS_Lexicon_Parser&operator=(const LJS_Lexicon_Parser & inp){deepCopy(inp); return *this;}
		Lexicon pop()
		{
			if(eof())
			{
				index++;
				return Lexicon();
			}else
			{
				Lexicon rv = l[index];
				index++;
				return rv;
			}
		}
		void unpop()
		{
			index--;
			if(index < 0) index = 0;
		}
		Lexicon check()
		{
			Lexicon rv = pop();
			unpop();
			return rv;
		}
		bool eof()
		{
			if(index >= length)
			{
				return true;
			}
			return false;
		}
		string getRestString()
		{
			string rv = "";
			for(int i = index; i < length; i++)
			{
				rv += string("(") + l[i].fullStr() + ")";
			}
			return rv;
		}
	};

	class LJS_Naming
	{
	public:
		int index;
		string front;
		LJS_Naming()
		{
			index = 0;
		}
		LJS_Naming(string s)
		{
			front = s;
		}
		LJS_Naming(const LJS_Naming & inp)
		{
			dcopy(inp);
		}
		LJS_Naming&operator=(const LJS_Naming & inp)
		{
			dcopy(inp);return *this;
		}
		void dcopy(const LJS_Naming & inp)
		{
			index = inp.index;
			front = inp.front;
		}
		string newName()
		{
			string rv = front + LJS_int2String(index);
			index++;
			return rv;
		}
	};

	class LJS_Function
	{
	public:
		string name;
		string scope;
		vector<string> stmtList;
		LJS_Function(){}

		LJS_Function(string Name, string Scope, vector<string> StmtList)
		{
			name = Name;
			scope = Scope;
			stmtList = StmtList;
		}
		LJS_Function(string Name, string Scope)
		{
			name = Name;
			scope = Scope;
		}
		LJS_Function(const LJS_Function & i){ cloneIn(i);}
		LJS_Function&operator=(const LJS_Function & i){ cloneIn(i);return *this;}

		void cloneIn(const LJS_Function & inp)
		{
			name = inp.name;
			scope = inp.scope;
			stmtList = inp.stmtList;
		}

		bool same(LJS_Function otherF)
		{
			if(name == otherF.name && scope == otherF.scope)
			{
				return true;
			}
			return false;
		}

		string getFName()
		{
			return scope + string("_") + name;
		}
	
	};

	//types PT_ARRAY, PT_ARRAY_ELEMENT, PT_FUNCTION, PT_OBJECT, PT_OBJECT_ELEMENT, PT_FUNCTION_ELEMENT, PT_NULL
	class LJS_Ptr 
	{
	public:
		int type, index1, index2;
		LJS_Ptr()
		{
			type = PT_NULL;
			index1 = -1;
			index2 = -1;
		}
		LJS_Ptr(int t, int i1 = -1, int i2 = -1)
		{
			type = t;
			index1 = i1;
			index2 = i2;
		}
		LJS_Ptr(const LJS_Ptr & i)
		{
			cloneIn(i);
		}
		LJS_Ptr&operator=(const LJS_Ptr & i)
		{
			cloneIn(i);
			return *this;
		}
		void cloneIn(const LJS_Ptr & i)
		{
			index1 = i.index1;
			index2 = i.index2;
			type = i.type;
		}
		bool requires_one_index()
		{
			if(type == PT_ARRAY || type == PT_FUNCTION || type == PT_OBJECT || type == PT_NULL)
			{
				return true;
			}
			return false;
		}
		bool requires_two_indices()
		{
			return !requires_one_index();
		}
		bool bad()
		{
			return type == PT_NULL || (requires_one_index() && index1<0) || (requires_two_indices() && index1<0 && index2<0);
		}
		bool ok()
		{
			return !bad();
		}
		bool isArray()
		{
			return type == PT_ARRAY;
		}
		bool isArrayElement()
		{
			return type == PT_ARRAY_ELEMENT;
		}
		bool isFunction()
		{
			return type == PT_FUNCTION;
		}
		bool isObject()
		{
			return type == PT_OBJECT;
		}
		bool isObjectElement()
		{
			return type == PT_OBJECT_ELEMENT;
		}
		bool isFunctionElement()
		{
			return type == PT_FUNCTION_ELEMENT;
		}
		bool isNULL()
		{
			return type == PT_NULL;
		}

		string toStr()
		{
			if(isArray())
			{
				return "[pointer to array]";
			}else if(isArrayElement())
			{
				return "[reference to array element]";
			}else if(isFunction())
			{
				return "[pointer to a function]";
			}else if(isObject())
			{
				return "[pointer to an object]";
			}else if(isObjectElement())
			{
				return "[pointer to an object's element]";
			}else if(isFunctionElement())
			{
				return "[pointer to an object's function]";
			}else
			{
				return "[NULL Pointer]";
			}
		}

		bool operator==(const LJS_Ptr & p)
		{
			if(type == p.type)
			{
				if(requires_two_indices())
				{
					return index1 == p.index1 && index2 == p.index2;
				}else
				{
					return index1 == p.index1;
				}
			}
			return false;
		}

		};

	class LJSVar
	{//string, number, pointer, undefined
	public:
		LJS_Ptr pt;
		string st;
		double num;
		int type;
		LJSVar()
		{
			type = BT_UNDEFINED;
		}

		LJSVar(string s)
		{
			type = BT_STRING;
			st = s;
		}

		LJSVar(char * s)
		{
			type = BT_STRING;
			st = s;
		}

		LJSVar(double s)
		{
			type = BT_NUMBER;
			//cout << "called this!" << endl;
			num = s;
		}

		LJSVar(int s)
		{
			type = BT_NUMBER;
			num = (double)s;
		}

		LJSVar(bool b)
		{
			type = BT_NUMBER;
			num = (b)?1.0:0.0;
		}

		LJSVar(LJS_Ptr p)
		{
			type = BT_POINTER;
			pt = p;
		}

	

		LJSVar&operator=(string s)
		{
			type = BT_STRING;
			st = s;
			return *this;
		}

		LJSVar&operator=(char * s)
		{
			type = BT_STRING;
			st = s;
			return *this;
		}

		LJSVar&operator=(double s)
		{
			type = BT_NUMBER;
			num = s;
			return *this;
		}
		LJSVar&operator=(int s)
		{
			type = BT_NUMBER;
			num = (double)s;
			return *this;
		}

		LJSVar&operator=(bool b)
		{
			type = BT_NUMBER;
			num = (b)?1.0:0.0;
			return *this;
		}

		LJSVar&operator=(LJS_Ptr p)
		{
			type = BT_POINTER;
			pt = p;
			return *this;
		}

	

		LJSVar(const LJSVar & i)
		{
			copy_in(i);
		}

		LJSVar&operator=(const LJSVar & i)
		{
			copy_in(i);
			return *this;
		}

		void copy_in(const LJSVar & i)
		{
			pt = i.pt;
			st = i.st;
			num = i.num;
			type = i.type;
		}

		bool tobool()
		{
			if((type == BT_NUMBER && num == 0.0) || type == BT_UNDEFINED)
			{
				return false;
			}else
			{
				return true;
			}
		}

		LJSVar copy()
		{
			LJSVar cp(*this);
			return cp;
		}

		double getDouble()
		{
			if(type != BT_NUMBER)
			{
				LJS_error("attempting to retrieve double!");
			}
			return num;
		}

		string getString()
		{
			if(type == BT_STRING)
			{
				return st;
			}else if(type == BT_UNDEFINED)
			{
				return "undefined";
			}else if(type == BT_POINTER)
			{
				return pt.toStr();
			}else if(type == BT_NUMBER)
			{
				return LJS_double2String(num);
			}
			return st;
		}

		string getFullString()
		{
			return string("{") + getString() + string(" , ") + LJS_BT2String(type) + string(" }");
		}

		LJSVar convert(int newType)
		{
			//can convert: anything to string, string to num, null to num
			if(newType == BT_STRING)
			{
				return LJSVar(getString());
			}else if(newType == BT_NUMBER)
			{
				if(type == BT_STRING)
				{
					return LJSVar(LJS_string2Double(st));
				}else
				{
					LJS_error(string("error, trying to convert ") + getFullString() + string(" to string"));
				}
			}
			LJS_error(string("error, trying to convert ") + getFullString() + string(" to string"));
		}

		void erop(string op)
		{
			LJS_error(string("warning: trying to perform ") + op + string(" on ") + getFullString());
		}

		void erop(string op, LJSVar v2)
		{
			LJS_error(string("warning: trying to perform ") + op + string(" on ") + getFullString() + string(" and " ) + v2.getFullString());
		}

		LJSVar negate()
		{
			if(type == BT_NUMBER)
			{
				return LJSVar(num * -1.0);
			}
			erop("negate");
		}

		LJSVar not()
		{
			return !tobool();
		}

		LJSVar or(LJSVar v2)
		{
			return tobool() || v2.tobool();
		}

		LJSVar and(LJSVar v2)
		{
			return tobool() && v2.tobool();
		}

		LJSVar plus(LJSVar v2)
		{
			if(type == BT_STRING || v2.type == BT_STRING)
			{
				return getString() + v2.getString();
			}else if(type == BT_NUMBER)
			{
				if(v2.type == BT_NUMBER)
				{
					return num + v2.num;
				}else if(v2.type == BT_UNDEFINED)
				{
					return num;
				}
			}
			erop("+", v2);
		}

		LJSVar subtract(LJSVar v2)
		{
			if(type == BT_NUMBER)
			{
				if(v2.type == BT_NUMBER)
				{
					return num - v2.num;
				}else if(v2.type == BT_UNDEFINED)
				{
					return num;
				}
			}
			erop("-", v2);
		}

		LJSVar divide(LJSVar v2)
		{
			if(type == BT_NUMBER)
			{
				if(v2.type == BT_NUMBER)
				{
					if(v2.num == 0.0) LJS_error("division by zero! ");;
					return num / v2.num;
				}else if(v2.type == BT_UNDEFINED)
				{
					return num;
				}
			}
			erop("/", v2);
		}

		LJSVar multiply(LJSVar v2)
		{
			if(type == BT_NUMBER)
			{
				if(v2.type == BT_NUMBER)
				{
					return num * v2.num;
				}else if(v2.type == BT_UNDEFINED)
				{
					return num;
				}
			}
			erop("*", v2);
		}

		LJSVar mod(LJSVar v2)
		{
			if(type == BT_NUMBER)
			{
				if(v2.type == BT_NUMBER)
				{
					return fmod(num,v2.num);
				}else if(v2.type == BT_UNDEFINED)
				{
					LJS_error("moded by zero! ");
				}
			}
			erop("%", v2);
		}

		LJSVar eq(LJSVar v)
		{
			if(type != v.type) return false;
			if(type == BT_STRING)
			{
				return st == v.st;
			}
			if(type == BT_NUMBER)
			{
				return num == v.num;
			}
			if(type == BT_POINTER)
			{
				return pt == v.pt;
			}
			return true;
		}

		LJSVar neq(LJSVar v)
		{
			return eq(v).not();
		}

		LJSVar lt(LJSVar v)
		{
			if(type != v.type) erop("<", v);
			if(type == BT_STRING)
			{
				return st < v.st;
			}
			if(type == BT_NUMBER)
			{
				return num < v.num;
			}
			
			erop("<", v);
		}

		LJSVar gt(LJSVar v)
		{
			if(type != v.type) erop(">", v);
			if(type == BT_STRING)
			{
				return st > v.st;
			}
			if(type == BT_NUMBER)
			{
				return num > v.num;
			}
			
			erop(">", v);
		}

		LJSVar geq(LJSVar v)
		{
			if(type != v.type) erop(">=", v);
			if(type == BT_STRING)
			{
				return st >= v.st;
			}
			if(type == BT_NUMBER)
			{
				return num >= v.num;
			}
			
			erop(">=", v);
		}

		LJSVar leq(LJSVar v)
		{
			if(type != v.type) erop("<=", v);
			if(type == BT_STRING)
			{
				return st <= v.st;
			}
			if(type == BT_NUMBER)
			{
				return num <= v.num;
			}
			
			erop("<=", v);
		}

		LJSVar operator + (LJSVar v)
		{
			return plus(v);
		}

		LJSVar operator - (LJSVar v)
		{
			return subtract(v);
		}

		LJSVar operator * (LJSVar v)
		{
			return multiply(v);
		}

		LJSVar operator / (LJSVar v)
		{
			return divide(v);
		}

		
		LJSVar operator < (LJSVar v)
		{
			return lt(v);
		}

		LJSVar operator <= (LJSVar v)
		{
			return leq(v);
		}

		LJSVar operator >= (LJSVar v)
		{
			return geq(v);
		}

		LJSVar operator > (LJSVar v)
		{
			return gt(v);
		}

		LJSVar operator == (LJSVar v)
		{
			return eq(v);
		}
		LJSVar operator != (LJSVar v)
		{
			return neq(v);
		}

		LJSVar operator && (LJSVar v)
		{
			return and(v);
		}

		LJSVar operator || (LJSVar v)
		{
			return or(v);
		}

		LJSVar operator ! ()
		{
			return not();
		}

		LJSVar operator - ()
		{
			return negate();
		}

		bool isPointer()
		{
			return type == BT_POINTER;
		}

	};

	class LJS_Parser
	{
	public:
		string st;
		LJS_Lexicon_Parser fp;
		LJS_Naming tmp_name, tmp_label, literal_name, reference_name;
		stack<vector<string>> stmt_stack;
		stack<string> breakLabel;
		stack<string> continueLabel;
		vector<LJS_Function> functionList;
		stack<string> scope_stack;
		map<string, LJSVar> literalList;

		vector<string> assembly_code;

		LJS_Parser()
		{
			tmp_name.front = "T't_";
			tmp_label.front = "Label't_";
			literal_name.front = "L't_";
			reference_name.front = "R't_";

		}

		void dumpAssembly()
		{
			for(vector<string>::iterator i = assembly_code.begin(); i != assembly_code.end(); i++)
			{
				cout << *i << endl;
			}
		}

		void match(Lexicon l, int type, string err_msg = "compiler error ")
		{
			if(l.type != type)
			{
				LJS_error(err_msg + string(" at line: ") + LJS_int2String( l.line_number ) );
			}
		}

		void match(int type, string err_msg = "compiler error ")
		{
			Lexicon l = fp.pop();
			if(l.type != type)
			{
				LJS_error(err_msg + string(" at line: ") + LJS_int2String( l.line_number ) );
			}
		}

		void add_stmt_stack()
		{
			vector<string> tmp;
			stmt_stack.push(tmp);
		}

		vector<string> pop_stmt_stack()
		{
			vector<string> rv = stmt_stack.top();
			stmt_stack.pop();
			return rv;
		}

		string get_scope()
		{
			if(scope_stack.empty())
			{
				return "";
			}
			return scope_stack.top();
		}

		bool hasFunction(string name, string scope)
		{
			LJS_Function tmp;
			tmp.name = name;
			tmp.scope = scope;
			for(int i = 0; i < functionList.size(); i++)
			{
				if(tmp.same(functionList[i]))
				{
					return true;
				}
			}
			return false;
		}

		void write_out(string s)
		{
			if(stmt_stack.size() <= 0)
			{
				//cout << s << endl;
				assembly_code.push_back(s);
			}else
			{
				stmt_stack.top().push_back(s);
			}
		}

		void write_out(vector<string> ss)
		{
			for(int i = 0; i < ss.size(); i++)
			{
				write_out(ss[i]);
			}
		}

		void spill_functions()
		{
			for(int i = 0; i < functionList.size(); i++)
			{
				write_out(functionList[i].stmtList);
			}
		}

		string add_literal(Lexicon l)
		{
			LJSVar newVar;
			if(l.type == NUMBER)
			{
				double d = LJS_string2Double(l.str);
				newVar = d;
			}else if(l.type == TRUE)
			{
				newVar = true;
			}else if(l.type == FALSE)
			{
				newVar = false;
			}else if(l.type == STRING)
			{
				newVar = l.str;
			}
			string nname = literal_name.newName();
			literalList[nname] = newVar;
			return nname;
		}

		void compile(vector<Lexicon> lexes)
		{
			fp = LJS_Lexicon_Parser(lexes);
			tmpBegin();
		}

		void tmpBegin()
		{
			//string rv = multistmt_any();
			//string rv = LJS_int2String( params() );
			//write_out(rv);
			loopstmts();
			write_out("exit");
			spill_functions();
		}

		void loopstmts()
		{
			while(stmts()){}
		}

		bool stmts()
		{
			Lexicon l = fp.check();
			if(l.type == SEMICOLON)
			{
				match(SEMICOLON);
				return true;
			}else if(l.type == OTHER || l.type == CLOSEBRACE || l.type == CASE || l.type == DEFAULT || fp.eof())
			{
				//cout << "reached end" << endl;
				return false;
			}else if(l.type == IF)
			{
				match(IF);
				match(OPENBRACK);
				string test = multistmt();
				match(CLOSEBRACK);
				string after = tmp_label.newName();
				write_out(string("ifngoto ") + test + string(" ") + after);
				match(OPENBRACE);
				loopstmts();
				match(CLOSEBRACE);
				else_(after);
				return true;
			}else if(l.type == SWITCH)
			{
				match(SWITCH);
				match(OPENBRACK);
				string a = variable_only();
				match(CLOSEBRACK);
				match(OPENBRACE);
				string after = tmp_label.newName();
				breakLabel.push(after);
				continueLabel.push("");
				string check = tmp_label.newName();
				write_out(string("goto ") + check);
				vector<string> case_list;
				vector<vector<string>> case_bods;
				switch_case(case_list, case_bods);
				if(case_list.size() != case_bods.size())
				{
					LJS_error("error processing switch statement on line : " + LJS_int2String(l.line_number));
				}
				match(CLOSEBRACE, "error on close brace from switch statement on line  " + LJS_int2String(l.line_number));
				breakLabel.pop();
				continueLabel.pop();
				vector<string> caseLabels;
				for(int i = 0; i < case_list.size(); i++)
				{
					caseLabels.push_back(tmp_label.newName());
				}
				for(int i = 0; i < case_list.size(); i++)
				{
					write_out(string("label: ") + caseLabels[i]);
					for(int j = 0; j < case_bods[i].size(); j++)
					{
						write_out(case_bods[i][j]);
					}
				}
				write_out(string("goto ") + after);
				write_out(string("label: ") + check);
				for(int i = 0; i < case_list.size(); i++)
				{
					string t_0 = tmp_name.newName();
					write_out(string("equals ") + t_0 + string(" ") + a + string(" ") + case_list[i]);
					write_out(string("ifgoto ") + t_0 + string(" ") + caseLabels[i]);
					//write_out(string("goto ") + after);
				}
				write_out(string("label: ") + after);
				return true;

			}else if(l.type == CONTINUE)
			{
				if(continueLabel.size() <= 0)
				{
					LJS_error("error, continue used incorrectly on line : " + LJS_int2String(l.line_number));
				}
				match(CONTINUE);
				match(SEMICOLON);
				if(continueLabel.top().size() == 0)
				{
					LJS_error("error, continue used incorrectly on line : " + LJS_int2String(l.line_number));
				}
				write_out(string("goto ") + continueLabel.top());
				return true;
			}else if(l.type == BREAK)
			{
				if(breakLabel.size() <= 0)
				{
					LJS_error("error, break used incorrectly on line : " + LJS_int2String(l.line_number));
				}
				match(BREAK);
				match(SEMICOLON);
				write_out(string("goto ") + breakLabel.top());
				return true;
			}else if(l.type == RETURN)
			{
				match(RETURN);
				string rv;
				if(fp.check().type != SEMICOLON)
				{
					rv = multistmt();
				}
				match(SEMICOLON);
				write_out(string("return ") + rv);
				return true;
			}else if(l.type == FOR)
			{
				match(FOR);
				match(OPENBRACK);
				vector<string> A, B, C, D;
				string a, b;

				if(fp.check().type != SEMICOLON)
				{
					add_stmt_stack();
					a = multistmt();
					A = pop_stmt_stack();
				}
				match(SEMICOLON);
				if(fp.check().type != SEMICOLON)
				{
					add_stmt_stack();
					b = multistmt();
					B = pop_stmt_stack();	
				}
				match(SEMICOLON);
				if(fp.check().type != SEMICOLON)
				{
					add_stmt_stack();
					multistmt();
					C = pop_stmt_stack();	
				}
				match(CLOSEBRACK);
				
				string start = tmp_label.newName();
				string after = tmp_label.newName();
				string cont = tmp_label.newName();
				continueLabel.push(cont);
				breakLabel.push(after);

				for(int i = 0; i < A.size(); i++)
				{
					write_out(A[i]);
				}
				write_out(string("label: ") + start);
				for(int i = 0; i < B.size(); i++)
				{
					write_out(B[i]);
				}
				write_out(string("ifngoto ") + b + string(" ") + after);
				match(OPENBRACE);
				loopstmts();
				match(CLOSEBRACE);
				write_out(string("label: ") + cont);
				for(int i = 0; i < C.size(); i++)
				{
					write_out(C[i]);
				}
				write_out(string("goto ") + start);
				write_out(string("label: ") + after);
				continueLabel.pop();
				breakLabel.pop();
				return true;
			}else if(l.type == DO)
			{
				string start = tmp_label.newName();
				string after = tmp_label.newName();
				write_out(string("label: ") + start);
				continueLabel.push(start);
				breakLabel.push(after);
				match(DO);
				match(OPENBRACE);
				loopstmts();
				match(CLOSEBRACE);
				match(WHILE);
				match(OPENBRACK);
				string a = multistmt();
				match(CLOSEBRACK);
				match(SEMICOLON);
				write_out(string("ifgoto ") + a + string(" ") +  start);
				write_out(string("label: ") + after);
				continueLabel.pop();
				breakLabel.pop();
				
				return true;
			}else if(l.type == WHILE)
			{
				string start = tmp_label.newName();
				string after = tmp_label.newName();
				continueLabel.push(start);
				breakLabel.push(after);
				write_out(string("label: ") + start);
				
				match(WHILE);
				match(OPENBRACK);
				string a = multistmt();
				match(CLOSEBRACK);

				write_out(string("ifngoto ") + a + string(" ") + after);
				match(OPENBRACE);
				loopstmts();
				match(CLOSEBRACE);

				write_out(string("goto ") + start);
				write_out(string("label: ") + after);

				continueLabel.pop();
				breakLabel.pop();
				return true;
			}else if(l.type == FUNCTION)
			{
				match(FUNCTION);
				vector<string> stmtList, frontStuff, backStuff;
				string name = variable_only();
				string scope = get_scope();
				LJS_Function tmpF(name, scope);
				frontStuff.push_back(string("Function: ") + tmpF.getFName() + string(" ") + name + string(" ") + scope);
				if(hasFunction(name, scope))
				{
					LJS_error("error on line: " +LJS_int2String( fp.check().line_number) + string(" function ") + name + string(" already defined"));
				}
				match(OPENBRACK);
				vector<string> args = arguments();
				match(CLOSEBRACK);
				match(OPENBRACE);
				for(int i = 0; i < args.size(); i++)
				{
					frontStuff.push_back(string("arg ") + args[i]);
				}
				scope_stack.push(LJS_Function(name, scope).getFName());
				add_stmt_stack();
				loopstmts();
				match(CLOSEBRACE);
				stmtList = pop_stmt_stack();
				backStuff.push_back(string("return"));
				scope_stack.pop();
				combineStmtList(frontStuff, stmtList);
				combineStmtList(frontStuff, backStuff);
				LJS_Function newFunction(name, scope, frontStuff);
				functionList.push_back(newFunction);
				return true;
			}else
			{
				string rv = multistmt_any();
				match(SEMICOLON);
				return true;
			}
		}

		void combineStmtList(vector<string>& l1, vector<string>& l2)
		{
			for(int i = 0; i < l2.size(); i++)
			{
				l1.push_back(l2[i]);
			}
		}

		void else_(string after, bool came_from_else = false, string af2 = "")
		{
			Lexicon l = fp.pop();
			Lexicon l2 = fp.check();
			fp.unpop();
			if(l.type == ELSE && l2.type == OPENBRACE && !came_from_else)
			{
				match(ELSE);
				match(OPENBRACE);
				string after2 = tmp_label.newName();
				write_out(string("goto ") + after2);
				write_out(string("label: ") + after);
				loopstmts();
				match(CLOSEBRACE);
				write_out(string("label: ") + after2);
			}else if(l.type == ELSE && l2.type == OPENBRACE)
			{
				match(ELSE);
				match(OPENBRACE);
				write_out(string("goto ") + af2);
				write_out(string("label: ") + after);
				loopstmts();
				match(CLOSEBRACE);
				write_out(string("label: ") + af2);
			}else if(l.type == ELSE && l2.type == IF)
			{
				match(ELSE);
				match(IF);
				match(OPENBRACK);
				string after2 = af2;
				if(!came_from_else) after2 = tmp_label.newName();
				string after3 = tmp_label.newName();
				write_out(string("goto ") + after2);
				write_out(string("label: ") + after);
				string test = multistmt();
				match(CLOSEBRACK);
				write_out(string("ifngoto ") + test + string(" ") + after3);
				match(OPENBRACE);
				loopstmts();
				match(CLOSEBRACE);
				else_(after3, true, after2);
				
			}else if(l.type != ELSE)
			{
				write_out(string("label: ") + after);
				if(came_from_else)
				{
					write_out(string("label: ") + af2);
				}
			}else
			{
				LJS_error("error with if-else statement on line: " + fp.check().line_number);
			}
		}

		void switch_case(vector<string> & caseList, vector<vector<string>> & caseBodies)
		{
			match(CASE);
			string lh = multistmt();
			caseList.push_back(lh);
			match(COLON);
			add_stmt_stack();
			loopstmts();
			vector<string> stlist = pop_stmt_stack();
			caseBodies.push_back(stlist);
			if(fp.check().type == CASE)
			{
				switch_case(caseList, caseBodies);
			}else if(fp.check().type == DEFAULT)
			{
				caseList.push_back(string("true"));
				match(DEFAULT);
				match(COLON);
				add_stmt_stack();
				loopstmts();
				vector<string> stlist = pop_stmt_stack();
				caseBodies.push_back(stlist);
			}
		}

		string multistmt_any()
		{
			if(fp.check().type == VAR)
			{
				return multistmt_var();
			}
			return multistmt();
		}

		//multistmt_var always begins with var and takes form: var a = b = c, i = 0, twentytwo = 22*50*(1/50)
		string multistmt_var()
		{
			match(VAR);
			string p1 = sassign(true);
			string p2 = moremultistmt_var(p1);
			return p2;
		}

		string moremultistmt_var(string p1)
		{
			if(fp.check().type == COMMA)
			{
				fp.pop();
				string p2 = sassign(true);
				return moremultistmt_var(p2);
			}else
			{
				return p1;
			}
		}

		//multistmt is for general stmts of form: a = b = c = 29.2*d, n = t[0], 2000, v() 
		//it has no var statement
		string multistmt()
		{
			string p1 = bassign();
			string p2 = moremultistmt(p1);
			return p2;
		}

		string moremultistmt(string p1)
		{
			if(fp.check().type == COMMA)
			{
				fp.pop();
				string p2 = bassign();
				return moremultistmt(p2);
			}else
			{
				return p1;
			}
		}

	

	

		

		string bassign(bool var = false)
		{
			stack<string> stck;
			string p1 = logics();
			string rv = morebassign(var, p1, stck);
			while(!stck.empty())
			{
				write_out(stck.top());
				stck.pop();
			}
			return p1;
		}

		string morebassign(bool var, string p1, stack<string> & stck)
		{

			Lexicon l = fp.pop();
			if(l.type == ASSIGN)
			{
				string op = (var)? "define " : "assign ";
				string p2 = logics();
				if(LJS_typeOfVar(p1) != VARIABLE && LJS_typeOfVar(p1) != REFERENCE)
				{
					LJS_error("error on line: " + LJS_int2String(l.line_number) + string(" illegal left hand assignment."));
				}
				string rv = op + p1 + string(" ") + p2;
				stck.push(rv);
				return morebassign(var, p2, stck);
			}else if(l.type == PLUSASSIGN)
			{
				string op = (var)? "define " : "assign ";
				string p2 = logics();
				if(LJS_typeOfVar(p1) != VARIABLE && LJS_typeOfVar(p1) != REFERENCE)
				{
					LJS_error("error on line: " + LJS_int2String(l.line_number) + string(" illegal left hand assignment."));
				}
				string nname = tmp_name.newName();
				string rv1 = string("plus ") + nname + string(" ") + p1 + string(" ") + p2;
				string rv = op + p1 + string(" ") + nname;
				stck.push(rv);
				stck.push(rv1);
				return morebassign(var, p2, stck);
			}else if(l.type == MINUSASSIGN)
			{
				string op = (var)? "define " : "assign ";
				string p2 = logics();
				if(LJS_typeOfVar(p1) != VARIABLE && LJS_typeOfVar(p1) != REFERENCE)
				{
					LJS_error("error on line: " + LJS_int2String(l.line_number) + string(" illegal left hand assignment."));
				}
				string nname = tmp_name.newName();
				string rv1 = string("subtract ") + nname + string(" ") + p1 + string(" ") + p2;
				string rv = op + p1 + string(" ") + nname;
				stck.push(rv);
				stck.push(rv1);
				return morebassign(var, p2, stck);
			}else if(l.type == DIVIDEASSIGN)
			{
				string op = (var)? "define " : "assign ";
				string p2 = logics();
				if(LJS_typeOfVar(p1) != VARIABLE && LJS_typeOfVar(p1) != REFERENCE)
				{
					LJS_error("error on line: " + LJS_int2String(l.line_number) + string(" illegal left hand assignment."));
				}
				string nname = tmp_name.newName();
				string rv1 = string("divide ") + nname + string(" ") + p1 + string(" ") + p2;
				string rv = op + p1 + string(" ") + nname;
				stck.push(rv);
				stck.push(rv1);
				return morebassign(var, p2, stck);
			}else if(l.type == MULTASSIGN)
			{
				string op = (var)? "define " : "assign ";
				string p2 = logics();
				if(LJS_typeOfVar(p1) != VARIABLE && LJS_typeOfVar(p1) != REFERENCE)
				{
					LJS_error("error on line: " + LJS_int2String(l.line_number) + string(" illegal left hand assignment."));
				}
				string nname = tmp_name.newName();
				string rv1 = string("mult ") + nname + string(" ") + p1 + string(" ") + p2;
				string rv = op + p1 + string(" ") + nname;
				stck.push(rv);
				stck.push(rv1);
				return morebassign(var, p2, stck);
			}else if(l.type == MODULOASSIGN)
			{
				string op = (var)? "define " : "assign ";
				string p2 = logics();
				if(LJS_typeOfVar(p1) != VARIABLE && LJS_typeOfVar(p1) != REFERENCE)
				{
					LJS_error("error on line: " + LJS_int2String(l.line_number) + string(" illegal left hand assignment."));
				}
				string nname = tmp_name.newName();
				string rv1 = string("mod ") + nname + string(" ") + p1 + string(" ") + p2;
				string rv = op + p1 + string(" ") + nname;
				stck.push(rv);
				stck.push(rv1);
				return morebassign(var, p2, stck);
			}else
			{
				fp.unpop();
				return p1;
			}
		}

		//simple assign, for var a = 5, c = 10 type expressions
		string sassign(bool var = false)
		{
			Lexicon l = fp.pop();
			Lexicon l2 = fp.check();
			fp.unpop();
			string op = (var)? "define " : "assign ";
			if(l.type == NAME && l2.type == ASSIGN)
			{
				string p1 = variable();
				fp.pop();
				string p2 = moresassign(var);
				write_out(string(op + p1 + string(" ") + p2));
				return p1;
			}else if(l.type == NAME && (l2.type == COMMA || l2.type == SEMICOLON))
			{
				string p1 = variable();
				write_out(string(op + p1 + string(" null")));
				return p1;
			}else
			{
				LJS_error("error parsing: assignment incorrect operator on line " + fp.check().line_number);
				return "";
			}
		}

		string moresassign(bool var = false)
		{
			Lexicon l = fp.pop();
			Lexicon l2 = fp.check();
			fp.unpop();
			string op = (var)? "define " : "assign ";
			if(l.type == NAME && l2.type == ASSIGN)
			{
				string p1 = variable();
				fp.pop();
				string p2 = moresassign(var);
				write_out(string(op + p1 + string(" ") + p2));
				return p1;
			}else
			{
				return logics();
			}
		}

		string logics()
		{
			string p1 = relations();
			return morelogics(p1);
		}

		string morelogics(string p1)
		{
			Lexicon l = fp.pop();
			if(l.type == AND)
			{
				string nname = tmp_name.newName();
				string p2 = relations();
				string rv = string("and ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morelogics(nname);
			}else if(l.type == OR)
			{
				string nname = tmp_name.newName();
				string p2 = relations();
				string rv = string("or ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morelogics(nname);
			}else
			{
				fp.unpop();
				return p1;
			}

		}

		string relations()
		{
			string p1 = terms();
			return morerelations(p1);
		}

		string morerelations(string p1)
		{
			Lexicon l = fp.pop();
			if(l.type == LT)
			{
				string nname = tmp_name.newName();
				string p2 = terms();
				string rv = string("lessThan ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morerelations(nname);
			}else if(l.type == GT)
			{
				string nname = tmp_name.newName();
				string p2 = terms();
				string rv = string("greaterThan ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morerelations(nname);
			}else if(l.type == EQ)
			{
				string nname = tmp_name.newName();
				string p2 = terms();
				string rv = string("equals ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morerelations(nname);
			}else if(l.type == LEQ)
			{
				string nname = tmp_name.newName();
				string p2 = terms();
				string rv = string("lessThanEq ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morerelations(nname);
			}else if(l.type == GEQ)
			{
				string nname = tmp_name.newName();
				string p2 = terms();
				string rv = string("greaterThanEq ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morerelations(nname);
			}else if(l.type == NE)
			{
				string nname = tmp_name.newName();
				string p2 = terms();
				string rv = string("notequals ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morerelations(nname);
			}else
			{
				fp.unpop();
				return p1;
			}

		}

		string terms()
		{
			string p1 = factors();
			return moreterms(p1);
		}

		string moreterms(string p1)
		{
			Lexicon l = fp.pop();
			if(l.type == PLUS)
			{
				string nname = tmp_name.newName();
				string p2 = factors();
				string rv = string("plus ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return moreterms(nname);
			}else if(l.type == MINUS)
			{
				string nname = tmp_name.newName();
				string p2 = factors();
				string rv = string("subtract ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return moreterms(nname);
			}else
			{
				fp.unpop();
				return p1;
			}

		}

		string factors()
		{
			string p1 = unary();
			return morefactors(p1);
		}

		string morefactors(string p1)
		{
			Lexicon l = fp.pop();
			if(l.type == MULT)
			{
				string nname = tmp_name.newName();
				string p2 = unary();
				string rv = string("mult ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morefactors(nname);
			}else if(l.type == DIVIDE)
			{
				string nname = tmp_name.newName();
				string p2 = unary();
				string rv = string("divide ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morefactors(nname);
			}else if(l.type == MODULO)
			{
				string nname = tmp_name.newName();
				string p2 = unary();
				string rv = string("mod ") + nname + string(" ") + p1 + string(" ") + p2;
				write_out(rv);
				return morefactors(nname);
			}else
			{
				fp.unpop();
				return p1;
			}

		}

		string unary()
		{
			Lexicon l = fp.pop();
			if(l.type == NOT)
			{
				string tmps = unary();
				string nname = tmp_name.newName();
				write_out(string("not ") + nname + string(" ") + tmps);
				return nname;
			}else if(l.type == MINUS)
			{
				string tmps = unary();
				string nname = tmp_name.newName();
				write_out(string("negate ") + nname + string(" ") + tmps);
				return nname;
			}else
			{
				fp.unpop();
				return LL();
			}
		}

		string LL()
		{
			Lexicon l = fp.check();
			if(l.type == NAME)
			{
				string v = variable_only();
				string rv = below(v);
				return rv;
			}else if(l.type == NUMBER)
			{
				fp.pop();
				return add_literal(l);
			}else if(l.type == STRING)
			{
				fp.pop();
				string v = add_literal(l);
				string rv = below(v);
				return rv;
			}else if(l.type == TRUE)
			{
				fp.pop();
				return add_literal(l);
			}else if(l.type == FALSE)
			{
				fp.pop();
				return add_literal(l);
			}else if(l.type == OPENBRACK)
			{
				match(OPENBRACK);
				string rv = multistmt();
				match(CLOSEBRACK);
				if(fp.check().type == QMARK)
				{
					match(QMARK);
					string nname = tmp_name.newName();
					string L1 = tmp_label.newName();
					string L2 = tmp_label.newName();
					string a = rv;
					string b = multistmt();
					match(COLON);
					string c = multistmt();
					write_out(string("ifngoto ") + a + string(" ") + L1);
					write_out(string("define ") + nname + string(" ") + b);
					write_out(string("goto ") + L2);
					write_out(string("label: ") + L1);
					write_out(string("define ") + nname + string(" ") + c);
					write_out(string("label: ") + L2);
					return nname;
				}else
				{
					return below(rv);
				}
			}else if(l.type == OPENSQR)
			{
				match(OPENSQR);
				vector<string> items;
				if(fp.check().type != CLOSESQR)
				{
					items = listItems();
				}
				match(CLOSESQR);
				string nname = tmp_name.newName();
				write_out(string("createArray ") + nname);
				for(int i = 0; i < items.size(); i++)
				{
					write_out(string("push ") + nname + string(" ") + items[i]);
				}
				return below(nname);
			}else if(l.type == NEW)
			{
				match(NEW);
				string callM = variable();
				string obtmp = tmp_name.newName();
				if(fp.check().type == OPENBRACK)
				{
					match(OPENBRACK);
					int param_count = 0;
					if(fp.check().type != CLOSEBRACK)
					{
						param_count = params();
					}
					match(CLOSEBRACK);
					write_out(string("objectCall ") + obtmp + string(" ") + callM + string(" ") + LJS_int2String(param_count));
					return below(obtmp);
				}else
				{
					write_out(string("objectCall ") + obtmp + string(" ") + callM + string(" 0"));
					return below(obtmp);
				}
			}else if(l.type == OPENBRACE)
			{
				match(OPENBRACE);
				string nname = tmp_name.newName();
				write_out(string("createObject ") + nname);
				if(fp.check().type != CLOSEBRACE)
				{
					multiObjectSetElement(nname);
				}
				match(CLOSEBRACE);
				return below(nname);
			}else if(l.type == INCREMENT)
			{
				match(INCREMENT);
				string v = variable_only();
				write_out(string("plus ") + v + string(" ") + v + string(" ") + add_literal(Lexicon(NUMBER, "1", l.line_number)));
				return v;
			}else if(l.type == DECREMENT)
			{
				match(DECREMENT);
				string v = variable_only();
				write_out(string("subtract ") + v + string(" ") + v + string(" ") + add_literal(Lexicon(NUMBER, "1", l.line_number)));
				return v;
			}else if(l.type == FUNCTION)
			{
				return LL_function();
			}
		}

		string LL_function()
		{
			match(FUNCTION);
			vector<string> stmtList, frontStuff, backStuff;
			string name = literal_name.newName();
			if(fp.check().type == NAME){ variable_only();}
			string scope = get_scope();
			LJS_Function tmpF(name, scope);
			frontStuff.push_back(string("Function: ") + tmpF.getFName() + string(" ") + name + string(" ") + scope);
			if(hasFunction(name, scope))
			{
				LJS_error("error on line: " +LJS_int2String( fp.check().line_number) + string(" function ") + name + string(" already defined"));
			}
			match(OPENBRACK);
			vector<string> args = arguments();
			match(CLOSEBRACK);
			match(OPENBRACE);
			for(int i = 0; i < args.size(); i++)
			{
				frontStuff.push_back(string("arg ") + args[i]);
			}
			scope_stack.push(LJS_Function(name, scope).getFName());
			add_stmt_stack();
			loopstmts();
			match(CLOSEBRACE);
			stmtList = pop_stmt_stack();
			backStuff.push_back(string("return"));
			scope_stack.pop();
			combineStmtList(frontStuff, stmtList);
			combineStmtList(frontStuff, backStuff);
			LJS_Function newFunction(name, scope, frontStuff);
			functionList.push_back(newFunction);
			return name;
		}

		string variable()
		{
			Lexicon l = fp.check();
			match(NAME);

			string v = string("V'") + l.str;
			return below_basic(v);
		}

		string variable_only()
		{
			Lexicon l = fp.check();
			match(NAME);
			return string("V'") + l.str;
		}

		string below(string p1)
		{
			Lexicon l = fp.check();
			if(l.type == OPENSQR)
			{
				match(OPENSQR);
				string index = multistmt();
				match(CLOSESQR);
				string nname = reference_name.newName();
				write_out(string("indexby ") + nname + string(" ") + p1 + string(" ") + index);
				return below(nname);
			}else if(l.type == DOT)
			{
				match(DOT);
				string el = variable_only();
				string nname = reference_name.newName();
				write_out(string("getelement ") + nname + string(" ") + p1 + string(" ") + el);
				return below(nname);
			}else if(l.type == OPENBRACK)
			{
				match(OPENBRACK);
				int param_count = 0;
				if(fp.check().type != CLOSEBRACK)
				{
					param_count = params();
				}
				match(CLOSEBRACK);
				string rv_tmp = tmp_name.newName();
				write_out(string("call ") + p1 + string(" ") + LJS_int2String(param_count));
				write_out(string("getReturnVal ") + rv_tmp);
				return below(rv_tmp);
			}else if(l.type == INCREMENT)
			{
				match(INCREMENT);
				string t_0 = tmp_name.newName();
				write_out(string("define ") + t_0 + string(" ") + p1);
				write_out(string("plus ") + p1 + string(" ") + p1 + string(" ") + add_literal(Lexicon(NUMBER, "1", l.line_number)));
				return t_0;
			}else if(l.type == DECREMENT)
			{
				match(INCREMENT);
				string t_0 = tmp_name.newName();
				write_out(string("define ") + t_0 + string(" ") + p1);
				write_out(string("subtract ") + p1 + string(" ") + p1 + string(" ") + add_literal(Lexicon(NUMBER, "1", l.line_number)));
				return t_0;
			}else
			{
				return p1;
			}

		}

		string below_basic(string p1)
		{
			Lexicon l = fp.check();
			if(l.type == OPENSQR)
			{
				match(OPENSQR);
				string index = multistmt();
				match(CLOSESQR);
				string nname = reference_name.newName();
				write_out(string("indexby ") + nname + string(" ") + p1 + string(" ") + index);
				return below(nname);
			}else if(l.type == DOT)
			{
				match(DOT);
				string el = variable_only();
				string nname = reference_name.newName();
				write_out(string("getelement ") + nname + string(" ") + p1 + string(" ") + el);
				return below(nname);
			}else
			{
				return p1;
			}

		}

		
		int params()
		{
			vector<string> pars;
			string p1 = bassign();
			pars.push_back(p1);
			moreparams(pars);
			for(int i = pars.size()-1; i >= 0; i--)
			{
				write_out(string("param ") + pars[i]);
			}
			return pars.size();
		}

		void moreparams(vector<string>& pars)
		{
			if(fp.check().type == COMMA)
			{
				fp.pop();
				string p2 = bassign();
				pars.push_back(p2);
				moreparams(pars);
			}else
			{
				return;
			}
		}

		vector<string> arguments()
		{
			vector<string> args;
			if(fp.check().type == CLOSEBRACK)
			{
				return args;
			}
			string p1 = variable_only();
			args.push_back(p1);
			morearguments(args);
			return args;
		}

		void morearguments(vector<string>& args)
		{
			if(fp.check().type == COMMA)
			{
				fp.pop();
				string p2 = variable_only();
				args.push_back(p2);
				morearguments(args);
			}else
			{
				return;
			}
		}

		vector<string> listItems()
		{
			vector<string> pars;
			string p1 = bassign();
			pars.push_back(p1);
			moreparams(pars);
			return pars;
		}



		string just_string()
		{
			Lexicon l = fp.check();
			match(STRING);
			string v = add_literal(l);
			return v;
		}

		void objectSetElement(string obname)
		{
			Lexicon l = fp.check();
			string element;
			if(l.type == NAME)
			{
				element = variable_only();
			}else
			{
				element = just_string();
			}
				match(COLON);
				string res = bassign();
				string nname = reference_name.newName();
				write_out(string("getelement ") + nname + string(" ") + obname + string(" ") + element);
				write_out(string("assign ") + nname + string(" ") + res);
		}

		void multiObjectSetElement(string obname)
		{
			objectSetElement(obname);
			moremultiObjectSetElement(obname);
		}

		void moremultiObjectSetElement(string obname)
		{
			if(fp.check().type == COMMA)
			{
				match(COMMA);
				objectSetElement(obname);
				moremultiObjectSetElement(obname);
				return;
			}
		}

	};

	

	class LJS_RunTimeStackElement
	{
	public:
		int programCounter;
		map<string, LJSVar> elements; //stack elements
		string myScope, prevScope;
		int id;
		LJSVar returnVal;
		stack<LJSVar> params;
		LJSVar thisDataObject;
		

		LJS_RunTimeStackElement(int programC, int id, string scopeName, string prevScopeName, LJSVar tdo)
		{
			programCounter = programC;
			myScope = scopeName;
			prevScope = prevScopeName;
			this->id = id;
			thisDataObject = tdo;
		}

		void incPC()
		{
			programCounter++;
		}

		void decPC()
		{
			programCounter--;
		}

		void setPC(int newPC)
		{
			programCounter = newPC;
		}

		bool getVar(string name, LJSVar * & pt)
		{
			if(elements.count(name) == 0)
			{
				return false;
			}else
			{
				pt =  &elements[name];
				return true;
			}
		}

		LJSVar * forceGetVar(string name)
		{
			if(elements.count(name) == 0)
			{
				elements[name] = LJSVar();
			}
			return &elements[name];
			
		}

		void addVar(string name)
		{
			elements[name] = LJSVar();
		}

		void dumpInfo()
		{
			cout << "program counter @ " << programCounter << endl;
			cout << "************stack************" << endl;
			for(map<string, LJSVar>::iterator i = elements.begin(); i!=elements.end(); i++)
			{
				if(LJS_typeOfVar(i->first) == TEMPORARY) continue;
				cout << i->first << " => " << i->second.getString() << endl;
			}
			cout << "************End************" << endl;
		}

		void addParam(LJSVar v)
		{
			params.push(v);
		}

		LJSVar popParam()
		{
			LJSVar rv = params.top();
			params.pop();
			return rv;
		}

		LJSVar getReturnVar()
		{
			return returnVal;
		}

		void setReturnVar(LJSVar i)
		{
			returnVal = i;
		}
	};

	class FunctionInfo
	{
	public:
		string fname, name;
		int loc;
		FunctionInfo()
		{
			loc = 0;
		}

		FunctionInfo(string fn, string n, int l)
		{
			fname = fn;
			name = n;
			loc = l;
		}

		FunctionInfo(const FunctionInfo&i)
		{
			cloneIn(i);
		}

		FunctionInfo&operator=(const FunctionInfo&i)
		{
			cloneIn(i);
			return *this;
		}

		void cloneIn(const FunctionInfo & i)
		{
			fname = i.fname;
			name = i.name;
			loc = i.loc;
		}
	};


	

	class LJS_RunTime
	{
	public:
		vector<string> program;
		map<string, LJSVar> literals;
		deque<LJS_RunTimeStackElement> stck;
		map<string, int> labelLocations;
		vector<FunctionInfo> functionData;
		vector<vector<LJSVar>> arrays;
		vector<LIndexMap<LJSVar>> objects;
		int idCount;
		bool fin;
		//should push on by pushing front, then the global space is the last element
		LJS_RunTime(vector<string> pgram, map<string, LJSVar> lits)
		{
			idCount = 0;
			literals = lits;
			program = pgram;
			int newObInd = newObject();
			LJSVar tdo = LJSVar(LJS_Ptr(PT_OBJECT, newObInd));
			stck.push_back(LJS_RunTimeStackElement(0, newId(), "", "", tdo));
			collectInfo();
			//printInfo();
			fin = false;
		}

		int PC()
		{
			return stck.front().programCounter;
		}

		void setPC(int npc)
		{
			if(npc >= 0 && npc < program.size())
			{
				stck.front().setPC(npc);
				return;
			}
			LJS_error("program counter out of bounds :(");
		}

		int getLabelLoc(string n)
		{
			if(labelLocations.count(n) <= 0)
			{
				return -1;
			}
			return labelLocations[n];
		}

		string getFrontFN()
		{
			return "";
			/*if(stck.size() <= 1)
			{
				return "_";
			}
			return stck.front().prevScope + string("_") + stck.front().myScope + "_";*/
		}

		int getFunctionLoc(string n)
		{
			for(int i = 0; i < functionData.size(); i++)
			{
				if(functionData[i].name == getFrontFN() + n)
				{
					return functionData[i].loc;
				}
			}
			return -1;
		}

		int getFunctionIndex(string n)
		{
			for(int i = 0; i < functionData.size(); i++)
			{
				//cout << "F: " << n << " to " << functionData[i].name << endl;
				if(functionData[i].name == getFrontFN() + n)
				{
					return i;
				}
				//cout << "no " << n << " to " << functionData[i].name << endl;
			}
			return -1;
		}

		FunctionInfo getFunctionData(string n)
		{
			for(int i = 0; i < functionData.size(); i++)
			{
				if(functionData[i].name == getFrontFN() + n)
				{
					return functionData[i];
				}
			}
			return FunctionInfo();
		}

		void cantFind(string s)
		{
			LJS_error(string("sorry, cannot find: ") + s);
		}

		LJSVar * getVar(string name, bool assign = false)
		{
			LJSVar * pt;
			if(LJS_typeOfVar(name) == LITERAL)
			{
				if(literals.count(name) <= 0)
				{
					int findex = getFunctionIndex(name);
					if(findex != -1)
					{
						LJSVar * tpt = addVar(name);
						(*tpt) = LJSVar(LJS_Ptr(PT_FUNCTION, findex));
						return tpt;
					}
					cantFind(name);
				}
				return &literals[name];
			}else if(LJS_typeOfVar(name) == TEMPORARY)
			{
				return stck.front().forceGetVar(name);
			}else if(LJS_typeOfVar(name) == REFERENCE)
			{
				bool b = stck.front().getVar(name, pt);
				if(b)
				{
					if(pt->type != BT_POINTER)
					{
						return pt;
					}else if(pt->pt.isArrayElement())
					{
						return &arrays[pt->pt.index1][pt->pt.index2];
					}else if(pt->pt.isObjectElement())
					{
						int objectsIndex = pt->pt.index2;
						int key = pt->pt.index1;
						return &objects[objectsIndex][key];
					}else if(pt->pt.isFunctionElement())
					{
						return pt;
					}
				}
				cantFind(name);
			}else if(LJS_typeOfVar(name) == VARIABLE && assign)
			{
				bool b = stck.front().getVar(name, pt);
				if(b) return pt;
				return stck.front().forceGetVar(name);
			}else
			{
				bool b = stck.front().getVar(name, pt);
				if(b) return pt;

				for(int i = 0; i < stck.size(); i++)
				{
					bool b = stck[i].getVar(name, pt);
					if(b) return pt;
				}
				if(getFunctionIndex(name) >= 0)
				{
					stck.front().elements[string("T'") + name] = LJSVar(LJS_Ptr(PT_FUNCTION, getFunctionIndex(name)));
					b = stck.front().getVar(string("T'") + name, pt);
					if(b) return pt;
				}
				cantFind(name);
			}
			
		}

		LJSVar * addVar(string name)
		{
			stck.front().addVar(name);
			return &stck.front().elements[name];
		}

		void incPC()
		{
			stck.front().incPC();
		}

		vector<string> getProgramLine()
		{
			return LJS_split(program[PC()], ' ');
		}

		bool finished()
		{
			return fin;
		}

		string getOp()
		{
			return getProgramLine()[0];
		}

		vector<string> getProgramLine(int i)
		{
			return LJS_split(program[i], ' ');
		}

		string getOp(int i)
		{
			return getProgramLine(i)[0];
		}
		
		void addParam(LJSVar v)
		{
			stck.front().addParam(v);
		}

		LJSVar getArg()
		{
			return stck[1].popParam();
		}

		int newArray()
		{
			arrays.push_back(vector<LJSVar>());
			return arrays.size() - 1;
		}

		int newObject()
		{
			objects.push_back(LIndexMap<LJSVar>());
			return objects.size() - 1;
		}

		void dumpStack()
		{
			stck.front().dumpInfo();
		}

		void iterate()
		{
			string op = getOp();
			vector<string> args = getProgramLine();
			if(op == "exit")
			{
				fin = true;
			}else if(op == "define")
			{
				if(args[2] == "null")
				{
					addVar(args[1]);
				}else
				{
					LJSVar * p2 = getVar(args[2]);
					addVar(args[1]);
					LJSVar * p1 = getVar(args[1]);
					(*p1) = *p2;
				}
				
				
			}else if(op == "assign")
			{
				LJSVar * p2 = getVar(args[2]);
				LJSVar * p1 = getVar(args[1], true);
				(*p1) = *p2;
			}else if(op == "plus")
			{
				
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) + *p2;
			}else if(op == "subtract")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) - *p2;
			}else if(op == "mult")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) * (*p2);
			}else if(op == "mod")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1).mod( (*p2));
			}else if(op == "divide")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) / (*p2);
			}else if(op == "lessThan")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) < (*p2);
			}else if(op == "greaterThan")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) > (*p2);
			}else if(op == "greaterThanEq")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) >= (*p2);
			}else if(op == "notequals")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) != (*p2);
			}else if(op == "or")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) || (*p2);
			}else if(op == "and")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) && (*p2);
			}else if(op == "equals")
			{
				LJSVar * p2 = getVar(args[3]);
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = (*p1) == (*p2);
			}else if(op == "negate")
			{
				LJSVar * p1 = getVar(args[2]);
				LJSVar * p0 = getVar(args[1]);
				(*p0) = -(*p1);
			}else if(op == "param")
			{
				LJSVar * p0 = getVar(args[1]);
				addParam(*p0);
			}else if(op == "ifngoto")
			{
				LJSVar * p1 = getVar(args[1]);
				int newSpot = getLabelLoc(args[2]);
				if(p1->not().tobool())
				{
					
					setPC(newSpot);
					return;
				}
			}else if(op == "goto")
			{
				int newSpot = getLabelLoc(args[1]);
				setPC(newSpot);
				return;
			}else if(op == "call")
			{
				LJSVar tdo;
				//cout << "in call: " << endl;
				if(args[1] == "V'print")
				{
					LJSVar tmp = stck.front().popParam();
					cout << tmp.getString();
				}else if(args[1] == "V'push")
				{
					LJSVar tmp = stck.front().popParam();
					LJSVar e = stck.front().popParam();
					if(tmp.isPointer() && tmp.pt.isArray())
					{
						arrays[tmp.pt.index1].push_back(e);
					}else
					{
						LJSVar("pushing to non array");
					}
				}else
				{
					int newLoc = -1;
					FunctionInfo f;
					int numArgs = LJS_string2Int(args[2]);
					newLoc = getFunctionLoc(args[1]);
					if(newLoc == -1)
					{
						LJSVar * p0 = getVar(args[1]);
						if(p0->pt.isFunction())
						{
							int indaaa = newObject();
							tdo = LJSVar(LJS_Ptr(PT_OBJECT, indaaa));
							newLoc = functionData[p0->pt.index1].loc;
							f = functionData[p0->pt.index1];
						}else if(p0->pt.isFunctionElement())
						{
							newLoc = functionData[p0->pt.index1].loc;
							f = functionData[p0->pt.index1];
							tdo = LJSVar(LJS_Ptr(PT_OBJECT, p0->pt.index2));
						}else
						{
							LJS_error("calling non function");
						}

					}else
					{
						f = getFunctionData(args[1]);	
						int indaaa = newObject();
						tdo = LJSVar(LJS_Ptr(PT_OBJECT, indaaa));
					}
				
					//cout << "end call";
					stck.push_front(LJS_RunTimeStackElement(newLoc, newId(), f.name, stck.front().myScope, tdo));
					return;
				}
			}else if(op == "objectCall")
			{
				LJSVar tdo;
				//cout << "in call: " << endl;
				int newLoc = -1;
				FunctionInfo f;
				int numArgs = LJS_string2Int(args[3]);
				newLoc = getFunctionLoc(args[2]);
				if(newLoc == -1)
				{
					LJSVar * p0 = getVar(args[2]);
					if(p0->pt.isFunction())
					{
						newLoc = functionData[p0->pt.index1].loc;
						f = functionData[p0->pt.index1];
					}else
					{
						LJS_error("creating object incorrectly");
					}

				}else
				{
					f = getFunctionData(args[2]);	
				}
				int indaaa = newObject();
				LJSVar * newOb = addVar(args[1]);
				tdo = LJSVar(LJS_Ptr(PT_OBJECT, indaaa));
				(*newOb) = tdo;
				//cout << "end call";
				stck.push_front(LJS_RunTimeStackElement(newLoc, newId(), f.name, stck.front().myScope, tdo));
				return;
				
			}else if(op == "getelement")
			{
				
				string elementName = args[3];
				LJSVar * ref = addVar(args[1]);
				if(args[2] == "V'this")
				{
					LJSVar * obj = &stck.front().thisDataObject;
					int index = objects[stck.front().thisDataObject.pt.index1].indexOf(elementName);
					if(objects[obj->pt.index1][index].type == BT_POINTER && objects[obj->pt.index1][index].pt.isFunction())
					{
						//cout << "found function: " << elementName << " as " << index << " from " << args[2] << endl;
						int funcIndex = objects[obj->pt.index1][index].pt.index1;
						*ref = LJSVar(LJS_Ptr(PT_FUNCTION_ELEMENT, funcIndex, obj->pt.index1));
					}else
					{
						*ref = LJSVar(LJS_Ptr(PT_OBJECT_ELEMENT, index, stck.front().thisDataObject.pt.index1));
					}
				}else
				{
					LJSVar * obj = getVar(args[2]);
					if(elementName == "V'length" && obj->isPointer() && obj->pt.isArray())
					{
						*ref = (int)arrays[obj->pt.index1].size();
					}else if(elementName == "V'length" && obj->type == BT_STRING)
					{
						*ref = (int)obj->getString().size();
					}else if(obj->isPointer() && obj->pt.isObject())
					{
						int index = objects[obj->pt.index1].indexOf(elementName);

						//LJSVar obele = objects[obj->pt.index1]
						if(objects[obj->pt.index1][index].type == BT_POINTER && objects[obj->pt.index1][index].pt.isFunction())
						{
							//cout << "found function: " << elementName << " as " << index << " from " << args[2] << endl;
							int funcIndex = objects[obj->pt.index1][index].pt.index1;
							*ref = LJSVar(LJS_Ptr(PT_FUNCTION_ELEMENT, funcIndex, obj->pt.index1));
						}else
						{
							*ref = LJSVar(LJS_Ptr(PT_OBJECT_ELEMENT, index, obj->pt.index1));
						}
					}else
					{
						LJS_error("error with element selection..." + elementName);
					}
				}
				
			}else if(op == "label:")
			{
				//do nothing
			}else if(op == "Function:")
			{
				//do nothing
			}else if(op == "arg")
			{
				LJSVar * p0 = addVar(args[1]);
				if(stck.size() < 2)
				{
					LJS_error("illegal arg call");
				}
				*p0 = getArg();
			}else if(op == "return")
			{
				LJSVar rv;
				if(args.size() > 1)
				{
					rv = *getVar(args[1]);	
				}
				LJS_RunTimeStackElement se = stck.front();
				stck.pop_front();
				stck.front().setReturnVar(rv);
			}else if(op == "getReturnVal")
			{
				LJSVar * p0 = getVar(args[1]);
				*p0 = stck.front().getReturnVar();
			}else if(op == "createArray")
			{
				LJSVar * p0 = getVar(args[1]);
				(*p0) = LJSVar(LJS_Ptr(PT_ARRAY, newArray()));
			}else if(op == "push")
			{
				LJSVar * p0 = getVar(args[1]);
				LJSVar * p1 = getVar(args[2]);
				if(p0->type != BT_POINTER)
				{
					LJS_error("pushing on a non array");
				}else if(!(p0->pt.isArray()))
				{
					LJS_error("pushing on a non array");
				}
				arrays[p0->pt.index1].push_back(*p1);
			}else if(op == "indexby")
			{
				LJSVar * refAc = addVar(args[1]);
				LJSVar * arr = getVar(args[2]);
				LJSVar * ind = getVar(args[3]);
				if(!(ind->type == BT_NUMBER) ){LJS_error("error accessing array with non number");}
				if(arr->type == BT_STRING)
				{
					int i = (int) ind->getDouble();
					if(i >= arr->getString().size() || i < 0)
					{
						LJS_error("error accessing string out of bounds");
					}
					string st = arr->getString();
					char buf[2];
					buf[1] = '\0';
					buf[0] = st[i];
					*refAc = LJSVar(string(buf));
				}else
				{

					if(!arr->pt.isArray() ){
						LJS_error("error accessing non array");}
					LJS_Ptr p(PT_ARRAY_ELEMENT);
					p.index1 = arr->pt.index1;
					p.index2 = (int) ind->getDouble();
					LJSVar ref(p);
					*refAc = ref;
				}
			}else if(op == "createObject")
			{
				LJSVar * p0 = getVar(args[1]);
				(*p0) = LJSVar(LJS_Ptr(PT_OBJECT, newObject()));
			}else
			{
				LJS_error("have not seen: " + op + " before :(");
			}

			incPC();
		}

		void collectInfo()
		{
			for(int i = 0; i < program.size(); i++)
			{
				if(getOp(i) == "label:")
				{
					
					vector<string> d = getProgramLine(i);
					labelLocations[d[1]] = i;
				}else if(getOp(i) == "Function:")
				{
					
					vector<string> d = getProgramLine(i);
					functionData.push_back(FunctionInfo(d[1], d[2], i));
				}
			}
		}

		void printInfo()
		{
			cout << "label list: " << endl;
			for(map<string,int>::iterator i = labelLocations.begin(); i != labelLocations.end(); i++)
			{
				cout << i->first << " on line: " << i->second << endl;
			}

			for(int i = 0; i < functionData.size(); i++)
			{
				cout << "function name: " << functionData[i].fname << " alias: " << functionData[i].name << " on line:  " << functionData[i].loc << endl;
			}
		}

		int newId()
		{
			int rv = idCount;
			idCount++;
			return idCount;
		}



	};

}

#endif