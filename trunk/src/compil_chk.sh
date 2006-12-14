echo Vérification de la syntaxe du code 3@ produit
echo fichier 3@: $1
echo construction de output.3a.c...
rm -f output.3a.c > /dev/null
cat header.3a.c >> output.3a.c
cat $1 >> output.3a.c
cat footer.3a.c >> output.3a.c
echo compilation de output.3a.c avec gcc -Wall...
gcc -Wall output.3a.c -o output
echo execution du binaire généré: ./output...
./output
echo Bye!

