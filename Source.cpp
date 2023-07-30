#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;


struct Node
{
	Node* links[26];
	bool flag = false;
	bool containKey(char ch)                   //checks if the reference trie is present or not
	{
		return (links[ch - 'a'] != NULL);
	}
	void put(char ch, Node* node)               //creating reference trie
	{
		links[ch - 'a'] = node;
	}
	Node* get(char ch)                          //to get the next node for traversal
	{
		return links[ch - 'a'];
	}
	void setEnd()                                //setting flag to true at the end of the word
	{
		flag = true;
	}
	bool isEnd()                                 //checking if the word is completed or not
	{
		return flag;
	}
};



class TrieTree
{
private:


	int sugg_Limit = 10;
	int count = 0;
	string* strSuggessions;


public:
	Node* root;


	TrieTree()
	{
		root = new Node();
		strSuggessions = new string[sugg_Limit];
	}


	void insert(string word)
	{
		Node* node = root;
		for (int i = 0; i < word.size(); i++)
		{
			if (!node->containKey(word[i]))        //If key is not contain then we add the node
			{
				node->put(word[i], new Node());    //IF that node is null then we create the node
			}
			node = node->get(word[i]);             //moves to reference trie
		}
		node->setEnd();                                //This will return true
	}



	void suggestionsRec(Node* root, string currword)
	{
		if (count < sugg_Limit)
		{
			if (root->flag)                    // found a string in Trie with the given prefix
			{
				strSuggessions[count] = currword;
				count++;
				cout << count << " : " << currword << endl;
			}
			for (int i = 0; i < 26; i++)
			{
				if (root->links[i])            // child node character value
				{

					char child = 'a' + i;
					suggestionsRec(root->links[i], currword + child);
				}
			}
		}
	}


	void selectWord(string& str)
	{
		int x = 0;
		string choice;
		char pressed;
		string temp = str;
		while (x < sugg_Limit)
		{
			system("cls");
			cout << "Enter / for moving to next word\nEnter ; to select the word\n\n";
			cout << "String --> " << str << endl << endl;
			for (int i = 0; i < sugg_Limit; ++i)
			{
				cout << i + 1 << " : " << strSuggessions[i] << endl;
			}
			if (_kbhit)
			{
				pressed = _getch();				//get key using kbhit
			}
			while (pressed != '/' && pressed != ';')
			{
				cout << "Invalid key pressed\nEnter again : \n";
				if (_kbhit)
				{
					pressed = _getch();
				}
			}
			if (pressed == '/')
			{
				str = strSuggessions[x];
				x++;
			}
			else if (pressed == ';')
			{
				break;
			}
		}
		if (x == sugg_Limit)
		{
			str = strSuggessions[sugg_Limit - 1];
		}
	}



	int printAutoSuggestions(Node* root, string word)           // print suggestions for given query prefix.
	{
		count = 0;
		int n = 0;
		Node* node = root;
		for (int i = 0; i < word.size(); ++i)
		{
			if (!node->containKey(word[i]))         //If key is not contain then we add the node
			{
				return false;                           //If already key contain then this will return false
			}
			node = node->get(word[i]);               //moves to reference trie
		}
		suggestionsRec(node, word);
		return 1;
	}

};


int main()
{
	TrieTree obj;
	string R;
	string search;
	int h = 0;
	ifstream wordsfile;
	wordsfile.open("outfile.txt");
	while (!wordsfile.eof())
	{
		int TT = 1;
		int s;
		wordsfile >> R;
		s = R.size();
		for (int i = 0; i < s; ++i)
		{
			if (R[i] < 'a' || R[i]>'z')
			{
				TT = 0;
			}
		}
		if (TT == 1)
		{
			obj.insert(R);
		}
		h++;
	}
	string str = "";
	string str2;
	string choice;
	cout << "Enter string : " << str;
	cin >> str2;
	while (str2.size() > 1)
	{
		cout << "Enter a character not a string\n";
		cin >> str2;
	}
	str = str + str2;
	int comp = obj.printAutoSuggestions(obj.root, str);
	do
	{
		cout << "---> Press 1 if you want to select from these suggessions\n---> Press 2 to add more characters\n---> Press any key to complete the word and for exit\n";
		cin >> choice;
		if (choice == "1")
		{
			obj.selectWord(str);
			break;
		}
		else if (choice == "2")
		{
			system("cls");
			cout << "Enter string : " << str;
			cin >> str2;
			while (str2.size() > 1)
			{
				cout << "Enter a character not a string\n";
				cin >> str2;
			}
			str += str2;
			int comp = obj.printAutoSuggestions(obj.root, str);
		}
		else
		{
			cout << "Loop ended\n";
			break;
		}
	} while (choice == "1" || choice == "2");
	cout << "\nEntered word is : " << str << endl;
	cout << "Total words in file are : " << h << endl;
	system("pause");
	return 0;

}