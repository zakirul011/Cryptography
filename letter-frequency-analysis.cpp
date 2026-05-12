#include <iostream>
using namespace std;

int main(void)
{
    string ciphertext;

    cout << "Enter ciphertext: ";
    getline(cin, ciphertext);

    int counter[26] = {0};

    for (char ch : ciphertext)
    {
        ch = toupper(ch);
        int indexCh = ch - 'A';
        if (isalpha(ch))
        {
            counter[indexCh]++;
        }
    }

    char ch;
    int count;
    int n = ciphertext.length();
    float result;

    for (int i = 0; i < 26; i++)
    {
        ch = char(i + 'A');
        count = counter[i];

        result = float(count) / n * 100.0;

        cout << ch << " is " << count << " times with " << result << '%' << endl;
    }
    cout << endl;
}