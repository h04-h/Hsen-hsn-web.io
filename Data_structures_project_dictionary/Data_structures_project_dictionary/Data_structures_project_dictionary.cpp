#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct sWord {
	char data[30];
	sWord* next;
};

struct dWord {
	char data[30];
	sWord* synonym, * antonym;
	dWord* next, * previous;
};

struct Dictionary {
	dWord* head, * tail;
};

void initialize(Dictionary* dict) {
	dict->head = NULL;
	dict->tail = NULL;
}

bool isEmpty(Dictionary* dict) {
	return(dict->head == NULL);
}

int dictSize() {
	ifstream inFile; // to take from file to code 
	inFile.open("C:\\Users\\Lenovo\\Desktop\\CCE\\data\\Data_structures_project_dictionary\\dictionary.txt");
	int lines = 0;
	string tmp;
	if (inFile.fail())
		cout << "File not found. Please try again." << endl;
	while (getline(inFile, tmp)) {
		lines++;
	}
	inFile.close();
	return lines;
}

sWord* insertAtTailS(sWord* head, char* word) {
	sWord* tmp = new sWord;
	strcpy(tmp->data, word);
	tmp->data[sizeof(tmp->data) - 1] = '\0';
	tmp->next = NULL;
	if (head == NULL)
		return tmp;
	sWord* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = tmp;
	return head;
}

Dictionary* insertAtTailD(Dictionary* dict, sWord* syn, sWord* anto) {
	dWord* tmp = new dWord;
	tmp->synonym = syn;
	tmp->antonym = anto;
	tmp->next = NULL;

	if (isEmpty(dict)) {
		tmp->previous = NULL;
		dict->head = tmp;
		dict->tail = tmp;
	}
	else {
		tmp->previous = dict->tail;
		dict->tail->next = tmp;
		dict->tail = tmp;
	}
	return dict;
}

Dictionary* fillDictList(Dictionary *dictionary) {
	int lineCount = dictSize();

	ifstream inFile; 	 
	inFile.open("C:\\Users\\Lenovo\\Desktop\\CCE\\data\\Data_structures_project_dictionary\\dictionary.txt");

	if (inFile.fail())
		cout << "File not found. Please try again." << endl;
	
	string line;
	Dictionary* cur = dictionary;
	for (int i = 0; i < lineCount; i++) {
		//cout << "1" << endl;	////
		sWord* tmpSyn = nullptr;
		sWord* tmpAnto = nullptr;
		getline(inFile, line);
		//cout << line << endl;
		while (!line.empty()) {
			//cout << line << endl;
			//cout << "2" << endl;	////
			int posOf2Points = line.find(":");
			if (posOf2Points == string::npos)
				break;
			string firstSynonym = line.substr(0,posOf2Points);
			char synonym[30];
			strcpy(synonym, firstSynonym.c_str());
			//cout << synonym << endl; //
			insertAtTailS(tmpSyn, synonym);
			line = line.substr(posOf2Points+1);
		}
		while (!line.empty()) {
			//cout << line << endl;
			//cout << "3" << endl;	////
			int posOfHashtag = line.find("#");
			if (posOfHashtag == string::npos)
				break;
			string firstAntonym = line.substr(0, posOfHashtag);
			char antonym[30];
			strcpy(antonym, firstAntonym.c_str());
			//cout << antonym << endl;  //
			insertAtTailS(tmpAnto, antonym);
			line = line.substr(posOfHashtag + 1);
		}
		insertAtTailD(dictionary, tmpSyn, tmpAnto);
		
	}
	inFile.close();
	return dictionary;
}

void fillFiles(Dictionary* dictionary) {
	ofstream emptyFile("C:\\Users\\Lenovo\\Desktop\\CCE\\data\\Data_structures_project_dictionary\\dictionary.txt");
	emptyFile.close(); // to empty the initial file

	ofstream outFile; // to take from code to file
	outFile.open("C:\\Users\\Lenovo\\Desktop\\CCE\\data\\Data_structures_project_dictionary\\dictionary.txt");
	dWord* curD = dictionary->head;
	while (curD != NULL) {
		sWord* curSyn = curD->synonym;
		sWord* curAnto = curD->antonym;
		while (curSyn != NULL) {

			outFile << curSyn->data << ":";
			curSyn = curSyn->next;
		}
		while (curAnto != NULL) {
			outFile << "#" << curAnto->data;
			curAnto = curAnto->next;
		}
		outFile << endl;
		curD = curD->next;
	}
	outFile.close();
}

int main() {

	Dictionary* dictionary = new Dictionary;
	initialize(dictionary);
	dictionary = fillDictList(dictionary);
	fillFiles(dictionary);
	return 0;
}



/*demo files
hi:hello#bye#zahet
nice:good#bad#khara
goodmorning:bonjour#bonnenuit#nem khlsne

*/