#pragma once
#include<mutex>

class User
{
	//1000
};

class UserManager
{
public:
	static UserManager* Instance()
	{
		static UserManager instance;
		return &instance;
	}

	User* GetUser(int32 id)
	{
		lock_guard<mutex> guard(_mutex);
		//¹º°¡¸¦ °®°í ¿È
		return nullptr;
	}

	void ProcessSave();

private:
	mutex _mutex;
};

