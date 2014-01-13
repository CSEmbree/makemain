#!/bin/bash


echo "mm:: Please enter a permanent author name: "

read authorName

export MM_AUTHOR="${authorName}"

echo "mm:: ran: export MM_AUTHOR=\"$authorName\""
echo "mm:: Author name '$authorName' set! makemain is ready to use."
