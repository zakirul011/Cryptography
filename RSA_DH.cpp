#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n);
bool checkGenerator(int g, int p);
int modPow(int b, int e, int m);

int getInverse(int a, int b);
int gcd(int a, int b);
bool isValidPublicKey(int e, int phi);

int main(void)
{

    cout << "Choose an option: " << endl;
    cout << "1. RSA \n2. Diffie Hellman" << endl << endl;

    int choose;
    cout << "Your option: ";
    cin >> choose;

    if (choose == 1)
    {
        cout << "\nEnter information for RSA:\n" << endl;
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
        int m;
        cout << "Enter message: ";
        cin >> m;

        // Encryption
        int E = modPow(m, e, n);
        
        // Decryption
        int M = modPow(E, d, n);

        cout << "\nOriginal Message: " << m << endl;
        cout << "Encrypted Message: " << E << endl;
        cout << "Decrypted Message: " << M << endl; 
    }

    else 
    {        
        cout << "\nEnter information for Diffie Hellman:\n" << endl;

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

