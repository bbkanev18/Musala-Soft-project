<style>
	h1		{color:#CC8CE9;}
	h2		{color:#C619D3;}
	h3		{color:#D31983;}
	h4		{color:#D31983;}
	body	
	{
		background-image: url("https://cdn.discordapp.com/attachments/588054501303255273/814543243260854312/cancer.jpg");
		background-size: 100% auto;
		background-repeat: repeat-y;
		background-color: #111F59;
	}
	div
	{
		padding: 10px;
		background-color: rgba(15,0,50,0.50);

	}
	li		{color: #E0D527}
	hr		{height:2px;border-width:0;color:gray;background-color:gray}
	p		{color: #E1E3EA}
</style>

<div>

# TODO

1. [x] create the data types
	- [x] create the structures and enumerators 
	- [x] figure out how to implement arrays
2. [x] create functions to work with said data types
	- [x] create sample - make a random object
	- [x] show - print one object
	- [x] insert in vector
	- [x] enter object - let the user create the object
	- [x] show vector - print a vector
	- [ ] show vector by a criteria - print a vector
	- [ ] check inputs!
	- think of more functions
3. [ ] create i/o functions to simplify workflow
4. [ ] make ui
<br>
<br>
<br>

# Data Types

## 1.Primary data types

###	●Person Structure

```c++
struct PERSON
{
	std::wstring name = L"Homo";
	std::wstring surname = L"Sapiens";
	struct EMAIL email = WstringToEmail(L"Iamarealhuman@mars.com");
	//maybe add more fields?
	//eg: age?
};
```

<hr>


###	●Student Structure

```c++
struct STUDENT
{
	PERSON info;					//Student's Personal info
	wchar_t Class = '!';				//The class that the student is in
	enum class ROLE role = ROLE::Undefined;		//Student's role in the team
};
```

<hr>


###	●Team Structure

```c++
struct TEAM
{
	std::wstring name = L"‎Decameron";
	std::wstring description = L"Ora";				//Short summary of the team
	struct tm dateOfSetup = {};					//TimeStamp for when the team was added
	enum class STATUS status = STATUS::Undefined;			//Project's (Team's) current status
	struct STUDENT students[4] = {};				//An array of students that are a part of the team
	PERSON teacherInfo;						//Personal info for the teacher that is the team's mentor
};
```
<hr>


###	●Teacher Structure

```c++
struct TEACHER
{
	PERSON info;
	std::vector<TEAM> teams;	//Array of teams the object is in
};
```

<hr>


###	●School Structure

```c++
struct SCHOOL
{
	std::wstring name = L"PGKPI";
	std::wstring city = L"Burgas";
	std::wstring address = L"Ортото 3";
	std::vector<TEAM> teams = {};
	std::vector<TEACHER> teachers = {};
};
```

<br>
<br>
<br>

## 2.Secondary data types

### ●Role Enumerator
```c++
enum class ROLE
{
	Undefined,		//The role is not defined
	ScrumTrainer,		//Scrum Trainer
	QAEngineer,		//Q&A Engineer
	BackendDev,		//Backend developer
	FrontendDev		//Frontend developer
};
```
<hr>


### ●Email Structure

```c++
struct EMAIL
{
	std::wstring username = L"";		//First part of an email
	std::wstring domain = L"";		//Second part of an email
};
```
<hr>


### ●Project Status Enumerator

```c++
enum class STATUS
{
	Undefined,		//The status is not defined
	InUse,			//The project/team is "in use"? - My guess is that they mean active instead of "in use"
	NotActive,		//The project/team is inactive
	Archived		//The project/team has been archived/finished
};
```

<br>
<br>
<br>

# Notes? idk

I plan on using a name database to pull both students' and teachers' names from said database.

I have found a repo on github with a large and comprehensive name database. https://github.com/smashew/NameDatabases

Student structure is almost finished. I need to add input validation, and sorting functions.

Added basic colours!

tm struct has been figured out!!!

!!!PASS ALL VECTORS BY REFERENCE &

```
  ┌──────────────┤ STUDENT ├──────────────┐
  │          Rosemarie Salisbury          │
  │                Class B                │
  │              Q&A Engineer             │
  │    rosemarie_salisbury.QA@sample.io   │
  └───────────────────────────────────────┘
```
^ This is the standart Print Student Function's output.

Create a PrintInline Function???

```
| Rosemarie Salisbury | Class B | Q&A Engineer | rosemarie_salisbury.QA@sample.io |
```

A PrintInline Function would ease readability when read in mass

A PrintInLine Function was created! However... It does not Level off each row, and you get
```
| Rita Fearnley | Class D | Q&A Engineer | rita_fearnley.QA@sample.io |
| Alan Caton | Class D | Backend Developer | alan_caton.BD@sample.io |
| Willena Butt | Class A | Frontend Developer | willena_butt.FD@sample.io |
| Venus Eddy | Class D | Q&A Engineer | venus_eddy.QA@sample.io |
| Bessie Ogden | Class D | Q&A Engineer | bessie_ogden.QA@sample.io |
```
instead of
```
| Rita Fearnley | Class D | Q&A Engineer       | rita_fearnley.QA@sample.io |
| Alan Caton    | Class D | Backend Developer  | alan_caton.BD@sample.io    |
| Willena Butt  | Class A | Frontend Developer | willena_butt.FD@sample.io  |
| Venus Eddy    | Class D | Q&A Engineer       | venus_eddy.QA@sample.io    |
| Bessie Ogden  | Class D | Q&A Engineer       | bessie_ogden.QA@sample.io  |
```
Keep thinking of a better way!!!

1. [ ] Add colours to the input functions!!!
2. [ ] Create menues!!!

print school -> school - team(teacher,students)

Maybe Seperate a function to create (name,surname,email) from Teacher/Student functions

Issue with create sample teacher! - First sample has the most teams!

Try to maker addtovec
not as different functions,
but as a few functions,
that have the same name
and are overloads of eachother

EnterTeacher -

	EnterPerson
	
	Choose the teams!
		Have it get passed a vec of all teams
		and then print only those with default value for teacherInfo
		from there let the user pick out from the list of the "free" teams
	
	That's all

What to do when an invalid input has been detected:

	Notify the user of the invalid input
	Notify the user why their input was invalid
	Let the user enter the input again
	?Save a log of the wrong input?

Person input validation

<br>

I should be able to overload more functions

Add id like functionality to all PrintVector functions!!!

<br>

Add a header to all enter functions

eg: `___/====\| STUDENT |/====\___`


Make a function to print guides for inlinePrint, to make it more user friendly

<br>

#### IMPORTANT

The file doesnt read Unicode and fails if given non ASCII values eg: Хелло

FIND A FIX!!!

FIIXXXXEEED!!!!
fixed by: passing the file data thru a wstringstream and doing some locale magic.




</div>