// HerculesProject.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
#include "Unit-test.cpp"

void RunUnitTest1()
{
	std::cout << "---------------\nRunning test 1...---------------\n\n\n\n";


	UMLObjectsHolder* holder = new UMLObjectsHolder();

	std::cout << "Creating example UMLObjects...\n\n\n";

	std::string before1 = "empty string", before2 = "empty string", after1, after2;
	UMLObject* a = NULL, * b = NULL;

	if (holder->CreateNewClass("Car"))
	{
		std::cout << "Successfully created class" << std::endl;

		a = holder->ReturnPtrToVector()[0];

		std::vector<std::string> testVec;

		a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
		a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
		a->AddMethod(UMLMethod("Drive()", "void", testVec, UMLFieldVisibilityPrivate));
		std::cout << a->ToString() << std::endl << std::endl;
		before1 = a->ToString();

	}
	else
	{
		std::cout << "Unable to create class due to duplicate name" << std::endl;
	}

	if (holder->CreateNewClass("Wheel"))
	{
		std::cout << "Successfully created class" << std::endl;

		b = holder->ReturnPtrToVector()[1];

		std::vector<std::string> testVec;
		testVec.push_back("Dummy param 1");
		testVec.push_back("Dummy param 2");

		b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
		b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
		b->AddMethod(UMLMethod("Rotate()", "unsigned int", testVec, UMLFieldVisibilityPrivate));
		std::cout << b->ToString() << std::endl << std::endl;
		before2 = b->ToString();

	}
	else
	{
		std::cout << "Unable to create class due to duplicate name" << std::endl;
	}

	std::cout << "Saving and destroying these UMLObjects...\n\n\n";

	//save them to file
	SavingLoadingIO::SaveProjectToFile(holder);

	//destory them out of memory
	delete holder;

	std::cout << "Reloading UMLObjects...\n\n\n";

	//load them into memory again
	holder = new UMLObjectsHolder();

	if (SavingLoadingIO::LoadProject(holder))
	{
		std::cout << "Load successful" << std::endl;
	}
	else
	{
		std::cout << "Unable to load" << std::endl;
	}



	std::cout << "Comparing UMLObjects before and after...\n\n\n";

	if (a != NULL)
	{
		a = holder->ReturnPtrToVector()[0];
		std::cout << a->ToString() << std::endl << std::endl;
		after1 = a->ToString();
	}

	if (b != NULL)
	{
		b = holder->ReturnPtrToVector()[1];
		std::cout << b->ToString() << std::endl << std::endl;
		after2 = b->ToString();
	}

	if (before1 == after1)
	{
		std::cout << "UMLObject1 is correct" << std::endl;
	}
	else std::cout << "UMLObject1 is not correct" << std::endl;

	if (before2 == after2)
	{
		std::cout << "UMLObject2 is correct" << std::endl;
	}
	else std::cout << "UMLObject2 is not correct" << std::endl;

	std::cout << "---------------\nTest 1 completed...---------------\n\n\n\n";

}

void RunUnitTest2()
{
	std::cout << "---------------\nRunning test 2...\n---------------\n\n\n\n";

	UMLObjectsHolder* holder = new UMLObjectsHolder();


	UMLObject* a = NULL, * b = NULL;

	if (holder->CreateNewClass("Car"))
	{
		std::cout << "Successfully created class" << std::endl;

		a = holder->ReturnPtrToVector()[0];

		std::vector<std::string> testVec;

		a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
		a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
		a->AddMethod(UMLMethod("Drive()", "void", testVec, UMLFieldVisibilityPrivate));
		std::cout << a->ToString() << std::endl << std::endl;

	}
	else
	{
		std::cout << "Unable to create class due to duplicate name" << std::endl;
	}

	if (holder->CreateNewClass("Wheel"))
	{
		std::cout << "Successfully created class" << std::endl;

		b = holder->ReturnPtrToVector()[1];

		std::vector<std::string> testVec;
		testVec.push_back("Dummy param 1");
		testVec.push_back("Dummy param 2");

		b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
		b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
		b->AddMethod(UMLMethod("Rotate()", "unsigned int", testVec, UMLFieldVisibilityPrivate));
		std::cout << b->ToString() << std::endl << std::endl;

	}
	else
	{
		std::cout << "Unable to create class due to duplicate name" << std::endl;
	}


	if (b != NULL)
	{
		if (holder->EditClassTitle("Car", "Wheel"))
		{
			std::cout << "Rename succeeded.... this should not have worked!\n\n\n";
			std::cout << "TEST 2 FAILED\n\n\n";
		}
		else
		{
			std::cout << "Unable to rename \"Wheel\" to \"Car\", class name already exists\n\n\n";
		}

		std::cout << b->ToString() << std::endl << std::endl;


		if (holder->EditClassTitle("Tire", "Wheel"))
		{
			std::cout << "Rename succeeded....\n\n\n";
		}
		else
		{
			std::cout << "Unable to rename \"Wheel\" to \"Tire\", class name already exists\n\n\n";
			std::cout << "TEST 2 FAILED\n\n\n";
		}

		std::cout << b->ToString() << std::endl << std::endl;
	}
	else
	{
		std::cout << "TEST 2 FAILED\n\n\n";

	}


	std::cout << "---------------\nTest 2 completed...\n---------------\n\n\n\n";
}
