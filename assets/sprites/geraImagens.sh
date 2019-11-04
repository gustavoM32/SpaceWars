#!/bin/bash
f1=nave1.png
f2=nave2.png
f3=projetil1.png
# f4=projetil2.png
n1=nave1.xpm
n2=nave2.xpm
n3=projetil1.xpm
# n4=projetil2.xpm
e1=./gif/explosion.gif
e2=./exp/explosion.png
c=11.25
background=background1920x1080.jpeg
planeta=planeta.xpm
width=1280
height=720
tam=50
start=0
convert $f1 -scale $(echo $tamx$tam) $n1
convert $f2 -scale $(echo $tamx$tam) $n2
convert $f3 -scale $(echo $tamx$tam) $n3
mkdir exp
convert -background none $e1 $e2
for b in $( ls ./exp/*) 
do
	convert -background none $b -scale $(echo $tamx$tam) ${b%.*}.xpm
done
# convert $f4 -scale $(echo $tamx$tam) $n4
# convert $planeta planeta.xpm
convert $background -scale $(echo $widthx$height) background.xpm
for b in {0..31}
do
	convert -background none $f1 -scale $(echo $tamx$tam) -distort SRT $(echo "$b*$c" | bc) ${n1%.*}\ -\ $b.xpm
	convert -background none $f2 -scale $(echo $tamx$tam) -distort SRT $(echo "$b*$c" | bc) ${n2%.*}\ -\ $b.xpm
	convert -background none $f3 -scale $(echo $tamx$tam) -distort SRT $(echo "$b*$c" | bc) ${n3%.*}\ -\ $b.xpm
	# convert -background none $f4 -scale $(echo $tamx$tam) -distort SRT $(echo "$b*$c" | bc) ${n4%.*}\ -\ $b.xpm
done
