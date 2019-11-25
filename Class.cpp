// System includes
#include <iterator>

// Local includes
#include "Class.h"

// Default constructor
Class::Class()
{
}

// Constructor given a name
Class::Class(const std::string &name)
	:mName(name)
{
}

// Changes the name of an existing class to a new given name
void Class::rename(const std::string &newName)
{
    mName = newName;
}

// Returns the name of a class
const std::string &Class::name() const
{
    return mName;
}

// Returns the raw name of a class
const char *Class::rawName() const
{
    return mName.c_str();
}

// Adds a field to the classes' field vector
void Class::addField(const Field &field)
{
    mFields.push_back(field);
}

// Adds a method to the classes' method vector
void Class::addMethod(const Method &method)
{
    mMethods.push_back(method);
}

// Removes a field from the vector of fields at the given index
void Class::removeField(int index)
{
	std::list<Field>::iterator it = mFields.begin();
	std::advance(it, index);
	mFields.erase(it);
}

// Removes a field from the vector of fields after finding its index
void Class::removeField(const std::string &name)
{
    unsigned int index = 0;
    for (auto &i : mFields)
    {
        if (i.name() == name)
        {
			mFields.remove(i);
        }
    }
}

// Removes a method from the vector of methods at the given index
void Class::removeMethod(int index)
{
	std::list<Method>::iterator it = mMethods.begin();
	std::advance(it, index);
	mMethods.erase(it);
}

// Removes a method from the vector of methods after finding its index
void Class::removeMethod(const std::string &name)
{
	std::string temp;

    for (auto &i : mMethods)
    {
		temp = i.name();
        if (temp == name)
        {
			mMethods.remove(i);
        }
    }
}

// Returns a method from the vector of methods given its name
Method &Class::method(const std::string &name)
{
    for (auto &i : mMethods)
    {
		if (i.name() == name)
		{
			return i;
		}
    }
}

// Returns a method from the vector of methods given its name
const Method &Class::method(const std::string &name) const
{
    for (auto &i : mMethods)
    {
		if (i.name() == name)
		{
			return i;
		}
    }
}

// Returns a method from the vector of methods given its index
Method &Class::method(int index)
{
	std::list<Method>::iterator it = mMethods.begin();
	std::advance(it, index);
	return *it;
}

// Returns a method from the vector of methods given its index
const Method &Class::method(int index) const
{
	std::list<Method>::const_iterator it = mMethods.begin();
	std::advance(it, index);
	return *it;
}

// Returns a field from the vector of fields gien its name
Field &Class::field(const std::string &name)
{
    for (auto &i : mFields)
    {
        if (i.name() == name)
            return i;
    }
}

// Returns a field from the vector of fields gien its name
const Field &Class::field(const std::string &name) const
{
    for (auto &i : mFields)
    {
        if (i.name() == name)
            return i;
    }
}

// Returns a field from the vector of fields gien its index
Field &Class::field(int index)
{
	std::list<Field>::iterator it = mFields.begin();
	std::advance(it, index);
	return *it;
}

// Returns a field from the vector of fields gien its index
const Field &Class::field(int index) const
{
	std::list<Field>::const_iterator it = mFields.begin();
	std::advance(it, index);
	return *it;
}

bool operator== (const Method &n1, const Method &n2)
{
	return n1.name() == n2.name();
}

bool operator== (const Field &n1, const Field &n2)
{
	return n1.name() == n2.name();
}

bool operator== (const Class &n1, const Class &n2)
{
	return n1.name() == n2.name();
}