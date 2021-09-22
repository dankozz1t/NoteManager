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

	void create();

	bool isImportant();
	void markAsImportant();
	
	void printDate();
	std::string printDateS();

	void print();
	std::string printS();

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
	void printDate(Note* note) override;
	std::string currentState() override;

	void next(Note* note) override;
	void previous(Note* note) override;
};

class ActiveNote : public INoteState
{
public:
	void printDate(Note* note) override;
	std::string currentState() override;

	void next(Note* note) override;
	void previous(Note* note) override;
};


class CompletedNote :public INoteState
{
public:
	void printDate(Note* note) override;
	std::string currentState() override;

	void next(Note* note) override;
	void previous(Note* note) override;
};


