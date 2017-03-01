#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;


void textMenu(){
	cout << "\n===========================================";
	cout << "\nМеню работы с программой:";
	cout << "\n1.Выполнить введённую команду";
	cout << "\n2.Запусть на исполнение скрипт(script)";
	cout << "\n3.Отослать содержимое указанного файла";
	cout << "\nуказанному пользователю";
	cout << "\n0.Выход";
	cout << "\nВыбранный вариант: ";
}

void runEnterCommand(){
	string command;
	cout << "\nВведите команду для исполнения: ";
	cin.get();
	getline(cin,command);
	cout << "Результат работы комманды:\n";
	system(command.c_str());
}

void runScript(){
	string pathScript("./script");
	cout << "\nРезультат работы скрипта:\n";
	system(pathScript.c_str());

}

void sendText(){
	string command("cat ");

	string fileName;
	cout << "\nВведите имя файла: ";
	cin >> fileName;
	command += fileName + " | write ";

	string username;
	cout << "\nВведите имя пользователя: ";
	cin >> username;
	command += username;
	
	cout << "Результат полученной комманды: ";
	system(command.c_str());

}

int main(){
	int choice = 0;
	bool exit = false;
	while(!exit){
		textMenu();

		cin >> choice;
	    cout<<"===========================================\n";
	
	switch(choice){
		case 1:
			runEnterCommand();
			break;
		case 2:
			runScript();
			break;
		case 3:
			sendText();
			break;
		case 0:
			exit = true;
			break;
		default:
			cout << "\nНеверный пункт меню";
			break;
		}		
				
	}	
	return 0;	
}
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;


void textMenu(){
	cout << "\n===========================================";
	cout << "\nМеню работы с программой:";
	cout << "\n1.Выполнить введённую команду";
	cout << "\n2.Запусть на исполнение скрипт(script)";
	cout << "\n3.Отослать содержимое указанного файла";
	cout << "\nуказанному пользователю";
	cout << "\n0.Выход";
	cout << "\nВыбранный вариант: ";
}

void runEnterCommand(){
	string command;
	cout << "\nВведите команду для исполнения: ";
	cin.get();
	getline(cin,command);
	cout << "Результат работы комманды:\n";
	system(command.c_str());
}

void runScript(){
	string pathScript("./script");
	cout << "\nРезультат работы скрипта:\n";
	system(pathScript.c_str());

}

void sendText(){
	string command("cat ");

	string fileName;
	cout << "\nВведите имя файла: ";
	cin >> fileName;
	command += fileName + " | write ";

	string username;
	cout << "\nВведите имя пользователя: ";
	cin >> username;
	command += username;
	
	cout << "Результат полученной комманды: ";
	system(command.c_str());

}

int main(){
	int choice = 0;
	bool exit = false;
	while(!exit){
		textMenu();

		cin >> choice;
	    cout<<"===========================================\n";
	
	switch(choice){
		case 1:
			runEnterCommand();
			break;
		case 2:
			runScript();
			break;
		case 3:
			sendText();
			break;
		case 0:
			exit = true;
			break;
		default:
			cout << "\nНеверный пункт меню";
			break;
		}		
				
	}	
	return 0;	
}
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;


void textMenu(){
	cout << "\n===========================================";
	cout << "\nМеню работы с программой:";
	cout << "\n1.Выполнить введённую команду";
	cout << "\n2.Запусть на исполнение скрипт(script)";
	cout << "\n3.Отослать содержимое указанного файла";
	cout << "\nуказанному пользователю";
	cout << "\n0.Выход";
	cout << "\nВыбранный вариант: ";
}

void runEnterCommand(){
	string command;
	cout << "\nВведите команду для исполнения: ";
	cin.get();
	getline(cin,command);
	cout << "Результат работы комманды:\n";
	system(command.c_str());
}

void runScript(){
	string pathScript("./script");
	cout << "\nРезультат работы скрипта:\n";
	system(pathScript.c_str());

}

void sendText(){
	string command("cat ");

	string fileName;
	cout << "\nВведите имя файла: ";
	cin >> fileName;
	command += fileName + " | write ";

	string username;
	cout << "\nВведите имя пользователя: ";
	cin >> username;
	command += username;
	
	cout << "Результат полученной комманды: ";
	system(command.c_str());

}

int main(){
	int choice = 0;
	bool exit = false;
	while(!exit){
		textMenu();

		cin >> choice;
	    cout<<"===========================================\n";
	
	switch(choice){
		case 1:
			runEnterCommand();
			break;
		case 2:
			runScript();
			break;
		case 3:
			sendText();
			break;
		case 0:
			exit = true;
			break;
		default:
			cout << "\nНеверный пункт меню";
			break;
		}		
				
	}	
	return 0;	
}
