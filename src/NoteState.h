#pragma once
#include <string>

class Note;

class INoteState
{
public:
	virtual std::string currentState() = 0;

	virtual void next(Note* note) = 0;
	virtual void previous(Note* note) = 0;
};


class DeferredNote :public INoteState
{
public:
	std::string currentState() override;

	void next(Note* note) override;
	void previous(Note* note) override;
};


class ActiveNote : public INoteState
{
public:
	std::string currentState() override;

	void next(Note* note) override;
	void previous(Note* note) override;
};


class CompletedNote :public INoteState
{
public:
	std::string currentState() override;

	void next(Note* note) override;
	void previous(Note* note) override;
};

