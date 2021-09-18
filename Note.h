#pragma once
#include <ctime>
#include <string>

class Note;

class INoteState
{
public:
	virtual void next(Note* note) = 0;
	virtual void previous(Note* note) = 0;

	virtual void printDate(Note* note) = 0;
};

class Note
{
	INoteState* state = nullptr;

	std::string tag;
	std::string note;
	std::string date;
public:
	Note();
	~Note();

	std::string getTag();
	std::string getNote();
	std::string getDate();
	INoteState* getState();

	void setDateNow(Note* note);

	void create();
	
	void print();

	void setState(INoteState* state);

	
	void next(Note* note);
	void previous(Note* note);

};



class DeferredNote :public INoteState
{
public:
	void printDate(Note* note) override;
	
	void next(Note* note) override;
	void previous(Note* note) override;
};

class ActiveNote : public INoteState
{
public:

	void printDate(Note* note) override;

	void next(Note* note) override;
	void previous(Note* note) override;
};


class CompletedNote :public INoteState
{
public:
	void printDate(Note* note) override;

	void next(Note* note) override;
	void previous(Note* note) override;
};


