main.pdf: main.tex
	latexmk -shell-escape -synctex=1 -interaction=nonstopmode -file-line-error -pdf main.tex