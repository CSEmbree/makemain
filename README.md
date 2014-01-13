
# Usage
makemain (mm) is a bit of code for quickly generating a basic 'main' file in C, C++, Python, and Java. Basically, I got tired of having to start from scratch with from a blank page to code, so I created something to give me a small starting place.

This project also allows you to quickly set up a permanent author name so when it creates the file it will already be labled by as yourself and timestamped.

Various options are available to change the default experience including:

```
	-a, --author  : Override the default author to another of your choice as the last argument.
	-v, --verbose : Prints information regarding file creation details.
	-h, --header  : UNSUPPORTED - Create a header file with the same name by default.
	-b, --basic   : UNSUPPORTED - Remove the Author and Time stamp from the main.
```


# Building

On OS X and Linux:

```
	git clone https://github.com/CSEmbree/makemain.git
	cd ~/<clone_path>/makemain
	sourse setup.sh
	make install
```

Optionally, no the `sourse setup.sh` can be skipped as it just sets an Envrionment Variable for the name of the default author. Skipping this step means a palceholder is put in for author names for mains. This behavior can be overridden by use of the `-a` option when running a file. For example:

```
./mm -a hello.c steven
```

will create a basic main file in C called hello.c with the author name steven.


# Running

To run makemain, execute a command with the format:

```
	./mm <fileName>.<extension>
```

For example:
	
```
	./mm helloworld.c
```


#Changing Default Main Text

Inside the `/makemain/templates/` are the default formats for mains. Edit as desired as makemain simply addes to those templates.


# Supported Languages

C, C++, Python, Java in the respective forms:

C
```
	./mm hello.c
```

C++
```
	./mm hello.c++
	OR
	./mm hello.cpp
```

PYTHON
```
	./mm hello.py
```

JAVA
```
	./mm hello.java	
```


# Notes

makemain was written in C for practice and lower level control. Tested in Bash on Mac OS X and Ubuntu.

- [ ] Include support for header options? (-h, --header)
- [ ] Add templates for other languages
- [ ] Improve setup experience
- [ ] Allow removal of author name and timestamp with option? (-b --basic)
- [ ] Account for errors when missing input that is expected
