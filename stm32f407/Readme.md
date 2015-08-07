# Comment effectuer sa première compilation pour STM32 !


0. Modifier les variables d'environnement en fonction de son installation dans les fichiers :

        Makefile
        lib/Makefile
        lib/search.sh
        lib/win2unix_paths.sh

1. Compiler les librairies:

        cd lib/
        sudo make prepare # Nécessaire pour nettoyer les dossiers et les chemins
        make
        cd ..
NB : pas besoin de sudo si les librairies sont accessibles en écriture par l'utilisateur

2. Écrire son code dans des fichiers .c dans source/

3. Mettre les headers associés dans headers

4. Compiler les fichiers. Dans le dossier racine :
    $ make

5. Envoyer le programme sur le ucontrolleur (make flash)
    $ make flash

6 Pour débugger
    $ make debug
