
# Building

On OS X and Linux:

```
	git clone https://github.com/CSEmbree/makemain.git
	cd ~/<some_directory_path>/makemain
	sh setup.sh
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

Inside the `/makemain/templates/` are the default formates. Edit those as desired as makemain simply addes to those templates.


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

makemain was written in C for practice and lower level control.