
# NAME
mm -- (makemain) Builds a quick main in C, C++, Python, or Java


# SYNOPSIS
./mm [-vhb] [fileName] [author]


# DESCRIPTION
makemain (mm) is a bit of code for quickly generating a basic 'main' file in C, C++, Python, and Java. Basically, I got tired of starting from scratch from a blank page to code, so I made something to give me a quick starting place.

You can also set a permanent author name so when mm creates a file it will already be labled by that author and timestamped.

Various options are available to change the output including:

```
	-v, --verbose : VERBOSE : UNSUPPORTED - Prints information regarding file creation details.
	-h, --header  : HEADER  : UNSUPPORTED - Create a header file with the same name by default.
	-b, --basic   : BASIC   : UNSUPPORTED - Remove the Author and Time stamp from the main.
```


# Building

On OS X and Linux:

```
	git clone https://github.com/CSEmbree/makemain.git
	cd ~/<clone_path>/makemain
	sudo make install
```

The user will be prompted for a permanent author name but this can be skipped. To add a permanent author later can be done with either a fresh `sudo make install` or by just running the script `sudo sh setup.sh`. 


Essentially, `makefile` compiles makemain and `setup.sh` creates a wrapper script called `mm` (placed in `/usr/local/bin/` - hence the sudo) that calls makemain whenever the user wants to run mm. This level of indirection allows us to setup preferences like a permanent author name.


An optional `sudo make debug` can be run to compile makemain and doing so allows you to see what is going on under the hood.



# Running

To run makemain, execute a command with the format:

```
	./mm <fileName>.<extension>
```

For example:
	
```
	./mm helloworld.c
```


# Cleanup

On OSX and Linux:
```
	sudo make clean
```
Removed any and all compiled and generated files taking the state back to when it was origionally cloned.



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

# Update Permanent Author

As mentioned in the Building section, a new permanent author can be set by running the `setup.sh` script by:
```
	sudo sh setup.sh
```


# Notes

makemain was written in C for practice and lower level control. Tested in Bash on Mac OS X and Ubuntu.

- [X] Remove `-a` and make it so any words after the file name are the overwritten author
- [ ] Finish including verbose implimentation (-v, --verbose)
- [ ] Include support for header options? (-h, --header)
- [ ] Add templates for other languages
- [X] Improve setup experience - ongoing
- [ ] Allow removal of author name and timestamp with option? (-b --basic)
- [ ] Account for errors when missing input that is expected
- [X] Make the executable `mm` runable from anywhere as part of the `make install`
- [ ] Remove make clean errors when there are no files to delete
