
# NAME
mm -- (makemain) Builds a quick main in C, C++, Python, or Java


# SYNOPSIS
./mm [-vhb] <fileName>.<extention> [author]




# DESCRIPTION
Makemain (mm) generates a basic 'main' file in C, C++, Python, and Java. Basically, I got tired of starting from scratch each time I wanted to do a bit of work, so I made something to give me a quick starting place.

You can set a permanent author name so when mm creates a file it will already be labled by that author and timestamped.

Various options are available to change the output including:

```
	-v, --verbose : VERBOSE : Prints information regarding file creation details.
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

At build you will be prompted for a permanent author name but this can be skipped. To add a permanent author later can be done with either a fresh `sudo make install` or by just running the script `sudo sh setup.sh`. 


Basically, the `makefile` compiles makemain and runs the `setup.sh` script that creates a wrapper script called `mm` (placed in `/usr/local/bin/` - hence the sudo). This wrapper script that is created calls makemain whenever the user wants to run mm. This level of indirection allows for setting up preferences like a permanent author name.


An optional `sudo make debug` will compile makemain for testing. makemain will not print out what is going on under the hood when creating a file in detail.



# Running

To run makemain, execute a command with the format:
```
	mm <fileName>.<extension> [author]
```

For example:
```
	mm helloworld.c
```

Or to overload the default author name:
```
	mm helloworld.c John Doe
```


# Cleanup

On OSX and Linux:
```
    cd ~/<makemain_path>/makemain
	sudo make clean
```
Removes all compiled and generated files which takes all the file states back to when it was first cloned.



#Changing Default Main Text

Inside the `/makemain/templates/` are the default formats for mains. Edit these as desired because makemain simply addes to those templates.


# Supported Languages

C, C++, Python and Java in the respective forms:

- C: `mm hello.c`
- C++: `mm hello.c++` OR `mm hello.cpp`
- PYTHON: `mm hello.py`
- JAVA: `mm hello.java`


# Update Permanent Author

A new permanent (default) author can be set by running the `setup.sh` script by itself (no need for a new `sudo make install`):
```
    cd ~/<makemain_path>/makemain
	sudo sh setup.sh
```


# Notes

makemain was written in C for practice and lower level control. Tested in Bash on Mac OS X and Ubuntu.

- [X] Remove `-a` and make it so any words after the file name are the overwritten author
- [X] Finish including verbose implimentation (-v, --verbose)
- [ ] Include support for header options? (-h, --header)
- [ ] Add templates for other languages - ONGOING
- [X] Improve setup experience - ONGOING
- [ ] Allow removal of author name and timestamp with option? (-b --basic)
- [ ] Account for errors when missing input that is expected
- [X] Improve file and author info extraction
- [X] Make the executable `mm` runable from anywhere as part of the `make install`
- [ ] Remove make clean errors when there are no files to delete
