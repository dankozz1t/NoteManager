#pragma once
#include <ctime>
#include <string>

class Note;

class INoteState
{
public:
	virtual void next(Note* note) = 0;
	virtual void previous(Note* note) = 0;

	virtual std::string printDate(Note * note) = 0;
	virtual std::string currentState() = 0;
};

class Note
{
	INoteState* state = nullptr;
	tm date;

	std::string tag;
	std::string note;

	bool important;

public:

	void Load();
	void Save(int i);

	void create();

	bool isImportant();
	void markAsImportant();
	
	//void printDate();
	std::string printDateS();

	std::string print();
	std::string printCompr();

	tm getDate();
	std::string getTag();
	std::string getNote();

	void setDate();
	void setNote();
	void setTag();

	void setState(INoteState* state);
	std::string currentState();


	void next(Note* note);
	void previous(Note* note);
};



class DeferredNote :public INoteState
{
public:
	std::string  printDate(Note* note) override;
	std::string currentState() override;

	void next(Note* note) override;
	void previous(Note* note) override;
};

class ActiveNote : public INoteState
{
public:
	std::string  printDate(Note* note) override;
	std::string currentState() override;

	void next(Note* note) override;
	void previous(Note* note) override;
};


class CompletedNote :public INoteState
{
public:
	std::string  printDate(Note* note) override;
	std::string currentState() override;

	void next(Note* note) override;
	void previous(Note* note) override;
};


