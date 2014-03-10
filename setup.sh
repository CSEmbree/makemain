#!/bin/bash

#creates the wrapper script to run makemain with appropreate envrionment variables for settings

echo "#!/bin/bash" > mm
echo "" >> mm


#all the arguments passed to the wrapper script need to be passed to the executable
echo "ARGS=\"\"" >> mm 
echo "SPACE=\" \"" >> mm

#make a copy of all arguments to be passed to make main executable
echo "for arg in \"\$@\"" >> mm
echo "do" >> mm
echo "    ARGS=\$ARGS\$SPACE\$arg" >> mm
echo "done" >> mm


#check for setting an author by default every time
echo "mm:: Want to enter a permanent author name?: [Y/n]"
read ans
yesAns="Y"

if [ $ans = $yesAns ]; then
	#save author preferences into wrapper script
    echo "mm:: Please enter a permanent author name: "
    read authorName
    echo "mm:: Author name set to: '$authorName'."
    echo "export MM_PERM_AUTHOR=\"${authorName}\" " >> mm
else
	#incorrect response will be assumed as a negative answer. Report it to user for clairity.
	echo "mm:: Your answer: '$ans'."
	echo "mm:: No permanent author name option selected!"
fi

#always export the template file location path
echo "export MM_TEMP_PATH=\"$(pwd)/templates\" " >> mm

#always export the executable path location for running makemain
echo "export MM_EXEC_PATH=\"$(pwd)/bin/makemain\" " >> mm
echo "exec \${MM_EXEC_PATH} \$ARGS" >> mm


#move the wrapper script to a standard execution path to allow makemain to be run from anywhere
chmod +x mm
mv mm /usr/local/bin/mm
