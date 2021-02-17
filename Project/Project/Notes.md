# TODO

1. [ ] create the data types
	- [x] create the structures and enumerators 
	- [ ] figure out how to implement arrays
2. [ ] create functions to work with said data types
	- [ ] create sample - make a random object
	- [ ] show - print one object
	- [ ] insert in vector
	- [ ] enter object - let the user create the object
	- [ ] show vector - print a vector
	- check inputs!
	- think of more functions
3. [ ] create i/o functions to simplify workflow

---
---
---

# Thinking place...

idk


---
---
---

# Data Types

## 1.Primary data types

###	●Student Structure

```c++
struct STUDENT
{
	std::wstring Name;
	std::wstring surname;
	char Class;
	enum class ROLE role;
	struct EMAIL email;
};
```

---
### ●Team Structure
```c++
struct TEAM
{
	std::wstring Name;
	std::wstring Description;
	struct tm DateOfSetup;
	struct STUDENT students[4];
	enum class STATUS status = STATUS::Undefined;
};
```
---
### ●Teacher Structure
```c++
struct TEACHER
{
	std::wstring Name;
	std::wstring surname;
	//Array of teams the object is in
	struct EMAIL email;
};
```

---
### ●School Structure
```c++
struct SCHOOL
{
	std::wstring Name;
	std::wstring City;
	std::wstring Address;
	//array of Students
	//array of Teams
	//array of Teachers
};
```

---
---

## 2.Secondary data types

### ●Role Enumerator
```c++
enum class ROLE
{
	Undefined,
	ScrumTrainer,
	QAEngineer,
	BackendDev,
	FrontendDev
};
```
---
### ●Email Structure
```c++
struct EMAIL
{
wstring username
wstring domain
}
```
---
### ●Project Status Enumerator
```c++
enum class STATUS
{
	Undefined,
	InUse,
	NotActive,
	Archived
};
```
---
---
---

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