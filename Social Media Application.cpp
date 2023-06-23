#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<class myClass>
static void Deallocation(myClass** List, int total) {
	for (int i = 0; i < total; i++)
		delete List[i];
	delete[]List;
}
class Activity;
class Post;
class Facebook;
class Object;
class User;
class Comment;
class Page;
class Helper {
public:
	static int StrLen(char* str) {
		int stringlen = 0;
		for (char* temp = str; *temp != '\0'; temp++)
			stringlen++;

		return stringlen;
	}
	static char* GetStringFromBuffer(char* buffer) {

		int strlen = StrLen(buffer);
		char* str = 0;

		if (strlen > 0)
		{
			str = new char[strlen + 1];
			char* tempdest = str;

			for (char* tempsrc = buffer; *tempsrc != '\0'; )
			{
				*tempdest++ = *tempsrc++;
			}
			*tempdest = '\0';
		}
		return str;
	}
	static bool isEqual(char* arr1, const char* arr2) {
		int i = 0;
		while (arr2[i] != '\0') {
			if (arr1[i] != arr2[i]) {
				return 0;
			}
			i++;
		}
		return true;
	}
	static char* int_to_char(int num) {
		int count = 0;
		int n = num, inc = 10;

		while (n != 0) {
			n /= 10;
			count += 1;

		}
		char* arr = new char[count + 1];
		int i;
		for (i = count - 1; i >= 0; i--) {
			arr[i] = (num % inc) + '0';
			num /= 10;
		}
		arr[count] = '\0';
		return arr;
	}
	static char* Concatenate(char* strOne, char* strTwo) {
		int i, j = 0;
		for (i = 0; strOne[i] != '\0'; i++)
			j++;
		for (i = 0; strTwo[i] != '\0'; i++) {
			strOne[j] = strTwo[i];
			j++;
		}
		strOne[j] = '\0';
		strOne = Helper::GetStringFromBuffer(strOne);
		return strOne;
	}
};
class Object {
private:
	char* ID;
public:
	Object() {
		ID = NULL;
	}
	~Object() {
		if (ID != NULL) {
			delete[] ID;
		}
	}
	virtual void AddPostToTimeline(Post* PTR) {};
	virtual void printName() {};
	virtual void PrintNameOnly() {};
	virtual void SetPost(Post*&) {};
	char* GetID();
	void SetID(char* id) {
		ID = Helper::GetStringFromBuffer(id);
	}
};
char* Object::GetID() {
	return ID;
}
class Date {
private:
	int DAY;
	int MONTH;
	int YEAR;
	static Date Current_Date;
public:
	Date(int D = 0, int M = 0, int Y = 0) {
		DAY = D;
		MONTH = M; 
		YEAR = Y;
	}
	~Date() {}
	void PrintDate() {
		cout << DAY << "/ " << MONTH << "/ " << YEAR << endl;
	}
	void SetDate(int _day, int _month, int _year) {
		DAY = _day;
		MONTH = _month;
		YEAR = _year;
	}
	void ReadDateFromFile(ifstream& filein) {
		filein >> DAY;
		filein >> MONTH;
		filein >> YEAR;
	}
	//----Getters---
	int GetDay() {
		return DAY;
	}
	int GetMonth() {
		return MONTH;
	}
	int GetYear() {
		return YEAR;
	}
	static void SetCurrentDate(int D, int M, int Y) {
		Current_Date.DAY = D;
		Current_Date.MONTH = M;
		Current_Date.YEAR = Y;
	}
	static Date GetCurrentDate() {
		return Current_Date;
	}
	bool operator==(Date rhs) {
		if (DAY == rhs.DAY && MONTH == rhs.MONTH && YEAR == rhs.YEAR)
			return true;
		else
			return false;
	}
};
Date Date::Current_Date;

class Activity {
private:
	int Type;
	char* Val;
public:
	Activity() {
		Type = 0;
		Val = NULL;
	}
	~Activity() {
		if (Val) {
			delete  Val;
		}
	}
	void ReadActivityFromFile(ifstream& filein);
	void ActivityPrint();
};
void Activity::ReadActivityFromFile(ifstream& filein) {
	char buffer[100];
	filein >> Type;
	filein.getline(buffer, 100);
	Val = Helper::GetStringFromBuffer(buffer);
}
void Activity::ActivityPrint() {

	switch (Type) {
	case 1:
		cout << " is Feeling " << Val << endl;
		break;
	case 2:
		cout << " is Thinking About " << Val << endl;
		break;
	case 3:
		cout << " is Making " << Val << endl;
		break;
	case 4:
		cout << " is Celebrating " << Val << endl;
		break;
	default:
		cout << "Invalid; Retry!";
		break;
	}
}

class Comment {
private:
	char* Comnt_ID;
	char* Text;
	Object* CommmentBY;
public:
	Comment() {
		Comnt_ID = NULL;
		Text = NULL;
		CommmentBY = NULL;
	}
	~Comment() {
		if (Comnt_ID)
			delete[] Comnt_ID;
		if (Text)
			delete[] Text;
	}
	void SetID(char* id) {
		Comnt_ID = Helper::GetStringFromBuffer(id);
	}
	void SetText(char* txt) {
		Text = Helper::GetStringFromBuffer(txt);
	}
	void SetCommentBy(Object* User_obj) {
		CommmentBY = User_obj;
	}

	//----------------Getter-----------------------
	char* GetID() {
		return Comnt_ID;
	}
	char* GetText() {
		return Text;
	}
	Object* GetCommentBy() {
		return CommmentBY;
	}
	//--------------------------------------

	void PrintComments() {
		CommmentBY->PrintNameOnly();  //change name to ensure poly
		cout << " wrote : ";
		cout << Text << endl;
	}
};

class Post : public Object {
private:
	int type;
	char* PostID;
	char* text;
	int N_Likes;
	int N_Comments;
	Object* Shared_by;
	Object** Liked_BY;
	Date Shared_Date;
	Comment** Cmnt;
	Activity* Actvty;
public:
	static int Total_Posts;
	Post() {
		type = 0;
		N_Likes = 0;
		N_Comments = 0;
		PostID = NULL;
		text = NULL;
		Actvty = NULL;
		Shared_by = NULL;
		Liked_BY = NULL;
		Cmnt = NULL;
		Cmnt = new Comment * [10];
		for (int i = 0; i < 10; i++) {
			Cmnt[i] = NULL;
		}
	}
	~Post();
	void ReadPostFromFile(ifstream& fin) {
		fin >> type;
		char buffer[100] = { '\0' };
		fin >> buffer;
		PostID = Helper::GetStringFromBuffer(buffer);
		
		Shared_Date.ReadDateFromFile(fin);
		fin.ignore();
		fin.getline(buffer, 100, '\n');
		text = Helper::GetStringFromBuffer(buffer);
		if (type == 2) {
			Actvty = new Activity;
			Actvty->ReadActivityFromFile(fin);
		}
	}

	void SetNoofLikes(int n) {
		N_Likes = n;
	}
	void LikeIncrement() {
		N_Likes++;
	}
	void CommentIncrement() {
		N_Comments++;
	}

	//-----Setter-----
	void SetSharedby(Object* ID_obj) {
		if (Shared_by == NULL) {
			Shared_by = ID_obj;
		}
	}
	void SetLikedBy(Object*& Like) {
			if (Liked_BY == 0){
				Liked_BY = new Object * [10];
				for (int i = 0; i < 10; i++){
					Liked_BY[i] = 0;
				}
			}

			if (N_Likes <= 10)
			{
				for (int i = 0; i < N_Likes; i++)
				{
					if (Liked_BY[i] == NULL){
						if (Liked_BY[i] != Like){
							Liked_BY[i] = Like;
							N_Likes++;
							break;
						}
					}
				}
			}
			else
				cout << "\nMaximum Llikes Have Been Liked\n";
	}
	void SetText(char* mystring) {
		text = Helper::GetStringFromBuffer(mystring);
	}
	void SetComment(Comment*& temp_comment) {
		if (N_Comments <= 10) {
			for (int i = 0; i < 10; i++) {
				if (Cmnt[i] == NULL) {
					Cmnt[i] = temp_comment;
					break;
				}
			}
		}
	}
	void SetDate(Date Date) {
		Shared_Date = Date;
	}
	virtual void SetValues(Post* p_pTR, char* posttext, Object* userPtr, char* ID) {}
	//---Getter
	char* GetID() {
		return PostID;
	}
	Object* GetSharedBy() { //GetPostBY
		return Shared_by;
	}
	Date GetPostDate() {
		return Shared_Date;
	}
	void ViewLikedList() {
		cout << "Post Liked By : \n" << endl;
		for (int i = 0; i < 10; i++)
		{
			if (Liked_BY[i] != nullptr) {
				Liked_BY[i]->printName();
				cout << endl;
			}
		}
	}
	void ViewPost() {
		cout << "--";
		Shared_by->PrintNameOnly();
		if (type == 2) {
			Actvty->ActivityPrint();
		}
		else {
			cout << " shared ";
		}
		cout << " \"" << text << "\"\t";

		Shared_Date.PrintDate();

		for (int i = 0; Cmnt[i] != nullptr; i++) {
			if (Cmnt[i] != 0)
				Cmnt[i]->PrintComments();

		}
	}
	void AddComment(Comment* _comment) {

		for (int i = 0; i < 10; i++) {
			if (Cmnt[i] == NULL) {
				Cmnt[i] = new Comment;
				Cmnt[i]->SetID(_comment->GetID());
				Cmnt[i]->SetText(_comment->GetText());
				Cmnt[i]->SetCommentBy(_comment->GetCommentBy());
				break;
			}
		}
	}
};

Post::~Post() {
	if (PostID)
		delete[] PostID;
	if (text)
		delete[] text;
	if (Shared_by)
		delete Shared_by;
	if (Liked_BY)
		delete Liked_BY;
	if (Actvty)
		delete Actvty;
	if (Cmnt) {
		for (int i = 0; i < 10; i++)
			delete Cmnt[i];
	}
}

int Post::Total_Posts = 0;


class Memory : public Post {
	Post* sharedPost;

public:
	Memory() {
		sharedPost = NULL;
	}

	void SetValues(Post* postptr, char* posttext, Object* userPtr, char* id) {
		sharedPost = postptr,

		this->SetID(id);
		this->SetText(posttext);
		this->SetSharedby(userPtr);
		this->SetDate(Date::GetCurrentDate());
	}
	~Memory() {
		delete sharedPost;
	}

};
class Page : public Object {
private:
	char* pagename;
	Post** Timeline;
	int N_postsSHARED = 0;

public:
	static int total_pages;
	Page();
	~Page();
	void AddPostToTimeline(Post* Ptr) {
		N_postsSHARED++;
		Timeline[N_postsSHARED] = Ptr;
	}
	void SetPost(Post*& newpost) {
		if (N_postsSHARED <= 10) {
			for (int i = 0; i < 10; i++) {

				if (Timeline[i] == NULL) {
					Timeline[i] = newpost;
					break;
				}
			}
		}
		else
			cout << "\nMaximum Posts Have Been Liked\n";
	}
	void printName() {
		cout << GetID() << " -" << pagename;
	}

	void ShowTimeline() {
		cout << pagename << endl << endl;
		for (int i = 0; Timeline[i] != nullptr; i++) {
			Timeline[i]->ViewPost();
			cout << endl;
		}
	}
	void SharedPostIncrement() {
		N_postsSHARED++;
	}
	void PagesINFromFile(ifstream& filein) {
		char buffer[100] = { '\0' };
		filein >> buffer;
		SetID(buffer);
		filein.getline(buffer, 100);
		pagename = Helper::GetStringFromBuffer(buffer);
	}
	//---------Getter()------
	int Getnumofposts() {
		return N_postsSHARED;
	}
	void PrintNameOnly() {
		cout << pagename;
	}
	void ViewPageTimeline();
	void ShowCurrentPost() {
		Date currentdate = Date::GetCurrentDate();
		Date previousdate(currentdate.GetDay() - 1, currentdate.GetMonth(), currentdate.GetYear());
		for (int i = 0; i < 10; i++) {
			if (Timeline[i] == NULL) {
				break;
			}
			else if (Timeline[i]->GetPostDate() == previousdate || Timeline[i]->GetPostDate() == currentdate)
			{
				Timeline[i]->ViewPost();
				cout << endl;
			}
		}
	}
};
void Page::ViewPageTimeline() {
	for (int i = 0; i < N_postsSHARED; i++) {
		cout << pagename << endl;
		if (Timeline[i]) {
			Timeline[i]->ViewPost();
			cout << endl;
		}
	}
}
Page::Page() {
	pagename = NULL;
	N_postsSHARED = 0;
	Timeline = NULL;
	Timeline = new Post * [10];
	for (int i = 0; i < 10; i++) {
		Timeline[i] = new Post;
		Timeline[i] = NULL;
	}
}
Page::~Page() {
	if (pagename) {
		delete[] pagename;
	}
	for (int i = 0; i < N_postsSHARED; i++)
		delete Timeline[i];
	delete[] Timeline;
}
int Page::total_pages = 0;

class User : public Object {
private:
	char* firstname;
	char* lastname;
	User** friendlist;
	Page** likedpages;
	int friendscount;
	int likedpages_count;
	Post** Timeline;
	int N_sharedposts;
public:
	static int T_Users;
	void SetPost(Post*& newpost) {
		if (N_sharedposts <= 10) {
			for (int i = 0; i < 10; i++) {
				if (Timeline[i] == NULL) {
					Timeline[i] = newpost;
					break;
				}
			}
		}
		else {
			cout << endl << "Liked Page Reached to Maximum Capacity" << endl;
		}
	}
	User() {
		firstname = NULL;
		lastname = NULL;
		friendlist = NULL;
		likedpages = NULL;
		friendscount = 0;
		likedpages_count = 0;
		N_sharedposts = 0;
		Timeline = new Post * [12];
		int j = 0;
		for (int i = 0; i < 12; i++) {
			Timeline[i] = nullptr;
		}
	}
	void PagesInFromFile(ifstream&);
	~User() {
		if (firstname != NULL)
			delete[] firstname;
		if (lastname != NULL)
			delete[] lastname;
		if (friendlist != 0)
			delete[]friendlist;
		if (likedpages != 0)
			delete[]likedpages;
		for (int i = 0; i < N_sharedposts; i++)
			if (Timeline[i] != nullptr)
				delete Timeline[i];

		delete[]Timeline;
	}
	//-----Setter------
	void SetTotalFriends(int Ns) {
		friendscount = Ns;
	}
	void SetterTotalLikedPages(int Ns) {
		likedpages_count = Ns;
	}
	void likedPageIncrement() {
		likedpages_count++;
	}
	void SharedPostIncrement() {
		N_sharedposts++;
	}
	int GetTotalFriends() {
		return friendscount;
	}
	int GetLikedPages() {
		return likedpages_count;
	}
	//-----------------

	void printName() {
		cout << firstname << " " << lastname;
	}
	void PrintNameOnly() {
		cout << firstname << " " << lastname;
	}
	void AddPostToTimeline(Post* Ptr) {
		Timeline[N_sharedposts] = Ptr;
		N_sharedposts++;
	}
	void LikePage(Page*& newPage) {
		if (likedpages == 0) {
			likedpages = new Page * [10];
			for (int i = 0; i < 10; i++) {
				likedpages[i] = 0;
			}
		}
		if (likedpages_count <= 10) {
			for (int i = 0; i < likedpages_count; i++) {
				if (likedpages[i] == NULL) {
					likedpages[i] = newPage;
					break;
				}
			}
		}
		else {
			cout << endl << "Maximum Page count has reached" << endl;
		}
	}
	void Allocate_friendlist() {
		friendlist = new User * [friendscount];
		for (int i = 0; i < friendscount; i++) {
			friendlist[i] = new User;
		}
	}
	void AddFriend(User*& newFriend) {

		if (friendlist == 0) {
			friendlist = new User * [10];
			for (int i = 0; i < 10; i++) {
				friendlist[i] = 0;
			}
		}

		if (friendscount <= 10) {
			for (int i = 0; i < friendscount; i++) {
				if (friendlist[i] == NULL) {
					friendlist[i] = newFriend;
					break;
				}
			}
		}
		else {
			cout << endl << "Liked Pages have reached to Max Count" << endl;
		}
	}

	void ViewFriendList() {
		cout << "-----------------------------------------------------------------------------------" << endl;
		this->printName();
		cout << "--Friend List" << endl << endl;
		for (int i = 0; friendlist[i] != NULL; i++) {
			if (friendlist[i]) {
				cout << friendlist[i]->GetID() << " - ";
				friendlist[i]->printName();
				cout << endl;
			}
		}
		cout << endl;
	}

	void ViewPagesList() {
		cout << "------------------------------------------------------------" << endl;
		this->PrintNameOnly();
		cout << "'s Liked Pages" << endl << endl;
		for (int j = 0; j < likedpages_count; j++) {
			if (likedpages[j]) {
				likedpages[j]->printName();
				cout << endl;
			}
		}
	}
	void ShowLikedPages() {
		this->PrintNameOnly();
		cout << " -- Like Pages" << endl << endl;
		for (int i = 0; i < likedpages_count; i++) {
			likedpages[i]->printName();
			cout << endl;
		}
		cout << "-------------------------------------------------------------------------------------------" << endl;

	}
	void ShowTimeline() {
		cout << firstname << " " << lastname << " -TimeLine" << endl << endl;
		int i = 0;
		for (int i = 0; Timeline[i] != NULL; i++) {
			Timeline[i]->ViewPost();
			cout << endl;
		}
	}
	void ViewHome() {
		PrintNameOnly();
		cout << " -Home Page\n" << endl;
		Date currentdate = Date::GetCurrentDate();
		Date previousdate(currentdate.GetDay() - 1, currentdate.GetMonth(), currentdate.GetYear());
		for (int i = 0; i < 10; i++) {
			if (friendlist[i] == nullptr)
				break;
			else {
				for (int j = 0; j < 10; j++) {

					if (friendlist[i]->Timeline[j] == nullptr)
						break;
					else {

						if (friendlist[i]->Timeline[j]->GetPostDate() == currentdate || friendlist[i]->Timeline[j]->GetPostDate() == previousdate) {
							friendlist[i]->Timeline[j]->ViewPost();
							cout << endl;
						}
					}
				}
			}
		}
		for (int i = 0; i < 10; i++) {

			if (likedpages[i] == nullptr)
				break;
			else
				likedpages[i]->ShowCurrentPost();
		}

	}
	void SeeYourMemory() {
		Date current = Date::GetCurrentDate();
		for (int i = 0; i < 10; i++) {
			if (Timeline[i] != nullptr) {
				Date postdate = Timeline[i]->GetPostDate();
				if (current.GetDay() == postdate.GetDay() && current.GetMonth() == postdate.GetMonth() && current.GetYear() > postdate.GetYear()) {
					cout << endl << "We hope you enjoy looking back and sharing your memories on Facebook, from most recent to long ago." << endl << endl;
					cout << "On this Day" << endl;
					cout << current.GetYear() - postdate.GetYear() << " Years ago" << endl;
					Timeline[i]->ViewPost();
				}
			}
		}

	}

};
void User::PagesInFromFile(ifstream& fin) {
	char buffer[80] = { '\0' };
	fin >> buffer;
	SetID(buffer);
	fin >> buffer;
	firstname = Helper::GetStringFromBuffer(buffer);
	fin >> buffer;
	lastname = Helper::GetStringFromBuffer(buffer);
}
int User::T_Users = 0;

class Facebook {
private:
	int totalPG;
	int totalPST;
	int totalUsers;
	int totalComments;
	Page** Pages;
	User** Users;
	Post** Posts;
public:
	Facebook() {
		Users = NULL;
		Pages = NULL;
		totalPG = 0;
		totalPST = 0;
		totalUsers = 0;
		totalComments = 0;
		Posts = NULL;
	}

	void LoadPages(const char* PG_file) {
		ifstream PageInput(PG_file);
		if (PageInput.is_open()) {
			int Pages_totalAdded = 0;
			PageInput >> totalPG;

			Pages = new Page * [totalPG];

			for (int i = 0; i < totalPG; i++) {
				Pages[i] = new Page;
				Pages[i]->PagesINFromFile(PageInput);
			}
			PageInput.close();
		}
		else {
			cout << endl << "File cannot be opened" << endl;
		}
	}
	void LoadData(const char* pgfile, const char* userfile, const char* postfile, const char* commentfile) {
		LoadPages(pgfile);
		LoadUsers(userfile);
		LoadPosts(postfile);
		LoadComments(commentfile);
	}
	User* SearchUserbyID(const char* friendID) {
		for (int i = 0; i < totalUsers; i++) {
			if (Helper::isEqual(Users[i]->GetID(), friendID) == 1) {
				return Users[i];
			}
		}
		return nullptr;
	}
	Page* SearchPagebyID(char* ID_pages) {
		for (int i = 0; i < totalUsers; i++) {
			if (Helper::isEqual(Pages[i]->GetID(), ID_pages) == 1) {
				return Pages[i];
			}
		}
		return nullptr;
	}
	Object* SearchObjectByID(char* id) {
		if (id[0] == 'u') {
			Object* userptr = SearchUserbyID(Helper::GetStringFromBuffer(id));
			return userptr;
		}
		else if (id[0] == 'p') {
			Object* pageptr = SearchPagebyID(Helper::GetStringFromBuffer(id));
			return pageptr;
		}
		else {
			return NULL;
		}
	}
	Post* search_PostById(char* id) {
		for (int i = 0; i < totalPST; i++) {

			if (Helper::isEqual(Posts[i]->GetID(), id)) {
				return Posts[i];				//retuning the object with req ID
			}
		}
		return NULL;
	}
	void ShareMemory(char* postid, char* posttext, User* currentUser) {
		cout << "Command : \tShareMemory(" << postid << "," << posttext << ")" << endl;
		Post* P = search_PostById(postid);
		Post* memoryptr = new Memory;
		char temppostid[7] = "post";
		char* IDtoSet = Helper::Concatenate(temppostid, Helper::int_to_char(totalComments));
		memoryptr->SetValues(P, posttext, currentUser, IDtoSet);
		currentUser->SetPost(memoryptr);
	}
	void Deallocatetemp(char*** tempList, int n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < Users[i]->GetTotalFriends(); j++) {
				delete[]tempList[i][j];
				tempList[i][j] = 0;
			}

		}
		delete[] tempList;
		tempList = 0;
	}
	void LoadUsers(const char* Userfile) {

		ifstream User_Filein(Userfile);
		if (User_Filein.is_open()) {
			User_Filein >> totalUsers;

			Users = new User * [totalUsers];

			char*** friendlist_temp = new char** [totalUsers];
			for (int i = 0; i < totalUsers; i++) {
				Users[i] = new User;
				Users[i]->PagesInFromFile(User_Filein);

				friendlist_temp[i] = new char* [10];

				char buffer[30]{};
				int j = 0;
				while (buffer[0] != '-') {
					User_Filein >> buffer;
					friendlist_temp[i][j++] = Helper::GetStringFromBuffer(buffer);
				}
				Users[i]->SetTotalFriends(j);

				char tempbuffer[30]{};
				while (tempbuffer[0] != '-') {
					User_Filein >> tempbuffer;
					char* idcheck = Helper::GetStringFromBuffer(tempbuffer);
					if (tempbuffer[0] != '-') {
						Page* pagePTR = SearchPagebyID(idcheck);
						Users[i]->likedPageIncrement();
						Users[i]->LikePage(pagePTR);
					}
				}
			}
			User_Filein.close();

			for (int i = 0; i < totalUsers; i++) {
				for (int j = 0; j < Users[i]->GetTotalFriends(); j++) {

					User* userptr = SearchUserbyID(friendlist_temp[i][j]);
					Users[i]->AddFriend(userptr);
				}
			}
			Deallocatetemp(friendlist_temp, totalUsers);
		}
		else {
			cout << "ERROR IN FILE OPENING\n";
		}
	}
	void SetCurrentDate(int d, int m, int y) {
		Date::SetCurrentDate(d, m, y);
		cout << "System Date set to :";
		Date::GetCurrentDate().PrintDate();
	}
	void ShowLikedList(char* postid)
	{
		Post* currentpost = 0;
		currentpost = search_PostById(postid);
		cout << "-------------------------------------------------------------------------------------------" << endl;

		if (currentpost != nullptr)
			currentpost->ViewLikedList();
		else
			cout << "\nPost Not Available" << endl;
	}
	void Run() {
		int day = 15, month = 11, year = 2017;
		cout << "Command :\tSet Current Date To : " << day << " " << month << " " << year << endl;

		SetCurrentDate(day, month, year);

		char User1[] = "u7";
		cout << "\n\nCommand :\tSet Current User To : " << User1 << endl;

		User* currentUser = 0;
		currentUser = SearchUserbyID(User1);
		if (currentUser != 0) {

			currentUser->PrintNameOnly();
			cout << " successfully set as CurrentUser" << endl << endl;


			cout << "\nCommand :\tViewFriendList" << endl;
			cout << "-------------------------------------------------------------------------------------------" << endl;
			currentUser->ViewFriendList();
			cout << "-------------------------------------------------------------------------------------------" << endl;

			cout << "\nCommand :\tViewLikedPages " << endl;
			cout << "-------------------------------------------------------------------------------------------" << endl;
			currentUser->ShowLikedPages();


			cout << "Command : \tView Home\n" << endl;
			cout << "-------------------------------------------------------------------------------------------" << endl;
			currentUser->ViewHome();
			cout << "-------------------------------------------------------------------------------------------" << endl;


			cout << "\nCommand : ViewTimeLine" << endl;
			cout << "-------------------------------------------------------------------------------------------" << endl;
			currentUser->ShowTimeline();


			char Postnum[] = "post5";

			Post* currentpost = 0;
			currentpost = search_PostById(Postnum);
			cout << "-------------------------------------------------------------------------------------------" << endl;

			if (currentpost != 0) {
				cout << "command:\tviewlikedlist(post5)\n";

				currentpost->ViewLikedList();
				cout << "-------------------------------------------------------------------------------------------" << endl;

				cout << "command:\tlikepost(" << Postnum << ")" << endl;

				Object* Current_usernow = currentUser;
				currentpost->SetLikedBy(Current_usernow);
				cout << "command:\tviewlikedlist(post5)\n";
				currentpost->ViewLikedList();
			}
			else {
				cout << "\nPost Not Available" << endl;
			}

			char postid[] = "post4";
			char addcomment[] = "Good Luck For Your Result";
			PostComment(postid, addcomment, currentUser);

			char postid1[] = "post8";
			char addcomment1[] = "Thanks for the wishes.";

			PostComment(postid1, addcomment1, currentUser);

			cout << "-------------------------------------------------------------------------------------------" << endl;

			cout << "Command : \tSee Your Memory" << endl;
			currentUser->SeeYourMemory();

			cout << "-------------------------------------------------------------------------------------------" << endl;
			char Pageid_[] = "p1";
			cout << "command:\tviewpage(" << Pageid_ << ")" << endl;
			Page* Current_Pages = SearchPagebyID(Pageid_);

			if (Current_Pages != 0)
				Current_Pages->ShowTimeline();
			else
				cout << "\nPage Not Found\n";
			cout << "-------------------------------------------------------------------------------------------" << endl;
			char postname[] = "post10";
			char memorytext[] = "\"Never thought I will be specialist in this field…\"";
			ShareMemory(postname, memorytext, currentUser);
			currentUser->ShowTimeline();
		}
		else {
			cout << "\nUser Not Found\n";
		}
		char User2[] = "u11";
		cout << "\n\nCommand :\tSet Current User To : " << User2 << endl;

		User* currentUser2 = 0;
		currentUser2 = SearchUserbyID(User2);
		if (currentUser2 != 0)
		{
			currentUser2->PrintNameOnly();
			cout << "  setted as curent user" << endl << endl;

			cout << "\nCommand : ViewTimeLine" << endl;
			cout << "-------------------------------------------------------------------------------------------" << endl;
			currentUser2->ShowTimeline();
			cout << "-------------------------------------------------------------------------------------------" << endl;

			cout << endl << "Command : \tView Home\n";
			cout << "-------------------------------------------------------------------------------------------" << endl;
			currentUser2->ViewHome();
			cout << "-------------------------------------------------------------------------------------------" << endl;


		}
		else
			cout << User2 << " not found" << endl;

	}

	void LoadPosts(const char* filename) {
		ifstream inPost(filename);
		if (inPost.is_open()) {
			inPost >> totalPST;
			Posts = new Post * [totalPST];
			for (int i = 0; i < totalPST; i++) {
				Posts[i] = new Post;
				Posts[i]->ReadPostFromFile(inPost);
				char buffer[80] = { '\0' };

				inPost >> buffer;

				Object* Ptr = SearchObjectByID(buffer);
				Posts[i]->SetSharedby(Ptr);
				Ptr->SetPost(Posts[i]);

				char likerbuffer[50] = { '\0' };
				//reading likers
				while (likerbuffer[0] != '-') {
					inPost >> likerbuffer;

					Object* likerptr = SearchObjectByID(likerbuffer);
					Posts[i]->LikeIncrement();
					Posts[i]->SetLikedBy(likerptr);
				}
			}
			inPost.close();
		}
		else {
			cout << "ERROR IN FILE OPENING\n";
		}
	}
	void CommentIncrement() {
		totalComments++;
	}
	void PostComment(char* postid, char* commenttext, User* userptr) {
		cout << "-------------------------------------------------------------------------------------------" << endl;

		cout << "command:\tpostcomment(" << postid << ", " << commenttext << ")" << endl;

		Facebook::CommentIncrement();

		Comment* commentptr = new Comment;
		char tempid[4] = "c";
		commentptr->SetID(Helper::Concatenate(tempid, Helper::int_to_char(totalComments)));
		commentptr->SetText(commenttext);
		commentptr->SetCommentBy(userptr);
		Post* postcommentptr = search_PostById(postid);
		postcommentptr->AddComment(commentptr);
		delete commentptr;
		cout << endl;
		postcommentptr->ViewPost();

	}

	void LoadComments(const char* filename) {
		ifstream inComment(filename);

		if (inComment.is_open()) {
			inComment >> totalComments;
			char buffer[100] = { '\0' };
			char buffer2[30] = { '\0' };

			for (int i = 0; i < totalComments; i++) {
				Comment* commentptr = new Comment;

				inComment >> buffer;
				commentptr->SetID(Helper::GetStringFromBuffer(buffer));
				inComment >> buffer;
				Post* ptr = search_PostById(Helper::GetStringFromBuffer(buffer));

				ptr->SetComment(commentptr);
				ptr->CommentIncrement();
				inComment >> buffer2;

				Object* commentbyPTR = SearchObjectByID(Helper::GetStringFromBuffer(buffer2));
				commentptr->SetCommentBy(commentbyPTR);

				inComment.getline(buffer, 100);
				commentptr->SetText(Helper::GetStringFromBuffer(buffer));
			}
		}
		else
			cout << "\nError in opening comments file\n";
	}
	~Facebook() {
		Deallocation(Pages, totalPG);
		Deallocation(Users, totalUsers);
	}
};

int main() {
	Facebook FBook;
	FBook.LoadData("Pages.txt", "User.txt", "Posts.txt", "Comments.txt");
	FBook.Run();
}