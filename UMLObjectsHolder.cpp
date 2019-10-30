#include "UMLObjectsHolder.h"
// Creates a constructor
UMLObjectsHolder::UMLObjectsHolder()
{
}
// Allows a new class using title as primary key
UMLObject * UMLObjectsHolder::CreateNewClass(std::string title)
{
	if (IsTitleUnique(title))
	{
		//std::cout << "Creating Class: " << title << std::endl;
		UMLObject* a = new UMLObject();
		a->SetTitle(title);
		UMLObjects_holder.push_back(a);
		return a;
	}
	else
	{
		//std::cout << "Duplicate name detected" << std::endl;
		return 0;
	}
}

bool UMLObjectsHolder::IsTitleUnique(std::string in)
{
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == in) return false;
	}
	return true;
}
// Destructor
UMLObjectsHolder::~UMLObjectsHolder()
{
	for (auto i : UMLObjects_holder)
	{
		delete i;
	}
}

void UMLObjectsHolder::ClearProject()
{
	for (auto i : UMLObjects_holder)
		delete i;
  
  UMLObjects_holder.clear();
}

void UMLObjectsHolder::UMLObjectPrintTitles()
{
	int count = 1;

	for (auto i : UMLObjects_holder)
	{
		std::cout << count << ". " << i->ReturnTitle() << std::endl;
		++count;
	}
}

void UMLObjectsHolder::UMLObjectPrintContents()
{
	for (auto i : UMLObjects_holder)
		std::cout << i->ToString() << std::endl;
}

std::vector<std::string> UMLObjectsHolder::UMLObjectReturnTitles()
{
	std::vector<std::string> out;
	for (auto  i : UMLObjects_holder)
	{
		out.push_back(i->ToString());
	}
	return out;
}

std::vector<std::string> UMLObjectsHolder::UMLObjectReturnTitlesString()
{
	std::vector<std::string> out;
	for (auto& i : UMLObjects_holder)
	{
		out.push_back(i->ReturnTitle());
	}
	return out;
}

std::vector<UMLObject*> UMLObjectsHolder::ReturnPtrToVector()
{
	return UMLObjects_holder;
}

void UMLObjectsHolder::AddUMLObject(UMLObject* in)
{
	if (in != NULL) UMLObjects_holder.push_back(in);
}

bool UMLObjectsHolder::DeleteUMLObject(std::string title)
{
	for (unsigned int i = 0; i < UMLObjects_holder.size(); i++)
	{
		if (UMLObjects_holder[i]->ReturnTitle() == title)
		{
		  for (auto j : UMLObjects_holder)
		  {
		    size_t del = j->GetIndexRelationshipWith(title);
		    if (del != -1)
		      j->DeleteRelationship(del);
		  }
		  
			UMLObjects_holder.erase(UMLObjects_holder.begin() + i);
			return true;
		}
	}
	return false;
}

size_t UMLObjectsHolder::Size()
{
	return UMLObjects_holder.size();
}

bool UMLObjectsHolder::EditClassTitle(std::string new_title, std::string old_title)
{
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == new_title) return false;
	}
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == old_title)
		{
			i->SetTitle(new_title);
			return true;
		}
	}
	return false;
}

bool UMLObjectsHolder::AddRelationship(std::string parent, std::string child, int type, int quantifier1, int quantifier2)
{
	UMLObject* p, * c;

	p = GetUMLObject(parent);
	c = GetUMLObject(child);

	if (p == 0 || c == 0) return false;

	if (p->GetIndexRelationshipWith(child) != -1 || c->GetIndexRelationshipWith(parent) != -1) return false;

	p->AddRelationship({ type, quantifier1, c, p, true});
	c->AddRelationship({ type, quantifier2, p, c, false});

	return true;
}

bool UMLObjectsHolder::EditRelationship(std::string parent, std::string child, int type, int quantifier1, int quantifier2)
{
	UMLObject* p, * c;

	p = GetUMLObject(parent);
	c = GetUMLObject(child);

	if (p == 0 || c == 0) return false;

	if (p->GetIndexRelationshipWith(child) == -1 || c->GetIndexRelationshipWith(parent) == -1) return false;

	p->UpdateRelationship(p->GetIndexRelationshipWith(child), type, quantifier1);
	c->UpdateRelationship(c->GetIndexRelationshipWith(parent), type, quantifier2);
	return true;
}

bool UMLObjectsHolder::DeleteRelationship(std::string parent, std::string child)
{
	UMLObject* p, * c;

	p = GetUMLObject(parent);
	c = GetUMLObject(child);

	if (p == 0 || c == 0) return false;

	if (p->GetIndexRelationshipWith(child) == -1 || c->GetIndexRelationshipWith(parent) == -1) return false;

	p->DeleteRelationship(p->GetIndexRelationshipWith(child));
	c->DeleteRelationship(c->GetIndexRelationshipWith(parent));
	return true;
}

void UMLObjectsHolder::RefreshRelationships()
{
	UMLRelationship* a, * b;
	for (auto i : UMLObjects_holder)
	{
		for (auto j : UMLObjects_holder)
		{
			a = i->GetRelationshipWith(j->ReturnTitle());
			if (a)
			{
				b = j->GetRelationshipWith(i->ReturnTitle());
				EditRelationship(i->ReturnTitle(), j->ReturnTitle(), a->type, a->quantifier, b->quantifier);
			}
		}
	}
}

UMLObject* UMLObjectsHolder::GetUMLObject(std::string title)
{
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == title) return i;
	}
	return 0;
}

int UMLObjectsHolder::GetRelationshipTypeFromString(std::string in)
{
	int result = 0;
	if (in.size() == 0) return result;
	std::transform(std::cbegin(in), std::cend(in), std::begin(in), [](const unsigned char i) { return std::tolower(i); });
	if (in[0] == 'a') result = RelationshipAggregation;
	else if (in[0] == 'c') result = RelationshipComposition;
	else if (in[0] == 'g') result = RelationshipGeneralization;
	else if (in[0] == 'r') result = RelationshipRealization;
	return result;
}