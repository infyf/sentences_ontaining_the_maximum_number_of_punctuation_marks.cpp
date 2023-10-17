#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <windows.h>
#include <regex> 
using namespace std;

bool isUkrainianPunctuation(char ch) {
    string ukrPunctuation = ".!?";
    return ukrPunctuation.find(ch) != string::npos;
}

int countPunctuation(const string& sentence) {
    int count = 0;
    for (char ch : sentence) {
        if (isUkrainianPunctuation(ch)) {
            count++;
        }
    }
    return count;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream file("text1.txt");

    if (!file.is_open()) {
        cout << "������� �������� �����!" << endl;
        return 1;
    }

    vector<string> sentences; // ������ ��� ��������� ������

    string line;
    string currentSentence;

    while (getline(file, line)) {
        currentSentence += line + " "; // ������ ����� ���� ������� �����
    }

    
    regex sentenceRegex("[^.!?]+[.!?]+"); 

    for (sregex_iterator it(currentSentence.begin(), currentSentence.end(), sentenceRegex), end; it != end; ++it) {
        sentences.push_back(it->str());
    }

 
    int maxPunctuation = 0;
    string maxPunctuationSentence;

    for (const string& sentence : sentences) {
        int punctuationCount = countPunctuation(sentence);
        if (punctuationCount > maxPunctuation) {
            maxPunctuation = punctuationCount;
            maxPunctuationSentence = sentence;
        }
    }


    cout << "������� � ������������ ������� ����� ����������:" << endl;
    cout << maxPunctuationSentence << endl;

    file.close();

    return 0;
}
