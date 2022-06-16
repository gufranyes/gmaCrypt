#include <vector>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

using namespace std;

int prime1, prime2, number, totient, i, flag;
long int publicKey[1000], privateKey[1000], temp[1000], j;
char en[1000], m[1000];
char msg[1000];
int prime(long int); // function to check for prime number
void encryption_key();
long int cd(long int);
string encrypt(string);
string decrypt();

struct file
{
	string filename;
	string date;
	string type;
	string content;
	string author;
	string permission;

	struct folder *lastfolder;
};

struct folder
{
	string foldername;
	string date;
	string password;

	int count;
	vector<folder *> nextfolder;
	vector<file *> nextfile;
	struct folder *lastfolder;
};

folder *addFolder(struct folder *f1, string name, string pass)
{
	folder *f2 = new folder;
	f2->foldername = name;
	f2->count = 0;
	f2->lastfolder = f1;
	f2->password = pass;

	time_t t;
	struct tm *tt;
	time(&t);
	tt = localtime(&t);
	f2->date = asctime(tt);

	return f2;
}

file *addFile(struct folder *f1, string name, string auth, string cont, string tp, string perm)
{
	file *f2 = new file;
	f2->filename = name;
	f2->author = auth;
	f2->lastfolder = f1;
	f2->content = cont;
	f2->type = tp;
	f2->permission = perm;

	time_t t;
	struct tm *tt;
	time(&t);
	tt = localtime(&t);
	f2->date = asctime(tt);

	return f2;
}

template <class T>
inline std::string to_string(const T &t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

int main()
{

	cout << "**********************************************************" << endl;
	cout << "****** Welcome to the gmaCrypt (Secure File System) ******" << endl;
	cout << "**********************************************************" << endl;

	// changing color to light cyan

	string perm = " -rwx------";

	printf("\033[0;96m");

	vector<string> dir;
	int in, x;
	string qt;
	string nm, auth, content, type;
	string enc_auth, enc_content, enc_type, enc_perm;
	string dec_auth, dec_content, dec_type, dec_perm;
	string new_content, enc_new_content;
	string v, cont;

	string newname, newauth, newtype, newperm, newcontent;
	string enc_newname, enc_newauth, enc_newtype, enc_newperm, enc_newcontent;

	struct folder *root = new folder();
	nm = "root";
	root->foldername = nm;
	root->count = 0;
	root->lastfolder = NULL;
	struct folder *p = root;

	// changing text to yellow, bold

	printf("\033[0;33m");
	printf("\033[1m");

	cout << endl;
	cout << setw(20) << left << "help"
		 << "to display all the functions\n";
	cout << setw(20) << left << "mkdir"
		 << "to create a directory\n";
	cout << setw(20) << left << "create"
		 << "to create a new file\n";
	cout << setw(20) << left << "cd .."
		 << "to go back\n";
	cout << setw(20) << left << "ls"
		 << "to list all the contents of the directory\n";
	cout << setw(20) << left << "read"
		 << "to read the contents of the file\n";
	cout << setw(20) << left << "fileinfo"
		 << "to display the details of the file\n";
	cout << setw(20) << left << "rename "
		 << "to rename a file\n";
	cout << setw(20) << left << "rm -rf"
		 << "to remove the folder\n";
	cout << setw(20) << left << "del"
		 << "to delete the file\n";
	cout << setw(20) << left << "exit"
		 << "to exit the file system\n";

	// changing color to white, normal

	printf("\033[0;39m");
	printf("\033[0m");

	dir.push_back(nm);
	while (true)
	{
		cout << endl;
		for (x = 0; x < dir.size(); x++)
			cout << dir[x] << ":\\> ";

		cin >> v;

		// 1. mkdir: used for making a new directory at the current path

		if (v == "mkdir")
		{

			// cout<<"Enter directory name:";
			string pass;
			cin >> nm;

			cout << "Would you like to protect the directory using a password ? y/n\n";
			cin >> pass;

			if (pass == "YES" || pass == "Yes" || pass == "yes" || pass == "Y" || pass == "y")
			{
				cout << "Enter password\n";
				cin.ignore();
				getline(cin, pass);
				(p->nextfolder).push_back(addFolder(p, nm, pass));
			}
			else
			{
				(p->nextfolder).push_back(addFolder(p, nm, ""));
			}
		}

		// 2. create file: creates a new file takes in author name and enables to write content

		else if (v == "create")
		{

			cin >> nm;

			string key;
			printf("\033[0;92m");
			cout << "\n*******This is a secure file system*****\n"
				 << endl;
			// cout<<"Please enter the 16-bit key: ";
			// cin.ignore();
			// getline(cin,key);
			cout << "\nPlease enter the first prime number!\n";
			cin >> prime1;

			// checking whether input is prime or not
			flag = prime(prime1);
			if (flag == 0)
			{
				cout << "\nINVALID INPUT\n";
				exit(0);
			}

			cout << "\nPlease enter the second prime number!\n";
			cin >> prime2;

			flag = prime(prime2);
			if (flag == 0 || prime1 == prime2)
			{
				cout << "\nINVALID INPUT\n";
				exit(0);
			}

			number = prime1 * prime2;
			totient = (prime1 - 1) * (prime2 - 1);

			encryption_key();
			cout << "\nPOSSIBLE VALUES OF Public Key AND Private Key ARE\n";

			for (i = 0; i < j - 1; i++)
				cout << "\n"
					 << publicKey[i] << "\t" << privateKey[i];

			cout << "\nYour private key: " << privateKey[0] << "\nDO NOT LOSE IT" << endl;

			printf("\033[0;39m");

			cout << "Enter author: ";
			cin >> auth;
			enc_auth = encrypt(auth);
			dec_auth = decrypt();

			cout << "Enter file type: ";
			cin >> type;
			enc_type = encrypt(type);
			dec_type = decrypt();

			cout << "What would you like to write in the file: ";
			cin.ignore();
			getline(cin, content);
			enc_content = encrypt(content);

			dec_content = decrypt();

			cout << "\nEncrypting permissions..." << endl;
			enc_perm = encrypt(perm);
			dec_perm = decrypt();

			(p->nextfile).push_back(addFile(p, nm, enc_auth, enc_content, enc_type, enc_perm));
		}

		// 3. cd .. to go back in path

		else if (v == "cd")
		{

			cin >> qt;
			if (qt == "..")
			{

				p = p->lastfolder;
				dir.pop_back();
			}

			else
			{
				string pass;
				for (x = 0; x < (p->nextfolder).size(); x++)
				{
					if (qt == (p->nextfolder[x])->foldername && p->nextfolder[x]->password != "")
					{
						cout << "The folder is protected using a password.\n Please enter the password to go inside it\n";
						cin.ignore();
						getline(cin, pass);
						if (pass == p->nextfolder[x]->password)
						{
							p = p->nextfolder[x];
							dir.push_back(p->foldername);
							break;
						}
						else
						{
							cout << "Wrong Password entered\n";
							break;
						}
					}
					else if (qt == (p->nextfolder[x])->foldername && p->nextfolder[x]->password == "")
					{
						p = p->nextfolder[x];
						dir.push_back(p->foldername);
						break;
					}
					if (x == (p->nextfolder).size())
						cout << "Directory not found\n";
				}
			}
		}

		// 4. ls command to display all content present in the current folder

		else if (v == "ls")
		{

			// changing color to red bold

			printf("\033[0;34m");
			printf("\033[1m");

			for (x = 0; x < (p->nextfolder).size(); x++)
				cout << setw(10) << left << " " << p->nextfolder[x]->foldername << endl;
			printf("\033[0;31m");
			printf("\033[1m");

			for (x = 0; x < (p->nextfile).size(); x++)
				cout << setw(10) << left << " " << p->nextfile[x]->filename << endl;

			printf("\033[0;39m");
			printf("\033[0m");
		}

		// fileinfo command to list metadata
		else if (v == "fileinfo")
		{

			cin >> qt;
			cout << "Showing File info\n\n";

			string keytodecrypt;
			printf("\033[0;92m");
			cout << "\n*******This is a secure file system*****\n"
				 << endl;
			cout << "Please enter the private key: ";
			cin.ignore();
			getline(cin, keytodecrypt);
			printf("\033[0;39m");

			for (x = 0; x < (p->nextfile).size(); x++)
			{

				if (p->nextfile[x]->filename == qt && keytodecrypt == to_string(privateKey[0]))
				{
					cout << setw(10) << left << "Author: " << dec_auth << endl;
					cout << setw(10) << left << "Permissions: " << dec_perm << endl;
					cout << setw(10) << left << "Type: " << dec_type << endl;
					break;
				}
			}
		}

		// rename
		else if (v == "rename")
		{

			cin >> qt;
			string newname;

			string keytoread;
			printf("\033[0;92m");
			cout << "\n*******This is a secure file system*****\n"
				 << endl;
			cout << "Please enter the private key: ";
			cin.ignore();
			getline(cin, keytoread);

			for (x = 0; x < (p->nextfile).size(); x++)
			{
				if (p->nextfile[x]->filename == qt && keytoread == to_string(privateKey[0]))
				{
					printf("\033[0;39m");

					// cout<<"Author: "<<p->nextfile[x]->author<<endl;
					cout << "Current file name: " << p->nextfile[x]->filename << endl;
					cout << "Enter new file name: \n";
					// cin.ignore();
					getline(cin, newname);
					p->nextfile[x]->filename = newname;
					break;
				}
			}
		}

		// read command to read the contents of the file
		else if (v == "read")
		{

			cin >> qt;
			cout << "Showing File content...\n";

			string keytoread;
			printf("\033[0;92m");
			cout << "\n*******This is a secure file system*****\n"
				 << endl;
			cout << "Please enter the private key: ";
			cin.ignore();
			getline(cin, keytoread);
			printf("\033[0;39m");

			for (x = 0; x < (p->nextfile).size(); x++)
			{

				if (p->nextfile[x]->filename == qt && keytoread == to_string(privateKey[0]))
				{

					// cout<<"Author: "<<p->nextfile[x]->author<<endl;
					cout << "Content:\n\n"
						 << dec_content << endl;
					break;
				}
			}
		}

		// 6. rm -rf command to remove the folder

		else if (v == "rm")
		{

			cin >> qt;

			if (qt != "-rf")
			{
				cin >> qt;
				cout << "Please check your command and try again\n";
				break;
			}

			cin >> qt;
			for (x = 0; x < (p->nextfolder).size(); x++)
			{

				if (qt == p->nextfolder[x]->foldername && p->nextfolder[x]->password == "")
				{

					(p->nextfolder).erase((p->nextfolder).begin() + x);
					break;
				}
				else
				{
					cout << "Enter password: ";
					string pass;
					cin.ignore();
					getline(cin, pass);

					if (pass == p->nextfolder[x]->password)
					{

						(p->nextfolder).erase((p->nextfolder).begin() + x);
					}
					else
					{
						cout << "Operation failed!!! wrong password!!!\n";
					}
					break;
				}
			}
		}

		// 7. del command to delete the given file

		else if (v == "del")
		{

			cin >> qt;

			for (x = 0; x < (p->nextfile).size(); x++)
			{

				if (qt == p->nextfile[x]->filename)
				{

					(p->nextfile).erase((p->nextfile).begin() + x);
					break;
				}
			}
		}

		// help command lists all the available commands

		else if (v == "help")
		{

			printf("\033[0;96m");
			printf("\033[1m");

			cout << setw(20) << left << "help"
				 << "to display all the functions\n";
			cout << setw(20) << left << "mkdir"
				 << "to create a directory\n";
			cout << setw(20) << left << "create"
				 << "to create a new file\n";
			cout << setw(20) << left << "cd .."
				 << "to go back\n";
			cout << setw(20) << left << "ls"
				 << "to list all the contents of the directory\n";
			cout << setw(20) << left << "read"
				 << "to read the contents of the file\n";
			cout << setw(20) << left << "fileinfo"
				 << "to show the info of the file\n";
			cout << setw(20) << left << "rm -rf"
				 << "to remove the folder\n";
			cout << setw(20) << left << "del"
				 << "to delete the file\n";
			cout << setw(20) << left << "exit"
				 << "to exit the file system\n";

			printf("\033[0;39m");
			printf("\033[0m");
		}

		else if (v == "exit")
		{
			break;
		}

		else
		{

			cout << "Command match not found\n";
			cout << "Try 'help' command\n";
		}
	}
}

int prime(long int pr)
{
	int i;
	j = sqrt(pr);
	for (i = 2; i <= j; i++)
	{
		if (pr % i == 0)
			return 0;
	}
	return 1;
}

long int cd(long int a)
{
	long int k = 1;
	while (1)
	{
		k = k + totient;
		if (k % a == 0)
			return (k / a);
	}
}

// function to generate encryption key
void encryption_key()
{
	int k;
	k = 0;
	for (i = 2; i < totient; i++)
	{
		if (totient % i == 0)
			continue;
		flag = prime(i);
		if (flag == 1 && i != prime1 && i != prime2)
		{
			publicKey[k] = i;
			flag = cd(publicKey[k]);
			if (flag > 0)
			{
				privateKey[k] = flag;
				k++;
			}
			if (k == 99)
				break;
		}
	}
}

// function to encrypt the message
string encrypt(string input)
{
	clock_t t = clock();
	for (i = 0; m[i] != NULL; i++)
	{
		m[i] = NULL;
	}

	for (i = 0; input[i] != NULL; i++)
	{
		m[i] = input[i];
	}

	long int pt, ct, key = publicKey[0], k, len;
	i = 0;
	len = strlen(m);

	while (i != len)
	{
		pt = m[i];
		pt = pt - 96;
		k = 1;
		for (j = 0; j < key; j++)
		{
			k = k * pt;
			k = k % number;
		}
		temp[i] = k;
		ct = k + 96;
		en[i] = ct;
		i++;
	}
	en[i] = -1;
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to encrypt.\n", t, ((float)t) / CLOCKS_PER_SEC);
	return string(en);
}

// function to decrypt the message
string decrypt()
{
	clock_t t = clock();
	long int pt, ct, key = privateKey[0], k;
	i = 0;
	while (en[i] != -1)
	{
		ct = temp[i];
		k = 1;
		for (j = 0; j < key; j++)
		{
			k = k * ct;
			k = k % number;
		}
		pt = k + 96;
		m[i] = pt;
		i++;
	}
	m[i] = -1;
	t = clock() - t;
	printf("It took me %d clicks (%f seconds) to decrypt.\n", t, ((float)t) / CLOCKS_PER_SEC);
	return string(m);
}