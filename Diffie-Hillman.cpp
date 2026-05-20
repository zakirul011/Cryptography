#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n);
bool checkGenerator(int g, int p);
int modPow(int b, int e, int m);

int main(void)
{

    int p;
    cout << "Enter prime number: ";
    cin >> p;

    if (!isPrime(p))
    {
        cout << "This is not a prime number!";
        return 1;
    }


    int g;
    cout << "Enter generator: ";
    cin >> g;

    if (!checkGenerator(g, p))
    {
        cout << "This is not a valid generator!";
        return 1;
    }


    int a;
    cout << "Enter private key of Alice: ";
    cin >> a;

    int A = modPow(g, a, p);


    int b;
    cout << "Enter private key of Bob: ";
    cin >> b;



    int B = modPow(g, b, p);


    int k_A = modPow(B, a, p);
    int k_B = modPow(A, b, p);    

    cout << endl;

    cout << "Private key of Alice: " << a << endl;
    cout << "Private key of Bob: " << b << endl;

    cout << "Public key of Alice: "  << A << endl;
    cout << "Public key of Bob: " << B << endl;

    cout << "Generated key of Alice: " << k_A << endl;
    cout << "Generated key of Bob: " << k_B << endl;
}

bool isPrime(int n)
{
    if (n < 2)
        return false;
    
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

bool checkGenerator(int g, int p)
{
    int checklist[p - 1] = {0};

    for (int i = 1; i < p; i++)
    {
        int gi = modPow(g, i, p);

        for (int j = 0; j < p - 1; j++)
        {
            if (checklist[j] == gi)
            {
                return false;
            }
        }

        checklist[i - 1] = gi;
    }

    return true;
}

int modPow(int b, int e, int m)
{
    int r = 1;

    for (int i = 0; i < e; i++)
    {
        r = (r * b) % m;
    }

    return r;
}

