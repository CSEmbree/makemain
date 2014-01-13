
# NAME
mm -- (makemain) Builds a quick main in C, C++, Python, or Java


# SYNOPSIS
./mm [-avhb] [fileName] [author]


# DESCRIPTION
makemain (mm) is a bit of code for quickly generating a basic 'main' file in C, C++, Python, and Java. Basically, I got tired of starting from scratch from a blank page to code, so I made something to give me a quick starting place.

You can also set a permanent author name so when mm creates a file it will already be labled by that author and timestamped.

Various options are available to change the output including:

```
	-a, --author  : AUTHOR  : Override the default author to another of your choice as the last argument.
	-v, --verbose : VERBOSE : UNSUPPORTED - Prints information regarding file creation details.
	-h, --header  : HEADER  : UNSUPPORTED - Create a header file with the same name by default.
	-b, --basic   : BASIC   : UNSUPPORTED - Remove the Author and Time stamp from the main.
```


# Building

On OS X and Linux:

```
	git clone https://github.com/CSEmbree/makemain.git
	cd ~/<clone_path>/makemain
	sourse setup.sh
	make install
```

Optionally, the `sourse setup.sh` can be skipped as it just sets an Envrionment Variable for the name of the default author. Skipping this step means a palceholder is put in for author names for default mains. This behavior also can be overridden by use of the `-a, --author` option when running a file. For example:

```
./mm -a hello.c steven
```

will create a plain main file in C called `hello.c` with the author name `steven`. NOTE: The option `-a` is limited to one string for now (no spaces), this will be changed later.


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

- [ ] Remove `-a` and make it so any words after the file name are the overwritten author
- [ ] Finish including verbose implimentation (-v, --verbose)
- [ ] Include support for header options? (-h, --header)
- [ ] Add templates for other languages
- [ ] Improve setup experience
- [ ] Allow removal of author name and timestamp with option? (-b --basic)
- [ ] Account for errors when missing input that is expected
- [ ] Make the executable `mm` runable from anywhere as part of the `make install`
