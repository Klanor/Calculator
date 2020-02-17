#include "Header.h"

using namespace std;

int main()
{
	Calculator cl;
	string h;

	while (true)
	{
		cout << "___---===*SUPER CALCULATOR*===---___" << endl;
		cout << "1 - to exit (without operation priority)" << endl;
		cin >> h;
		if (h == "1")
			break;
		try
		{
			cl.Set(h);
		}
		catch (string str)
		{
			cout << str << endl;
			continue;
		}
		cout << cl.Get() << endl;
		cout << endl << endl;
	}


	return 0;
}