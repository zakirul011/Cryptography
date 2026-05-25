#include <iostream>
#include <cmath>
using namespace std;

int getInverse(int a, int b);
int modPow(int base, int exp, int mod);
int gcd(int a, int b);
bool isValidPublicKey(int e, int phi);
bool isPrime(int a);

int main(void)
{
    int p, q;
    cout << "Enter p and q: ";
    cin >> p >> q;

    if (!isPrime(p) || !isPrime(q))
    {
        cout << "p or q is not prime number!";
        return 1;
    }

    int n = p * q;
    int phi = (p-1) * (q-1);

    // public key
    int e;
    cout << "Enter Public key: ";
    cin >> e;

    // if not valid public key then return
    if (!isValidPublicKey(e, phi))
    {
        cout << "The public key is not valid!";
        return 1;
    }

    // private key
    int d = getInverse(e, phi);
    if (d < 1)
    {
        cout << "The inverse is not exist!";
        return 1;
    }

    // Message
    char m;
    cout << "Enter message: ";
    cin >> m;

    if (m >= n)
    {
        cout << "Message must be less than n!";
        return 1;
    }

    // Encryption
    char E = modPow(m, e, n);
    
    // Decryption
    char M = modPow(E, d, n);

    cout << "\nOriginal Message: " << m << endl;
    cout << "Encrypted Message: " << E << endl;
    cout << "Decrypted Message: " << M << endl;
}


int getInverse(int a, int b)
{
    for (int i = 2; i < b; i++)
    {
        if (a * i % b == 1)
        {
            return i;
        }
    }

    return -1;
}

int modPow(int base, int exp, int mod)
{
    int result = 1;

    for (int i = 0; i < exp; i++)
    {
        result = (result * base) % mod;
    }

    return result;
}

int gcd(int a, int b)
{
    while (b > 0)
    {
        int t = a % b;
        a = b;
        b = t;
    }

    return a;
}


bool isValidPublicKey(int e, int phi)
{
    if (e > 1 && e < phi && gcd(e, phi) == 1)
    {
        return true;
    }

    return false;
}

bool isPrime(int a)
{
    if (a < 2)
    {
        return false;
    }

    for (int i = 2; i <= sqrt(a); i++)
    {
        if (a % i == 0)
            return false;
    }

    return true;
}