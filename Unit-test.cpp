#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
#include "REPL.h"

TEST_CASE("Create a Class", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	holder->CreateNewClass("Car");
	UMLObject* a = NULL;
	a = holder->ReturnPtrToVector()[0];
	SECTION("Class Constructor", "0")
	{
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Car");
	}
	delete holder;
}

TEST_CASE("Edit a class", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	holder->CreateNewClass("Car");
	SECTION("Class Constructor", "0")
	{
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Car");
	}

	holder->EditClassTitle("Vehicle", "Car");

	SECTION("Class Rename", "0")
	{
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Vehicle");
	}

	holder->CreateNewClass("Vehicle");

	SECTION("Class Creation Duplicate", "0")
	{
		REQUIRE(holder->Size() == 1);
	}
	delete holder;
}


TEST_CASE("Add multiple classes", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	holder->CreateNewClass("Vehicle");
	holder->CreateNewClass("Tire");

	SECTION("Class Multiples", "0")
	{
		REQUIRE(holder->Size() == 2);
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Vehicle");
		REQUIRE(holder->UMLObjectReturnTitlesString()[1] == "Tire");
	}
	delete holder;
}

TEST_CASE("Add relationship between classes", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	holder->CreateNewClass("Vehicle");
	holder->CreateNewClass("Tire");

	SECTION("Create classes", "0")
	{
		REQUIRE(holder->Size() == 2);
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Vehicle");
		REQUIRE(holder->UMLObjectReturnTitlesString()[1] == "Tire");
	}

	holder->AddRelationship("Vehicle", "Tire", "Composition", "one", "many");

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->ReturnPtrToVector()[0]->ReturnRelationships() == "{{Vehicle is Parent in relationship Composition One-to-Many with Tire}, }");
		REQUIRE(holder->ReturnPtrToVector()[1]->ReturnRelationships() == "{{Tire is Child in relationship Composition Many-to-One with Vehicle}, }");
	}
	delete holder;
}

TEST_CASE("Relationships functionality test multiple relationships on item", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	holder->CreateNewClass("Vehicle");

	for (unsigned int i = 0; i < 4; i++)
	{
		holder->CreateNewClass("Door" + std::to_string(i + 1));
		holder->AddRelationship("Vehicle", "Door" + std::to_string(i + 1), "Composition", "one", "many");

		holder->CreateNewClass("Tire" + std::to_string(i + 1));
		holder->AddRelationship("Vehicle", "Tire" + std::to_string(i + 1), "Composition", "one", "many");
	}

	SECTION("Create classes", "0")
	{
		REQUIRE(holder->Size() == 9);
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Vehicle");
		for (unsigned int i = 0; i < 4; i++)
		{
			REQUIRE(holder->UMLObjectReturnTitlesString()[1+(i*2)] == "Door" + std::to_string(i + 1));
			REQUIRE(holder->UMLObjectReturnTitlesString()[2 + (i*2)] == "Tire" + std::to_string(i + 1));
		}
	}

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->ReturnPtrToVector()[0]->ReturnRelationships() ==   "{{Vehicle is Parent in relationship Composition One-to-Many with Door1}, {Vehicle is Parent in relationship Composition One-to-Many with Tire1}, {Vehicle is Parent in relationship Composition One-to-Many with Door2}, {Vehicle is Parent in relationship Composition One-to-Many with Tire2}, {Vehicle is Parent in relationship Composition One-to-Many with Door3}, {Vehicle is Parent in relationship Composition One-to-Many with Tire3}, {Vehicle is Parent in relationship Composition One-to-Many with Door4}, {Vehicle is Parent in relationship Composition One-to-Many with Tire4}, }");
		for (unsigned int i = 0; i < 4; i++)
		{
			REQUIRE(holder->ReturnPtrToVector()[1 + (i * 2)]->ReturnRelationships() == "{{Door" + std::to_string(i + 1) + " is Child in relationship Composition Many-to-One with Vehicle}, }");
			REQUIRE(holder->ReturnPtrToVector()[2 + (i * 2)]->ReturnRelationships() == "{{Tire" + std::to_string(i + 1) + " is Child in relationship Composition Many-to-One with Vehicle}, }");
		}
	}
	delete holder;
}

TEST_CASE("Relationships edit functionality test", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	holder->CreateNewClass("Vehicle");
	holder->CreateNewClass("Tire");
	holder->CreateNewClass("Door");
	holder->CreateNewClass("Light");
	holder->CreateNewClass("Cylinders");
	holder->CreateNewClass("Engine");
	holder->CreateNewClass("Fleet");
	holder->CreateNewClass("Driver");

	//every one of these must succeed
	REQUIRE((
		holder->AddRelationship("Vehicle", "Tire", "Composition", "one", "many") == ElementSuccess &&
		holder->AddRelationship("Vehicle", "Door", "Composition", "one", "many") == ElementSuccess &&
		holder->AddRelationship("Vehicle", "Light", "Composition", "one", "many") == ElementSuccess &&
		holder->AddRelationship("Vehicle", "Engine", "Composition", "one", "one") == ElementSuccess &&
		holder->AddRelationship("Engine", "Cylinders", "Composition", "one", "many") == ElementSuccess &&
		holder->AddRelationship("Fleet", "Vehicle", "Aggregation", "many", "many") == ElementSuccess &&
		holder->AddRelationship("Driver", "Vehicle", "Realization", "one", "one") == ElementSuccess
	));

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Composition One-to-Many with Tire}, {Vehicle is Parent in relationship Composition One-to-Many with Door}, {Vehicle is Parent in relationship Composition One-to-Many with Light}, {Vehicle is Parent in relationship Composition One-to-One with Engine}, {Vehicle is Child in relationship Aggregation Many-to-Many with Fleet}, {Vehicle is Child in relationship Realization One-to-One with Driver}, }");

		REQUIRE(holder->GetUMLObject("Tire")->ReturnRelationships() == "{{Tire is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Door")->ReturnRelationships() == "{{Door is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Light")->ReturnRelationships() == "{{Light is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Child in relationship Composition One-to-One with Vehicle}, {Engine is Parent in relationship Composition One-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Composition Many-to-One with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{{Fleet is Parent in relationship Aggregation Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{{Driver is Parent in relationship Realization One-to-One with Vehicle}, }");
	}

	//these values might not make sense in the real world, they are just for the purpose of the test
	REQUIRE((
		holder->EditRelationship("Vehicle", "Tire", "Generalization", "many", "many") == ElementSuccess &&
		holder->EditRelationship("Door", "Vehicle", "Realization", "many", "many") == ElementSuccess &&
		holder->EditRelationship("Vehicle", "Light", "Realization", "many", "many") == ElementSuccess &&
		holder->EditRelationship("Cylinders", "Engine", "Realization", "many", "many") == ElementSuccess &&
		holder->EditRelationship("Fleet", "Vehicle", "Realization", "one", "one") == ElementSuccess &&
		holder->EditRelationship("Vehicle", "Driver", "Generalization", "many", "many") == ElementSuccess
		));

	SECTION("Verify relationships after edit", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Generalization Many-to-Many with Tire}, {Vehicle is Parent in relationship Realization Many-to-Many with Door}, {Vehicle is Parent in relationship Realization Many-to-Many with Light}, {Vehicle is Parent in relationship Composition One-to-One with Engine}, {Vehicle is Child in relationship Realization One-to-One with Fleet}, {Vehicle is Child in relationship Generalization Many-to-Many with Driver}, }");

		REQUIRE(holder->GetUMLObject("Tire")->ReturnRelationships() == "{{Tire is Child in relationship Generalization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Door")->ReturnRelationships() == "{{Door is Child in relationship Realization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Light")->ReturnRelationships() == "{{Light is Child in relationship Realization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Child in relationship Composition One-to-One with Vehicle}, {Engine is Parent in relationship Realization Many-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Realization Many-to-Many with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{{Fleet is Parent in relationship Realization One-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{{Driver is Parent in relationship Generalization Many-to-Many with Vehicle}, }");
	}

	holder->DeleteRelationship("Light", "Vehicle");
	holder->DeleteRelationship("Vehicle", "Engine");

	SECTION("Verify relationships after relationship deletion", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Generalization Many-to-Many with Tire}, {Vehicle is Parent in relationship Realization Many-to-Many with Door}, {Vehicle is Child in relationship Realization One-to-One with Fleet}, {Vehicle is Child in relationship Generalization Many-to-Many with Driver}, }");

		REQUIRE(holder->GetUMLObject("Tire")->ReturnRelationships() == "{{Tire is Child in relationship Generalization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Door")->ReturnRelationships() == "{{Door is Child in relationship Realization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Light")->ReturnRelationships() == "{}");
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Parent in relationship Realization Many-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Realization Many-to-Many with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{{Fleet is Parent in relationship Realization One-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{{Driver is Parent in relationship Generalization Many-to-Many with Vehicle}, }");
	}

	delete holder;
}

TEST_CASE("Relationships composite delete functionality test", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	holder->CreateNewClass("Vehicle");
	holder->CreateNewClass("Tire");
	holder->CreateNewClass("Door");
	holder->CreateNewClass("Light");
	holder->CreateNewClass("Cylinders");
	holder->CreateNewClass("Engine");
	holder->CreateNewClass("Fleet");
	holder->CreateNewClass("Driver");

	//every one of these must succeed
	REQUIRE((
		holder->AddRelationship("Vehicle", "Tire", "Composition", "one", "many") == ElementSuccess &&
		holder->AddRelationship("Vehicle", "Door", "Composition", "one", "many") == ElementSuccess &&
		holder->AddRelationship("Vehicle", "Light", "Composition", "one", "many") == ElementSuccess &&
		holder->AddRelationship("Vehicle", "Engine", "Composition", "one", "one") == ElementSuccess &&
		holder->AddRelationship("Engine", "Cylinders", "Composition", "one", "many") == ElementSuccess &&
		holder->AddRelationship("Fleet", "Vehicle", "Aggregation", "many", "many") == ElementSuccess &&
		holder->AddRelationship("Driver", "Vehicle", "Realization", "one", "one") == ElementSuccess
		));

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Composition One-to-Many with Tire}, {Vehicle is Parent in relationship Composition One-to-Many with Door}, {Vehicle is Parent in relationship Composition One-to-Many with Light}, {Vehicle is Parent in relationship Composition One-to-One with Engine}, {Vehicle is Child in relationship Aggregation Many-to-Many with Fleet}, {Vehicle is Child in relationship Realization One-to-One with Driver}, }");

		REQUIRE(holder->GetUMLObject("Tire")->ReturnRelationships() == "{{Tire is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Door")->ReturnRelationships() == "{{Door is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Light")->ReturnRelationships() == "{{Light is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Child in relationship Composition One-to-One with Vehicle}, {Engine is Parent in relationship Composition One-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Composition Many-to-One with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{{Fleet is Parent in relationship Aggregation Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{{Driver is Parent in relationship Realization One-to-One with Vehicle}, }");
	}

	holder->DeleteUMLObject("Door");

	//Delete just one class, see what happens
	SECTION("Verify relationships after class deletion", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Composition One-to-Many with Tire}, {Vehicle is Parent in relationship Composition One-to-Many with Light}, {Vehicle is Parent in relationship Composition One-to-One with Engine}, {Vehicle is Child in relationship Aggregation Many-to-Many with Fleet}, {Vehicle is Child in relationship Realization One-to-One with Driver}, }");

		REQUIRE(holder->GetUMLObject("Door") == NULL);
	}

	holder->DeleteUMLObject("Vehicle");

	//tire and light should be deleted, since they are both composed children of Vehicle with no other connections
	//fleet and driver lost their only relationship (which was with vehcile)
	//engine lost 1 relationship
	//cylinder is unchanged
	SECTION("Verify relationships after class deletion", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle") == NULL);
		REQUIRE(holder->GetUMLObject("Tire") == NULL);
		REQUIRE(holder->GetUMLObject("Light") == NULL);
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Parent in relationship Composition One-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Composition Many-to-One with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{}");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{}");
	}
	
	delete holder;
}

/*
		std::ofstream out("out.txt");
		out << holder->GetUMLObject("Vehicle")->ReturnRelationships();
		out.close();
		*/

TEST_CASE("Test Saving Loading All Items", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	UMLObject* a = NULL, * b = NULL;

	REQUIRE(holder->CreateNewClass("Car") == ElementSuccess);
	a = holder->ReturnPtrToVector()[0];
	std::vector<UMLParameter> testVec;
	a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
	a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
	a->AddMethod(UMLMethod("Drive()", "void", testVec, UMLFieldVisibilityPrivate));
	a->SetXPosition(100);
	a->SetYPosition(200);

	REQUIRE(holder->CreateNewClass("Wheel") == ElementSuccess);
	b = holder->ReturnPtrToVector()[1];
	testVec.clear();
	testVec.push_back(UMLParameter("int", "Dummy param 1"));
	testVec.push_back(UMLParameter("float", "Dummy param 2", "true", "0.0f"));
	b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
	b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
	b->AddMethod(UMLMethod("Rotate()", "unsigned int", testVec, UMLFieldVisibilityPrivate));
	b->SetXPosition(300);
	b->SetYPosition(400);

	holder->EditClassTitle("Tire", "Wheel");
	holder->AddRelationship("Car", "Tire", "Composition", "one", "many");


	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "tempfile.txt", true) == SaveSuccess);
	
	UMLObjectsHolder* holder2 = new UMLObjectsHolder();

	REQUIRE(SavingLoadingIO::LoadProject(holder2, "tempfile.txt") == true);

	std::vector<UMLObject*> c, d;
	c = holder->ReturnPtrToVector();
	d = holder2->ReturnPtrToVector();

	SECTION("Verify Save Contents", "0")
	{
		REQUIRE(c.size() == d.size());
		REQUIRE(c[0]->ReturnTitle() == "Car");
		REQUIRE(c[0]->ReturnTitle() == d[0]->ReturnTitle());


		REQUIRE(c[0]->ReturnMethods() == "{{Drive(), void, {}, Private}, }");
		REQUIRE(c[0]->ReturnMethods() == d[0]->ReturnMethods());


		REQUIRE(c[0]->ReturnFields() == "{{Color, string, Public}, {Make, string, Public}, }");
		REQUIRE(c[0]->ReturnFields() == d[0]->ReturnFields());

		REQUIRE(c[0]->ReturnRelationships() == "{{Car is Parent in relationship Composition One-to-Many with Tire}, }");
		REQUIRE(c[0]->ReturnRelationships() == d[0]->ReturnRelationships());

		REQUIRE(c[0]->GetXPosition() == 100);
		REQUIRE(c[0]->GetXPosition() == d[0]->GetXPosition());

		REQUIRE(c[0]->GetYPosition() == 200);
		REQUIRE(c[0]->GetYPosition() == d[0]->GetYPosition());
	   
		REQUIRE(c[1]->ReturnTitle() == "Tire");
		REQUIRE(c[1]->ReturnTitle() == d[1]->ReturnTitle());


		REQUIRE(c[1]->ReturnMethods() == "{{Rotate(), unsigned int, {int Dummy param 1, float Dummy param 2 = 0.0f, }, Private}, }");
		REQUIRE(c[1]->ReturnMethods() == d[1]->ReturnMethods());


		REQUIRE(c[1]->ReturnFields() == "{{Manufacturer, string, Public}, {Diameter, unsigned int, Public}, }");
		REQUIRE(c[1]->ReturnFields() == d[1]->ReturnFields());
		
		REQUIRE(c[1]->ReturnRelationships() == "{{Tire is Child in relationship Composition Many-to-One with Car}, }");
		REQUIRE(c[1]->ReturnRelationships() == d[1]->ReturnRelationships());
		
		REQUIRE(c[1]->GetXPosition() == 300);
		REQUIRE(c[1]->GetXPosition() == d[1]->GetXPosition());

		REQUIRE(c[1]->GetYPosition() == 400);
		REQUIRE(c[1]->GetYPosition() == d[1]->GetYPosition());
	}

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder2, "tempfile2.txt", true) == SaveSuccess);

	std::ifstream in("tempfile.txt");

	std::string line;
	std::vector<std::string> lines1, lines2;
	while (std::getline(in, line))
	{
		lines1.push_back(line);
	}
	in.close();


	std::ifstream in2("tempfile2.txt");

	while (std::getline(in2, line))
	{
		lines2.push_back(line);
	}
	in2.close();

	SECTION("Verify Identical files", "0")
	{
		REQUIRE(lines1.size() != 0);
		REQUIRE(lines1.size() == lines2.size());
		for (size_t i = 0; i < lines1.size(); i++)
		{
			REQUIRE(lines1[i] == lines2[i]);
		}
	}

	delete holder;
	delete holder2;
}

TEST_CASE("Test Saving Overwriting", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "do_not_overwrite_me.txt", true) == SaveSuccess);

	REQUIRE(SavingLoadingIO::LoadProject(holder, "do_not_overwrite_me.txt") == true);

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "do_not_overwrite_me.txt") == SaveAlreadyExists);

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "do_not_overwrite_me.txt", true) == SaveSuccess);
	delete holder;
}

TEST_CASE("Test Invalid Loading", "0")
{

	std::string randfilename = "does_not_exist";
	srand((unsigned int)time(0));
	for (size_t i = 0; i < 10; i++)
	{
		randfilename += std::to_string(rand() % 10);
	}
	randfilename += ".txt";

	UMLObjectsHolder* holder = new UMLObjectsHolder();

	REQUIRE(SavingLoadingIO::LoadProject(holder, randfilename) == false);

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, randfilename, true) == SaveSuccess);

	REQUIRE(SavingLoadingIO::LoadProject(holder, randfilename) == true);

	delete holder;
}

TEST_CASE("Test Invalid Saving", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	//verify that file cannot be opened if it has no name
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "", false) == SaveError);

	//should still fail, even if we want to overwrite
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "", true) == SaveError);

	delete holder;
}

TEST_CASE("Test Terminal Class Functionality", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	RunREPL(holder, "help");
	RunREPL(holder, "exit");
	RunREPL(holder, "this is an outrageous command that is expected to fail");

	RunREPL(holder, "add class test_class1");
	REQUIRE(holder->Size() == 1);
	REQUIRE(holder->GetUMLObject("test_class1") != NULL);

	RunREPL(holder, "edit class test_class1 new_class_name");

	REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "new_class_name");

	RunREPL(holder, "edit class new_class_name test_class1");

    RunREPL(holder, "add class test_class2");
    RunREPL(holder, "add class test_class3");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "add class a b");
    REQUIRE(holder->Size() == 3);

    RunREPL(holder, "add class");
    REQUIRE(holder->Size() == 3);

    RunREPL(holder, "add class test_class2");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "edit class");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "edit class a b");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "edit class test_class1");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "edit class test_class4 test_classA");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

	RunREPL(holder, "load this_file_does_notexist");
	RunREPL(holder, "save /");
	RunREPL(holder, "save filename");
	RunREPL(holder, "load filename");

    RunREPL(holder, "delete class test_class4");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "delete class");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "delete class test_class1 a");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "delete class test_class2");
    REQUIRE(holder->Size() == 2);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class3");

	RunREPL(holder, "list");
	RunREPL(holder, "titles");

	delete holder;
}

TEST_CASE("Test Terminal Field Functionality", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	RunREPL(holder, "add class test_class1");

	RunREPL(holder, "add field test_class1 test_field1 int public");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, int, Public}, }");

	RunREPL(holder, "add field test_class1 test_field2 str -");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, int, Public}, {test_field2, str, Private}, }");

	RunREPL(holder, "add field test_class1 test_field3 bool protected");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, int, Public}, {test_field2, str, Private}, {test_field3, bool, Protected}, }");

	// Add to class that doesnt exist
	RunREPL(holder, "add field test_class2 test_field4 int public");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, int, Public}, {test_field2, str, Private}, {test_field3, bool, Protected}, }");

	// Add field that already exists
	RunREPL(holder, "add field test_class1 test_field2 char #");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, int, Public}, {test_field2, str, Private}, {test_field3, bool, Protected}, }");

	// mispelled command
	RunREPL(holder, "add fields test_class1 test_field2 char #");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, int, Public}, {test_field2, str, Private}, {test_field3, bool, Protected}, }");

	// Delete field
	RunREPL(holder, "delete field test_class1 test_field3");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, int, Public}, {test_field2, str, Private}, }");

	// Delete from class that doesnt exist
	RunREPL(holder, "delete field test_class2 test_field2");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, int, Public}, {test_field2, str, Private}, }");

	// Delete field that doesnt exist
	RunREPL(holder, "delete field test_class1 test_field7");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, int, Public}, {test_field2, str, Private}, }");

	// Edit field name
	RunREPL(holder, "edit field name test_class1 test_field1 test_fieldA");
	RunREPL(holder, "edit field name test_class1 test_field2 test_fieldB");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, int, Public}, {test_fieldB, str, Private}, }");

	// mispelled command should fail
	RunREPL(holder, "edit fields name test_class1 test_field2 test_fieldB");
	RunREPL(holder, "edit field names test_class1 test_field2 test_fieldB");
	RunREPL(holder, "edit field names test_classs test_field2 test_fieldB");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, int, Public}, {test_fieldB, str, Private}, }");

	// Edit field in nonexistant class
	RunREPL(holder, "edit field name test_class2 test_fieldA test_fieldC");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, int, Public}, {test_fieldB, str, Private}, }");

	// Edit field that doesnt exist
	RunREPL(holder, "edit field name test_class1 test_fieldC test_fieldD");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, int, Public}, {test_fieldB, str, Private}, }");

	// Edit field type
	RunREPL(holder, "edit field type test_class1 test_fieldA bool");
	RunREPL(holder, "edit field type test_class1 test_fieldB bool");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, bool, Public}, {test_fieldB, bool, Private}, }");

	// Edit type in nonexistant class
	RunREPL(holder, "edit field type test_class2 test_fieldA int");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, bool, Public}, {test_fieldB, bool, Private}, }");
	
	// Edit field that doesnt exist
	RunREPL(holder, "edit field type test_class1 test_fieldC str");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, bool, Public}, {test_fieldB, bool, Private}, }");

	// Edit field visibility
	RunREPL(holder, "edit field visibility test_class1 test_fieldA private");
	RunREPL(holder, "edit field visibility test_class1 test_fieldB public");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, bool, Private}, {test_fieldB, bool, Public}, }");

	RunREPL(holder, "edit field visibility test_class1 test_fieldA #");
	RunREPL(holder, "edit field visibility test_class1 test_fieldB #");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, bool, Protected}, {test_fieldB, bool, Protected}, }");

	// mispelled command
	RunREPL(holder, "edit field visiblity test_class1 test_fieldB #");
	RunREPL(holder, "edit field visibility test_class1 test_fieldB $");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, bool, Protected}, {test_fieldB, bool, Protected}, }");

	// Edit visibility in nonexistant class
	RunREPL(holder, "edit field type test_class2 test_fieldA +");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, bool, Protected}, {test_fieldB, bool, Protected}, }");
	
	// Edit field that doesnt exist
	RunREPL(holder, "edit field type test_class1 test_fieldC -");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, bool, Protected}, {test_fieldB, bool, Protected}, }");

	delete holder;
}

TEST_CASE("Test Terminal Method Functionality", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	RunREPL(holder, "add class test_class1");

	RunREPL(holder, "add method test_class1 test_method1 int public");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, int, {}, Public}, }");

	RunREPL(holder, "add method test_class1 test_method2 str -");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, int, {}, Public}, {test_method2, str, {}, Private}, }");

	RunREPL(holder, "add method test_class1 test_method3 bool protected");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, int, {}, Public}, {test_method2, str, {}, Private}, {test_method3, bool, {}, Protected}, }");

	// Add to class that doesnt exist
	RunREPL(holder, "add method test_class2 test_method4 int public");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, int, {}, Public}, {test_method2, str, {}, Private}, {test_method3, bool, {}, Protected}, }");

	// Add method that already exists
	RunREPL(holder, "add method test_class1 test_method2 char #");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, int, {}, Public}, {test_method2, str, {}, Private}, {test_method3, bool, {}, Protected}, }");

	// Delete method
	RunREPL(holder, "delete method test_class1 test_method3");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, int, {}, Public}, {test_method2, str, {}, Private}, }");

	// Delete from class that doesnt exist
	RunREPL(holder, "delete method test_class2 test_method2");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, int, {}, Public}, {test_method2, str, {}, Private}, }");

	// Delete method that doesnt exist
	RunREPL(holder, "delete method test_class1 test_method7");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, int, {}, Public}, {test_method2, str, {}, Private}, }");

	// Edit method name
	RunREPL(holder, "edit method name test_class1 test_method1 test_methodA");
	RunREPL(holder, "edit method name test_class1 test_method2 test_methodB");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, int, {}, Public}, {test_methodB, str, {}, Private}, }");

	// Edit method in nonexistant class
	RunREPL(holder, "edit method name test_class2 test_methodA test_methodC");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, int, {}, Public}, {test_methodB, str, {}, Private}, }");

	// Edit method that doesnt exist
	RunREPL(holder, "edit method name test_class1 test_methodC test_methodD");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, int, {}, Public}, {test_methodB, str, {}, Private}, }");

	// Edit method type
	RunREPL(holder, "edit method type test_class1 test_methodA bool");
	RunREPL(holder, "edit method type test_class1 test_methodB bool");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, bool, {}, Public}, {test_methodB, bool, {}, Private}, }");

	// Edit type in nonexistant class
	RunREPL(holder, "edit method type test_class2 test_methodA int");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, bool, {}, Public}, {test_methodB, bool, {}, Private}, }");
	
	// Edit method that doesnt exist
	RunREPL(holder, "edit method type test_class1 test_methodC str");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, bool, {}, Public}, {test_methodB, bool, {}, Private}, }");

	// Edit method visibility
	RunREPL(holder, "edit method visibility test_class1 test_methodA private");
	RunREPL(holder, "edit method visibility test_class1 test_methodB public");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, bool, {}, Private}, {test_methodB, bool, {}, Public}, }");

	//this one should fail
	RunREPL(holder, "edit method visibility test_class1 test_methodB privublic");
	RunREPL(holder, "edit method visiblity test_class1 test_methodB privublic");
	RunREPL(holder, "edit methods visibility test_class1 test_methodB public");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, bool, {}, Private}, {test_methodB, bool, {}, Public}, }");

	RunREPL(holder, "edit method visibility test_class1 test_methodA #");
	RunREPL(holder, "edit method visibility test_class1 test_methodB #");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, bool, {}, Protected}, {test_methodB, bool, {}, Protected}, }");

	// Edit visibility in nonexistant class
	RunREPL(holder, "edit method type test_class2 test_methodA +");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, bool, {}, Protected}, {test_methodB, bool, {}, Protected}, }");
	
	// Edit method that doesnt exist
	RunREPL(holder, "edit method type test_class1 test_methodC -");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, bool, {}, Protected}, {test_methodB, bool, {}, Protected}, }");

	delete holder;
}

TEST_CASE("Test Terminal Relationship Functionality (Deleting)", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	RunREPL(holder, "add class test_class1");
	RunREPL(holder, "add class test_class2");
	RunREPL(holder, "add class test_class3");

	//these should pass
	RunREPL(holder, "add relationship test_class1 test_class2 a 1 m");
	RunREPL(holder, "add relationship test_class2 test_class3 c many o");

	//these should fail
	RunREPL(holder, "add relationship test_class1 test_class2 a invalid_quantifier o");
	RunREPL(holder, "add relationship test_class2 test_class3 c many 12");
	RunREPL(holder, "add relationship test_class2 test_class3 m many one");

	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{{test_class1 is Parent in relationship Aggregation One-to-Many with test_class2}, }");
	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{test_class2 is Child in relationship Aggregation Many-to-One with test_class1}, {test_class2 is Parent in relationship Composition Many-to-One with test_class3}, }");
	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{test_class3 is Child in relationship Composition One-to-Many with test_class2}, }");

	RunREPL(holder, "add relationship test_class2 test_class3 g one many");

	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{{test_class1 is Parent in relationship Aggregation One-to-Many with test_class2}, }");
	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{test_class2 is Child in relationship Aggregation Many-to-One with test_class1}, {test_class2 is Parent in relationship Composition Many-to-One with test_class3}, }");
	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{test_class3 is Child in relationship Composition One-to-Many with test_class2}, }");

	RunREPL(holder, "edit relationship test_class1 test_class2 r one one");

	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{{test_class1 is Parent in relationship Realization One-to-One with test_class2}, }");
	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{test_class2 is Child in relationship Realization One-to-One with test_class1}, {test_class2 is Parent in relationship Composition Many-to-One with test_class3}, }");
	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{test_class3 is Child in relationship Composition One-to-Many with test_class2}, }");

	RunREPL(holder, "delete relationship test_class test_class2");

	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{{test_class1 is Parent in relationship Realization One-to-One with test_class2}, }");
	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{test_class2 is Child in relationship Realization One-to-One with test_class1}, {test_class2 is Parent in relationship Composition Many-to-One with test_class3}, }");
	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{test_class3 is Child in relationship Composition One-to-Many with test_class2}, }");

	RunREPL(holder, "delete relationship test_class1 test_class2");

	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{}");
	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{test_class2 is Parent in relationship Composition Many-to-One with test_class3}, }");
	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{test_class3 is Child in relationship Composition One-to-Many with test_class2}, }");

	RunREPL(holder, "edit relationship test_class1 test_class2 a 1 m");

	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{}");
	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{test_class2 is Parent in relationship Composition Many-to-One with test_class3}, }");
	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{test_class3 is Child in relationship Composition One-to-Many with test_class2}, }");

	RunREPL(holder, "delete relationship test_class2");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{}");
	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{test_class2 is Parent in relationship Composition Many-to-One with test_class3}, }");
	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{test_class3 is Child in relationship Composition One-to-Many with test_class2}, }");

	RunREPL(holder, "delete relationship");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{}");
	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{test_class2 is Parent in relationship Composition Many-to-One with test_class3}, }");
	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{test_class3 is Child in relationship Composition One-to-Many with test_class2}, }");

	//expect this to fail - mispelled
	RunREPL(holder, "edit relationships test_class1 test_class2 r one one");
	delete holder;
}