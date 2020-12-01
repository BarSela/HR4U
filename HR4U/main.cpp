#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WHITE "\033[0m"    //color reset to white
#define BLOCKCOLOR "\033[1;100;30m" //block of color
#include <stdlib.h>
#include <iostream>
#include <json.hpp>
#include <jsoncons_ext/jmespath/jmespath.hpp>
#include <jsoncons_ext/jsonpath/jsonpath.hpp>
#include <jsoncons_ext/jsonpointer/jsonpointer.hpp>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <json/value.h>
#include <json/writer.h>
#include <windows.h>


using namespace jsoncons::jsonpointer;
using namespace jsoncons::jsonpath;
using namespace jsoncons;
using namespace std;
using std::cout;
using std::cin;

//declarations:
char GenRand();
string GenRandomChars(int n);
void Logo();
void changeColor(int desiredColor);
void print_title(string title);
void Login();
void write_to_file(json jsonf, string path);
bool check_card(string credit_card);
bool check_phone(string phone);
bool check_email(string email);
void Edit_Account(string user_id);
bool Employer_Check_Availability(string employee_id);
void Employer_Edit_Account(string user_id);
void Manager_Edit_Employee(string employee_id);
void Employee_Inquiries_Menu(string employee_id);
void Employee_All_Inquiries(string employee_id);
void Employee_Add_Inquiries(string employee_id);
void Employee_Menu(string employee_id);
void Manager_Menu(string manager_id);
void Employer_Menu(string employer_id);
void Manage_Inquiries_Status();
//dont forget to declar


//*************************************************************************************************************
static const char alphnum[] = "0123456789" "!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
int strLen = sizeof(alphnum) - 1;
char GenRand()
{
	return alphnum[rand() % strLen];
}
string GenRandomChars(int n)
{
	int c = 0, s = 0;
	srand(time(0));
N:
	char C;
	string password;
	for (int z = 0; z < n; z++)
	{
		C = GenRand();
		password += C;
		if (isdigit(C))
		{
			c++;
		}
		if (C == '!' || C == '@' || C == '$' || C == '%' || C == '^' || C == '&' || C == '*' || C == '#')
		{
			s++;
		}
	}
	if (n > 2 && (s == 0 || c == 0))
	{
		goto N;
	}
	return password;
}
//************************************************************************************************************
void Logo()
{
	system("color 9");
	cout << endl;
	cout << "                           #     #       # # # #         #       #       #       # " << endl;
	cout << "                           #     #       #      #        #       #       #       # " << endl;
	cout << "                           #     #       #      #        #       #       #       # " << endl;
	cout << "                           # # # #       # # # #         # # # # #       #       # " << endl;
	cout << "                           #     #       #     #                 #       #       # " << endl;
	cout << "                           #     #       #      #                #       #       # " << endl;
	cout << "                           #     #       #       #               #        # # # #  " << endl;
	cout << endl;
}
//**************************************************************************************************************
void changeColor(int desiredColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);

}
void print_title(string title)
{
	for (int i = 0; title[i] != '\0'; i++)
	{
		if (title[i] == ' ')
			cout << " ";
		if (title[i] != ' ')
			cout << title[i];
		changeColor(i + 1);
	}
	cout << endl;
	cout << BLOCKCOLOR << "             " << WHITE << endl;
}

//*******************************************************************************************************************
void Login()
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);

	int choice, choice1 = 1;
	string user_name, password;
	string security_ans[3];
	bool all_answer_right = true;
	bool flag ;

	do
	{
		cout << endl;
		cout << "Please enter your choice:" << endl;
		cout << "1.Login with username and password" << endl;
		cout << "2.Forgot user name/password?" << endl;
		cout << "3.New here? register  as employer" << endl;
		cout << "4.exit" << endl;
		cin >> choice;


		switch (choice)
		{
		case 1:
			do
			{
				flag = false;
				cout << "Enter user name: " << endl;
				cin >> user_name;
				cout << "Enter password: " << endl;
				cin >> password;
				for (std::size_t i = 0; i < alldata.size(); ++i)
				{
					json& data = alldata[i];
					if (contains(data, "/user name/"))
					{
						if (data["user name"] == user_name)
						{
							if (data["password"] == password)
							{
								system("color 2");
								string user_id = data["id"].as_string();
								if (data["type"] == "employee")
								{
									cout << endl << "#########################################################" << endl << endl;
									cout << endl << "welcome  " << data["first name"] << endl << endl;

									Employee_Menu(user_id);
								}
								if (data["type"] == "manager")
								{
									cout << endl << "#########################################################" << endl << endl;
									cout << endl << "welcome  " << data["first name"] << endl << endl;
									Manager_Menu(user_id);
								}
								if (data["type"] == "employer")
								{
									cout << endl << "#########################################################" << endl << endl;
									cout << endl << "welcome  " << data["first name"] << endl << endl;
									Employer_Menu(user_id);
								}
								flag = true;
								break;
							}
							else
							{
								system("color 4");
								cout << "Incorrect  password" << endl;
								cout << "1.try again" << endl;
								cout << "2.back" << endl;
								cin >> choice1;
								system("color 9");
								if (choice1 != 1 && choice1 != 2)
								{
									do
									{
										cout << "Invalid value. Please try again. Enter your choice: 1 or 2." << endl;
										cin >> choice1;
									} while (choice1 != 1 && choice1 != 2);
									
								}
								flag = true;
								break;
							}
							
						}
					}
				}
				if (flag == false)
				{
					system("color 4");
					cout << endl << "Incorrect user name" << endl;
					cout << "1.try again" << endl;
					cout << "2.back" << endl;
					cin >> choice1;
					system("color 9");
					if (choice1 != 1 && choice1 != 2)
					{
						do
						{
							cout << "Invalid value. Please try again. Enter your choice: 1 or 2." << endl;
							cin >> choice1;
						} while (choice1 != 1 && choice1 != 2);
					}
				}
			} while (choice1 == 1);
			break;
		case 2:
			cout << "Please answer to your security questions " << endl;
			cout << "1.What is your mother`s name?" << endl;
			cin >> security_ans[0];
			cout << "2.What is your date of birth?(format:XX.XX.XXXX)" << endl;
			cin >> security_ans[1];
			cout << "3.What's your main hobby?" << endl;
			cin >> security_ans[2];
			for (std::size_t i = 0; i < alldata.size(); ++i)
			{
				json& data = alldata[i];
				for (int i = 0;i < 3;i++)
				{
					if (data["reset password details"][i] != security_ans[i])
					{
						all_answer_right = false;
					}
				}
				if (all_answer_right)
				{
					string new_user_name = data["first name"].as_string() + GenRandomChars(2);
					string new_password = GenRandomChars(8);
					cout << endl << "You answered all the questions correctly" << endl << "your new username and password: " << endl << endl;
					cout << "user name: " << new_user_name << endl;
					cout << "password: " << new_password << endl;
					std::error_code ec;
					jsonpointer::replace(data, "/user name", json(new_user_name), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates user name 
					}
					jsonpointer::replace(data, "/password", json(new_password), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates user name 
					}

				}
				else
				{
					cout << "You answered one of the questions incorrectly" << endl << "You are returned to the login screen " << endl;
				}
				break;

			}

			break;
		case 3:

			//add new employer
			break;
		case 4:
			cout << "Thank you for using HR4U!" << endl << "bye bye" << endl;
			break;
		default:
			cout << "Invalid value. Please try again. Enter your choice: 1-4." << endl;
			cin >> choice;
			break;
		}
	} while (choice != 4);

}

//READ&WRITE FILE **********************************************************************************************//

void write_to_file(json jsonf, string path) //**FUNCTION FOR RE-WRITING THE FILE (with all changes&updates) **//
{
	ofstream db;
	db.open(path, std::ofstream::trunc); //destroy the last file,and opens a path
	if (!db.is_open()) {
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	else {
		db << pretty_print(jsonf); //prints to the json file 
		db.close();
	}
}

json read_file() {   //**FUNCTION FOR READING THE FILE (and puts all data from the file into a json object) **//
	std::string path = "./database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return 0;
	}
	json alldata = json::parse(is);
	return alldata;
}

//*******************************************************************************************************************
//CHECKING functions: credit-card/phone/email details

bool check_card(string credit_card) {
	if (credit_card.length() == 16)
	{
		int counter = 0;
		for (int i = 0; i < credit_card.length(); ++i)
		{
			if (credit_card[i] >= 0 || credit_card[i] <= 9) //checks wether the phone number contains only digits 0-9
				counter++;
		}
		if (counter == 16)
			return true;
	}
	else {
		cout << "credit card number invalid.please enter 16 digits " << endl;
	}
	return false;
}
bool check_phone(string phone) {
	if (phone.length() == 10)
	{
		int counter = 0;
		for (int i = 0; i < phone.length(); ++i)
		{
			if (phone[i] >= 0 || phone[i] <= 9) //checks wether the phone number contains only digits 0-9
				counter++;
		}
		if (counter == 10)
			return true;
	}
	else {
		cout << "phone number invalid.please enter 10 digits phone number" << endl;
	}
	return false;
}
bool check_email(string email) {
	int counter1 = 0, counter2 = 0;
	for (int i = 0; i < email.length(); ++i)
	{
		if (email[i] == '@') //checks wether the phone number contains '@'
			counter1++;
		else if (email[i] == '.') //checks wether the phone number contains '.'
			counter2++;
	}
	if (counter1 == 1 && counter2 >= 1)
		return true;
	else {
		cout << "phone number invalid.please enter 10 digits phone number" << endl;
		return false;
	}
}
//*******************************************************************************************************************

void Edit_Account(string user_id)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i) //runs all objectss
	{
		json& data = alldata[i];
		if (data["id"] == user_id)
		{
			int choice;
			do {
				cout << "Edit Account By Employee:Choose what details would you like to edit:" << endl;
				cout << "1.Edit Adress" << endl;
				cout << "2.Edit Email" << endl;
				cout << "3.Edit Phone number" << endl;
				cout << "4.Edit Emergency contact" << endl;
				cout << "5.Back" << endl;
				cin >> choice;
				switch (choice) {
				case 1:
				{
					//edit adress
					cout << "Enter your new adress:" << endl;
					string newadress;
					cin >> newadress;
					std::error_code ec;
					jsonpointer::replace(data, "/address", json(newadress), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;
				case 2:
				{
					//edit email
					cout << "Enter your new email:" << endl;
					string newemail;
					cin >> newemail;
					while (!check_email(newemail)) //while email is invalid
						cin >> newemail;
					std::error_code ec;
					jsonpointer::replace(data, "/email", json(newemail), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;
				case 3:
				{
					//edit phone-number
					cout << "Enter your new phone number:" << endl;
					string newphone;
					cin >> newphone;
					while (!check_phone(newphone)) //while the phone number is invaild.
						cin >> newphone;

					std::error_code ec;
					jsonpointer::replace(data, "/phone", json(newphone), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;
				case 4:
				{
					//edit emergency contact details
					cout << "Enter your new emergency contact name:" << endl;
					string newname;
					cin >> newname;
					cout << "Enter your new emergency contact pone:" << endl;
					string newphone;
					cin >> newphone;
					while (!check_phone(newphone)) //while the phone number is invaild.
						cin >> newphone;

					std::error_code ec;
					jsonpointer::replace(data, "/emergency contact name", json(newname), ec);
					jsonpointer::replace(data, "/emergency contact phone", json(newphone), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;
				case 5:
					cout << "Back to menu" << endl;
					break;
				default:
					cout << "Invalid value. Please try again. Enter your choice: 1-5." << endl;
					cin >> choice;
				}
			} while (choice != 5);
		}
		break;
	}

}
void Employer_Edit_Account(string user_id)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i) //runs all objectss
	{
		json& data = alldata[i];
		if (data["id"] == user_id)
		{
			int choice;
			do {
				cout << "Edit Account By Employee:Choose what details would you like to edit:" << endl;
				cout << "1.Edit Adress" << endl;
				cout << "2.Edit Email" << endl;
				cout << "3.Edit Phone number" << endl;
				cout << "4.Edit Emergency contact" << endl;
				cout << "5.Edit credit card number" << endl;
				cout << "6.Edit user name" << endl;
				cout << "7.Edit password" << endl;
				cout << "8.Back" << endl;
				cin >> choice;
				switch (choice) {
				case 1:
				{
					//edit adress
					cout << "Enter your new adress:" << endl;
					string newadress;
					cin >> newadress;
					std::error_code ec;
					jsonpointer::replace(data, "/address", json(newadress), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;
				case 2:
				{
					//edit email
					cout << "Enter your new email:" << endl;
					string newemail;
					cin >> newemail;
					while (!check_email(newemail)) //while email is invalid
						cin >> newemail;
					std::error_code ec;
					jsonpointer::replace(data, "/email", json(newemail), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;
				case 3:
				{
					//edit phone-number
					cout << "Enter your new phone number:" << endl;
					string newphone;
					cin >> newphone;
					while (!check_phone(newphone)) //while the phone number is invaild.
						cin >> newphone;

					std::error_code ec;
					jsonpointer::replace(data, "/phone", json(newphone), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;
				case 4:
				{
					//edit emergency contact details
					cout << "Enter your new emergency contact name:" << endl;
					string newname;
					cin >> newname;
					cout << "Enter your new emergency contact pone:" << endl;
					string newphone;
					cin >> newphone;
					while (!check_phone(newphone)) //while the phone number is invaild.
						cin >> newphone;

					std::error_code ec;
					jsonpointer::replace(data, "/emergency contact name", json(newname), ec);
					jsonpointer::replace(data, "/emergency contact phone", json(newphone), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;
				case 5:
				{	//edit phone-number
					cout << "Enter your new credit card number:" << endl;
					string newcard;
					cin >> newcard;
					while (!check_card(newcard)) //while the phone number is invaild.
						cin >> newcard;

					std::error_code ec;
					jsonpointer::replace(data, "/credit card number", json(newcard), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;
				case 6:
				{
					string new_user_name = data["first name"].as_string() + GenRandomChars(2);
					cout << "Your new user name: " << new_user_name << endl;
					std::error_code ec;
					jsonpointer::replace(data, "/user name", json(new_user_name), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates user name 
					}

				}
				break;
				case 7:
				{
					string new_password = GenRandomChars(8);
					cout << "Yuor new password: " << new_password << endl;
					std::error_code ec;
					jsonpointer::replace(data, "/password", json(new_password), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates user name 
					}
				}
				break;
				case 8:
				{
					cout << "Back to employer menu" << endl;
				}
				break;
				default:
					cout << "Invalid value. Please try again. Enter your choice: 1-5." << endl;
					cin >> choice;
				}
			} while (choice != 8);
		}
	}
}

void Employee_Inquiries_Menu(string employee_id) {
	int choice;
	do {
		cout << "****************************************************************" << endl;
		cout << "Inquiries MENU! ADD/ALL" << endl;
		cout << "Enter your choice:" << endl;
		cout << "1.All Inquiries" << endl;
		cout << "2.Add Inquiry" << endl;
		cout << "3.Back" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			Employee_All_Inquiries(employee_id);
			break;
		case 2:
			Employee_Add_Inquiries(employee_id);
			break;
		default:
			cout << "Invalid input.Please try again,Enter your choice 1-3:" << endl;
			cin >> choice;
			break;
		}
	} while (choice != 3);
}

void Manage_Inquiries_Status() {
	std::string path = "./database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];

		if (data["type"] == "employee")
		{
			string employee_id = data["id"].as_string();
			Employee_All_Inquiries(employee_id);
		}
	}
	string employee_id;
	cout << "Enter the id you want to edit:" << endl;
	cin >> employee_id;
	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];

		if (data["id"] == employee_id)
		{
			cout << "Enter the inquiry number you would like to update (by status)" << endl;
			int num;
			string ans;
			cin >> num;
			cout << "Enter your choice (approved/disapproved)" << endl;
			cin >> ans;
			//data["inquiries status"][num] = ans;
			std::error_code ec;
			jsonpointer::replace(data, "/inquiries status", json(ans), ec); //need to chek how we change the specific inq status
			if (ec)
			{
				cout << ec.message() << std::endl;
			}
			else
			{
				write_to_file(alldata, path); //updates inquiries in file
			}
		}


	}

}

void Employee_All_Inquiries(string employee_id) {//the inquires detail has been changed. we need to deside what is the best way.g
	std::string path = "./database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			cout << "ID:" << employee_id << endl;
			if (data["inquiries subject"].size() != 0)
			{
				for (int i = 0; i < data["inquiries subject"].size(); ++i)
				{
					cout << "Inquiry number " << i << ":" << endl;
					cout << "Subject: " << data["inquiries subject"][i] << endl;
					cout << "Body: " << data["inquiries body"][i] << endl;
					cout << "Status: " << data["inquiries status"][i] << endl;
					cout << "-------------------------------------------------" << endl;
				}
			}
			else if (data["inquiries subject"].size() == 0)
			{
				cout << "No inquiries have been found." << endl;
				cout << "-------------------------------------------------" << endl;
			}
		}
	}
}

void Employee_Add_Inquiries(string employee_id)
{
	std::string path = "./database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			int choice;
			do {
				cout << "****************************************************************" << endl;
				cout << "Add inquiries:" << endl;
				cout << "enter your choice:" << endl;
				cout << "1.add new inquiry" << endl;
				cout << "2.back" << endl;
				cin >> choice;
				switch (choice)
				{
				case 1: {
					string body;
					string subject;
					const string status = "in process";
					cout << "please enter your inquiry subject" << endl;
					cin.ignore();
					getline(cin, subject);
					cout << "please specify your inquiry:(up to 250 letters)" << endl;
					cin.ignore();
					getline(cin, body);

					while (subject.length() > 250)
					{
						cout << "your inquiry body is way too long. please try again" << endl;
						cout << "please specify your inquiry:(up to 250 letters)" << endl;
						cin >> body;
					}
					data["inquiries subject"].push_back(subject);
					data["inquiries body"].push_back(body);
					data["inquiries status"].push_back(status);
					cout << "INQUIRY DETAILS SAVED, we`re working on it. thank you." << endl;
					write_to_file(alldata, path);
				}
					  break;
				case 2:
					cout << "thank you.back to inquiries menu" << endl;
					break;
				default:
					cout << "invalid input.please try again.please enter your choice 1-2 only:" << endl;
					break;
				}
			} while (choice != 2);
		}
	}
}

void Manager_Edit_Employee(string employee_id)
{
	std::string path = "./database.json";
	std::fstream is(path);
	if (!is)
	{
		std::cout << "Cannot open " << path << std::endl;
		return;
	}
	json alldata = json::parse(is);

	for (std::size_t i = 0; i < alldata.size(); ++i)
	{
		bool changed = false;
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			changed = true;
			int choice;
			do
			{
				cout << "Please choose which employee details you xant to change :" << endl;
				cout << "1.First Name" << endl;
				cout << "2.Last Name" << endl;
				cout << "3.ID" << endl;
				cout << "4.Hourly Wage" << endl;
				cout << "5.Type" << endl;
				cout << "6.Exit" << endl;
				cin >> choice;

				while (1)
				{
					if (!(choice >= 1 && choice <= 6))
						cout << "Bad input : Enter again , your choise must be between 1 and 6" << endl;
					else
						break;
					cin >> choice;
				}

				switch (choice)
				{
				case 1:
				{
					//edit first name
					cout << "Enter the first name:" << endl;
					string new_first_name;
					cin >> new_first_name;
					std::error_code ec;
					jsonpointer::replace(data, "/first name", json(new_first_name), ec);
					if (ec)
					{
						cout << ec.message() << std::endl;
					}
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;

				case 2:
				{
					//edit last name
					cout << "Enter the last name:" << endl;
					string new_last_name;
					cin >> new_last_name;
					std::error_code ec;
					jsonpointer::replace(data, "/last name", json(new_last_name), ec);
					if (ec)
						cout << ec.message() << std::endl;
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;

				case 3:
				{
					//edit id
					cout << "Enter the new id /:" << endl;
					string new_id;
					cin >> new_id;
					while (1)//while the id is invaild.
					{
						if (new_id.length() == 9)
						{
							int counter = 0;
							for (int i = 0; i < new_id.length(); ++i)
							{
								if (new_id[i] >= '0' && new_id[i] <= '9') //checks wether the id contains only digits 0-9
									++counter;
							}
							if (counter == 9)
								break;
						}
						else
							cout << "ID number invalid.Please enter 9 digits ID:" << endl;
						cin >> new_id;
					}
					std::error_code ec;
					jsonpointer::replace(data, "/id", json(new_id), ec);
					if (ec)
						cout << ec.message() << std::endl;
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;

				case 4:
				{
					//edit hourly wage
					cout << "Enter the new hourly wage:" << endl;
					int new_hourly_wage;
					cin >> new_hourly_wage;
					while (1)
					{
						if (new_hourly_wage <= 0)
							cout << "Bad input : Enter again , hourly wage must be a positve number" << endl;
						else
							break;
						cin >> new_hourly_wage;
					}
					std::error_code ec;
					jsonpointer::replace(data, "/hourly wage", json(new_hourly_wage), ec);
					if (ec)
						cout << ec.message() << std::endl;
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;

				case 5:
				{
					//edit type
					cout << "Enter the new type:" << endl;
					string new_type;
					cin >> new_type;
					std::error_code ec;
					jsonpointer::replace(data, "/type", json(new_type), ec);
					if (ec)
						cout << ec.message() << std::endl;
					else
					{
						write_to_file(alldata, path); //updates the file(actually,re-writes it)! 
						cout << "Data updated successfully ! " << endl;
					}
				}
				break;

				case 6:
					cout << "Good Bye.";
					break;

				default:
					cout << "Invalid value. Please try again. Enter your choice: 1-5." << endl;
					cin >> choice;
				}

			} while (choice != 6); // end of while	
		} // end of "if"

		if (changed)
			break;

	} // end of "for"
} // end of "Manager_Edit_Employee"

void Employee_Menu(string employee_id) {
	int choice;
	do {
		cout << "Employee Menu!" << endl;
		cout << "Please enter your choice:" << endl;
		cout << "1.Edit Account" << endl;
		cout << "2.Salary" << endl;
		cout << "3.Inquiries" << endl;
		cout << "4.History" << endl;
		cout << "5.Exit/Enter shift" << endl;
		cout << "6.EXIT SYSTEM" << endl;
		cin >> choice;
		system("color 9");
		switch (choice) {
		case 1:
			Edit_Account(employee_id);
			break;
		case 2:
			//print history
			break;
		case 3:
			Employee_Inquiries_Menu(employee_id);
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
	} while (choice != 6);
}

void Employer_Menu(string employer_id)
{
	string title = "Employer menu";
	print_title(title);//only for printing colourful title
	int choice;
	do
	{
		cout << "Please enter your choice:" << endl;
		cout << "1. Search & book employees" << endl << "2. Rate employee" << endl << "3. Watch hiring history" << endl << "4. Edit account" << endl << "5. Exit system(back to login screen)" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter your choice:" << endl << "1.Search employee" << endl << "2.Book employee" << endl << "3.Exit" << endl;
			cin >> choice;
			if (choice != 3)
			{
				switch (choice)
				{
				case 1:
					//search employee
					break;
				case 2:
					//book employee
					break;
				default:
					cout << "Wrong choice, try again" << endl;
					cin >> choice;
				}
			}
			break;
		case 2:
			//rate employee
			break;
		case 3:
			//hiring history
			break;
		case 4:
			//Edit_Account(string employer_id)    
			break;
		case 5:
			cout << "Back to login screen" << endl;
			break;
		default:
			cout << "Wrong choice, try again" << endl;
			break;
		}
	} while (choice != 5);
}

void Manager_Menu(string manager_id)
{
	int choice;
	do {
		cout << "Manager Menu!" << endl;
		cout << "Please enter your choice:" << endl;
		cout << "1.Edit your Account" << endl;
		cout << "2.View company statistics" << endl;
		cout << "3.Manage Inquiries" << endl;
		cout << "4.View/edit employee details" << endl;
		cout << "5.Add/Remove employee" << endl;
		cout << "6.EXIT SYSTEM" << endl;
		cin >> choice;
		system("color 9");
		switch (choice) {
		case 1:
			Edit_Account(manager_id);
			break;
		case 2:
			//statistics
			break;
		case 3:
			//Manage Inquiries
			Manage_Inquiries_Status();
			break;
		case 4:
			//View/edit employee details
			break;
		case 5:
			cout << "Enter your choice:" << endl;
			cout << "1.Add employee" << endl;
			cout << "2.Remove employee" << endl;
			cout << "3.Exit" << endl;
			cin >> choice;
			if (choice != 3)
			{
				switch (choice) {
				case 1:
					//add employee
					break;
				case 2:
					//remove employee
					break;
				default:
					cout << "Invalid input.Please try again,Enter your choice 1-3:" << endl;
					cin >> choice;
				}
			}
			break;
		case 6:
			cout << "Back to login screen" << endl;
			break;
		default:
			cout << "Invalid value. Please try again. Enter your choice: 1-6." << endl;
			cin >> choice;
			break;
		}
	} while (choice != 6);
}
//Checking an employee's availability on the selected date 
bool Employer_Check_Availability(string employee_id,string date,string proffesion, int hourly_wage)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);
	
	for (std::size_t i = 0; i < alldata.size(); ++i) //runs all objectss
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			if (data["proffesion"] == proffesion)
			{
				if (data["hourly wage"] == hourly_wage)
				{
					if (Available_Date(employee_id, date))
						return true;

				}
			}
			break;
		}

	}
	return false;

}

bool Available_Date(string employee_id,string date)
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);

	int length=0;
	for (std::size_t i = 0; i < alldata.size(); ++i) //runs all objectss
	{
		json& data = alldata[i];
		if (data["id"] == employee_id)
		{
			length = data["unavailability"].size();
			for (int i = 0;i < length;i++)
			{
				if (data["unavailability"][i] == date)
					return false;
			}
			break;
		}
	}
	return true;
}

void Employer_Search()//not done!!!!!
{
	string path = "./database.json";
	fstream is(path);
	if (!is)
	{
		cout << "Cannot open " << path << endl;
		return;
	}
	json alldata = json::parse(is);
	int hourly_wage, counter = 0;
	string date, proffesion;
	do
	{
		cout << "Please enter selected date: ";
		cin >> date;
		cout << "Enter profession: ";
		cin >> proffesion;
		cout << "Enter employee's maximum hourly wage: ";
		cin >> hourly_wage;
		cout << endl << "Results:" << endl << endl;
		cout << "date: " << date << "      " << "proffesion: " << proffesion << endl << endl;
		cout << "-------------------------------------------------------------------" << endl;
		for (std::size_t i = 0; i < alldata.size(); ++i)
		{
			json& data = alldata[i];
			if (data["type"] == "employee")
			{
				if (Employer_Check_Availability(data["id"].as_string, date, proffesion, hourly_wage))
				{
					cout << data["id"].as_string << "      " << data["first name"].as_string << "      " << data["last name"].as_string << "      " << data["hourly wage"].as_string << endl << endl;
					counter++;
				}
			}
		}
		if (counter != 0)
		{
			cout << "About" << counter << " results";
		}
		else
		{
			cout << "No results were found" << endl;
		}
	} while (true);
	

}

int main() {
	Logo();
	Login();
	return 0;
}

