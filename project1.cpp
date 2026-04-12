#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void getWords(vector<string> &words, ifstream &file);
void sortWords(vector<string> &words);
vector<pair<string, int>> getWordCounts(vector<string> &words);
string cleanWord(string word);

int main()
{
    ifstream file("homes.txt");

    if (!file)
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    vector<string> words;
    vector<pair<string, int>> wordCounts;

    getWords(words, file);
    file.close();

    sortWords(words);

    wordCounts = getWordCounts(words);

    for (int index = 0; index < wordCounts.size(); index++)
    {
        cout << wordCounts[index].first << " : " << wordCounts[index].second << endl;
    }

    return 0;
}

void getWords(vector<string> &words, ifstream &file)
{
    string word;

    while (file >> word)
    {
        word = cleanWord(word);

        if (word != "")
        {
            words.push_back(word);
        }
    }
}

void sortWords(vector<string> &words)
{
    sort(words.begin(), words.end());
}

vector<pair<string, int>> getWordCounts(vector<string> &words)
{
    vector<pair<string, int>> counts;

    if (words.size() == 0)
    {
        return counts;
    }

    string currentWord = words[0];
    int currentCount = 1;

    for (int index = 1; index < words.size(); index++)
    {
        if (words[index] == currentWord)
        {
            currentCount++;
        }
        else
        {
            counts.push_back(make_pair(currentWord, currentCount));
            currentWord = words[index];
            currentCount = 1;
        }
    }

    counts.push_back(make_pair(currentWord, currentCount));

    return counts;
}

string cleanWord(string word)
{
    string cleanedWord = "";

    for (int index = 0; index < word.length(); index++)
    {
        if (isalpha(word[index]))
        {
            cleanedWord = cleanedWord + char(tolower(word[index]));
        }
    }

    return cleanedWord;
}