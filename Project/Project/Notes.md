# TODO

1. [ ] create the data types
	- [x] create the structures and enumerators 
	- [ ] figure out how to implement arrays
2. [ ] create functions to work with said data types
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
	std::wstring SurName;
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
	std::wstring SurName;
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
