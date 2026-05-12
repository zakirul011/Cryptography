#include <iostream>
#include <algorithm>
using namespace std;

struct letterFreq{
    char letter;
    int count = 0;
};

bool compare(letterFreq a, letterFreq b)
{
    return a.count > b.count;
}

int main(void)
{
    string ciphertext;

    cout << "Enter ciphertext: ";
    getline(cin, ciphertext);

    int totalLetters = 0;
    letterFreq freq[26];

    for (char ch : ciphertext)
    {
        if (isalpha(ch))
        {
            ch = toupper(ch);
            freq[ch - 'A'].letter = ch;
            freq[ch - 'A'].count++;
            totalLetters++;
        }
    }
    
    for (int i = 0; i < 26; i++)
    {
        char ch = freq[i].letter;
        int count = freq[i].count;

        if (count > 0)
        {
            float percent = float(count) / totalLetters * 100;
            cout << ch << " appears " << count << " times ("<< percent << "%)" << endl;
        }
        

    }
    cout << endl;

    sort(freq, freq + 26, compare);

    cout << "The top 5 Most frequent lettes: " << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << freq[i].letter << " : " << freq[i].count << " times" << endl;
    }
}