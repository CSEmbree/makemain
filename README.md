
# Building

On OS X and Linux:

```
	git clone https://github.com/CSEmbree/makemain.git
	cd ~/<clone_path>/makemain
	sourse setup.sh
	make install
```

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

- [ ] include support for headers?
- [ ] add templates for other languages
- [ ] improve setup experience
