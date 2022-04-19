// Chess 
#include "Chess.h"
#include "Board.h";


int main()
{
	//string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
	string board   = "R#BQKB#R################################################r#bqkb#r";
	Chess a(board);
	Board b(board);

	int codeResponse = 0;
	string res = a.getInput();
	while (res != "exit")
	{
		/* 
		{ 
			cout << "code response >> ";
			cin >> codeResponse;
		}
		*/

		codeResponse = b.statusCheckForCode(res,true);
		if (codeResponse >= 40)
		{
			b.switchTurn();
		}

		a.setCodeResponse(codeResponse);
		res = a.getInput(); 
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}