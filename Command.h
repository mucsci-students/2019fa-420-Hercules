#pragma once

#include <iostream>

#include "Model.h"

class Command {
public:
  virtual void execute() const = 0;

  static void setModelInstance(Model *instance);

  static const std::vector<std::string> allCommands();

  static const std::string& helpFor(const std::string&)
;
protected:
  static Model *modelInstance;
};

class ErrorCommand : public Command {

public:
  ErrorCommand(std::ostream& where, const std::string &name);

  virtual void execute() const override;

private:
  std::ostream& mWhere;
  std::string mName;
};


class AddClassCommand : public Command {

public:
  AddClassCommand(const std::string &name);

  virtual void execute() const override;

private:
  std::string mName;
};

class EditClassCommand : public Command {

public:
	EditClassCommand(const std::string &oldname, const std::string &name);

	virtual void execute() const override;

private:
	std::string mOldname;
	std::string mName;
};

class DeleteClassCommand : public Command {

public:
	DeleteClassCommand(const std::string &name);

	virtual void execute() const override;

private:
	std::string mName;
};

class AddRelationshipCommand : public Command {
public:
	AddRelationshipCommand(const std::string& parent, const std::string& child, const std::string& type);

	virtual void execute() const override;

private:
	std::string mParent;
	std::string mChild;
	RelationshipType mType;
};

class EditRelationshipCommand : public Command {
public:
	EditRelationshipCommand(const std::string& parent, const std::string& child, const std::string& type);

	virtual void execute() const override;

private:
	std::string mParent;
	std::string mChild;
	RelationshipType mType;
};

class DeleteRelationshipCommand : public Command {
public:
	DeleteRelationshipCommand(const std::string& parent, const std::string& child, const std::string& type);

	virtual void execute() const override;

private:
	std::string mParent;
	std::string mChild;
};

class AddFieldCommand : public Command {
public:
	AddFieldCommand(const std::string& className, const std::string& fieldName, const std::string& fieldType, const std::string& fieldVisibility);

	virtual void execute() const override;

private:
	std::string mclassName, mfieldName, mfieldType, mfieldVisibility;
};

class EditFieldCommand : public Command {
public:
	EditFieldCommand(const std::string& whichAttr, const std::string& className, const std::string& fieldName, const std::string& newValue);

	virtual void execute() const override;

private:
	std::string mclassName, mfieldName, mNewValue, mWhichAttr;
};

class DeleteFieldCommand : public Command {
public:
	DeleteFieldCommand(const std::string& className, const std::string& fieldName);

	virtual void execute() const override;

private:
	std::string mclassName, mfieldName;
};

class AddMethodCommand : public Command {
public:
	AddMethodCommand(const std::string& className, const std::string& methodName, const std::string& methodType, const std::string& methodVisibility);

	virtual void execute() const override;

private:
	std::string mclassName, mmethodName, mmethodType, mmethodVisibility;
};

class EditMethodCommand : public Command {
public:
	EditMethodCommand(const std::string& whichAttr, const std::string& className, const std::string& methodName, const std::string& newValue);

	virtual void execute() const override;

private:
	std::string mclassName, mmethodName, mNewValue, mWhichAttr;
};

class DeleteMethodCommand : public Command {
public:
	DeleteMethodCommand(const std::string& className, const std::string& methodName);

	virtual void execute() const override;

private:
	std::string mclassName, mmethodName;
};

class AddParameterCommand : public Command {
public:
	AddParameterCommand(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& ParameterType);

	virtual void execute() const override;

private:
	std::string mclassName, mmethodName, mParameterName, mParameterType;
};

class EditParameterCommand : public Command {
public:
	EditParameterCommand(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& NewValue, const std::string& WhichAttr);

	virtual void execute() const override;

private:
	std::string mclassName, mmethodName, mParameterName, mNewValue, mWhichAttr;
};

class DeleteParameterCommand : public Command {
public:
	DeleteParameterCommand(const std::string& className, const std::string& methodName, const std::string& ParameterName);

	virtual void execute() const override;

private:
	std::string mclassName, mmethodName, mParameterName;
};

class ListCommand : public Command {
public:
	ListCommand();

	virtual void execute() const override;
};

class HelpCommand : public Command {
public:
  HelpCommand ();

  virtual void execute() const override;

};

class HelpForCommand : public Command {
public:
  HelpForCommand (const std::string &name);

  virtual void execute() const override;

private:
  std::string mName;
};